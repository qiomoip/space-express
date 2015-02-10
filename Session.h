#pragma once

#include "Sync.h"
#include "define.h"
#include "protocol.h"


//중첩 IO를 위한 구조체 및 Flag값 설정
#define IOCP_SEND 0
#define IOCP_RECV 1

typedef struct	OVERLAPPEDEX : OVERLAPPED
{
	DWORD	flags; //작업 확인용
}OVERLAPPEDEX;

class CSession
{
private:
	CSession();
	~CSession();

	CCriticalSection	m_Sync;
	OVERLAPPEDEX		Ov_Recv;
	OVERLAPPEDEX		Ov_Send;
	WSABUF				SendWsa,RecvWsa;
	WSAEVENT			RecvEvent;
	char				RecvBuffer[BUFFERSIZE];
	DWORD				m_receivedByte;
	
		
public:
	static CSession&	GetInstance();
	


	void			EventSelect();
	void			DisPatchReceive();
	void			Close();
	bool			IsValidPacket(char* packet);
	void			Dispatch(char* packet);
	BOOL			Onsend(void* packet,int size);

	bool			MSG_Connect_Req( char *NewID);	
	char*			MSG_Connect_Ack(char* recvPacket);

	void			MSG_DisConnect_Req(char *NewID);
	char*			MSG_DisConnect_Ack(char* recvPacket);

	void			MSG_Move_Ack_Fun(char* recvPacket);
	void			MSG_CharMove_Req(char *NewID, Position &NewPositionX);
	void			MSG_Crash_Req(char *NewID);
	
//	bool			GetFlage(){return SessionFlag;}
};

//#pragma once
//
//#include "Sync.h"
//#include "stdafx.h"
//
////중첩 IO를 위한 구조체 및 Flag값 설정
//#define IOCP_SEND 0
//#define IOCP_RECV 1
//
//typedef struct	OVERLAPPEDEX : OVERLAPPED
//{
//	DWORD	flags; //작업 확인용
//}OVERLAPPEDEX;
//
//
//class CSession
//{
//private:
//	CSession();
//	~CSession();
//
//	CCriticalSection	m_Sync;
//	OVERLAPPEDEX		Ov_Recv;
//	OVERLAPPEDEX		Ov_Send;
//	WSABUF				SendWsa,RecvWsa;
//	WSAEVENT			RecvEvent;
//	char				RecvBuffer[BUFFERSIZE];
//	DWORD				m_receivedByte;
//	
//	int					Count;
//
//	
//	bool				m_SendRoomEnter;
//	
//		
//public:
//	static CSession&	GetInstance();
//
//	bool				EnemyReady;
//	bool				SessionFlag;
//	bool				m_bCreateRoom;
//	bool				GameStart;
//	bool				HeroReady;
//	bool				EnemyCheck;
//	bool				Result;
//	float				EnemyX;
//
//
//	void			EventSelect();
//	void			DisPatchReceive();
//	void			Close();
//	bool			IsValidPacket(char* packet);
//	void			Dispatch(char* packet);
//	BOOL			Onsend(void* packet,int size);
//
//	float			GetPosEnemyX(){return EnemyX;}
//
//	bool			MSG_Connect_Req( char *NewID);	
//	char*			MSG_Connect_Ack(char* recvPacket);
//
//	void			MSG_DisConnect_Req(char *NewID);
//	char*			MSG_DisConnect_Ack(char* recvPacket);
//
//	void			MSG_Move_Ack_Fun(char* recvPacket);
//	void			MSG_CharMove_Req(char *NewID, Position &NewPositionX);
//	void			MSG_Crash_Req(char *NewID);
//	
////	char*			MSG_Enter_Room_Ack(char* recvPacket);
////	void			MSG_Enter_Room_Req(char* NewID);
//
//	void			MSG_Enter_Lobby_Req( char *NewID);
//	void			MSG_EnterLobby_Ack_Fun(char* recvPacket);
//
//	void			MSG_LeaveLobby_Ack_Fun(char* recvPacket);
//
//	bool			MSG_CreateRoom_Req( char *NewID, int MaximumNum );
//
//	void			MSG_EnterRoom_Req( char *NewID, int RoomID );
//
//	void			MSG_UserList_Ack_Fun(char* recvPacket);	
//	void			MSG_Ready_Ack_Fun(char* recvPacket);
//	bool			MSG_Ready_Req( BOOL NewReadyState );
//	//bool			MSG_Ready_Ack_Fun( char* recvPacket );
//	void			MSG_StartComplete_Req_Fun();
//	void			MSG_StartCompleteAck_Fun(char* recvPacket);				
//	bool			MSG_Crash_Ack_fun(/*char* recvPacket*/);
//	//bool			MSG_Match_Req(char *NewID);
//	//void			MSG_Match_Ack(char* recvPacket);
//	bool			GetFlage(){return SessionFlag;}
//};

