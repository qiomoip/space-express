
#include "Session.h"
#include "Connect.h"

#include "Debug.h"


CSession::CSession()
{
	//SessionFlag = false;
	
	//Count = 0;
	//HeroReady = false;
	//EnemyCheck = false;
	//Result = false;
	RecvEvent = ::WSACreateEvent();
	::ZeroMemory(RecvBuffer,sizeof(RecvBuffer));
}

CSession::~CSession()
{
}

CSession& CSession::GetInstance()
{
	static CSession Instance;
	return Instance;
}

void CSession::EventSelect()
{
	::WSANETWORKEVENTS	NetEvent;

	//���Ͽ� �߻��� �̺�Ʈ �˻�
	::ZeroMemory(&NetEvent,sizeof(NetEvent));
	CConnect* pConnect = CConnect::GetInstance();
	SOCKET sock = pConnect->GetClientSock();
	::WSAEventSelect(sock,RecvEvent,FD_READ | FD_CLOSE);
	//::WSAEventSelect(CConnect::GetInstance()->GetClientSock(),RecvEvent,FD_READ | FD_CLOSE);
	::WSAEnumNetworkEvents(CConnect::GetInstance()->GetClientSock(),RecvEvent,&NetEvent);

	if((NetEvent.lNetworkEvents & FD_READ) == FD_READ)
	{
		DisPatchReceive();
	}
	else if((NetEvent.lNetworkEvents & FD_CLOSE) == FD_CLOSE)
	{
		Close();
	}
}


void CSession::DisPatchReceive()
{
	CSynchronize	lock(m_Sync);

	int		retval = 0;
	DWORD	dwRecv,dwFlags = 0;

	//��ø IO�� �ʿ��� ����ü �� WSABUF �ʱ�ȭ
	ZeroMemory(&Ov_Recv,sizeof(OVERLAPPEDEX));
	ZeroMemory(&RecvWsa,sizeof(WSABUF));
	//WSABUF�� �ܺι��� ����
	RecvWsa.buf = RecvBuffer;
	RecvWsa.len = BUFFERSIZE;
	//�۾� ������ �˷��� flag�� ����
	Ov_Recv.flags = IOCP_RECV;
	m_receivedByte = 0;

	//��ø IO�ޱ� �۾� ��û
	retval = WSARecv(CConnect::GetInstance()->GetClientSock(),
									&RecvWsa,1,&dwRecv,&dwFlags,&Ov_Recv,NULL);

	if(retval == 0)
	{
		//�ѹ��� �ޱ� ����
	}
	else if(retval == SOCKET_ERROR && ::WSAGetLastError() == WSA_IO_PENDING)
	{
		//��ø IO��û ����
	}
	else
	{
		::closesocket(CConnect::GetInstance()->GetClientSock());
		//recv���� ����
	}

	//��Ŷó�� �κ�
	if(dwRecv > 0)
	{
		m_receivedByte += dwRecv;
	}

	while(m_receivedByte > 0)
	{
		char buffer[BUFFERSIZE] = {0,};

		if(IsValidPacket(RecvBuffer))
		{
			PacketHeader* header = (PacketHeader*)RecvBuffer;
			Dispatch(RecvBuffer);
			
			//MsgMoveAck* Msg_Move_Ack = (MsgMoveAck*)packet;

			//cout<<Msg_Move_Ack->pos.x<<endl;
			memcpy(buffer, RecvBuffer+header->size, m_receivedByte);
			memcpy(RecvBuffer,buffer,sizeof(buffer));
		}
		else
		{
			break;
		}
	}
}

bool CSession::IsValidPacket(char *packet)
{
	if(m_receivedByte >= sizeof(PacketHeader))
	{
		PacketHeader* header = (PacketHeader*)packet;
		if(header->size == 0)
		{
			return false;
		}
		if(header->size <= m_receivedByte)
		{
			return true;
		}
	}

	return false;
}

void CSession::Dispatch(char *packet)
{
	PacketHeader* recvPacket = (PacketHeader*)packet;
	
	//MsgMoveAck* Msg_Move_Ack = (MsgMoveAck*)packet;

	//cout<<Msg_Move_Ack->pos.x<<endl;

	switch(recvPacket->code)
	{
	case MSG_MOVE_ACK:
		MSG_Move_Ack_Fun(packet);
		break;
	

	case MSG_CONNECT_ACK:
		MSG_Connect_Ack(packet);
		break;

	//case MSG_ENTER_ROOM_ACK:
	//	MSG_Enter_Room_Ack(packet);
	//	break;
	//case MSG_USERLIST_ACK:
	//	MSG_UserList_Ack_Fun(packet);
	//	break;
	//case MSG_ENTERLOBBY_ACK:
	//	MSG_EnterLobby_Ack_Fun(packet);
	//	break;
	//case MSG_LEAVELOBBY_ACK:
	//	MSG_LeaveLobby_Ack_Fun(packet);
	//	break;
	//case MSG_READY_ACK: 
	//	MSG_Ready_Ack_Fun(packet);
	//	break;
	//case MSG_STARTCOMPLETE_ACK:
	//	MSG_StartCompleteAck_Fun(packet);
	//	break;
	//case MSG_CRASH_ACK:
	//	MSG_Crash_Ack_fun();
	//	break;



	default :
		break;
	}
}



BOOL CSession::Onsend(void* packet,int size)
{
	CSynchronize	lock(m_Sync);

	int		retval;
	DWORD	dwSend;
	//�ʱ�ȭ
	ZeroMemory(&Ov_Send,sizeof(OVERLAPPEDEX));
	Ov_Send.flags = IOCP_SEND;

	//�ܺι��� ����
	SendWsa.buf = (char*)packet;
	SendWsa.len = size;


	//��ø IO ������ �۾� ��û
	retval = WSASend(CConnect::GetInstance()->GetClientSock(), &SendWsa,1,&dwSend,0,&Ov_Send,NULL);

	if(retval == 0)
	{
		//cout<<dwSend<<"byte ���� ����"<<endl;
		return TRUE;
		//�ѹ��� ������ ����
	}
	else if(retval == SOCKET_ERROR && ::WSAGetLastError() == WSA_IO_PENDING)
	{
		//��ø IO��û ����
	}
	else
	{
		::closesocket(CConnect::GetInstance()->GetClientSock());
		//send ���� ����
	}

	return FALSE;
}

void CSession::Close()
{
	if(RecvEvent != INVALID_HANDLE_VALUE)
	{
		::WSACloseEvent(RecvEvent);
		RecvEvent = INVALID_HANDLE_VALUE;
	}

	shutdown(CConnect::GetInstance()->GetClientSock(),SD_BOTH);
	closesocket(CConnect::GetInstance()->GetClientSock());
}


void CSession::MSG_Move_Ack_Fun(char *recvPacket)
{
	MsgMoveAck* Msg_Move_Ack = (MsgMoveAck*)recvPacket;

	//EnemyCheck = true;
	//EnemyX = Msg_Move_Ack->pos.x;
	//cout<<"�� ��ǥ : "<<EnemyX<<endl;
	//cout<<Msg_Move_Ack->playName<<endl;
	//cout<<"�� �̵� : "<<SessionFlag<<endl;
	
	//SessionFlag = true;

	//return SessionFlag;
}

bool CSession::MSG_Connect_Req(char *NewID)
{
	MsgConnectReq Connect_Req;
	strcpy_s( Connect_Req.playName, NewID );
	if( Onsend((void *)&Connect_Req,sizeof(Connect_Req)) )
	{
//		cout << "[CONNECT REQUEST] : " << "���� ���� ��û ����." << std::endl;
		_SINGLE(CDebug)->AddLog(10, _T("���� ���� ��û ����."));
		return true;
	}
	else
	{
//		cout << "[CONNECT REQUEST] : " << "���� ���� ��û ����." << std::endl;
		_SINGLE(CDebug)->AddLog(10, _T("���� ���� ��û ����."));
		return false;
	}
}

void CSession::MSG_DisConnect_Req(char* NewID)
{
	MsgDisConnectReq Msg_DisConnect_Req;
	strcpy_s( Msg_DisConnect_Req .playName, NewID );
	Onsend((void *)&Msg_DisConnect_Req ,sizeof(Msg_DisConnect_Req));
}


void CSession::MSG_CharMove_Req(char *NewID, Position &NewPosition )
{
	MsgMoveReq Move_Req;
	strcpy_s(Move_Req.playName,NewID);
	memcpy(&Move_Req.pos, &NewPosition, sizeof(NewPosition));
	Onsend((void*)&Move_Req, sizeof(Move_Req));
}

void CSession::MSG_Crash_Req( char *NewID)
{
	MsgCrashReq Crash_Req;
	strcpy_s(Crash_Req.playName,NewID);
	//memcpy(&Move_Req.pos, &NewPosition, sizeof(NewPosition));
	Onsend((void*)&Crash_Req, sizeof(Crash_Req));
}

char* CSession::MSG_Connect_Ack(char* recvPacket)
{
	MsgConnectAck* Msg_Connect_Ack = (MsgConnectAck*)recvPacket;

	//strcpy_s( MsgConnectAck.playName, NewID );

	//cout << "["<<Msg_Connect_Ack->playName<<"���� �����ϼ���]\n"<<endl;

	TCHAR szRecv[100] = {0};

	MultiByteToWideChar(
		CP_ACP, MB_PRECOMPOSED, 
		recvPacket, 
		strlen(recvPacket) + 1,
		szRecv , 
		_tcslen(szRecv) + 1);

	TCHAR szRet[256] = _T("���� �����ߴ� ����");

	_tcscat_s(szRecv, szRet);

	_SINGLE(CDebug)->AddLog(11, szRecv);
	return Msg_Connect_Ack->playName;
}
//
//char* CSession::MSG_Enter_Room_Ack(char* recvPacket)
//{
//	MsgEnterRoomAck* Msg_EnterRoom_Ack = (MsgEnterRoomAck*)recvPacket;
//
//	//strcpy_s( MsgConnectAck.playName, NewID );
//	cout << "["<<Msg_EnterRoom_Ack->playName<<"���� �뿡 �����ϼ���]\n"<<endl;
//	
//	return Msg_EnterRoom_Ack->playName;
//}
//void CSession::MSG_Enter_Room_Req( char *NewID)
//{
//	MsgEnterRoomReq Msg_EnterRoom_Req;
//	strcpy_s(Msg_EnterRoom_Req.playName, NewID);
//	Onsend((void*)&Msg_EnterRoom_Req, sizeof(Msg_EnterRoom_Req));
//}
//void CSession::MSG_Enter_Lobby_Req( char *NewID)
//{
//	MsgEnterLobbyReq Msg_EnterLobby_Req;
//	strcpy_s(Msg_EnterLobby_Req.playName, NewID);
//	Onsend((void*)&Msg_EnterLobby_Req, sizeof(Msg_EnterLobby_Req));
//}
//
//void CSession::MSG_EnterLobby_Ack_Fun( char* recvPacket )
//{
//	MsgEnterLobbyAck* Msg_LobbyEnter_Ack = (MsgEnterLobbyAck*)recvPacket;
//	std::cout << "[ENTERLOBBY RECV] : " << "[" << Msg_LobbyEnter_Ack->playName << "]" << std::endl;
//
//	//g_GM.InsertUser( Msg_LobbyEnter_Ack->playName );
//}
//
//void CSession::MSG_LeaveLobby_Ack_Fun( char* recvPacket )
//{
//	MsgLeaveLobbyAck* Msg_LeaveLobby_Ack = (MsgLeaveLobbyAck*)recvPacket;
//	std::cout << "[LOBBY EXIT RECV] : " << "[" << Msg_LeaveLobby_Ack->playName << "]" << "����." << std::endl;
//
//	//g_GM.DeleteUser( Msg_LeaveLobby_Ack->playName );
//}
//
//bool CSession::MSG_CreateRoom_Req( char *NewID, int MaximumNum )
//{
//	MsgCreateRoomReq CreatRoom_Req;
//	strcpy_s( CreatRoom_Req.playName, NewID );
//	//strcpy_s( CreatRoom_Req.roomName, NewRoomName );
//	CreatRoom_Req.maxUserCount = MaximumNum;
//	if( Onsend((void *)&CreatRoom_Req,sizeof(CreatRoom_Req)) )
//	{
//		std::cout << "[CREATE_ROOM REQUEST] : " << "�� ���� ��û ����." << std::endl;
//		m_bCreateRoom = true;
//		return m_bCreateRoom;
//	}
//	else
//	{
//		std::cout << "[CREATE_ROOM REQUEST] : " << "�� ���� ��û ����." << std::endl;
//		m_bCreateRoom = false;
//		return m_bCreateRoom;
//	}
//}
//void CSession::MSG_EnterRoom_Req( char *NewID, int RoomID )
//{
//	if( !m_SendRoomEnter )
//	{
//		MsgEnterRoomReq EnterRoom_Req;
//		strcpy_s( EnterRoom_Req.playName, NewID );
//		EnterRoom_Req.roomIndex = RoomID;
//
//		if( Onsend( ( void * )&EnterRoom_Req, sizeof( EnterRoom_Req ) ) )
//			std::cout << "[ENTER_ROOM REQUEST] : " << "�� ���� ��û ����." << std::endl;
//		else
//			std::cout << "[ENTER_ROOM REQUEST] : " << "�� ���� ��û ����." << std::endl;
//
//		m_SendRoomEnter = TRUE;
//	}
//}
//
//void CSession::MSG_UserList_Ack_Fun( char* recvPacket )
//{
//	MsgUserListAck* Msg_UserList_Ack = (MsgUserListAck*)recvPacket;
//	std::cout << "[USERLIST RECV] : " << Msg_UserList_Ack->userList << std::endl;
//	//g_GM.InsertUser( Msg_UserList_Ack->userList );
//}
//
//bool CSession::MSG_Ready_Req( BOOL NewReadyState )
//{
//	MsgReadyReq Ready_Req;
//	Ready_Req.readyState = NewReadyState;
//	if( Onsend((void *)&Ready_Req,sizeof(Ready_Req)) )
//	{
//		if( !NewReadyState )
//		{
//			std::cout << "[READY REQUEST] : " << "�غ� ���� ���� ��û." << std::endl;
//			return false;
//		}
//		else
//		{
//			std::cout << "[READY REQUEST] : " << "�غ� ���� ��û." << std::endl;
//			return true;
//		}
//	}
//	else
//	{
//		std::cout << "[READY REQUEST] : " << "�غ� ���� ��û ����." << std::endl;
//		return false;
//	}
//}
//
//void CSession::MSG_Ready_Ack_Fun( char* recvPacket )
//{
//	MsgReadyAck * Msg_Ready_Ack = (MsgReadyAck*)recvPacket;
//	EnemyReady = true;
//	if( Msg_Ready_Ack->readyState)
//	{
//		std::cout << "[READY RECV] : " << "[" << Msg_Ready_Ack->playName << "]" << "�غ�." << std::endl;
//	}
//	else
//	{
//		std::cout << "[READY RECV] : " << "[" << Msg_Ready_Ack->playName << "]" << "�غ� ����." << std::endl;
//		//return EnemyReady;
//	}
//}
//
//void CSession::MSG_StartComplete_Req_Fun( )
//{
//	//MsgPlayGameInfoAck *Msg_PlayGameInfo_Ack = (MsgPlayGameInfoAck*)recvPacket;
//	//std::cout << "[ALLGAMEINFO_INFO RECV] : " << "��� ���� ����." << std::endl;
//
//	MsgStartCompleteReq Msg_StartComplete_Req;
//	
//	if( Onsend( ( void * )&Msg_StartComplete_Req, sizeof( Msg_StartComplete_Req ) ) )
//		std::cout << "[STARTCOMPLETE REQUEST] : " << "���� ��� ��û ����." << std::endl;
//	else
//		std::cout << "[STARTCOMPLETE REQUEST] : " << "���� ��� ��û ����." << std::endl;
//}
//
//void CSession::MSG_StartCompleteAck_Fun(char* recvPacket)
//{
//	MsgStartCompleteAck Msg_StartComplete_Ack;
//	GameStart = true;
//}
//
//bool CSession::MSG_Crash_Ack_fun(/*char* recvPacket*/)
//{
//	Result = true;
//	return Result;
//}
//void CSession::MSG_Ready_Ack_Fun( char* recvPacket )
//{
//	MsgReadyAck * Msg_Ready_Ack = (MsgReadyAck*)recvPacket;
//	if( Msg_Ready_Ack->readyState )
//		std::cout << "[READY RECV] : " << "[" << Msg_Ready_Ack->playName << "]" << "�غ�." << std::endl;
//	else
//		std::cout << "[READY RECV] : " << "[" << Msg_Ready_Ack->playName << "]" << "�غ� ����." << std::endl;
//}