//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : utils.h
//
// Version          : $Id: utils.h,v 1.2 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Some utility functions I needed to do various
//                    string manipulations and read/write all data
//                    to file descriptors. Basically these are functions
//                    that do not have a home and can be used by anyone.
//
// Revision History : 
//
// $Log: utils.h,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __UTILS_H_
#define __UTILS_H_

#include <string>
#include <unistd.h>

string trimLeft(const string &value);
string trimRight(const string &value);

ssize_t Read(int fd, void* buf, size_t count);
ssize_t Write(int fd, const void* buf, size_t count);

void traceBegin(const string& method);
void traceEnd(const string& method);
void TRACE(const string& method, const char* fmt, ...);
void DEBUG(const string& method, const char* fmt, ...);
void SYSLOG(int code, const char* fmt, ...);

void makeTimespec(int nTimeout /* ms */, struct timespec& ts);

#endif // __UTILS_H_

