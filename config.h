//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : config.h
//
// Version          : $Id: $
//
// File Overview    : Reads in the configuration file once and puts
//                    each name value pair into a map for quick
//                    hashing and retrieval. This is thread-safe.
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <map>
#include <string>
#include <pthread.h>

typedef map<string, string> CMap;

class CConfig
{
public:
    CConfig();
    CConfig(const char* szFilename);
    virtual ~CConfig();
    
    bool Read(const char* szFilename);

    inline char* operator()(char* szName, char* szDefault)
        { return GetValueAsString(szName, szDefault); }

    inline int operator()(char* szName, int nDefault)
        { return GetValueAsInt(szName, nDefault); }

    void Dump();

private:
    void ParseString(char* s);
    int GetValueAsInt(char* szName, int nDefault);
    char* GetValueAsString(char* szName, char* szDefault);

    CMap m_map;
    pthread_mutex_t m_lock;
};

#endif // __CONFIG_H_

