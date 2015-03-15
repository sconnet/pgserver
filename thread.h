//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : thread.h
//
// Version          : $Id: thread.h,v 1.2 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Abstract class that gives derived classes threaded
//                    functionality. Derived classes MUST override the
//                    pure virtual function "Thread()".
//
// Revision History : 
//
// $Log: thread.h,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __THREAD_H_
#define __THREAD_H_

#include <pthread.h>

class CThread
{
 public:
  CThread();
  virtual ~CThread();
  
  virtual void start();
  virtual void stop(bool waitForThreadJoin = true);
  bool waitForKillEvent(int nTimeout = 0);
  pthread_t gtThreadId() { return m_tid; }
  
 private:
  // thread id
  pthread_t m_tid;
  
  // kill event variables
  pthread_cond_t m_killCondition;
  pthread_mutex_t m_killLock;
  bool m_bKillEventSet;
  
  // pure virtual function must be overridden by subclassed objects
  virtual void thread() = 0;
  static void* _thread(void* pData) 
    { reinterpret_cast<CThread*>(pData)->thread(); return 0; }
};

#endif // __THREAD_H_
