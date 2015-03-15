//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 22, 2001
//
// Source File Name : workloginQ.h
//
// Version          : $Id: workloginQ.h,v 1.1 2001/04/23 01:05:46 sconnet Exp sconnet $
//
// File Overview    : Process clients on the login queue
//
// Revision History :
//
// $Log: workloginQ.h,v $
// Revision 1.1  2001/04/23 01:05:46  sconnet
// Initial revision
//
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
    void ProcessQueue(CClient &client) const;
};

#endif // __WORKLOGINQ_H_
