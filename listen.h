//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : listen.cpp
//
// Version          : $Id: $
//
// File Overview    : Listens for incoming connections
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __LISTEN_H_
#define __LISTEN_H_

#include "thread.h"
#include "client.h"

class CListen : public CThread
{
public:
    CListen();
    virtual ~CListen();

    virtual void Start(int nPort, int nTimeout);
    void DisplayLocalHost();

    int m_nTimeout;

    virtual void Thread();

private:
    int m_listenfd;             // listening socket

    // must be overidden by subclass to handle accepted connections
    virtual void OnAccept(CClient* pClient) = 0;
};

#endif // __LISTEN_H_
