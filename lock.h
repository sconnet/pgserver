//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 20, 2001
//
// Source File Name : lock.h
//
// Version          : $Id: lock.h,v 1.1 2001/04/21 04:30:24 sconnet Exp sconnet $
//
// File Overview    : Base class for locking mechanism
//
// Revision History : 
//
// $Log: lock.h,v $
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
  CLock() { pthread_mutex_init(&lock_, NULL); }
  virtual ~CLock() { pthread_mutex_destroy(&lock_); }
  
  virtual void lock() { pthread_mutex_lock(&lock_); }
  virtual void unlock() { pthread_mutex_unlock(&lock_); }
  virtual bool trylock() { return pthread_mutex_trylock(&lock_) == 0; }
  
 private:
  pthread_mutex_t lock_;
};

#endif // __LOCK_H_
