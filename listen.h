//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : listen.cpp
//
// Version          : $Id: listen.h,v 1.2 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Listens for incoming connections
//
// Revision History : 
//
// $Log: listen.h,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __LISTEN_H_
#define __LISTEN_H_

/*
  Abstract class
 */

#include "thread.h"
#include "client.h"

class CListen : public CThread
{
 public:
  CListen() {}
  virtual ~CListen() {}
  
  void init(int nPort, int nTimeout = 1000 /* ms */);
  void start();
  
  void displayLocalHost();
  
  int timeout() { return m_nTimeout; }
  void thread();
  
 private:
  int m_listenfd;             // listening socket
  int m_nTimeout;
  int m_nPort;

  // must be overidden by subclass to handle accepted connections
  virtual void onAccept(const CClient& client) = 0;
};

#endif // __LISTEN_H_
