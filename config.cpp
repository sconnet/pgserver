//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : config.cpp
//
// Version          : $Id: $
//
// File Overview    : Implementation of the config object
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include "pgserver.h"
#include "config.h"
#include "utils.h"

#include <stdio.h>
#include <unistd.h>

#include <algorithm>

extern char* g_sConfigfile;

//
//-------------------------------------------------------------------------
// Function       : CConfig::CConfig()
//
// Implementation : Constructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CConfig::CConfig()
{
   pthread_mutex_init(&m_lock, NULL);
}

//
//-------------------------------------------------------------------------
// Function       : CConfig::~CConfig()
//
// Implementation : Destructor
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
CConfig::~CConfig()
{
    pthread_mutex_destroy(&m_lock);
    m_map.clear();
}

//
//-------------------------------------------------------------------------
// Function       : bool CConfig::Read(const char* szFilename)
//
// Implementation : Reads the config file and parses each line
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
bool CConfig::Read(const char* szFilename)
{
    FILE* f = fopen(szFilename, "r");
    if(f != NULL)
    {
        char s[82];

        // Read in a string a parse it
        fgets(s, 80, f);
        ParseString(s);

        // Keep doing it until we reach the end of file
        while(!feof(f))
        {
            fgets(s, 80, f);
            ParseString(s);
        }

        fclose(f);
    }
    
    return (f != NULL);

} // Read

//
//-------------------------------------------------------------------------
// Function       : void CConfig::ParseString(char* s)
//
// Implementation : Parses the passed string and putting the
//                  name value pair into a map for later retrieval.
//                  Converts everything to upper case.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void CConfig::ParseString(char* s)
{
    char* pEq = NULL;
    
    // Parse message if it isn't a comment and it contains a name-value pair
    if((s[0] != '#') && ((pEq = strchr(s, '=')) != NULL) && strlen(s) > 1)
    {
        // temp so we can trim and convert to upper
        char szName[41];
        char szValue[41];
        
        string sName;
        string sValue;

        // axe the additonal cr/lf
        s[strlen(s) - 1] = '\0';      // just a cr for linux
        //        s[strlen(s) - 2] = '\0';

        // copy name/value into newly allocated memory
        strcpy(szValue, pEq + 1);
        *pEq = '\0';
        strcpy(szName, s);

        // trim whitespace
        strcpy(szName, trim_right(szName));
        strcpy(szValue, trim_left(szValue));

        // append to strings
        sName.append(szName);
        sValue.append(szValue);

        // convert to upper case
        transform(sName.begin(), sName.end(), sName.begin(), toupper);
        transform(sValue.begin(), sValue.end(), sValue.begin(), toupper);
        
        // insert copies into the map
        //m_map.insert(pair<string, string>(sName, sValue));
        m_map[sName] = sValue; // this is the same thing but easier to read
    }

} // ParseString

//
//-------------------------------------------------------------------------
// Function       : char* CConfig::GetValueAsString(char* szName, 
//                                                  char* szDefault)
//
// Implementation : Returns a value given a name. If name is not
//                  found then default is returned.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
char* CConfig::GetValueAsString(char* szName, char* szDefault)
{
    char* sReturnVal = szDefault;
    pthread_mutex_lock(&m_lock);
    
    // convert to upper case    
    string sName  = szName;
    transform(sName.begin(), sName.end(), sName.begin(), toupper);

    // find it in the map
    CMap::iterator p;
    p = m_map.find(sName);
    pthread_mutex_unlock(&m_lock);

    // point to it if we found it
    if(p != m_map.end())
        sReturnVal = (char*)p->second.c_str();

    return sReturnVal;

} // GetValueAsString

//
//-------------------------------------------------------------------------
// Function       : int CConfig::GetValueAsInt(char* szName, int nDefault)
//
// Implementation : Returns a value given a name. The value is converted
//                  to an int. If the name is not found, the default
//                  value is returned.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
int CConfig::GetValueAsInt(char* szName, int nDefault)
{
    int nRetVal = nDefault;
    char* p = GetValueAsString(szName, NULL);
    if(p)
        nRetVal = atoi(p);

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
    for(p = m_map.begin(); p != m_map.end(); p++)
        cout << p->first << "=" << p->second << endl;
    
    cout << endl;

} // Dump
