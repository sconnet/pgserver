//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : acceptstats.h
//
// Version          : $Id: $
//
// File Overview    : spew stats out to a newly connected client
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __ACCEPTSTATS_H_
#define __ACCEPTSTATS_H_

#include "listen.h"
#include "client.h"

class CAcceptStats : public CListen
{
public:
    CAcceptStats();
    virtual ~CAcceptStats();

    virtual void Start();
    virtual void Stop();

private:
    virtual void OnAccept(CClient* pClient);
};

#endif // __ACCEPTSTATS_H_
