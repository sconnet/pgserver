//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : clientQ.cpp
//
// Version          : $Id: $
//
// File Overview    : Queue of clients waiting to be logged in
//
// Revision History : 
//
// $Log: $
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
CClientQ::CClientQ()
{
    pthread_mutex_init(&m_lock, NULL);
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
    pthread_mutex_destroy(&m_lock);
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
    // lock the queue
    pthread_mutex_lock(&m_lock);

    if(pClient != NULL)
        m_queue.push(pClient);

    // unlock the queue
    pthread_mutex_unlock(&m_lock);

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
    // lock the queue
    pthread_mutex_lock(&m_lock);

    bool bIsNotEmpty = (bool)!m_queue.empty();
    if(bIsNotEmpty)
    {
        pClient = m_queue.front();
        m_queue.pop();
    }

    // unlock the queue
    pthread_mutex_unlock(&m_lock);
    return (bIsNotEmpty && (pClient != NULL));

} // PopFront


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
int CClientQ::Size()
{
    pthread_mutex_lock(&m_lock);
    int nSize = m_queue.size();
    pthread_mutex_unlock(&m_lock);
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
  //    cerr << "ClientQ Disconnecting ALL! <--" << endl;

    CClient* pClient = NULL;
    pthread_mutex_lock(&m_lock);

    while(!m_queue.empty())
    {
        pClient = m_queue.front();
        m_queue.pop();
        delete pClient;
    }

    pthread_mutex_unlock(&m_lock);

    //    cerr << "ClientQ Disconnecting ALL! -->" << endl;

} // DisconnectAll
