//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : acceptstats.h
//
// Version          : $Id: acceptstats.h,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : spew stats out to a newly connected client
//
// Revision History : 
//
// $Log: acceptstats.h,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __ACCEPTSTATS_H_
#define __ACCEPTSTATS_H_

#include "listen.h"
#include "client.h"

class CAcceptStats : public CListen
{
 public:
  CAcceptStats();
  virtual ~CAcceptStats() {}
  
  void start();
  void stop(bool waitForThreadJoin = true);
  
 private:
  void onAccept(const CClient& client);
};

#endif // __ACCEPTSTATS_H_
