//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : acceptstats.cpp
//
// Version          : $Id: $
//
// File Overview    : Implementation of stats spewer
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include "pgserver.h"
#include "acceptstats.h"
#include "config.h"

extern CConfig g_cfg;

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
    DisplayLocalHost();
}

//
//-------------------------------------------------------------------------
// Function       : CAcceptStats::~CAcceptStats()
//
// Implementation : Destructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CAcceptStats::~CAcceptStats()
{
}


//
//-------------------------------------------------------------------------
// Function       : void CAcceptStats::Start()
//
// Implementation : Perform initialization and start the listening thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptStats::Start()
{
    // do initialization here

    // call base class
    CListen::Start(g_cfg(STATPORT_STR, STATPORT), 
                   g_cfg(ACCEPTSTATS_THREAD_TIMEOUT_STR, ACCEPTSTATS_THREAD_TIMEOUT));

} // Start


//
//-------------------------------------------------------------------------
// Function       : void CAcceptStats::Stop()
//
// Implementation : Clean up and stop listening thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptStats::Stop()
{
    // clean up

    // call base class
    CListen::Stop();

} // Stop


//
//-------------------------------------------------------------------------
// Function       : void CAcceptStats::OnAccept(CClient* pClient)
//
// Implementation : Spew statistics to client
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptStats::OnAccept(CClient* pClient)
{
    // tell stats object to spew data to this fd
//TODO:    g_Stats.Spew(pClient->Getfd());
// problem.. need to lock fd. fd is private
//TODO:    g_Stats << pClient->Getfd();

  //    cerr << "dumping stats to client..." << endl;
    delete pClient;

} // OnAccept
