//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 22, 2001
//
// Source File Name : workcommQ.cpp
//
// Version          : $Id: workcommQ.cpp,v 1.1 2001/04/23 01:05:46 sconnet Exp sconnet $
//
// File Overview    : Process clients on the comm queue
//
// Revision History :
//
// $Log: workcommQ.cpp,v $
// Revision 1.1  2001/04/23 01:05:46  sconnet
// Initial revision
//
//
//
//*****************************************************************************

#include "pgserver.h"
#include "workcommQ.h"
#include "safeQ.h"
#include "client.h"
#include "pgconfig.h"
#include "pollclients.h"

using namespace std;

extern CSafeQ<CClient> g_commQ;
extern CPollClients g_pollClients;
extern CPGConfig g_cfg;

//
//-------------------------------------------------------------------------
// Function       : void CWorkCommQ::ProcessQueue(CClient& client) const
//
// Implementation : Check and process the comm queue
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWorkCommQ::ProcessQueue(CClient &client) const
{
    string method("CWorkCommQ::ProcessQueue");
    traceBegin(method);

    if(g_commQ >> client) {
        int nMsg = -1;
        int nRes;
        bool bGibberish = false;

        if((nRes = (client >> nMsg)) > 0) {
            DEBUG(method, "client msg: %d\n", nMsg);

            // search, identify, chat, disconnect, etc.

            switch(nMsg) {
                case MSG_DISCONNECT:
                    cout << "MSG_DISCONNECT" << endl;
                    break;
                case MSG_SEARCHRESULT:
                    cout << "MSG_SEARCHRESULT" << endl;
                    break;
                case MSG_USERID:
                    cout << "MSG_USERID" << endl;
                    break;
                default:
                    SYSLOG(LOG_WARNING, "Client sending gibberish=%d %s:%d, disconnecting",
                           nMsg, client.getIpAddr().c_str(), client.getPort());
                    disconnect(client);
                    bGibberish = true;
                    break;
            }

            // insert client back in pollClients if they seem to make sense
            if(!bGibberish) {
                g_pollClients << client;
            }
        }
        else if(nRes == 0) {
            SYSLOG(LOG_INFO, "Client disconnected %s:%d",
                   client.getIpAddr().c_str(), client.getPort());
            disconnect(client);
        }
        else {
            SYSLOG(LOG_WARNING, "Error reading client %s:%d, disconnecting",
                   client.getIpAddr().c_str(), client.getPort());
            disconnect(client);
        }
    }

    traceEnd(method);

} // ProcessQueue
