//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : work.cpp
//
// Version          : $Id: $
//
// File Overview    : Implementation of the work thread object
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include "pgserver.h"
#include "work.h"
#include "clientQ.h"
#include "config.h"
#include "utils.h"
#include "pollclients.h"

#include <algorithm>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>      // for signal blocking

extern CClientQ g_loginQ;
extern CClientQ g_commQ;
extern CConfig g_cfg;
extern CPollClients g_pollClients;

//
//-------------------------------------------------------------------------
// Function       : CWork::CWork()
//
// Implementation : Constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CWork::CWork()
{
}

//
//-------------------------------------------------------------------------
// Function       : CWork::~CWork()
//
// Implementation : Destructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CWork::~CWork()
{
}


//
//-------------------------------------------------------------------------
// Function       : void CWork::Start()
//
// Implementation : Perform initialization and start work thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWork::Start()
{
    // Perform initialization here

    // Call base class to start thread
    CThread::Start();

} // Start


//
//-------------------------------------------------------------------------
// Function       : void CWork::Stop()
//
// Implementation : Perform clean up and stop the work thread
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWork::Stop()
{
    // Clean up

    // Call base class to stop thread
    CThread::Stop();

} // Stop

//
//-------------------------------------------------------------------------
// Function       : void CWork::Thread()
//
// Implementation : Checks for clients on the login queue and for clients 
//                  ready to communication on the commQ
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWork::Thread()
{
    // TODO: maybe this should go in the base class CThread
    // block these signals, we want main to handle them
    // main is da man!
    sigset_t intmask;
    sigemptyset(&intmask);
    sigaddset(&intmask, SIGINT);
    pthread_sigmask(SIG_BLOCK, &intmask, NULL);

    CClient* pClient = NULL;
    int nTimeout = g_cfg(WORK_IDLE_STR, WORK_IDLE);

    // keep going forever until we see a kill event
    while(true)
    {
        // idle
        if(WaitForKillEvent(nTimeout))
            break;

        // Check for clients in the loginQ
        if(g_loginQ >> pClient)
        {
          //            cerr << "Client in login q ... putting in pollClients" << endl;
            // login client
            // put on pollClients
            g_pollClients << pClient;
        }

        // Check for clients in the commQ
        if(g_commQ >> pClient)
        {
          //            cerr << "Msg from client <-- " << endl;
            int nMsg = 0;
            int nRes;

            // TODO: this line looks too complicated, simplify it
            if((nRes = (*pClient >> nMsg)) > 0)
            {
              //    cerr << "Msg from client -->  " << nMsg << endl;

                // search, identify, chat, disconnect, etc.
                switch(nMsg)
                {
                    case MSG_DISCONNECT:
                        break;
                    case MSG_SEARCHRESULT:
                        break;
                    case MSG_USERID:
                        break;
                }
                
                // insert client back in pollClients
                g_pollClients << pClient;
            }
            else
            {
               // disconnect client
              //               syslog(LOG_WARNING, "Error reading client %s:%d, disconnecting", 
              //                      pClient->GetIpAddr(), pClient->GetPort());

               g_pollClients >> pClient; // erase
               delete pClient;
            }                
        }

    } // end while loop

} // Thread

