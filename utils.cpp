//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : utils.cpp
//
// Version          : $Id: $
//
// File Overview    : Implementation of the utility functions.
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifdef _DEBUG_
#include <stdio.h> // for debug msg's
#endif //_DEBUG_

#include "utils.h"
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//
//-------------------------------------------------------------------------
// Function       : char *strrev(char* str)
//
// Implementation : Reverse the passed character string. The passed string
//                  must be NULL terminated. Returns a pointer to the
//                  beginning of the reversed string.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
char* strrev(char* str)
{
    char *p1 = NULL;
    char *p2 = NULL;

    if (! str || ! *str)
        return str;

    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }

    return (str);

} // strrev


//
//-------------------------------------------------------------------------
// Function       : char* trim_left(char* p)
//
// Implementation : Moves the passed pointer forward until there are
//                  no more spaces. Returns the incremented pointer.
//                  Do not use this with dynamically allocted strings.
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
char* trim_left(char* p)
{
    while(isspace(*p))
        ++p;
    
    return (p);

} // trim_left


//
//-------------------------------------------------------------------------
// Function       : char* trim_right(char* p)
//
// Implementation : Reverses the string then calles trim_left. 
//                  Returns the incremented pointer. 
//
// Author         : Steve Connet
//
//-------------------------------------------------------------------------
//
char* trim_right(char* p)
{
    return strrev(trim_left(strrev(p)));

} // trim_right


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
  size_t nBytes = 0;

  // keep reading until we read everything
  while(nTotal < count)
  {
     // bail out if there is an error reading
     // 0 indicates EOF (client disconnected)
     if((nBytes = read(fd, (char*)buf + nTotal, count - nTotal)) <= 0)
     {
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
   size_t nBytes = 0;

   // keep writing until we write everything
   while(nTotal < count)
   {
      if((nBytes = write(fd, (char*)buf + nTotal, count - nTotal)) <= 0)
      {
         nTotal = nBytes;
         break;
      }
      else
         nTotal += nBytes;
   }

   return nTotal;

} // Write
