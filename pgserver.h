//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//
// Source File Name : pgserver.h
//
// Version          : $Id: $
//
// File Overview    : Standard include that should be included in 
//                    EVERY implementation file. Has basic definitions
//                    and various stuff used by all objects.
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************


#ifndef __PGSERVER_H_
#define __PGSERVER_H_

#include <iostream> // for debuggin
#include <syslog.h>
#include <signal.h>

// messages
#define MSG_PING          0
#define MSG_DISCONNECT    1
#define MSG_SEARCHRESULT  2
#define MSG_USERID        3

// configuration values
#define STATPORT_STR "StatsPort"
#define STATPORT 32902

#define ACCEPTSTATS_THREAD_TIMEOUT_STR "AcceptStatsThreadTimeout"
#define ACCEPTSTATS_THREAD_TIMEOUT 1000

#define CLIENTPORT_STR "ClientPort"
#define CLIENTPORT 32903

#define ACCEPTCLIENT_THREAD_TIMEOUT_STR "AcceptClientThreadTimeout"
#define ACCEPTCLIENT_THREAD_TIMEOUT 1000

#define MAX_CONNECTIONS_PERIP_STR "MaxSameIPConnections"
#define MAX_CONNECTIONS_PERIP      5

#define GETCLIENTBYNAME_STR "LogClientName"
#define GETCLIENTBYNAME "NO"

#define WORKPOOL_SIZE_STR "WorkPoolSize"
#define WORKPOOL_SIZE 10

#define WORK_IDLE_STR "WorkIdle"
#define WORK_IDLE 1000

// communication
#define ACK    6     // acknowledge
#define NAK    21    // not acknowledge

#endif // __PGSERVER_H_
