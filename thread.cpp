///*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : thread.cpp
//
// Version          : $Id: $
//
// File Overview    : Implementation of the thread base class object.
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include <sys/time.h>

#include "pgserver.h"
#include "thread.h"

//
//-------------------------------------------------------------------------
// Function       : CThread::CThread()
//
// Implementation : Constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CThread::CThread() :
   m_tid(0),
   m_bKillEventSet(false)
{
  pthread_mutex_init(&m_killLock, NULL);
  pthread_cond_init(&m_killCondition, NULL);
}


//
//-------------------------------------------------------------------------
// Function       : CThread::~CThread()
//
// Implementation : Destructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CThread::~CThread()
{
    pthread_mutex_destroy(&m_killLock);
    pthread_cond_destroy(&m_killCondition);
}

//
//-------------------------------------------------------------------------
// Function       : void CThread::Start()
//
// Implementation : Spawns the thread in the subclassed object
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CThread::Start()
{
    if(!m_tid)
        pthread_create(&m_tid, NULL, &_Thread, this);


} // Start


//
//-------------------------------------------------------------------------
// Function       : void CThread::Stop()
//
// Implementation : Sets the kill event to true and signals the kill 
//                  signal. It waits for spawned threads to die. 
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CThread::Stop()
{
    pthread_mutex_lock(&m_killLock);
    m_bKillEventSet = true;
    pthread_mutex_unlock(&m_killLock);
    pthread_cond_signal(&m_killCondition);

    pthread_join(m_tid, NULL);
    m_tid = 0;
    m_bKillEventSet = false;

} // Stop


//
//-------------------------------------------------------------------------
// Function       : TIMESPEC CThread::MakeTimespec(int nTimeout)
//
// Implementation : Returns a timespec struct to be used in a
//                  pthread_cond_timedwait. nTimeout must be in 
//                  milliseconds.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
TIMESPEC CThread::MakeTimespec(int nTimeout)
{
    const long billion = 1000000000L;

    struct timespec deadline;
    struct timespec interval;

    interval.tv_sec = nTimeout / 1000;
    interval.tv_nsec = (nTimeout % 1000) * 1000000L;

    struct timeval now;
    gettimeofday(&now, NULL);
    deadline.tv_sec = now.tv_sec;
    deadline.tv_nsec = now.tv_usec * 1000;

    if((deadline.tv_nsec += interval.tv_nsec) >= billion)
    {
        deadline.tv_nsec -= billion;
        deadline.tv_sec += 1;
    }
    deadline.tv_sec += interval.tv_sec;

    return deadline;

} // MakeTimespec


//
//-------------------------------------------------------------------------
// Function       : bool CThread::WaitForKillEvent(int nTimeout)
//
// Implementation : Waits specified timeout period on the kill event.
//                  nTimeout is in milliseconds. Subclassed objects
//                  should use this function in their thread function
//                  to give "breathing room" for other threads. Using
//                  this function will prevent the CPU from being railed,
//                  which is a VERY BAD thing.
//
//                  This function returns TRUE if the kill event has
//                  been signalled (ie. the Stop function was called).
//                  When this function returns true, the subclassed
//                  object's thread should exit!
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
bool CThread::WaitForKillEvent(int nTimeout)
{
    pthread_mutex_lock(&m_killLock);

    bool bKillEventSet = m_bKillEventSet;
    if(!bKillEventSet)
    {
        TIMESPEC tm = MakeTimespec(nTimeout);
        pthread_cond_timedwait(&m_killCondition, &m_killLock, &tm);
    }

    pthread_mutex_unlock(&m_killLock);
    return bKillEventSet;

} // WaitForKillEvent

