//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : config.cpp
//
// Version          : $Id: config.cpp,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Implementation of the config object
//
// Revision History : 
//
// $Log: config.cpp,v $
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

#include <fstream>
#include <algorithm>

extern string g_sConfigfile;

//
//-------------------------------------------------------------------------
// Function       : bool CConfig::Read(const string& sFilename)
//
// Implementation : Reads the config file and parses each line
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
bool CConfig::Read(const string& sFilename)
{
  string buf;
  m_map.clear();
  ifstream infile(sFilename.c_str(), ios::in);
  while(getline(infile, buf)) {
    if(buf.length() && isalpha(buf[0])) {
      transform(buf.begin(), buf.end(), buf.begin(), toupper);
      string::size_type pos = buf.find_first_of('=');
      string name(buf.substr(0, pos));
      string value(buf.substr(pos + 1));
      lock();
      m_map[name] = value;
      unlock();
    }
  }

  infile.close();
  return (infile != NULL);
  
} // Read

//
//-------------------------------------------------------------------------
// Function       : string CConfig::GetValueAsStr(const char* sName,
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
string& CConfig::GetValueAsStr(const char* szName,
                               const char* szDefault = NULL)
{
  static string sReturnVal(szDefault);
  string sName(szName);
  transform(sName.begin(), sName.end(), sName.begin(), toupper);
  
  // find it in the map
  lock();
  CMap::iterator p = m_map.find(sName);
  if(p != m_map.end())
    sReturnVal = p->second;
  unlock();  
  return sReturnVal;
  
} // GetValueAsString

//
//-------------------------------------------------------------------------
// Function       : int CConfig::GetValueAsInt(const char* szName,
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
int CConfig::GetValueAsInt(const char* szName, int nDefault = 0)
{
  int nRetVal = nDefault;
  string& s = GetValueAsStr(szName, NULL);
  if(s.length())
    nRetVal = atoi(s.c_str());
  
  return nRetVal;
  
} // GetValueAsInt

//
//-------------------------------------------------------------------------
// Function       : void CConfig::Dump()
//
// Implementation : Dump the map of name-value pairs to stdout
//                  Helpful in debugging.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CConfig::Dump()
{
  cout << "[" << g_sConfigfile << "]" << endl;
  
  CMap::iterator p;
  lock();
  for(p = m_map.begin(); p != m_map.end(); p++)
    cout << p->first << "=" << p->second << '\n';
  unlock();
  
  cout << endl;
  
} // Dump
