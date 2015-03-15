//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : utils.cpp
//
// Version          : $Id: utils.cpp,v 1.2 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Implementation of the utility functions.
//
// Revision History : 
//
// $Log: utils.cpp,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#include "utils.h"

#include <iostream>
#include <cctype>
#include <cstdio>

#include <sys/time.h>
#include <syslog.h>

using namespace std;

//
//-------------------------------------------------------------------------
// Function       : ssize_t Read(int fd, void* buf, size_t count)
//
// Implementation : Continues reading count bytes from the
//                  specified file descriptor until all data has
//                  been read into buf. Returns the number of bytes
//                  read. Returns -1 if the read failed.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
ssize_t Read(int fd, void* buf, size_t count)
{
  size_t nTotal = 0;
  int nBytes = 0;
  
  // keep reading until we read everything
  while(nTotal < count) {
    
    // bail out if there is an error reading
    // 0 indicates EOF (client disconnected)
    if((nBytes = read(fd, (char*)buf + nTotal, count - nTotal)) <= 0) {
      nTotal = nBytes;
      break;
    }
    else
      nTotal += nBytes;
    
    //     printf("reading, %d %d\n", nTotal, nBytes);
  }
  
  return nTotal;
  
} // Read

//
//-------------------------------------------------------------------------
// Function       : ssize_t Write(int fd, const void* buf, size_t count);
//
// Implementation : Continues to write count bytes from buf to the
//                  specified file descriptor until all bytes have
//                  been written. Returns the number of bytes written
//                  or -1 if the write failed.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
ssize_t Write(int fd, const void* buf, size_t count)
{
  size_t nTotal = 0;
  int nBytes = 0;
  
  // keep writing until we write everything
  while(nTotal < count) {
    if((nBytes = write(fd, (char*)buf + nTotal, count - nTotal)) <= 0) {
      nTotal = nBytes;
      break;
    }
    else
      nTotal += nBytes;
  }
    
  return nTotal;
    
} // Write


//
//-------------------------------------------------------------------------
// Function       : string trimLeft(const string &value)
//
// Implementation : Remove whitespace from the left of the string
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
string trimLeft(const string &value)
{
   string::size_type where = value.find_first_not_of(' ');
  
   // string has nothing but space
   if(where == string::npos)
     return string();
   
   // string has no leading space,
   // don't copy its contents (assuming COW strings)
   if(where == 0)
     return value;
   
   return value.substr(where);
}


//
//-------------------------------------------------------------------------
// Function       : string trimRight(const string &value)
//
// Implementation : Remove whitespace from the right of the string
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
string trimRight(const string &value)
{
  string::size_type where = value.find_last_not_of(' ');
  
  // string has nothing but space
  if(where == string::npos)
    return string();
  
  // string has no trailing space, don't copy its contents
  if(where == (value.length() - 1))
    return value;
  
  return value.substr(0, where + 1);
}


//
//-------------------------------------------------------------------------
// Function       : void traceBegin(const string& method)
//
// Implementation : log to stderr if compiled with TRACE
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void traceBegin(const string& method)
{
#ifdef _TRACE
  cerr << "TRACE " << method << " <--" << endl;
#endif
  
} // traceBegin


//
//-------------------------------------------------------------------------
// Function       : void traceEnd(const string& method)
//
// Implementation : log to stderr if compiled with TRACE
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void traceEnd(const string& method)
{
#ifdef _TRACE
  cerr << "TRACE " << method << " -->" << endl;
#endif

} // traceEnd


//
//-------------------------------------------------------------------------
// Function       : void TRACE(const string& method, const char* fmt, ...)
//
// Implementation : log to stdout if compiled with _TRACE
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void TRACE(const string& method, const char* fmt, ...)
{
#ifdef _TRACE
  char msg[1024];
  va_list ap;
  va_start (ap, fmt);
  int retval = vsnprintf(msg, 1023, fmt, ap);
  va_end (ap);

  cout << "TRACE " << method << " ";
  if(retval) {
    cout << msg;
    cout << flush;
  }
#endif
  
} // TRACE              

//
//-------------------------------------------------------------------------
// Function       : void DEBUG(const string& method, const char* fmt, ...)
//
// Implementation : log to stdout if compiled with _DEBUG
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void DEBUG(const string& method, const char* fmt, ...)
{
#ifdef _DEBUG
  char msg[1024];
  va_list ap;
  va_start (ap, fmt);
  int retval = vsnprintf(msg, 1023, fmt, ap);
  va_end (ap);

  cout << "DEBUG " << method << " ";
  if(retval) {
    cout << msg;
    cout << flush;
  }
#endif
  
} // DEBUG


//
//-------------------------------------------------------------------------
// Function       : void SYSLOG(int code, const char* fmt, ...)
//
// Implementation : log to stdout if compiled with _DEBUG otherwise
//                  send to the system log daemon
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void SYSLOG(int code, const char* fmt, ...)
{
  char msg[1024];
  va_list ap;
  va_start (ap, fmt);
  int retval = vsnprintf(msg, 1023, fmt, ap);
  va_end (ap);
  
  if(retval) {
#ifndef _DEBUG
    syslog(code, "%s", msg);
#else
    cout << msg << endl;
#endif
  }
  
} // SYSLOG


//
//-------------------------------------------------------------------------
// Function       :void makeTimespec(int nTimeout /* ms */,
//                                   struct timespec& ts)
//
//
// Implementation : Returns a timespec struct to be used in a
//                  pthread_cond_timedwait. nTimeout must be in 
//                  milliseconds.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
void makeTimespec(int nTimeout /* ms */, struct timespec& ts)
{
  const long billion = 1000000000L;
  
  struct timespec interval;
  
  interval.tv_sec = nTimeout / 1000;
  interval.tv_nsec = (nTimeout % 1000) * 1000000L;
  
  struct timeval now;
  gettimeofday(&now, NULL);
  ts.tv_sec = now.tv_sec;
  ts.tv_nsec = now.tv_usec * 1000;
  
  if((ts.tv_nsec += interval.tv_nsec) >= billion) {
    ts.tv_nsec -= billion;
    ts.tv_sec += 1;
  }

  ts.tv_sec += interval.tv_sec;
  
} // makeTimespec
