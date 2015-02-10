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

	_SINGLE(CDebug)->AddLog(_T("������ ���ӵ� �����Դϴ�. ���� ���� ���ٹٹ�"));

	return retval;
}

void CConnect::Destroy()
{
	closesocket(m_Socket);
	// ���� ����
	WSACleanup();
}

void CConnect::SendInfo()
{
//�������� Ŀ��Ʈ ��û�� �� �� �� �����͸� ������
	//WSASend(CConnect::GetInstance()->GetClientSock(), &SendWsa,1,&dwSend,0,&Ov_Send,NULL);
	MsgConnectAck* cConnectAck = new MsgConnectAck;
	//memset(cConnectAck, 0, sizeof(MsgConnectAck));
	strcpy(cConnectAck->playName, "�׽�Ʈ ������1");
	if(!_SINGLE(CSession).Onsend(cConnectAck, sizeof(MsgConnectAck)))
	{
		_SINGLE(CDebug)->AddLog(_T("�� ������"));
	}

	_SINGLE(CDebug)->AddLog(_T("������ ����"));

	Safe_Delete(cConnectAck);
}