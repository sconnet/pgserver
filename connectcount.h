//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : connectcount.h
//
// Version          : $Id: connectcount.h,v 1.2 2001/04/23 01:05:46 sconnet Exp $
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
// $Log: connectcount.h,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
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

#include "lock.h"

#include <string>
#include <map>
typedef std::map<std::string /* ipaddr */, int /* count */> CountMap;

class CConnectCount : private CLock
{
  public:
  CConnectCount() {}
  virtual ~CConnectCount() {}
  
  inline bool operator+=(const std::string& sIpAddr) { return Insert(sIpAddr); }
  inline bool operator-=(const std::string& sIpAddr) { return Erase(sIpAddr); }
  inline int operator<<(const std::string& sIpAddr) { return GetCount(sIpAddr); }
  int GetTotal() const;
  
 private:
  bool Insert(const std::string& sIpAddr);
  bool Erase(const std::string& sIpAddr);
  int GetCount(const std::string& sIpAddr) const;
  
 private:
  CountMap m_map;
};

#endif // __CONNECTCOUNT_H_
