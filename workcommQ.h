//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 22, 2001
//
// Source File Name : workcommQ.h
//
// Version          : $Id: workcommQ.h,v 1.1 2001/04/23 01:05:46 sconnet Exp sconnet $
//
// File Overview    : Process clients on the comm queue
//
// Revision History : 
//
// $Log: workcommQ.h,v $
// Revision 1.1  2001/04/23 01:05:46  sconnet
// Initial revision
//
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
  void ProcessQueue(CClient& client) const;
};

#endif // __WORKCOMMQ_H_
