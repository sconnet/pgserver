#ifndef __POLLCLIENTS_H_
#define __POLLCLIENTS_H_

#include "thread.h"
#include "client.h"

#include <map>
typedef map<int, CClient*> ClientMap;

class CPollClients : public CThread
{
  public:
    CPollClients();
    virtual ~CPollClients();

    inline void operator<<(CClient* pClient) { Insert(pClient); }
    inline void operator>>(CClient* pClient) { Erase(pClient); }

    int Size();
    void DisconnectAll();

    virtual void Start();
    virtual void Stop();

  private:
    virtual void Thread();
    void Insert(CClient* pClient);
    void Erase(CClient* pClient);

  private:
    ClientMap m_map;
    fd_set m_clients;
    pthread_mutex_t m_lock;
    int m_nMaxFd;
};

#endif // __POLLCLIENTS_H_
