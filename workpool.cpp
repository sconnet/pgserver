//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : workpool.cpp
//
// Version          : $Id: $
//
// File Overview    : Implementation of the work pool
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include "pgserver.h"
#include "workpool.h"
#include "config.h"

#include <unistd.h>

extern CConfig g_cfg;

//
//-------------------------------------------------------------------------
// Function       : CWorkPool::CWorkPool()
//
// Implementation : Constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CWorkPool::CWorkPool()
{
}

//
//-------------------------------------------------------------------------
// Function       : CWorkPool::~CWorkPool()
//
// Implementation : Destructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CWorkPool::~CWorkPool()
{
}

//
//-------------------------------------------------------------------------
// Function       : void CWorkPool::Start()
//
// Implementation : Spawns all the requested work threads
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWorkPool::Start()
{
    // Start with user specified number of worker threads
    int nThreads = g_cfg(WORKPOOL_SIZE_STR, WORKPOOL_SIZE);
    for(int n = 0; n < nThreads; n++)
        Hire();

} // Start

//
//-------------------------------------------------------------------------
// Function       : void CWorkPool::Stop()
//
// Implementation : Tells each worker thread object on the queue to
//                  stop working and deletes it from memory
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWorkPool::Stop()
{
    // Stop all workers
    CWork* pWork = NULL;
    while(!m_queue.empty())
    {
        pWork = m_queue.front();
        m_queue.pop();

        if(pWork != NULL)
        {
            pWork->Stop();
            delete pWork;
        }
    }

} // Stop

//
//-------------------------------------------------------------------------
// Function       : void CWorkPool::Fire()
//
// Implementation : Tells the last work thread object, the one that is
//                  at the front of the queue, to stop working and
//                  deletes it.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWorkPool::Fire()
{
    CWork* pWork = NULL;

    // Must always have at least 1 worker
    if(m_queue.size() > 1)
    {
        pWork = m_queue.front();
        m_queue.pop();
    }

    if(pWork != NULL)
        pWork->Stop();

    delete pWork;

} // Fire

//
//-------------------------------------------------------------------------
// Function       : void CWorkPool::Hire()
//
// Implementation : Instantiates a new work thread object and tells
//                  it to start working. It then puts it on a queue
//                  so we can get to it later to tell it to stop working
//                  and delete it from memory. see Fire()
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CWorkPool::Hire()
{
    CWork* pWork = new CWork;
    if(pWork != NULL)
    {
        pWork->Start();
        m_queue.push(pWork);
    }

} // Hire



