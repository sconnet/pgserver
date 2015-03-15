//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : acceptclient.h
//
// Version          : $Id: acceptclient.cpp,v 1.2 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Implementation of handling newly accepted clients
//
// Revision History :
//
// $Log: acceptclient.cpp,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "acceptclient.h"
#include "connectcount.h"
#include "safeQ.h"
#include "client.h"
#include "pgconfig.h"

using namespace std;

extern CConnectCount g_connectCount;
extern CSafeQ<CClient> g_loginQ;
extern CPGConfig g_cfg;


//
//-------------------------------------------------------------------------
// Function       : void CAcceptClient::start()
//
// Implementation : Initialize and start the listening thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptClient::start()
{
    string method("CAcceptClient::start");
    traceBegin(method);

    // perform initialization here

    // call base class
    init(g_cfg.clientPort(),
         g_cfg.acceptClientThreadTimeout());
    CListen::start();

    traceEnd(method);

} // start


//
//-------------------------------------------------------------------------
// Function       : void CAcceptClient::stop(bool waitForThreadJoin = true)
//
// Implementation : Clean up and stop the listening thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CAcceptClient::stop(bool waitForThreadJoin)
{
    string method("CAcceptClient::stop");
    traceBegin(method);

    // clean up here

    // call base class
    CListen::stop(waitForThreadJoin);

    traceEnd(method);

} // stop


//
//-------------------------------------------------------------------------
// Function       : void CAcceptClient::onAccept(CClient* pClient)
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
void CAcceptClient::onAccept(const CClient &client)
{
    string method("CAcceptClient::onAccept");
    traceBegin(method);

    // increment connection count for this ip
    if(g_connectCount += client.getIpAddr()) {
        g_loginQ << client;
    }
    else {
        SYSLOG(LOG_INFO, "%s has too many connections", client.getIpAddr().c_str());

        // fuck 'em, they be bad people
        client.disconnect();
    }

    traceEnd(method);

} // onAccept
