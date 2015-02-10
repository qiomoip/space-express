#include "Connect.h"
#include "Session.h"
#include "Debug.h"

CConnect* CConnect::m_pInstance = NULL;

CConnect::CConnect(void)
{

}


CConnect::~CConnect(void)
{
	Destroy();
}

SOCKET	CConnect::GetClientSock()
{
	return m_Socket;
}


void CConnect::err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

int CConnect::Initialize()
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return -1;

	// socket()
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_Socket == INVALID_SOCKET)
	{
		err_quit("socket()");
	}
	int retval;

	ZeroMemory(&m_ServerAddr, sizeof(m_ServerAddr));
	m_ServerAddr.sin_family = AF_INET;
	m_ServerAddr.sin_addr.s_addr = inet_addr(SERVERIP);
	m_ServerAddr.sin_port = htons(SERVERPORT);
	retval = connect(m_Socket, (SOCKADDR *)&m_ServerAddr, sizeof(m_ServerAddr));
	if(retval == SOCKET_ERROR)
	{
		err_quit("connect()");
		return SOCKET_ERROR;
	}

	_SINGLE(CDebug)->AddLog(_T("서버에 접속된 상태입니다. 접속 성공 빠바바밤"));

	return retval;
}

void CConnect::Destroy()
{
	closesocket(m_Socket);
	// 윈속 종료
	WSACleanup();
}

void CConnect::SendInfo()
{
//서버에게 커넥트 요청을 할 때 내 데이터를 보낸다
	//WSASend(CConnect::GetInstance()->GetClientSock(), &SendWsa,1,&dwSend,0,&Ov_Send,NULL);
	MsgConnectAck* cConnectAck = new MsgConnectAck;
	//memset(cConnectAck, 0, sizeof(MsgConnectAck));
	strcpy(cConnectAck->playName, "테스트 데이터1");
	if(!_SINGLE(CSession).Onsend(cConnectAck, sizeof(MsgConnectAck)))
	{
		_SINGLE(CDebug)->AddLog(_T("안 보내짐"));
	}

	_SINGLE(CDebug)->AddLog(_T("데이터 보냄"));

	Safe_Delete(cConnectAck);
}