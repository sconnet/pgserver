//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 10, 2001
//
// Source File Name : workpool.cpp
//
// Version          : $Id: workpool.h,v 1.2 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Manages all the work thread objects by using a queue
//                    to keep track of them.
//
// Revision History : 
//
// $Log: workpool.h,v $
// Revision 1.2  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.1  2001/04/21 02:51:43  sconnet
// Initial revision
//
//
//*****************************************************************************

#ifndef __WORKPOOL_H_
#define __WORKPOOL_H_

#include "work.h"

#include <queue>
typedef queue<CWork*> workQ;

class CWorkPool
{
 public:
  CWorkPool() {}
  virtual ~CWorkPool() {}
  
  inline int size() { return m_queue.size(); }
  
  virtual void start();
  virtual void stop();
  
 private:
  workQ m_queue;
  void fire();
  void hire(CWork* pWork);
};

#endif // __WORKPOOL_H_
