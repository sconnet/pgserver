//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 22, 2001
//
// Source File Name : workcommQ.h
//
// Version          : $Id: $
//
// File Overview    : Process clients on the comm queue
//
// Revision History : 
//
// $Log: $
//
//
//*****************************************************************************

#ifndef __WORKCOMMQ_H_
#define __WORKCOMMQ_H_

#include "work.h"

class CWorkCommQ : public CWork
{
 public:
  CWorkCommQ() {}
  virtual ~CWorkCommQ() {}
  
 private:
  void ProcessQueue();
};

#endif // __WORKCOMMQ_H_
