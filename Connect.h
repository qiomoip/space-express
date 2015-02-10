#pragma once

#include "Sync.h"
#include "define.h"
#include "protocol.h"

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    512

class CConnect
{
private:
	static CConnect*	m_pInstance;

	SOCKET		m_Socket;
	SOCKADDR_IN m_ServerAddr;

public:
	SOCKET		GetClientSock();

	int	Initialize();
	void SendInfo();

	void Destroy();

	void err_quit(char *msg);

public:
	static CConnect* GetInstance()
	{
		if(!m_pInstance)
		{
			m_pInstance = new CConnect;
		}
		return m_pInstance;
	}
	static void KillInstance()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
private:
	CConnect(void);
	~CConnect(void);
};


