///*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : thread.cpp
//
// Version          : $Id: thread.cpp,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Implementation of the thread base class object.
//
// Revision History : 
//
// $Log: thread.cpp,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "utils.h"
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
// Function       : void CThread::start()
//
// Implementation : Spawns the thread in the subclassed object
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CThread::start()
{
  if(!m_tid)
    pthread_create(&m_tid, NULL, &_thread, this);
  
} // start


//
//-------------------------------------------------------------------------
// Function       : void CThread:: stop(bool waitForThreadJoin = true)
//
// Implementation : Sets the kill event to true and signals the kill 
//                  signal. It waits for spawned threads to die if
//                  requested.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CThread:: stop(bool waitForThreadJoin = true)
{ 
  pthread_mutex_lock(&m_killLock);
  m_bKillEventSet = true;
  pthread_mutex_unlock(&m_killLock);
  pthread_cond_signal(&m_killCondition);
  
  if(waitForThreadJoin) {
    pthread_join(m_tid, NULL);
    m_tid = 0;
    m_bKillEventSet = false;
  }
  
} // stop

//
//-------------------------------------------------------------------------
// Function       : bool CThread::waitForKillEvent(int nTimeout = 0)
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
bool CThread::waitForKillEvent(int nTimeout = 0)
{
  pthread_mutex_lock(&m_killLock);
  
  // TODO: I THINK THIS IS WRONG
  // IT WILL ALWAYS RETURN FALSE EVEN IF EVENT HAS BEEN TRIGGERED,
  // THEN ON NEXT ENCOUNTER OF WAITFORKILLEVENT IT WILL RETURN TRUE
  // INVESTIGATE
  
//    bool bKillEventSet = m_bKillEventSet;
//    if(!bKillEventSet) {
//      struct timespec tm;
//      makeTimespec(nTimeout, tm);
//      pthread_cond_timedwait(&m_killCondition, &m_killLock, &tm);
//    }
  
//    pthread_mutex_unlock(&m_killLock);
//    return bKillEventSet;
  
  if(!m_bKillEventSet) {
    struct timespec tm;
    makeTimespec(nTimeout, tm);
    pthread_cond_timedwait(&m_killCondition, &m_killLock, &tm);
  }
  
  pthread_mutex_unlock(&m_killLock);
  return m_bKillEventSet;
  
} // waitForKillEvent

