//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : utils.h
//
// Version          : $Id: $
//
// File Overview    : Some utility functions I needed to do various
//                    string manipulations and read/write all data
//                    to file descriptors. Basically these are functions
//                    that do not have a home and can be used by anyone.
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __UTILS_H_
#define __UTILS_H_

#include <unistd.h>

char* strrev(char* str);
char* trim_left(char* p);
char* trim_right(char* p);

ssize_t Read(int fd, void* buf, size_t count);
ssize_t Write(int fd, const void* buf, size_t count);

#endif // __UTILS_H_


//*****************************************************************************
//
// Security Classification: UNCLASSIFIED
//                                   
