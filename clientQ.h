//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : clientQ.h
//
// Version          : $Id: clientQ.h,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Queue of clients
//
// Revision History : 
//
// $Log: clientQ.h,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __CLIENTQ_H_
#define __CLIENTQ_H_

#include "client.h"
#include "lock.h"

#include <queue>
typedef queue<CClient*> ClientQ;

class CClientQ : private CLock
{
 public:
  CClientQ();
  virtual ~CClientQ();
  
  inline void operator<<(CClient* pClient)
    { return Push(pClient); }

  inline bool operator>>(CClient*& pClient)
    { WaitOnTrigger(); return PopFront(pClient); }

  int Size() const;
  void DisconnectAll();
  void Trigger();
  
 private:
  void Push(CClient* pClient);
  bool PopFront(CClient*& pClient);
  
 private:
  void WaitOnTrigger();
  ClientQ m_queue;
  bool m_bTrigger;
  pthread_cond_t m_triggerCond;
  pthread_mutex_t m_triggerMutex;
};

#endif // __CLIENTQ_H_
