//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Arpil 22, 2001
//
// Source File Name : safeQ.h
//
// Version          : $Id: $
//
// File Overview    : Thread-safe queue of anything you want with trigger
//                    on insert
//
// Revision History : 
//
// $Log: $
//
//
//*****************************************************************************

#ifndef __SAFEQ_H_
#define __SAFEQ_H_

#include "utils.h"
#include "pgconfig.h"
#include "lock.h"

#include <errno.h>
#include <queue>

extern CPGConfig g_cfg;

template<class TYPE>
class CSafeQ : private CLock
{
 public:
  CSafeQ() {
    string method("CSafeQ::CSafeQ");
    traceBegin(method);
    
    pthread_mutex_init(&m_triggerMutex, NULL);
    pthread_cond_init(&m_triggerCond, NULL);
    
    traceEnd(method);
  }

  virtual ~CSafeQ() {
    string method("CSafeQ::~CSafeQ");
    traceBegin(method);
    
    pthread_mutex_destroy(&m_triggerMutex);
    pthread_cond_destroy(&m_triggerCond);
    
    traceEnd(method);
  }
  
  inline void operator<<(TYPE obj) {
    return push(obj);
  }

  // wait for trigger
  inline bool operator>>(TYPE& obj) {
    waitOnTrigger(g_cfg.triggerTimeout());
    return popFront(obj);
  }

  int size() const {
    string method("CSafeQ::size");
    traceBegin(method);
    
    lock();
    int nSize = m_queue.size();
    unlock();
    
    traceEnd(method);
    return nSize;

  } // size
  
  void push(TYPE obj) {
    string method("CSafeQ::push");
    traceBegin(method);
    
    lock();  
    m_queue.push(obj);
    trigger();
    unlock();
    
    traceEnd(method);

  } // push
  
  bool popFront(TYPE& obj) {
    string method("CSafeQ::popFront");
    traceBegin(method);
    
    lock();
    bool bEmpty = (bool)m_queue.empty();
    if(!bEmpty) {
      obj = m_queue.front();
      m_queue.pop();
    }  
    unlock();
    
    traceEnd(method);
    return !bEmpty;

  } // popFront
  
  // pass is 0 to wait forever
  void waitOnTrigger(int nTimeout = 1000 /* ms */) {
    string method("CSafeQ::waitOnTrigger");
    traceBegin(method);
    
    pthread_mutex_lock(&m_triggerMutex);

    // turn off the trigger if the queue is empty
    if(size() == 0)
      m_bTrigger = false;
    
    if(!m_bTrigger) {
      if(nTimeout) {
        struct timespec tm;
        makeTimespec(nTimeout, tm);
        while(!m_bTrigger) {
          if(pthread_cond_timedwait(&m_triggerCond,
                                    &m_triggerMutex, &tm) == ETIMEDOUT)
            break;
        }
      }
      else
        while(!m_bTrigger)
          pthread_cond_wait(&m_triggerCond, &m_triggerMutex);
    }

    pthread_mutex_unlock(&m_triggerMutex);    
    traceEnd(method);

  } // waitOnTrigger
  
  void trigger(bool bAll = false) {
    string method("CSafeQ::trigger");
    traceBegin(method);
    
    // turn the trigger on
    pthread_mutex_lock(&m_triggerMutex);
    m_bTrigger = true;
    pthread_mutex_unlock(&m_triggerMutex);
    if(bAll)
      pthread_cond_broadcast(&m_triggerCond);
    else
      pthread_cond_signal(&m_triggerCond);
    
    traceEnd(method);

  } // trigger
  
 private:
  queue<TYPE> m_queue;
  bool m_bTrigger;
  pthread_cond_t m_triggerCond;
  pthread_mutex_t m_triggerMutex;
};

#endif // __SAFEQ_H_
