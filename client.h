//*****************************************************************************
//
// Copyright (C) 2001 Pear Gear, Inc.  All rights reserved.
//
// Programmer       : Steve Connet
//                    Feb. 9, 2001
//
// Source File Name : client.h
//
// Version          : $Id: $
//
// File Overview    : Non-concurrent client connection
//                    This object *is* the client connection and is 
//                    smart enough to know how to send pings, disconnection
//                    notices, search results, etc, etc. 
//                    Every send is surrounded by a mutex lock so sending
//                    to this client from different threads is safe
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <pthread.h>

class CClient
{
    friend class CPollClients;

  public:
    CClient();
    CClient(int fd, int nPort, char* sIpAddr, char* sHostname = NULL);
    virtual ~CClient();

    void Init(int fd, int nPort, char* sIpAddr, char* sHostname = NULL);
    inline int operator<<(int nMsg) { return SendMessage(nMsg); }
    inline int operator>>(int& nMsg) { return ReadMessage(nMsg); }

    // access methods
    inline int Lock() { pthread_mutex_lock(&m_lock); return m_fd; }
    inline void Unlock() { pthread_mutex_unlock(&m_lock); }
    inline int GetPort() { return m_nPort; }
    inline char* GetHostname() { return m_sHostname; }
    inline char* GetIpAddr() { return m_sIpAddr; }

    inline void SetGracefulShutdown(bool bGracefulShutdown = true) 
        { m_bGracefulShutdown = bGracefulShutdown; }
    
// TODO:
//    int SendSearchResult(...);
//    int SendUserId(...);

  private:
    int SendMessage(int nMsg);
    int ReadMessage(int& nMsg);

  private:
    pthread_mutex_t m_lock;
    int m_fd;
    int m_nPort;
    char m_sHostname[256];
    char m_sIpAddr[16];
    bool m_bGracefulShutdown;
};

#endif // __CLIENT_H_


/* 
IRON MAIDEN:
... the doors shut slowly, so that the very sharp points penetrated his arms, 
and his legs in several places, and his belly and chest, and his bladder and 
the root of his member, and his eyes, and his shoulders, and his buttocks, 
but not enough to kill him; and so he remained making great cry and lament 
for two days, after which he died.
*/
