//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 20, 2001
//
// Source File Name : pgconfig.h
//
// Version          : $Id: $
//
// File Overview    : Stores all configuration items
//
// Revision History : 
//
// $Log: $
//
//
//*****************************************************************************

#ifndef __PGCONFIG_H_
#define __PGCONFIG_H_

#include "config.h"

class CPGConfig : public CConfig
{
 public:
  CPGConfig() :
    nStatsPort(32902),
    nAcceptStatsThreadTimeout(1000),
    nClientPort(32903),
    nAcceptClientThreadTimeout(1000),
    nMaxConnectionsPerIP(5),
    nWorkPoolSize(10),
    nWorkIdleTime(1000),
    sLogClientName("NO")
    {}
  ~CPGConfig() {}
  
  bool Read(const string& sFilename)
    {
      bool ok = Config::Read(sFilename);
      if(ok) {
        nStatsPort = GetValueAsInt("StatsPort", nStatsPort);
        nAcceptStatsThreadTimeout = GetValueAsInt("AcceptStatsThreadTimeout",
                                                  nAcceptStatsThreadTimeout);
        nClientPort = GetValueAsInt("ClientPort", nClientPort);
        nAcceptClientThreadTimeout = GetValueAsInt("acceptclientthreadtimeout",
                                                   nAcceptClientThreadTimeout);
        nMaxConnectionsPerIP = GetValueAsInt("MaxConnectionsPerIP", nMaxConnectionsPerIP);
        nWorkPoolSize = GetValueAsInt("WorkPoolSize", nWorkPoolSize);
        nWorkIdleTime = GetValueAsInt("WorkIdleTime", nWorkIdleTime);
        sLogClientName = GetValueAsStr("LogClientName", sLogClientName);        
      }
      return ok;
    }

  inline int GetAcceptStatsThreadTimeout() { return nAcceptStatsThreadTimeout; }
  inline int GetClientPort() { return nClientPort; }
  inline int GetAcceptClientThreadTimeout() { return nAcceptClientThreadTimeout; }
  inline int GetMaxConnectionsPerIP() { return nMaxConnectionsPerIP; }
  inline int GetWorkPoolSize() { return nWorkPoolSize; }
  inline int GetWorkIdleTime() { return nWorkIdleTime; }
  inline const string& GetLogClientName() { return sLogClientName; }

 private:
  int nStatsPort;
  int nAcceptStatsThreadTimeout;
  int nClientPort;
  int nAcceptClientThreadTimeout;
  int nMaxConnectionsPerIP;
  int nWorkPoolSize;
  int nWorkIdleTime;
  string sLogClientName;
};

#endif // __PGCONFIG_H_
