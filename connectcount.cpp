//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : connectcount.cpp
//
// Version          : $Id: connectcount.cpp,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Implementation of the connect count class
//
// Revision History : 
//
// $Log: connectcount.cpp,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "connectcount.h"
#include "pgconfig.h"

extern CPGConfig g_cfg;


//
//-------------------------------------------------------------------------
// Function       : bool CConnectCount::Insert(const string& sIpAddr)
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
bool CConnectCount::Insert(const string& sIpAddr)
{
  string method("CConnectCount::Insert");
  traceBegin(method);
  
  bool bSuccess = true;  
  lock();
  
  // find it in the map
  CountMap::iterator p = m_map.find(sIpAddr);
  if(p != m_map.end()) {

    // already connected
    if(p->second >= g_cfg.maxConnectionsPerIP())
      bSuccess = false;
    else
      p->second++;  // increment connnection count
  }
  else
    m_map[sIpAddr] = 1; // add to map, 1st connection
  
  unlock();

  traceEnd(method);
  return bSuccess;
  
} // Insert


//
//-------------------------------------------------------------------------
// Function       : bool CConnectCount::Erase(const string& sIpAddr)
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
bool CConnectCount::Erase(const string& sIpAddr)
{
  string method("CConnectCount::Erase");
  traceBegin(method);
  
  int nCount = 0;  
  lock();
  
  // find it in the map
  CountMap::iterator p = m_map.find(sIpAddr);
  if(p != m_map.end()) {
    nCount = --(p->second);
    if(nCount == 0)
      m_map.erase(sIpAddr);
  }
  
  unlock();  

  traceEnd(method);
  return (nCount == 0);
  
} // Erase


//
//-------------------------------------------------------------------------
// Function       : int CConnectCount::GetCount(const string& sIpAddr) const
//
// Implementation : Returns the number of connections for the specified
//                  ip address
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int CConnectCount::GetCount(const string& sIpAddr) const
{
  string method("CConnectCount::GetCount");
  traceBegin(method);
  
  int nCount = 0;  
  lock();  

  // find it in the map
  CountMap::const_iterator p = m_map.find(sIpAddr);
  if(p != m_map.end())
    nCount = p->second;
  
  unlock();  

  traceEnd(method);
  return nCount;
  
} // GetCount


//
//-------------------------------------------------------------------------
// Function       : int CConnectCount::GetTotal() const
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
int CConnectCount::GetTotal() const
{
  string method("CConnectCount::GetTotal");
  traceBegin(method);
  
  int nTotal = 0;
  lock();
  
  // iterate the map and add 'em all up
  CountMap::const_iterator p = m_map.begin();
  while(p != m_map.end()) {
    nTotal += p->second;
    p++;
  }
  
  unlock();

  traceEnd(method);
  return nTotal;
  
} // GetTotal
