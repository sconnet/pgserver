//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 8, 2001
//
// Source File Name : acceptclient.h
//
// Version          : $Id: acceptclient.h,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Handle accepted client
//
// Revision History : 
//
// $Log: acceptclient.h,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __ACCEPTCLIENT_H_
#define __ACCEPTCLIENT_H_

#include "listen.h"
#include "client.h"

class CAcceptClient : public CListen
{
 public:
  CAcceptClient() {}
  virtual ~CAcceptClient() {}
  
  void start();
  void stop(bool waitForThreadJoin = true);
  
 private:
  void onAccept(const CClient& client);
};

#endif // __ACCEPTCLIENT_H_

