//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 9, 2001
//
// Source File Name : client.cpp
//
// Version          : $Id: client.cpp,v 1.2 2001/04/23 01:05:46 sconnet Exp sconnet $
//
// File Overview    : Implementation of the client connection
//
// Revision History : 
//
// $Log: client.cpp,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "client.h"
#include "utils.h"

#include <sys/socket.h>

#include <cstring>
#include <cstdlib>
#include <new>

//
//-------------------------------------------------------------------------
// Function       :  ostream& operator<<(ostream& output,
//                                       const CClient& client);
//
// Implementation : write data members to output stream
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
ostream& operator<<(ostream& output, const CClient& client)
{
  string fn("CClient operator<<");
  traceBegin(fn);
  
  output << client.m_sIpAddr << ":" << client.m_nPort;
  output << " " << client.m_sHostname;
    
  traceEnd(fn);
  return output;
  
} // operator<<

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
  string method("CClient::CClient (default)");
  traceBegin(method);
  traceEnd(method);
}

//
//-------------------------------------------------------------------------
// Function       : CClient::CClient(int fd, int port, 
//                                   const char* sIpAddr, 
//                                   const char* sHostname = NULL)
//
// Implementation : default constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CClient::CClient(int fd, int nPort, const char* sIpAddr,
                 const char* sHostname = NULL) :
  m_fd(fd),
  m_nPort(nPort),
  m_bGracefulShutdown(true),
  m_sHostname(sHostname),
  m_sIpAddr(sIpAddr)
{
  string method("CClient::CClient");
  traceBegin(method);
  
  SYSLOG(LOG_INFO, "Connect %s:%u %s", m_sIpAddr.c_str(), m_nPort,
         m_sHostname.c_str());
  
  traceEnd(method);
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
  string method("CClient::~CClient");
  traceBegin(method);
  traceEnd(method);
}


//
//-------------------------------------------------------------------------
// Function       : void CClient::disconnect() const
//
// Implementation : disconnect this client
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CClient::disconnect() const
{
  string method("CClient::disconnect");
  traceBegin(method);

  // tell the world we are dumping this stooge
  syslog(LOG_INFO, "Closing %s:%u %s", m_sIpAddr.c_str(), m_nPort,
         m_sHostname.c_str());

  if(m_bGracefulShutdown) {
    sendMessage(MSG_DISCONNECT);
    shutdown(m_fd, SHUT_RDWR);
  }

  close(m_fd);
  traceEnd(method);

} // disconnect


//
//-------------------------------------------------------------------------
// Function       : int CClient::sendMessage(int nMsg) const
//
// Implementation : Send message to client
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int CClient::sendMessage(int nMsg) const
{
  string method("CClient::sendMessage");
  traceBegin(method);

  lock();
  int nResult = Write(m_fd, &nMsg, sizeof(nMsg));
  unlock();
  
  traceEnd(method);
  return nResult;

} // sendMessage



//
//-------------------------------------------------------------------------
// Function       : int CClient::readMessage(int &nMsg) const
//
// Implementation : Read message from client
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int CClient::readMessage(int &nMsg) const
{
  string method("CClient::readMessage");
  traceBegin(method);
  
  lock();
  int nResult = read(m_fd, &nMsg, sizeof(nMsg));
  unlock();
  
  traceEnd(method);
  return nResult;
  
} // readMessage
