//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    April 20, 2001
//
// Source File Name : lock.h
//
// Version          : $Id: $
//
// File Overview    : Base class for locking mechanism
//
// Revision History : 
//
// $Log: $
//
//
//*****************************************************************************

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
