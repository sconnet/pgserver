//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : work.h
//
// Version          : $Id: work.h,v 1.1 2001/04/21 02:51:43 sconnet Exp sconnet $
//
// File Overview    : Multiple work thread objects are spawned by
//                    the WorkPool object. The purpose of the
//                    work thread object is to check for clients on the
//                    login queue and for clients ready to communication
//                    on the commQ
//
// Revision History : 
//
// $Log: work.h,v $
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __WORK_H_
#define __WORK_H_

#include "thread.h"

class CWork : public CThread
{
 public:
  CWork() {}
  virtual ~CWork() {}
  
  void start();
  void stop(bool waitForThreadJoin = true);

 private:
  virtual void ProcessQueue() = 0;  
  void thread();
};

#endif // __WORK_H_
