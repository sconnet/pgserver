//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 22, 2001
//
// Source File Name : workloginQ.cpp
//
// Version          : $Id: $
//
// File Overview    : Process clients on the login queue
//
// Revision History : 
//
// $Log: $
//
//
//*****************************************************************************

#include "pgserver.h"
#include "workloginQ.h"
#include "safeQ.h"
#include "client.h"
#include "pgconfig.h"
#include "pollclients.h"

extern CSafeQ<CClient> g_loginQ;
extern CPollClients g_pollClients;
extern CPGConfig g_cfg;

void CWorkLoginQ::ProcessQueue()
{
  string method("CWorkLoginQ::ProcessQueue");
  traceBegin(method);
  
  CClient client;
  if(g_loginQ >> client) {

    // login client

    // put on pollClients
    DEBUG(method, "\t\tg_pollClients << client\n");
    g_pollClients << client;
  }

  traceEnd(method);
  
} // ProcessQueue
