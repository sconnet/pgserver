//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//
// Source File Name : pgserver.h
//
// Version          : $Id: pgserver.h,v 1.2 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Standard include that should be included in
//                    EVERY implementation file. Has basic definitions
//                    and various stuff used by all objects.
//
// Revision History :
//
// $Log: pgserver.h,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************


#ifndef __PGSERVER_H_
#define __PGSERVER_H_

#include <iostream> // for debuggin
#include <syslog.h>
#include <signal.h>

#include "utils.h"

// messages
#define MSG_PING          0
#define MSG_DISCONNECT    1
#define MSG_SEARCHRESULT  2
#define MSG_USERID        3

// communication
#define ACK    6     // acknowledge
#define NAK    21    // not acknowledge

#endif // __PGSERVER_H_
