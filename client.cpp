//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 9, 2001
//
// Source File Name : client.cpp
//
// Version          : $Id: $
//
// File Overview    : Implementation of the client connection
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include "pgserver.h"
#include "client.h"
#include "utils.h"

#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>

//
//-------------------------------------------------------------------------
// Function       : CClient::CClient()
//
// Implementation : default constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CClient::CClient() :
  m_fd(-1),
  m_nPort(-1),
  m_bGracefulShutdown(true)
{
    strcpy(m_sIpAddr, "");
    strcpy(m_sHostname, "");

    pthread_mutex_init(&m_lock, NULL);
}

//
//-------------------------------------------------------------------------
// Function       : CClient::CClient(int fd, int port, 
//                                           char* sIpAddr, 
//                                           char* sHostname = NULL)
//
// Implementation : default constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CClient::CClient(int fd, int nPort, char* sIpAddr, char* sHostname = NULL) :
  m_fd(fd),
  m_nPort(nPort),
  m_bGracefulShutdown(true)
{
    strcpy(m_sIpAddr, sIpAddr);
    strcpy(m_sHostname, sHostname != NULL ? sHostname : "");

    pthread_mutex_init(&m_lock, NULL);

    // tell the world we have a new connection
    //    syslog(LOG_INFO, "Connect %s:%u %s", m_sIpAddr, m_nPort, m_sHostname);
}


//
//-------------------------------------------------------------------------
// Function       : CClient::~CClient()
//
// Implementation : destructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CClient::~CClient()
{
    // tell the world we are dumping this stooge
  //    syslog(LOG_INFO, "Closing %s:%u %s", m_sIpAddr, m_nPort, m_sHostname);

    if(m_bGracefulShutdown)
    {
        SendMessage(MSG_DISCONNECT);
        shutdown(m_fd, SHUT_RDWR);
    }

    close(m_fd);
    pthread_mutex_destroy(&m_lock);
}


//
//-------------------------------------------------------------------------
// Function       : void CClient::Init(int fd, int port, char* sIpAddr, 
//                                     char* sHostname = NULL)
//
// Implementation : Init if default constructor is used
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CClient::Init(int fd, int nPort, char* sIpAddr, char* sHostname = NULL)
{
    // prevent someone from changing info from an already connected client
    if(m_fd == -1)
    {
        m_fd = fd;
        m_nPort = nPort;
        strcpy(m_sIpAddr, sIpAddr);
        strcpy(m_sHostname, sHostname != NULL ? sHostname : "");
    }

} // Init


//
//-------------------------------------------------------------------------
// Function       : int CClient::SendMessage(int nMsg)
//
// Implementation : Send message to client
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int CClient::SendMessage(int nMsg)
{
    pthread_mutex_lock(&m_lock);
    int nResult = Write(m_fd, &nMsg, sizeof(nMsg));
    pthread_mutex_unlock(&m_lock);

    return nResult;

} // SendMessage

int CClient::ReadMessage(int &nMsg)
{
    char sTemp[256] = { 0 };
    pthread_mutex_lock(&m_lock);
//    int nResult = Read(m_fd, &nMsg, sizeof(nMsg));
    //    cerr << "CClient::ReadMessage <--" << endl;
    int nResult = Read(m_fd, sTemp, sizeof(nMsg));
    //    cerr << "CClient::ReadMessage -->" << endl;
    pthread_mutex_unlock(&m_lock);
    nMsg = atoi(sTemp);
    return nResult;

} // ReadMessage
