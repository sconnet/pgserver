//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : acceptclient.h
//
// Version          : $Id: $
//
// File Overview    : Implementation of handling newly accepted clients
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include "pgserver.h"
#include "acceptclient.h"
#include "connectcount.h"
#include "clientQ.h"
#include "config.h"

extern CConnectCount g_connectCount;
extern CClientQ g_loginQ;
extern CConfig g_cfg;


//
//-------------------------------------------------------------------------
// Function       : CAcceptClient::CAcceptClient()
//
// Implementation : Constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CAcceptClient::CAcceptClient()
{
}


//
//-------------------------------------------------------------------------
// Function       : CAcceptClient::~CAcceptClient()
//
// Implementation : Destructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CAcceptClient::~CAcceptClient()
{
}

//
//-------------------------------------------------------------------------
// Function       : void CAcceptClient::Start()
//
// Implementation : Initialize and start the listening thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptClient::Start()
{
    // perform initialization here

    // call base class
    CListen::Start(g_cfg(CLIENTPORT_STR, CLIENTPORT), 
                   g_cfg(ACCEPTCLIENT_THREAD_TIMEOUT_STR, 
                         ACCEPTCLIENT_THREAD_TIMEOUT));

} // Start


//
//-------------------------------------------------------------------------
// Function       : void CAcceptClient::Stop()
//
// Implementation : Clean up and stop the listening thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptClient::Stop()
{
    // clean up here

    // call base class
    CListen::Stop();

} // Stop


//
//-------------------------------------------------------------------------
// Function       : void CAcceptClient::OnAccept(CClient* pClient)
//
// Implementation : Called by the base class when a new connection
//                  has been accepted
//
//                  Check to see if the connectCount object will
//                  allow anymore connections from this ip address
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptClient::OnAccept(CClient* pClient)
{
    // increment connection count for this ip
    if(g_connectCount += pClient->GetIpAddr())
        g_loginQ << pClient;
    else        
    {
        syslog(LOG_INFO, "%s has too many connections", pClient->GetIpAddr());

        // fuck 'em, they be bad people
        delete pClient;
    }

} // OnAccept
