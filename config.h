//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : config.h
//
// Version          : $Id: config.h,v 1.4 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Reads in the configuration file once and puts
//                    each name value pair into a map for quick
//                    hashing and retrieval. This is thread-safe.
//
// Revision History : 
//
// $Log: config.h,v $
// Revision 1.4  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.3  2001/04/21 06:22:56  sconnet
// derived from lock
//
// Revision 1.2  2001/04/21 06:19:51  sconnet
// developmental changes
//
// Revision 1.1  2001/04/21 02:50:32  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <map>
#include <string>
#include <iostream>

#include "lock.h"

typedef map<string, string> CMap;

class CConfig : private CLock
{
 public:
  CConfig() {}
  virtual ~CConfig() {}
  
  virtual bool read(const string& sFilename);  
  
  inline string operator()(const char* szName, const char* szDefault = "")
    { return getValueAsStr(szName, szDefault); }
  
  inline int operator()(const char* szName, int nDefault = 0)
    { return getValueAsInt(szName, nDefault); }

  friend ostream& operator<<(ostream& out, const CConfig& cfg);

 protected:
  string getValueAsStr(const char* szName, const char* szDefault = "");
  int getValueAsInt(const char* szName, int nDefault = 0);
  
 private:
  CMap m_map;
};

#endif // __CONFIG_H_

