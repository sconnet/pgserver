//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 20, 2001
//
// Source File Name : pgconfig.h
//
// Version          : $Id: pgconfig.h,v 1.2 2001/04/21 06:27:39 sconnet Exp sconnet $
//
// File Overview    : Stores all configuration items
//
// Revision History : 
//
// $Log: pgconfig.h,v $
// Revision 1.2  2001/04/21 06:27:39  sconnet
// developmental changes
//
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
    m_nStatsPort(32902),
    m_nAcceptStatsThreadTimeout(1000),
    m_nClientPort(32903),
    m_nAcceptClientThreadTimeout(1000),
    m_nMaxConnectionsPerIP(5),
    m_nLoginQThreads(5),
    m_nCommQThreads(10),
    m_nWorkIdleTime(1000),
    m_nTriggerTimeout(1000),
    m_bLogClientName(false)
    {}
  ~CPGConfig() {}

  friend ostream& operator<<(ostream& out, const CPGConfig& cfg);

  inline int statsPort() const { return m_nStatsPort; }
  inline int acceptStatsThreadTimeout() const
    { return m_nAcceptStatsThreadTimeout; }
  inline int clientPort() const { return m_nClientPort; }
  inline int acceptClientThreadTimeout() const
    { return m_nAcceptClientThreadTimeout; }
  inline int maxConnectionsPerIP() const { return m_nMaxConnectionsPerIP; }
  inline int loginQThreads() const { return m_nLoginQThreads; }
  inline int commQThreads() const { return m_nCommQThreads; }
  inline int workIdleTime() const { return m_nWorkIdleTime; }
  inline int triggerTimeout() const { return m_nTriggerTimeout; }
  inline bool logClientName() const { return m_bLogClientName; }
  
  bool read(const string& sFilename);
  
 private:
  int m_nStatsPort;
  int m_nAcceptStatsThreadTimeout;
  int m_nClientPort;
  int m_nAcceptClientThreadTimeout;
  int m_nMaxConnectionsPerIP;
  int m_nLoginQThreads;
  int m_nCommQThreads;
  int m_nWorkIdleTime;
  int m_nTriggerTimeout;
  bool m_bLogClientName;
};

#endif // __PGCONFIG_H_
