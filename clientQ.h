//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : clientQ.h
//
// Version          : $Id: $
//
// File Overview    : Queue of clients
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __CLIENTQ_H_
#define __CLIENTQ_H_

#include "client.h"

#include <pthread.h>
#include <queue>
typedef queue<CClient*> ClientQ;

class CClientQ
{
  public:
    CClientQ();
    virtual ~CClientQ();

    inline void operator<<(CClient* pClient) { return Push(pClient); }
    inline bool operator>>(CClient*& pClient) { return PopFront(pClient); }
    int Size();
    void DisconnectAll();

  private:
    void Push(CClient* pClient);
    bool PopFront(CClient*& pClient);

  private:
    ClientQ m_queue;
    pthread_mutex_t m_lock;
};

#endif // __CLIENTQ_H_
