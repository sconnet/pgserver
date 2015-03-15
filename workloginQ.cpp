//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 22, 2001
//
// Source File Name : workloginQ.cpp
//
// Version          : $Id: workloginQ.cpp,v 1.1 2001/04/23 01:05:46 sconnet Exp sconnet $
//
// File Overview    : Process clients on the login queue
//
// Revision History :
//
// $Log: workloginQ.cpp,v $
// Revision 1.1  2001/04/23 01:05:46  sconnet
// Initial revision
//
//
//
//*****************************************************************************

#include "pgserver.h"
#include "workloginQ.h"
#include "safeQ.h"
#include "client.h"
#include "pgconfig.h"
#include "pollclients.h"

using namespace std;

extern CSafeQ<CClient> g_loginQ;
extern CPollClients g_pollClients;
extern CPGConfig g_cfg;

//
//-------------------------------------------------------------------------
// Function       : void CWorkLoginQ::ProcessQueue(CClient& client) const
//
// Implementation : Check and process the login queue
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWorkLoginQ::ProcessQueue(CClient &client) const
{
    string method("CWorkLoginQ::ProcessQueue");
    traceBegin(method);

    if(g_loginQ >> client) {

        // login client

        // put on pollClients
        g_pollClients << client;
    }

    traceEnd(method);

} // ProcessQueue
