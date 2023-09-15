#pragma once

#include <string>
#include <map>
#include "win2unix.h"
//#include <hash_map>

#define WM_HEARTBEAT_MESSAGE        WM_USER + 4

/** Ŭ���̾�Ʈ�� ��ε�ĳ���� �� �� ����� ������ �����Ѵ�.
 *
 */
using namespace std;
class CBroadCastMgr
{
public:
    CBroadCastMgr(void);
    ~CBroadCastMgr(void);

public:
    SOCKET      GetHandle (void)  {
        return m_hSock;
    }

public:
	pthread_t m_handle;
    bool        Prepare (int iPort);
    //bool        Process (WPARAM wParam, LPARAM lParam);
    //bool        Process (void);
    bool        Process (SOCKET cli_fd, UINT fd_status);
    void        Close (void);
    int         Update (std::string name);
    bool        Delete (std::string name);
	static void *Start(void *arg);
	bool        CheckArrivedAtClient (std::string name);

#ifndef __ORG__
private:
	bool        UpdateAddress (std::string name, SOCKADDR_IN* pAddr);
#endif

private:
	int mPort;
    SOCKET                              m_hSock;
    map<string, int>  m_hashNameToIndex;
    //stdext::hash_map<std::string, int>  m_hashNameToIndex;
};

extern CBroadCastMgr g_BroadCastMgr;
