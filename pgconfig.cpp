//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 21, 2001
//
// Source File Name : pgconfig.cpp
//
// Version          : $Id: pgconfig.cpp,v 1.1 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Stores all configuration items
//
// Revision History :
//
// $Log: pgconfig.cpp,v $
// Revision 1.1  2001/04/23 01:05:46  sconnet
// Initial revision
//
//
//
//*****************************************************************************

#include "pgserver.h"
#include "pgconfig.h"

using namespace std;

//
//-------------------------------------------------------------------------
// Function       : ostream& operator<<(const ostream& out,
//                                      const CPGConfig& cfg)
//
// Implementation : dump the values we are using
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
ostream &operator<<(ostream &out, const CPGConfig &cfg)
{
    string method("CPGConfig::operator<<");
    traceBegin(method);

    out << static_cast<CConfig>(cfg);

    out << "USING VALUES:" << '\n';
    out << "StatsPort=" << cfg.statsPort() << '\n';
    out << "AcceptStatsThreadTimeout=" << cfg.acceptStatsThreadTimeout() << '\n';
    out << "ClientPort=" << cfg.clientPort() << '\n';
    out << "AcceptClientThreadTimeout=" <<
        cfg.acceptClientThreadTimeout() << '\n';
    out << "MaxConnectionsPerIP=" << cfg.maxConnectionsPerIP() << '\n';
    out << "LoginQThreads=" << cfg.loginQThreads() << '\n';
    out << "CommQThreads=" << cfg.commQThreads() << '\n';
    out << "WorkIdleTime=" << cfg.workIdleTime() << '\n';
    out << "LogClientName=" << cfg.logClientName() << '\n';
    out << endl;

    traceEnd(method);
    return out;

} // operator<<


//
//-------------------------------------------------------------------------
// Function       : bool CPGConfig::read(const string& sFilename)
//
// Implementation : set data members from values in base class
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
bool CPGConfig::read(const string &sFilename)
{
    string method("CPGConfig::read");
    traceBegin(method);

    bool ok = CConfig::read(sFilename);
    if(ok) {
        m_nStatsPort = getValueAsInt("StatsPort", m_nStatsPort);
        m_nAcceptStatsThreadTimeout = getValueAsInt("AcceptStatsThreadTimeout",
                                      m_nAcceptStatsThreadTimeout);
        m_nClientPort = getValueAsInt("ClientPort", m_nClientPort);
        m_nAcceptClientThreadTimeout = getValueAsInt("acceptclientthreadtimeout",
                                       m_nAcceptClientThreadTimeout);
        m_nMaxConnectionsPerIP = getValueAsInt("MaxConnectionsPerIP",
                                               m_nMaxConnectionsPerIP);
        m_nLoginQThreads = getValueAsInt("LoginQThreads", m_nLoginQThreads);
        m_nCommQThreads = getValueAsInt("CommQThreads", m_nCommQThreads);
        m_nWorkIdleTime = getValueAsInt("WorkIdleTime", m_nWorkIdleTime);
        m_nTriggerTimeout = getValueAsInt("TriggerTimeout", m_nTriggerTimeout);
        m_bLogClientName = getValueAsStr("LogClientName", "NO") == "YES";
    }

    traceEnd(method);
    return ok;

} // read

