//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : work.cpp
//
// Version          : $Id: work.cpp,v 1.2 2001/04/23 01:05:46 sconnet Exp sconnet $
//
// File Overview    : Implementation of the work thread object
//
// Revision History : 
//
// $Log: work.cpp,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "work.h"
#include "safeQ.h"
#include "client.h"
#include "pgconfig.h"
#include "pollclients.h"

#include <algorithm>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>      // for signal blocking

using namespace std;

extern CSafeQ<CClient> g_loginQ;
extern CSafeQ<CClient> g_commQ;
extern CPGConfig g_cfg;
extern CPollClients g_pollClients;

//
//-------------------------------------------------------------------------
// Function       : void CWork::start()
//
// Implementation : Perform initialization and start work thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWork::start()
{
  string method("CWork::start");
  traceBegin(method);
  
  // Perform initialization here
  
  // Call base class to start thread
  CThread::start();

  traceEnd(method);
  
} // start


//
//-------------------------------------------------------------------------
// Function       : void CWork::stop(bool waitForThreadJoin = true);
//
// Implementation : Perform clean up and stop the work thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWork::stop(bool waitForThreadJoin)
{
  string method("CWork::stop");
  traceBegin(method);

  // Call base class to stop thread
  CThread::stop(waitForThreadJoin);

  traceEnd(method);
  
} // stop

//
//-------------------------------------------------------------------------
// Function       : void CWork::disconnect(const Client& client) const
//
// Implementation : Remove client polling and disconnect them
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWork::disconnect(const CClient& client) const
{
  g_pollClients.erase(client);
  client.disconnect();

} // disconnect

//
//-------------------------------------------------------------------------
// Function       : void CWork::thread()
//
// Implementation : Check and process the client queues
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWork::thread()
{
  string method("CWork::thread");
  traceBegin(method);
  
  // TODO: maybe this should go in the base class CThread
  // block these signals, we want main to handle them
  // main is da man!
  sigset_t intmask;
  sigemptyset(&intmask);
  sigaddset(&intmask, SIGINT);
  pthread_sigmask(SIG_BLOCK, &intmask, NULL);

  CClient client;
  while(true) {
    ProcessQueue(client);

    if(waitForKillEvent(g_cfg.workIdleTime()))
      break;
  }
  
  traceEnd(method);
  
} // thread

