//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : connectcount.cpp
//
// Version          : $Id: $
//
// File Overview    : Implementation of the connect count class
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include "pgserver.h"
#include "connectcount.h"
#include "config.h"

extern CConfig g_cfg;


//
//-------------------------------------------------------------------------
// Function       : CConnectCount::CConnectCount()
//
// Implementation : Constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CConnectCount::CConnectCount()
{
    pthread_mutex_init(&m_lock, NULL);
}


//
//-------------------------------------------------------------------------
// Function       : CConnectCount::~CConnectCount()
//
// Implementation : Destructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CConnectCount::~CConnectCount()
{
    pthread_mutex_destroy(&m_lock);
}


//
//-------------------------------------------------------------------------
// Function       : bool CConnectCount::Insert(const char* sIpAddr)
//
// Implementation : Checks to see if the ip is already in the map. If it
//                  is, the ip's count is incremented given that the ip
//                  hasn't reached their maximum number of connections.
//                  If the ip is not in the map, it is added with a count
//                  of 1 because it is the 1st connection from that ip
//                  address. Make sense? Ask Steve Dake
//
//                  Note: clients connected to the statistics port are
//                  not put in this map
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
bool CConnectCount::Insert(const char* sIpAddr)
{
    string sAddr(sIpAddr);
    bool bSuccess = true;
    CountMap::iterator p;

    int nMaxConnectionsPerIp = g_cfg(MAX_CONNECTIONS_PERIP_STR, MAX_CONNECTIONS_PERIP);

    // lock the map
    pthread_mutex_lock(&m_lock);

    // find it in the map
    p = m_map.find(sAddr);
    if(p != m_map.end())
    {
        // already connected
        if(p->second >= nMaxConnectionsPerIp)
            bSuccess = false;
        else
            p->second++;  // increment connnection count
    }
    else
        m_map[sAddr] = 1; // add to map, 1st connection

    // unlock the map
    pthread_mutex_unlock(&m_lock);

    return bSuccess;

} // Insert


//
//-------------------------------------------------------------------------
// Function       : bool CConnectCount::Erase(const char* sIpAddr)
//
// Implementation : If the ip address is in the map, it's count is
//                  decremented. If the count reaches 0, the ip
//                  is removed from the map. Returns true if the
//                  ip was removed from the map.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
bool CConnectCount::Erase(const char* sIpAddr)
{
    string sAddr(sIpAddr);
    int nCount = 0;
    CountMap::iterator p;

    // lock the map
    pthread_mutex_lock(&m_lock);

    // find it in the map
    p = m_map.find(sAddr);
    if(p != m_map.end())
    {
        nCount = --(p->second);
        if(nCount == 0)
            m_map.erase(sAddr);
    }

    // unlock the map
    pthread_mutex_unlock(&m_lock);

    return (nCount == 0);

} // Erase


//
//-------------------------------------------------------------------------
// Function       : int CConnectCount::GetCount(const char* sIpAddr)
//
// Implementation : Returns the number of connections for the specified
//                  ip address
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int CConnectCount::GetCount(const char* sIpAddr)
{
    string sAddr(sIpAddr);
    int nCount = 0;
    CountMap::iterator p;

    // lock the map
    pthread_mutex_lock(&m_lock);

    // find it in the map
    p = m_map.find(sAddr);
    if(p != m_map.end())
        nCount = p->second;

    // unlock the map
    pthread_mutex_unlock(&m_lock);

    return nCount;

} // GetCount


//
//-------------------------------------------------------------------------
// Function       : int CConnectCount::GetTotal()
//
// Implementation : Returns the total number of client connections
//
//                  Note: clients connected to the statistics port are
//                  not put in this map
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int CConnectCount::GetTotal()
{
    int nTotal = 0;

    // lock the map
    pthread_mutex_lock(&m_lock);

    // iterate the map and add 'em all up
    CountMap::iterator p = m_map.begin();
    while(p != m_map.end())
    {
        nTotal += p->second;
        p++;
    }

    // unlock the map
    pthread_mutex_unlock(&m_lock);

    return nTotal;
   
} // GetTotal
