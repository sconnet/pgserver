//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : pollclients.h
//
// Version          : $Id: pollclients.h,v 1.2 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : 
//
// Revision History : 
//
// $Log: pollclients.h,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
//
//
//*****************************************************************************

#ifndef __POLLCLIENTS_H_
#define __POLLCLIENTS_H_

#include "thread.h"
#include "lock.h"
#include "client.h"

#include <map>
typedef std::map<int, CClient> ClientMap;

class CPollClients : public CThread, private CLock
{
 public:
  CPollClients();
  virtual ~CPollClients();
  
  inline void operator<<(const CClient& client) { insert(client); }
  //  inline void operator>>(const CClient& client) { erase(client); }
  
  void insert(const CClient& client);
  void erase(const CClient& client);

  int size();
  void disconnectAll();
  
  void start();
  void stop(bool waitForThreadJoin = true);
  
 private:
  void thread();
  
 private:
  ClientMap m_map;
  fd_set m_clients;
  int m_nMaxFd;
};

#endif // __POLLCLIENTS_H_
