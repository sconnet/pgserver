//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : connectcount.h
//
// Version          : $Id: $
//
// File Overview    : Keeps track of the number of connections
//                    for each unique ip address. Does not allow
//                    more than a preconfigured number of connections
//                    per ip address.
//
//                    Note: you must erase the client's ip address
//                    when the client disconnects. This decrements
//                    their count. If the count reaches zero, their
//                    ip is taken out of the map
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************
// we write a class so that this map is
// thread safe
// will be accessed by acceptclient.cpp to check for max connections
// and by workerthread removing the client from the map when the
// client disconnects
// also used by the pingthread to remove client from the map when
// the client cannot be pinged

#ifndef __CONNECTCOUNT_H_
#define __CONNECTCOUNT_H_

#include <pthread.h>

#include <string>
#include <map>
typedef map<string /* ipaddr */, int /* count */> CountMap;

class CConnectCount
{
  public:
    CConnectCount();
    virtual ~CConnectCount();

    inline bool operator+=(const char* sIpAddr) { return Insert(sIpAddr); }
    inline bool operator-=(const char* sIpAddr) { return Erase(sIpAddr); }
    inline int operator<<(const char* sIpAddr) { return GetCount(sIpAddr); }
    int GetTotal();

  private:
    bool Insert(const char* sIpAddr);
    bool Erase(const char* sIpAddr);
    int GetCount(const char* sIpAddr);

  private:
    CountMap m_map;
    pthread_mutex_t m_lock;
};

#endif // __CONNECTCOUNT_H_
