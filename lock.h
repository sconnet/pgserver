//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 20, 2001
//
// Source File Name : lock.h
//
// Version          : $Id: lock.h,v 1.3 2001/04/23 01:05:46 sconnet Exp $
//
// File Overview    : Base class for locking mechanism
//
// Revision History : 
//
// $Log: lock.h,v $
// Revision 1.3  2001/04/23 01:05:46  sconnet
// continued development
//
// Revision 1.2  2001/04/21 06:11:38  sconnet
// added gaurds
//
// Revision 1.1  2001/04/21 04:30:24  sconnet
// Initial revision
//
//
//
//*****************************************************************************

#ifndef __LOCK_H_
#define __LOCK_H_

#include <pthread.h>

class CLock
{
 protected:
  CLock() { pthread_mutex_init(&m_lock, NULL); }
  virtual ~CLock() { pthread_mutex_destroy(&m_lock); }
  
  virtual void lock() const { pthread_mutex_lock(&m_lock); }
  virtual void unlock() const { pthread_mutex_unlock(&m_lock); }
  virtual bool trylock() const { return pthread_mutex_trylock(&m_lock) == 0; }
  
 private:
  mutable pthread_mutex_t m_lock;
};

#endif // __LOCK_H_
