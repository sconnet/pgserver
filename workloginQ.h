//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 22, 2001
//
// Source File Name : workloginQ.h
//
// Version          : $Id: $
//
// File Overview    : Process clients on the login queue
//
// Revision History : 
//
// $Log: $
//
//
//*****************************************************************************

#ifndef __WORKLOGINQ_H_
#define __WORKLOGINQ_H_

#include "work.h"

class CWorkLoginQ : public CWork
{
 public:
  CWorkLoginQ() {}
  virtual ~CWorkLoginQ() {}
  
 private:
  void ProcessQueue();
};

#endif // __WORKLOGINQ_H_
