//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : pgserver.cpp
//
// Version          : $Id: pgserver.cpp,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : main launch point of the Peer Gear server
//
// Revision History : 
//
// $Log: pgserver.cpp,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "pgconfig.h"
#include "acceptstats.h"
#include "acceptclient.h"
#include "connectcount.h"
#include "safeQ.h"
#include "client.h"
#include "workpool.h"
#include "pollclients.h"

#include <sys/types.h>
#include <sys/stat.h>

// global variables
volatile sig_atomic_t g_bQuit = false;
string g_sConfigfile("/etc/pgserver.conf");

CPGConfig g_cfg;
CConnectCount g_connectCount;
CSafeQ<CClient> g_loginQ;
CSafeQ<CClient> g_commQ;
CPollClients g_pollClients;

// function prototypes
void SignalHandler(int signum);
void ReadConfigurationFile();
int daemon_init(void);

//
//-------------------------------------------------------------------------
// Function       : int main(int argc, char* argv[])
//
// Implementation : If you don't know what this is then you
//                  need to stop looking at this. Stop! STOP NOW I SAY!
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int main(int argc, char* argv[])
{
  string fn("main");
  traceBegin(fn);
  
  // become a daemon
#ifndef _DEBUG
  if(daemon_init() < 0) {
    cerr << "Could not initialize as a daemon process." << endl;
    exit(1);
  }
#endif
  
  // setup signals to catch
  signal(SIGTERM, SignalHandler);
  signal(SIGINT, SignalHandler);
  signal(SIGHUP, SignalHandler);
  signal(SIGUSR1, SignalHandler);
  signal(SIGUSR2, SignalHandler);
  
  // signals to ignore
  signal(SIGPIPE, SIG_IGN);     // handle pipe err's in socket comm.
  
  // Tell the syslog we are alive
  SYSLOG(LOG_INFO, "Peer Gear Server v0.01 starting up!");
  ReadConfigurationFile();
  
#ifdef _DEBUG
  cout << g_cfg;
#endif
  
  // Start listening for incoming connections on the stats port
  CAcceptStats acceptStats;
  acceptStats.start();
  
  // Start listening for incoming connections on the clients port
  CAcceptClient acceptClient;
  acceptClient.start();
  
  // Create thread pool of worker objects to do all the work
  CWorkPool workPool;
  workPool.start();
  g_pollClients.start();
  
  // block nothing, sleep until signaled to quit
  sigset_t emptyset;
  sigemptyset(&emptyset);
  sigprocmask(SIG_SETMASK, &emptyset, NULL);
  while(!g_bQuit)
    sigsuspend(&emptyset);
  
  // inform the world we are stopping
  SYSLOG(LOG_INFO, "Shutting down...");
  DEBUG(fn, "  acceptStats.stop();\n");
  acceptStats.stop();
  DEBUG(fn, "  acceptClient.stop();\n");
  acceptClient.stop();
  DEBUG(fn, "  workPool.stop();\n");
  workPool.stop();
  DEBUG(fn, "  g_pollClients.stop();\n");
  g_pollClients.stop();
  
  // Clean up
  g_loginQ.trigger(true);
  g_commQ.trigger(true);

  DEBUG(fn, "trigger's set\n");
  // disconnect clients lingering in the client queues
  //  g_loginQ.disconnectAll();
  //  g_commQ.disconnectAll();
  g_pollClients.disconnectAll();
  
  SYSLOG(LOG_INFO, "Exit Success!");
  
  traceEnd(fn);
  return EXIT_SUCCESS;
  
} // main

//
//-------------------------------------------------------------------------
// Function       : void SignalHandler(int signum)
//
// Implementation : Handles signals we've requested to intercept
//                  Let's us do stuff on certain signals
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void SignalHandler(int signum)
{
  string fn("SignalHandler");
  traceBegin(fn);
  
  signal(signum, SignalHandler);
  SYSLOG(LOG_INFO, "Signal caught: %d", signum);
  
  switch(signum) {
  case SIGTERM:
  case SIGINT:
    g_bQuit = true;
    break;
    
    // Reconfigure
  case SIGHUP:
    // this may be unsafe
    ReadConfigurationFile();
    break;
    
  case SIGUSR1:
  case SIGUSR2:
    break;
  }
  
  traceEnd(fn);
  
} // SignalHandler


//
//-------------------------------------------------------------------------
// Function       : void ReadConfigurationFile()
//
// Implementation : Reads the configuration file into memory
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void ReadConfigurationFile()
{
  string fn("ReadConfigurationFile");
  traceBegin(fn);
  
  if(g_cfg.read(g_sConfigfile) == false)
    SYSLOG(LOG_WARNING, "Error reading '%s' -- using default values.", 
           g_sConfigfile.c_str());
  else
    SYSLOG(LOG_INFO, "Config file loaded: %s", g_sConfigfile.c_str());
  
  traceEnd(fn);
  
} // ReadConfigurationFile


//
//-------------------------------------------------------------------------
// Function       : int daemon_init(void)
//
// Implementation : Initialize as a daemon
//
// Author         : W. Richard Stevens
//                  Advanced Programming in the UNIX Environment, 1992
//                  ISBN 0-201-56317-7
//
//-------------------------------------------------------------------------
//
int daemon_init(void)
{
  string fn("daemon_init");
  traceBegin(fn);
   
  pid_t pid;
  
  if ( (pid = fork()) < 0)
    return(-1);
  else if (pid != 0)
    exit(0);            /* parent goes bye-bye */
  
  /* child continues */
  setsid();             /* become session leader */
  
  chdir("/");           /* change working directory */
  
  umask(0);             /* clear our file mode creation mask */
  
  traceEnd(fn);
  return(0);
  
} // daemon_init
