//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 9, 2001
//
// Source File Name : client.h
//
// Version          : $Id: client.h,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Non-concurrent client connection
//                    This object *is* the client connection and is 
//                    smart enough to know how to send pings, disconnection
//                    notices, search results, etc, etc. 
//                    Every send is surrounded by a mutex lock so sending
//                    to this client from different threads is safe
//
// Revision History : 
//
// $Log: client.h,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <iostream>
#include <string>

#include "lock.h"

class CClient : private CLock
{
  friend class CPollClients;

 public:
  CClient();
  CClient(int fd, int nPort, const char* sIpAddr,
          const char* sHostname = NULL);
  virtual ~CClient();
  
  void disconnect() const;
  inline int operator<<(int nMsg) { return sendMessage(nMsg); }
  inline int operator>>(int& nMsg) { return readMessage(nMsg); }
  friend ostream& operator<<(ostream& output, const CClient& client);
  
  // access methods
  inline int getFD() const { return m_fd; }
  inline int getPort() const { return m_nPort; }
  inline const string& getHostname() const { return m_sHostname; }
  inline const string& getIpAddr() const { return m_sIpAddr; }
  
  inline void setGracefulShutdown(bool bGracefulShutdown = true)
    { m_bGracefulShutdown = bGracefulShutdown; }
  
  // TODO:
  //    int SendSearchResult(...);
  //    int SendUserId(...);
  
 private:
  int sendMessage(int nMsg) const;
  int readMessage(int& nMsg) const;
  
 private:
  int m_fd;
  int m_nPort;
  bool m_bGracefulShutdown;
  string m_sHostname;
  string m_sIpAddr;
  //  char m_sHostname[256];
  //  char m_sIpAddr[16];
};

#endif // __CLIENT_H_


/* 
   IRON MAIDEN:
   ... the doors shut slowly, so that the very sharp points penetrated his arms, 
   and his legs in several places, and his belly and chest, and his bladder and 
   the root of his member, and his eyes, and his shoulders, and his buttocks, 
   but not enough to kill him; and so he remained making great cry and lament 
   for two days, after which he died.
*/
