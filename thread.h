//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : thread.h
//
// Version          : $Id: $
//
// File Overview    : Base class the gives derived classes threaded
//                    functionality. Derived classes MUST override the
//                    pure virtual function "Thread()".
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __THREAD_H_
#define __THREAD_H_

#include <pthread.h>

typedef struct timespec TIMESPEC;

class CThread
{
public:
    CThread();
    virtual ~CThread();

    virtual void Start();
    virtual void Stop();
    bool WaitForKillEvent(int nTimeout);
    pthread_t GetThreadId() { return m_tid; }

private:
    // thread id
    pthread_t m_tid;
    
    // kill event variables
    pthread_cond_t m_killCondition;
    pthread_mutex_t m_killLock;
    bool m_bKillEventSet;

    TIMESPEC MakeTimespec(int nTimeout);

    // pure virtual function must be overridden by subclassed objects
    virtual void Thread() = 0;
    static void* _Thread(void* pData) 
        { reinterpret_cast<CThread*>(pData)->Thread(); return 0; }
};

#endif // __THREAD_H_
