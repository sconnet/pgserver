//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : pollclients.cpp
//
// Version          : $Id: $
//
// File Overview    : 
//
// Revision History : 
//
// $Log: $
//
//
//*****************************************************************************

#include "pgserver.h"
#include "pollclients.h"
#include "safeQ.h"
#include "client.h"

#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

extern CSafeQ<CClient> g_commQ;
extern CPollClients g_PollClients;

CPollClients::CPollClients() :
  m_nMaxFd(0)
{
  string method("CPollClients::CPollClients");
  traceBegin(method);  
  FD_ZERO(&m_clients);
  traceEnd(method);
}

CPollClients::~CPollClients()
{
  string method("CPollClients::~CPollClients");
  traceBegin(method);  
  FD_ZERO(&m_clients);
  m_map.clear();
  traceEnd(method);
}

void CPollClients::start()
{
  string method("CPollClients::start");
  traceBegin(method);
  CThread::start();
  traceEnd(method);
    
} // start

void CPollClients::stop(bool waitForThreadJoin = true)
{
  string method("CPollClients::stop");
  traceBegin(method);

  g_commQ.trigger();
  CThread::stop(waitForThreadJoin);

  traceEnd(method);
  
} // stop

int CPollClients::size()
{
  string method("CPollClients::size");
  traceBegin(method);
  
  lock();
  int nSize = m_map.size();
  unlock();

  traceEnd(method);
  return nSize;

} // size

void CPollClients::insert(const CClient& client)
{
  string method("CPollClients::insert");
  traceBegin(method);
  
  lock();
  m_map[client.m_fd] = client;
  unlock();
  
  FD_SET(client.m_fd, &m_clients);

  // TODO: this may not work if the fd's roll back to a lower number
  if(m_nMaxFd <= client.m_fd)
    m_nMaxFd = client.m_fd;
  
  traceEnd(method);
  
} // insert

void CPollClients::erase(const CClient& client)
{
  string method("CPollClients::erase");
  traceBegin(method);
  
  lock();
  m_map.erase(client.m_fd);
  unlock();
  FD_CLR(client.m_fd, &m_clients);

  traceEnd(method);
  
} // erase

void CPollClients::disconnectAll()
{
  string method("CPollClients::disconnectAll");
  traceBegin(method);
  
  lock();
  ClientMap::iterator p = m_map.begin();
  while(p != m_map.end())
    ((p++)->second).disconnect();
  unlock();
  
  traceEnd(method);

} // disconnectAll

void CPollClients::thread()
{
  string method("CPollClients::thread");
  traceBegin(method);
  
  // block these signals, we want main to handle them
  // main is da man!
  sigset_t intmask;
  sigemptyset(&intmask);
  sigaddset(&intmask, SIGINT);
  pthread_sigmask(SIG_BLOCK, &intmask, NULL);

  const int secs = 0;
  const int usecs = 250000; // 250ms

  struct timeval timeout;
  timeout.tv_sec = secs;
  timeout.tv_usec = usecs;
  
  // check for readable clients
  int fd_max = m_nMaxFd;
  fd_set read_set;
  memcpy(&read_set, &m_clients, sizeof(fd_set));
  int nResult = select(fd_max + 1, &read_set, NULL, NULL, &timeout);
  while(nResult != -1) {

    // check for kill event
    if(waitForKillEvent())
      break;
    
    if(nResult > 0) {
      
      // find out which file descriptors are set
      lock();
      ClientMap::iterator p = m_map.begin();
      while(p != m_map.end()) {
        if(FD_ISSET(p->second.m_fd, &read_set)) {
                    
          // remove fd from master fd_set
          FD_CLR(p->second.m_fd, &m_clients);

          // insert client in queue to be read
          g_commQ << p->second;
        }
        
        // check next fd
        p++;
      }
      unlock();
    }
    
    timeout.tv_sec = secs;
    timeout.tv_usec = usecs;
    fd_max = m_nMaxFd;
    memcpy(&read_set, &m_clients, sizeof(fd_set));
    nResult = select(fd_max + 1, &read_set, NULL, NULL, &timeout);
  }
  
  traceEnd(method);

} // thread

