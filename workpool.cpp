//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : workpool.cpp
//
// Version          : $Id: workpool.cpp,v 1.2 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Implementation of the work pool
//
// Revision History : 
//
// $Log: workpool.cpp,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "workpool.h"
#include "pgconfig.h"
#include "workloginQ.h"
#include "workcommQ.h"

#include <unistd.h>

extern CPGConfig g_cfg;


//
//-------------------------------------------------------------------------
// Function       : void CWorkPool::start()
//
// Implementation : Spawns all the requested work threads
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWorkPool::start()
{
  string method("CWorkPool::start");
  traceBegin(method);
  
  CWork* pWork = NULL;
  // Start with user specified number of login Q threads
  for(int n = 0; n < g_cfg.loginQThreads(); n++) {
    pWork = new(nothrow)CWorkLoginQ();
    hire(pWork);
  }

  // Start with user specified number of comm Q threads
  for(int n = 0; n < g_cfg.commQThreads(); n++) {
    pWork = new(nothrow)CWorkCommQ();
    hire(pWork);
  }

  traceEnd(method);
  
} // start

//
//-------------------------------------------------------------------------
// Function       : void CWorkPool::stop()
//
// Implementation : Tells each worker thread object on the queue to
//                  stop working
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWorkPool::stop()
{
  string method("CWorkPool::stop");
  traceBegin(method);
  
  // Stop all workers
  CWork* pWork = NULL;
  while(!m_queue.empty()) {
    pWork = m_queue.front();
    m_queue.pop();
    
    if(pWork) {
      pWork->stop(false);
      delete pWork;
    }
  }

  traceEnd(method);
  
} // stop

//
//-------------------------------------------------------------------------
// Function       : void CWorkPool::hire()
//
// Implementation : Instantiates a new work thread object and tells
//                  it to start working. It then puts it on a queue
//                  so we can get to it later to tell it to stop working
//                  
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWorkPool::hire(CWork* pWork)
{
  string method("CWorkPool::hire");
  traceBegin(method);
  
  if(pWork) {
    pWork->start();
    m_queue.push(pWork);
  }
  else
    SYSLOG(LOG_WARNING, "failed to alloc mem for new CWork in %s",
           method.c_str());
  
  traceEnd(method);
  
} // hire



