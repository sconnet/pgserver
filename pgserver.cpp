//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : pgserver.cpp
//
// Version          : $Id: $
//
// File Overview    : main launch point of the Peer Gear server
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include "pgserver.h"
#include "config.h"
#include "acceptstats.h"
#include "acceptclient.h"
#include "connectcount.h"
#include "clientQ.h"
#include "workpool.h"
#include "pollclients.h"

#include <string>

#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// global variables
volatile sig_atomic_t g_bQuit = false;
string g_sConfigfile = "/etc/pgserver.conf";

CConfig g_cfg;
CConnectCount g_connectCount;
CClientQ g_loginQ;
CClientQ g_commQ;
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
  // become a daemon
  if(daemon_init() < 0) {
    cerr << "Could not initialize as a daemon process." << endl;
    exit(1);
  }
  
  // setup signals to catch
  signal(SIGTERM, SignalHandler);
  signal(SIGINT, SignalHandler);
  signal(SIGHUP, SignalHandler);
  signal(SIGUSR1, SignalHandler);
  signal(SIGUSR2, SignalHandler);
  
  // signals to ignore
  signal(SIGPIPE, SIG_IGN);     // handle pipe err's in socket comm.
  
  // Tell the syslog we are alive
  syslog(LOG_INFO, "Peer Gear Server v0.01 starting up!");
  ReadConfigurationFile();
  
  // Start listening for incoming connections on the stats port
  CAcceptStats acceptStats;
  acceptStats.Start();
  
  // Start listening for incoming connections on the clients port
  CAcceptClient acceptClient;
  acceptClient.Start();
  
  // Create thread pool of worker objects to do all the work
  CWorkPool workPool;
  workPool.Start();
  g_pollClients.Start();
  
  // block nothing, sleep until signaled to quit
  sigset_t emptyset;
  sigemptyset(&emptyset);
  sigprocmask(SIG_SETMASK, &emptyset, NULL);
  while(!g_bQuit)
    sigsuspend(&emptyset);
  
  // inform the world we are stopping
  syslog(LOG_INFO, "Shutting down...");
  acceptStats.Stop();
  acceptClient.Stop();
  workPool.Stop();
  g_pollClients.Stop();
  
  // disconnect clients lingering in the client queues
  g_loginQ.DisconnectAll();
  g_commQ.DisconnectAll();
  g_pollClients.DisconnectAll();
  
  syslog(LOG_INFO, "Exit Success!");
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
    signal(signum, SignalHandler);
    syslog(LOG_INFO, "Signal caught: %d", signum);

    switch(signum)
    {
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
  if(g_cfg.Read(g_sConfigfile) == false)
    syslog(LOG_WARNING, 
           "Error reading '%s' -- using default values.", 
           g_sConfigfile);
  else
    syslog(LOG_INFO, "Config file loaded: %s", g_sConfigfile);
  
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
    pid_t pid;
    
    if ( (pid = fork()) < 0)
        return(-1);
    else if (pid != 0)
        exit(0);          /* parent goes bye-bye */

    /* child continues */
    setsid();             /* become session leader */

    chdir("/");           /* change working directory */

    umask(0);             /* clear our file mode creation mask */

    return(0);

} // daemon_init
