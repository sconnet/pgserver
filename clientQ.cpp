//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : clientQ.cpp
//
// Version          : $Id: clientQ.cpp,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Queue of clients waiting to be logged in
//
// Revision History : 
//
// $Log: clientQ.cpp,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "clientQ.h"

//
//-------------------------------------------------------------------------
// Function       : CClientQ::CClientQ()
//
// Implementation : Constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CClientQ::CClientQ() :
  m_bTrigger(false)
{
  string method("CClientQ::CClientQ");
  traceBegin(method);
  
  pthread_mutex_init(&m_triggerMutex, NULL);
  pthread_cond_init(&m_triggerCond, NULL);

  traceEnd(method);
}

//
//-------------------------------------------------------------------------
// Function       : CClientQ::~CClientQ()
//
// Implementation : Destructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CClientQ::~CClientQ()
{
  string method("CClientQ::~CClientQ");
  traceBegin(method);
  
  pthread_mutex_destroy(&m_triggerMutex);
  pthread_cond_destroy(&m_triggerCond);

  traceEnd(method);
}

//
//-------------------------------------------------------------------------
// Function       : void CClientQ::Push(CClient* pClient)
//
// Implementation : Pushes a client pointer onto the queue
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CClientQ::Push(CClient* pClient)
{
  string method("CClientQ::Push");
  traceBegin(method);

  lock();  
  if(pClient != NULL) {
    m_queue.push(pClient);
    Trigger();
  }
  unlock();

  traceEnd(method);

} // Push


//
//-------------------------------------------------------------------------
// Function       : bool CClientQ::PopFront(CClient*& pClient)
//
// Implementation : Returns true if there was an item on the queue.
//                  If so, the passed pointer will point to the item popped
//                  off the queue.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
bool CClientQ::PopFront(CClient*& pClient)
{
  string method("CClientQ::PopFront");
  traceBegin(method);
  
  lock();
  bool bIsNotEmpty = (bool)!m_queue.empty();
  if(bIsNotEmpty) {
    pClient = m_queue.front();
    m_queue.pop();
  }
  
  unlock();

  traceEnd(method);
  return (bIsNotEmpty && (pClient != NULL));

} // PopFront

//
//-------------------------------------------------------------------------
// Function       : bool CClientQ::WaitOnTrigger()
//
// Implementation : Returns when a trigger, which is a new client arriving
//                  or main setting the trigger to wake up waiting threads
//                  cause the app wants to exit
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CClientQ::WaitOnTrigger()
{
  string method("CClientQ::WaitOnTrigger");
  traceBegin(method);

  pthread_mutex_lock(&m_triggerMutex);
  m_bTrigger = false;
  while(!m_bTrigger)
    pthread_cond_wait(&m_triggerCond, &m_triggerMutex);
  //  m_bTrigger = false;
  pthread_mutex_unlock(&m_triggerMutex);

  traceEnd(method);
  
} // WaitOnTrigger

//
//-------------------------------------------------------------------------
// Function       : bool CClientQ::Trigger()
//
// Implementation : Sets the trigger so that waiting threads can be woken
//                  up to take action
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CClientQ::Trigger()
{
  string method("CClientQ::Trigger");
  traceBegin(method);
  
  pthread_mutex_lock(&m_triggerMutex);
  m_bTrigger = true;
  pthread_mutex_unlock(&m_triggerMutex);
  pthread_cond_broadcast(&m_triggerCond);

  traceEnd(method);
  
} // Trigger

//
//-------------------------------------------------------------------------
// Function       : int CClientQ::Size()
//
// Implementation : Returns number of elements in the queue
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int CClientQ::Size() const
{
  string method("CClientQ::Size");
  traceBegin(method);
  
  lock();
  int nSize = m_queue.size();
  unlock();

  traceEnd(method);
  return nSize;
  
} // Size


//
//-------------------------------------------------------------------------
// Function       : void CClientQ::DisconnectAll()
//
// Implementation : Pop's everyone off the queue and deletes them. The
//                  client's destructor actually closes the socket.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CClientQ::DisconnectAll()
{
  string method("CClientQ::DisconnectAll");
  traceBegin(method);

  CClient* pClient = NULL;
  lock();
  
  while(!m_queue.empty()) {
    pClient = m_queue.front();
    m_queue.pop();
    delete pClient;
  }
  
  unlock();
  
  traceEnd(method);
  
} // DisconnectAll
