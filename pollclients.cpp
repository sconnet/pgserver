#include "pgserver.h"
#include "pollclients.h"
#include "clientQ.h"

#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

extern CClientQ g_commQ;
extern CPollClients g_PollClients;

CPollClients::CPollClients() :
  m_nMaxFd(0)
{
    pthread_mutex_init(&m_lock, NULL);
    FD_ZERO(&m_clients);
}

CPollClients::~CPollClients()
{
    pthread_mutex_destroy(&m_lock);
    FD_ZERO(&m_clients);
    m_map.clear();
}

void CPollClients::Start()
{
    CThread::Start();

} // Start

void CPollClients::Stop()
{
  //    cerr << "CPollClients::Stop <--" << endl;

    CThread::Stop();
    //    cerr << "CPollClients::Stop -->" << endl;

} // Stop

int CPollClients::Size()
{
    pthread_mutex_lock(&m_lock);
    int nSize = m_map.size();
    pthread_mutex_unlock(&m_lock);
    return nSize;

} // Size

void CPollClients::Insert(CClient* pClient)
{
  //    cerr << "CPollClients::Insert <--" << endl;

    pthread_mutex_lock(&m_lock);
    m_map[pClient->m_fd] = pClient;
    pthread_mutex_unlock(&m_lock);

    FD_SET(pClient->m_fd, &m_clients);
    if(m_nMaxFd <= pClient->m_fd)
        m_nMaxFd = pClient->m_fd;

    //    cerr << "CPollClients::Insert --> " << m_nMaxFd << endl;

} // Insert

void CPollClients::Erase(CClient* pClient)
{
  //    cerr << "CPollClients::Erase <--" << endl;

    pthread_mutex_lock(&m_lock);
    m_map.erase(pClient->m_fd);
    pthread_mutex_unlock(&m_lock);

    FD_CLR(pClient->m_fd, &m_clients);

    //cerr << "CPollClients::Erase -->" << endl;

} // Erase

void CPollClients::DisconnectAll()
{
  //    cerr << "PollClients Disconnecting ALL! <--" << endl;

    pthread_mutex_lock(&m_lock);
    ClientMap::iterator p = m_map.begin();
    while(p != m_map.end())
        delete (p++)->second;
    pthread_mutex_unlock(&m_lock);

    //    cerr << "PollClients Disconnecting ALL! -->" << endl;

} // DisconnectAll

void CPollClients::Thread()
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 250000; // 250ms

    // check for readable clients
    int fd_max = m_nMaxFd;
    fd_set read_set;
    memcpy(&read_set, &m_clients, sizeof(fd_set));
    int nResult = select(fd_max + 1, &read_set, NULL, NULL, &timeout);

    while(nResult != -1)
    {
        // check for kill event
        if(WaitForKillEvent(0))
            break;

        if(nResult > 0)
        {
            // find out which file descriptors are set
            pthread_mutex_lock(&m_lock);
            ClientMap::iterator p = m_map.begin();
            while(p != m_map.end())
            {
                if(FD_ISSET(p->second->m_fd, &read_set))
                {
                    // remove fd from master fd_set
                    FD_CLR(p->second->m_fd, &m_clients);

                    // insert client in queue to be read
                    g_commQ << p->second;
                }

                // check next fd
                p++;
            }
            pthread_mutex_unlock(&m_lock);
        }

        timeout.tv_sec = 0;
        timeout.tv_usec = 250000; // 250ms
        fd_max = m_nMaxFd;
        memcpy(&read_set, &m_clients, sizeof(fd_set));
        nResult = select(fd_max + 1, &read_set, NULL, NULL, &timeout);
    }

    //    cerr << "CPollClients::Thread BAILING!" << endl;
}
