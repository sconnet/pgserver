//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : config.h
//
// Version          : $Id: config.h,v 1.1 2001/04/21 02:50:32 sconnet Exp sconnet $
//
// File Overview    : Reads in the configuration file once and puts
//                    each name value pair into a map for quick
//                    hashing and retrieval. This is thread-safe.
//
// Revision History : 
//
// $Log: config.h,v $
// Revision 1.1  2001/04/21 02:50:32  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <map>
#include <string>

typedef map<string, string> CMap;

class CConfig
{
 public:
  CConfig() {}
  virtual ~CConfig() {}
  
  virtual bool Read(const string& sFilename);  
  virtual void Dump();
  
  inline string& operator()(const char* szName, const char* szDefault = NULL)
    { return GetValueAsStr(szName, szDefault); }
  
  inline int operator()(const char* szName, int nDefault = 0)
    { return GetValueAsInt(szName, nDefault); }

 protected:
  string& GetValueAsStr(const char* szName, const char* szDefault = NULL);
  int GetValueAsInt(const char* szName, int nDefault = 0);
  
 private:
  CMap m_map;
};

#endif // __CONFIG_H_

