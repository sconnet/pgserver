//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 20, 2001
//
// Source File Name : pgconfig.h
//
// Version          : $Id: pgconfig.h,v 1.1 2001/04/21 06:12:52 sconnet Exp sconnet $
//
// File Overview    : Stores all configuration items
//
// Revision History : 
//
// $Log: pgconfig.h,v $
// Revision 1.1  2001/04/21 06:12:52  sconnet
// Initial revision
//
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
    nStatsPort_(32902),
    nAcceptStatsThreadTimeout_(1000),
    nClientPort_(32903),
    nAcceptClientThreadTimeout_(1000),
    nMaxConnectionsPerIP_(5),
    nWorkPoolSize_(10),
    nWorkIdleTime_(1000),
    bLogClientName_(false)
    {}
  ~CPGConfig() {}
  
  bool Read(const string& sFilename)
    {
      bool ok = CConfig::Read(sFilename);
      if(ok) {
        nStatsPort_ = GetValueAsInt("StatsPort", nStatsPort_);
        nAcceptStatsThreadTimeout_ = GetValueAsInt("AcceptStatsThreadTimeout",
                                                  nAcceptStatsThreadTimeout_);
        nClientPort_ = GetValueAsInt("ClientPort", nClientPort_);
        nAcceptClientThreadTimeout_ = GetValueAsInt("acceptclientthreadtimeout",
                                                   nAcceptClientThreadTimeout_);
        nMaxConnectionsPerIP_ = GetValueAsInt("MaxConnectionsPerIP", nMaxConnectionsPerIP_);
        nWorkPoolSize_ = GetValueAsInt("WorkPoolSize", nWorkPoolSize_);
        nWorkIdleTime_ = GetValueAsInt("WorkIdleTime", nWorkIdleTime_);
        bLogClientName_ = GetValueAsStr("LogClientName", "NO") == "YES";
      }
      return ok;
    }

  inline int AcceptStatsThreadTimeout() { return nAcceptStatsThreadTimeout_; }
  inline int ClientPort() { return nClientPort_; }
  inline int AcceptClientThreadTimeout() { return nAcceptClientThreadTimeout_; }
  inline int MaxConnectionsPerIP() { return nMaxConnectionsPerIP_; }
  inline int WorkPoolSize() { return nWorkPoolSize_; }
  inline int WorkIdleTime() { return nWorkIdleTime_; }
  inline bool LogClientName() { return bLogClientName_; }

 private:
  int nStatsPort_;
  int nAcceptStatsThreadTimeout_;
  int nClientPort_;
  int nAcceptClientThreadTimeout_;
  int nMaxConnectionsPerIP_;
  int nWorkPoolSize_;
  int nWorkIdleTime_;
  bool bLogClientName_;
};

#endif // __PGCONFIG_H_
