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
// File Overview    : Multiple work thread objects are spawned by
//                    the WorkPool object. The purpose of the
//                    work thread object is to check for clients on the
//                    login queue and for clients ready to communication
//                    on the commQ
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __WORK_H_
#define __WORK_H_

#include "thread.h"

class CWork : public CThread
{
public:
    CWork();
    virtual ~CWork();

    virtual void Start();
    virtual void Stop();

private:
    virtual void Thread();
};

#endif // __WORK_H_
