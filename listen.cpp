//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : listen.cpp
//
// Version          : $Id: listen.cpp,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Implementation of the listen object
//
// Revision History : 
//
// $Log: listen.cpp,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "listen.h"
#include "pgconfig.h"

#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>      // gethostbyname
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_ntoa
#include <sys/socket.h> // AF_INET
#include <fcntl.h>      // fcntl
#include <signal.h>     // raise and for signal blocking
#include <string.h>     // FD_SET (bzero)

extern CPGConfig g_cfg;


//
//-------------------------------------------------------------------------
// Function       : void CListen::start(int nPort, int nTimeout = 1000)
//
// Implementation : Starts the listening object. Creates the socket,
//                  binds to the port, and starts listening for 
//                  connections. It then starts a thread which
//                  accepts incoming connections.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CListen::start(int nPort, int nTimeout = 1000 /* ms */)
{
  string method("CListen::start");
  traceBegin(method);
  
  m_nTimeout = nTimeout;
  struct sockaddr_in server;
  
  // create out listening socket
  if((m_listenfd = socket(AF_INET, SOCK_STREAM, 0)) != -1) {
    // allow rebinding of this socket
    long l = 1;
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &l, sizeof(l));
    
    // bind to port and listen for connections
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons((short)nPort);
    if((bind(m_listenfd, (struct sockaddr*)&server, sizeof(server)) != -1) && 
       (listen(m_listenfd, SOMAXCONN) != -1)) {
      // Set to non blocking
      int fd_flags = fcntl(m_listenfd, F_GETFL, 0);
      if(fd_flags != -1) 
        fcntl(m_listenfd, F_SETFL, fd_flags | O_NONBLOCK);
      
      SYSLOG(LOG_INFO, "Listening on port %u", nPort);
    }
    else {
      SYSLOG(LOG_ERR, "Bind/listen failed, terminating.");
      raise(SIGINT);
    }
  }
  else {
    SYSLOG(LOG_ERR, "Create socket failed, terminating.");
    raise(SIGINT);
  }
  
  // call base class
  CThread::start();
  
  traceEnd(method);
  
} // start

//
//-------------------------------------------------------------------------
// Function       : void CListen::displayLocalHost()
//
// Implementation : Displays the local hostname and IP address for
//                  NIC 0 (usually called eth0).
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CListen::displayLocalHost()
{
  string method("CListen::displayLocalHost");
  traceBegin(method);
  
  // get local host name and ip address
  char szBuf[256];
  gethostname(szBuf, 255);
  struct hostent* pHostEnt = gethostbyname(szBuf);
  struct sockaddr_in IP;
  memcpy(&IP.sin_addr.s_addr, pHostEnt->h_addr_list[0], pHostEnt->h_length);    // adapter 0
  SYSLOG(LOG_INFO, "Localhost: %s (%s)", pHostEnt->h_name, inet_ntoa(IP.sin_addr));
  
  traceEnd(method);
  
} // displayLocalHost

//
//-------------------------------------------------------------------------
// Function       : void CListen::thread()
//
// Implementation : Thread which accepts incoming connections and tells
//                  the subclasses to handle the new connection. 
//                  Idling occurs in the select function for this 
//                  thread, not the WaitForKillEvent function.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CListen::thread()
{
  string method("CListen::thread");
  traceBegin(method);
  
  struct timeval timeout;
  
  // block these signals, we want main to handle them
  // main is da man!
  sigset_t intmask;
  sigemptyset(&intmask);
  sigaddset(&intmask, SIGINT);
  pthread_sigmask(SIG_BLOCK, &intmask, NULL);
  
  // setup socket set
  fd_set readset;
  FD_ZERO(&readset);
  
  struct hostent* pHost = NULL;
  
  // keep listening and accepting until told to die
  while(true) {

    // if kill event is set then exit
    if(waitForKillEvent())
      break;
    
    // Wait x second(s) for a connection
    timeout.tv_sec = m_nTimeout / 1000; // convert from ms to seconds
    timeout.tv_usec = 0;
    FD_SET(m_listenfd, &readset);
    if(select(m_listenfd + 1, &readset, NULL, NULL, &timeout) != -1) {
      // accept here
      if(FD_ISSET(m_listenfd, &readset)) {
        FD_CLR(m_listenfd, &readset);
        
        struct sockaddr_in acceptSock;
        socklen_t len = sizeof(acceptSock);
        int client_fd = accept(m_listenfd, (struct sockaddr*)&acceptSock, &len);
        if(client_fd != -1) {
          // Set to blocking
          // int fd_flags = fcntl(m_listenfd, F_GETFL, 0);
          // if(fd_flags != -1) 
          //   fcntl(m_listenfd, F_SETFL, fd_flags & ~O_NONBLOCK);

          // Set to non blocking
          int fd_flags = fcntl(client_fd, F_GETFL, 0);
          if(fd_flags != -1) 
            fcntl(client_fd, F_SETFL, fd_flags | O_NONBLOCK);
          
          // get client's hostname
          pHost = NULL;
          if(g_cfg.logClientName())
            pHost = gethostbyaddr((char*)&acceptSock.sin_addr, 4, AF_INET);
          
          // create new connection (optional: gethostname too)
          onAccept(CClient(client_fd, 
                           ntohs(acceptSock.sin_port),
                           inet_ntoa(acceptSock.sin_addr),
                           pHost != NULL ? pHost->h_name : NULL));
        }
        else {
          // DEBUG: test
          // what do we do now?
          SYSLOG(LOG_WARNING, "accept failed");
          FD_ZERO(&readset);
        }
      }
    }
    else {
      SYSLOG(LOG_ERR, "select failed, terminating");
      raise(SIGINT);
      break;
    }
    
  } // end while loop
  
  shutdown(m_listenfd, SHUT_RDWR);
  close(m_listenfd);
  
  traceEnd(method);
  
} // thread

