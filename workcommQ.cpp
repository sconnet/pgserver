//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 22, 2001
//
// Source File Name : workcommQ.cpp
//
// Version          : $Id: $
//
// File Overview    : Process clients on the comm queue
//
// Revision History : 
//
// $Log: $
//
//
//*****************************************************************************

#include "pgserver.h"
#include "workcommQ.h"
#include "safeQ.h"
#include "client.h"
#include "pgconfig.h"
#include "pollclients.h"

extern CSafeQ<CClient> g_commQ;
extern CPollClients g_pollClients;
extern CPGConfig g_cfg;

void CWorkCommQ::ProcessQueue()
{
  string method("CWorkCommQ::ProcessQueue");
  traceBegin(method);
  
  CClient client;
  if(g_commQ >> client) {
    DEBUG(method, "Msg from client <--");
    int nMsg = 0;
    int nRes;
      
    // TODO: this line looks too complicated, simplify it
    if((nRes = (client >> nMsg)) > 0) {

      DEBUG(method, "Msg from client --> %d\n", nMsg);
      // search, identify, chat, disconnect, etc.
      switch(nMsg) {
      case MSG_DISCONNECT:
        break;
      case MSG_SEARCHRESULT:
        break;
      case MSG_USERID:
        break;
      }
      
      // insert client back in pollClients
      g_pollClients << client;
    }
    else {

      // disconnect client
      SYSLOG(LOG_WARNING, "Error reading client %s:%d, disconnecting", 
             client.getIpAddr().c_str(), client.getPort());
      
      g_pollClients.erase(client);
      client.disconnect();
    }                
  }
  
  traceEnd(method);
  
} // ProcessQueue
