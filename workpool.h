//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : workpool.cpp
//
// Version          : $Id: $
//
// File Overview    : Manages all the work thread objects by using a queue
//                    to keep track of them.
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __WORKPOOL_H_
#define __WORKPOOL_H_

#include "work.h"

#include <queue>
typedef queue<CWork*> workQ;

class CWorkPool
{
public:
    CWorkPool();
    virtual ~CWorkPool();

    inline int Size() { return m_queue.size(); }

    virtual void Start();
    virtual void Stop();

private:
    workQ m_queue;
    void Fire();
    void Hire();
};

#endif // __WORKPOOL_H_
