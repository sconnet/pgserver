//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : acceptstats.cpp
//
// Version          : $Id: acceptstats.cpp,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Implementation of stats spewer
//
// Revision History : 
//
// $Log: acceptstats.cpp,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "acceptstats.h"
#include "pgconfig.h"

extern CPGConfig g_cfg;

//
//-------------------------------------------------------------------------
// Function       : CAcceptStats::CAcceptStats()
//
// Implementation : Constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CAcceptStats::CAcceptStats()
{
  string method("CAcceptStats::CAcceptStats");
  traceBegin(method);
  displayLocalHost();
  traceEnd(method);
}

//
//-------------------------------------------------------------------------
// Function       : void CAcceptStats::start()
//
// Implementation : Perform initialization and start the listening thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptStats::start()
{
  string method("CAcceptStats::start");
  traceBegin(method);

  // do initialization here
  
  // call base class
  CListen::start(g_cfg.statsPort(),
                 g_cfg.acceptStatsThreadTimeout());
  
  traceEnd(method);
  
} // start


//
//-------------------------------------------------------------------------
// Function       : void CAcceptStats::stop(bool waitForThreadJoin = true)
//
// Implementation : Clean up and stop listening thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptStats::stop(bool waitForThreadJoin = true)
{
  string method("CAcceptStats::stop");
  traceBegin(method);

  // clean up

  // call base class
  CListen::stop(waitForThreadJoin);
  
  traceEnd(method);
  
} // stop


//
//-------------------------------------------------------------------------
// Function       : void CAcceptStats::onAccept(const CClient& client)
//
// Implementation : Spew statistics to client
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptStats::onAccept(const CClient& client)
{
  string method("CAcceptStats::onAccept");
  traceBegin(method);
  
  // tell stats object to spew data to this fd
  // maybe put them in a queue
  // then the stats object will read the queue and dump the stats
  // that way we return immediately for more accepts
  //TODO:    g_Stats.Spew(pClient->Getfd());
  // problem.. need to lock fd. fd is private
  //TODO:    g_Stats << pClient->Getfd();
  
  client.disconnect();
  
  traceEnd(method);
  
} // onAccept
