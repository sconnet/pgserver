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
// File Overview    : Handle accepted client
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __ACCEPTCLIENT_H_
#define __ACCEPTCLIENT_H_

#include "listen.h"
#include "client.h"

class CAcceptClient : public CListen
{
public:
    CAcceptClient();
    virtual ~CAcceptClient();

    virtual void Start();
    virtual void Stop();

private:
    virtual void OnAccept(CClient* pClient);
};

#endif // __ACCEPTCLIENT_H_

