//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : config.cpp
//
// Version          : $Id: config.cpp,v 1.3 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Implementation of the config object
//
// Revision History :
//
// $Log: config.cpp,v $
// Revision 1.3  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.2  2001/04/21 06:23:15  sconnet
// lock around container access
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "pgserver.h"
#include "config.h"
#include "utils.h"

#include <stdio.h>
#include <unistd.h>

#include <cctype>
#include <fstream>
#include <algorithm>

using namespace std;

extern string g_sConfigfile;

//
//-------------------------------------------------------------------------
// Function       : ostream& operator<<(const ostream& out,
//                                      const CConfig& cfg)
//
// Implementation : dump the values in the map
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
ostream &operator<<(ostream &out, const CConfig &cfg)
{
    string method("CConfig::operator<<");
    traceBegin(method);

    out << "[" << g_sConfigfile << "]" << '\n';

    CMap::const_iterator p;
    cfg.lock();
    for(p = cfg.m_map.begin(); p != cfg.m_map.end(); p++) {
        out << p->first << "=" << p->second << '\n';
    }
    cfg.unlock();

    out << endl;

    traceEnd(method);
    return out;

} // operator<<


//
//-------------------------------------------------------------------------
// Function       : bool CConfig::read(const string& sFilename)
//
// Implementation : Reads the config file and parses each line
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
bool CConfig::read(const string &sFilename)
{
    string method("CConfig::read");
    traceBegin(method);

    string buf;
    m_map.clear();
    ifstream infile(sFilename.c_str(), ios::in);
    bool ok = infile;
    while(getline(infile, buf)) {
        if(buf.length() && isalpha(buf[0])) {
            transform(buf.begin(), buf.end(), buf.begin(), ::toupper);
            string::size_type pos = buf.find_first_of('=');
            string name(buf.substr(0, pos));
            string value(buf.substr(pos + 1));
            lock();
            m_map[trimLeft(trimRight(name))] = trimLeft(trimRight(value));
            unlock();
        }
    }

    infile.close();

    traceEnd(method);
    return ok;

} // read

//
//-------------------------------------------------------------------------
// Function       : string CConfig::getValueAsStr(const char* sName,
//                                                const char* sDefault)
//
//
// Implementation : Returns a value given a name. If name is not
//                  found then default is returned.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
string CConfig::getValueAsStr(const char *szName,
                              const char *szDefault)
{
    string method("CConfig::GetValueAsStr");
    traceBegin(method);

    string sReturnVal(szDefault);
    string sName(szName);
    transform(sName.begin(), sName.end(), sName.begin(), ::toupper);

    // find it in the map
    lock();
    CMap::iterator p = m_map.find(sName);
    if(p != m_map.end()) {
        sReturnVal = p->second;
    }
    unlock();

    traceEnd(method);
    return sReturnVal;

} // getValueAsString

//
//-------------------------------------------------------------------------
// Function       : int CConfig::getValueAsInt(const char* szName,
//                                             int nDefault)
//
// Implementation : Returns a value given a name. The value is converted
//                  to an int. If the name is not found, the default
//                  value is returned.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int CConfig::getValueAsInt(const char *szName, int nDefault)
{
    string method("CConfig::getValueAsInt");
    traceBegin(method);

    int nRetVal = nDefault;
    string s(getValueAsStr(szName));
    if(s.length()) {
        nRetVal = atoi(s.c_str());
    }

    traceEnd(method);
    return nRetVal;

} // getValueAsInt
