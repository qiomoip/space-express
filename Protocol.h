#pragma once


const INT  g_PlayerNameLEN = 256;

enum PACKET_TYPE
{
	MSG_CONNECT_ACK = 100,	MSG_CONNECT_REQ,
	MSG_DISCONNECT_ACK,		MSG_DISCONNECT_REQ,

	MSG_CREATEROOM_ACK,		MSG_CREATEROOM_REQ,
	MSG_ROOMLIST_ACK,		MSG_ROOMLIST_REQ,

	MSG_READY_ACK,			MSG_READY_REQ,
	MSG_USERLIST_ACK,		MSG_USERLIST_REQ,
	MSG_ENTER_ROOM_ACK,		MSG_ENTER_ROOM_REQ,
	MSG_LEAVE_ROOM_ACK,		MSG_LEAVE_ROOM_REQ,
	MSG_ENTERLOBBY_ACK,		MSG_ENTERLOBBY_REQ,
	MSG_LEAVELOBBY_ACK,		MSG_LEAVELOBBY_REQ,

	MSG_STARTCOMPLETE_ACK,	MSG_STARTCOMPLETE_REQ,

	MSG_MOVE_ACK,			MSG_MOVE_REQ,
	MSG_CRASH_ACK,			MSG_CRASH_REQ,
	MSG_MATCH_ACK,			MSG_MATCH_REQ
};



class PacketHeader
{
public:
	WORD size;
	PACKET_TYPE code;
};

struct Position
{
	float x;
	//float y;
	//float r;
	Position() {}
	Position(float nx)
	{
		x = nx;
	//	y = ny;
	}
};

class MsgConnectAck : public PacketHeader
{
public:
	MsgConnectAck()
	{
		size = sizeof( MsgConnectAck );
		code = MSG_CONNECT_ACK;
		memset( playName, 0, sizeof( playName ) );
	}
	char playName[ g_PlayerNameLEN ];
};

class MsgConnectReq : public PacketHeader
{
public:
	MsgConnectReq()
	{
		size = sizeof( MsgConnectReq );
		code = MSG_CONNECT_REQ;
		memset( playName, 0, sizeof( playName ) );
		
	}
	char playName[ g_PlayerNameLEN ];
};

class MsgDisConnectAck: public PacketHeader
{
public:
	MsgDisConnectAck()
	{
		size = sizeof( MsgDisConnectAck );
		code = MSG_DISCONNECT_ACK;
		memset( playName, 0, sizeof( playName ) );
	}
	char playName[ g_PlayerNameLEN ];
};

class MsgDisConnectReq: public PacketHeader
{
public:
	MsgDisConnectReq()
	{
		size = sizeof( MsgDisConnectReq );
		code = MSG_DISCONNECT_REQ;
		memset( playName, 0, sizeof( playName ) );
	}
	char playName[ g_PlayerNameLEN ];
};

class MsgMoveAck : public PacketHeader
{
public:
	MsgMoveAck()
	{
		size = sizeof( MsgMoveAck );
		code = MSG_MOVE_ACK;		
	}
	char playName[ g_PlayerNameLEN ];
	Position pos;
};

class MsgMoveReq : public PacketHeader
{
public:
	MsgMoveReq()
	{
		size = sizeof( MsgMoveReq );
		code = MSG_MOVE_REQ;
	}
	char playName[ g_PlayerNameLEN ];
	Position pos;
};

class MsgCrashAck: public PacketHeader
{
public:
	MsgCrashAck()
	{
		size = sizeof( MsgCrashAck );
		code = MSG_CRASH_ACK;
		memset( playName, 0, sizeof( playName ) );
	}
	char playName[ g_PlayerNameLEN ];
};
class MsgCrashReq: public PacketHeader
{
public:
	MsgCrashReq()
	{
		size = sizeof( MsgCrashReq );
		code = MSG_CRASH_REQ;
		memset( playName, 0, sizeof( playName ) );
	}
	char playName[ g_PlayerNameLEN ];
};

class MsgEnterRoomAck : public PacketHeader
{
public:
	MsgEnterRoomAck()
	{
		size = sizeof( MsgEnterRoomAck );
		code = MSG_ENTER_ROOM_ACK;
		memset( playName, 0, sizeof( playName ) );
	}
	char playName[ g_PlayerNameLEN ];
};

//class MsgEnterRoomReq : public PacketHeader
//{
//public:
//	MsgEnterRoomReq()
//	{
//		size = sizeof( MsgEnterRoomReq );
//		code = MSG_ENTER_ROOM_REQ;
//		memset( playName, 0, sizeof( playName ) );
//	}
//	char playName[ g_PlayerNameLEN ];
//};

class MsgEnterLobbyReq: public PacketHeader
{
public:
	MsgEnterLobbyReq()
	{
		size = sizeof( MsgEnterLobbyReq );
		code = MSG_ENTERLOBBY_REQ;
		ZeroMemory( playName, sizeof( playName ) );
	}	
	CHAR playName[ g_PlayerNameLEN ];
};

class MsgEnterLobbyAck: public PacketHeader
{
public:
	MsgEnterLobbyAck()
	{
		size = sizeof( MsgEnterLobbyAck );
		code = MSG_ENTERLOBBY_ACK;	
		ZeroMemory( playName, sizeof( playName ) );		
	}	
	CHAR playName[ g_PlayerNameLEN ];
};

class MsgUserListAck: public PacketHeader
{
public:
	MsgUserListAck()
	{
		size = sizeof( MsgUserListAck );
		code = MSG_USERLIST_ACK;				
		ZeroMemory( userList, sizeof (userList ) );		
	}	
	CHAR userList[ g_PlayerNameLEN ];

};

class MsgLeaveLobbyReq: public PacketHeader
{
public:
	MsgLeaveLobbyReq()
	{
		size = sizeof( MsgLeaveLobbyReq );
		code = MSG_LEAVELOBBY_REQ;
	}
};

class MsgLeaveLobbyAck: public PacketHeader
{
public:
	MsgLeaveLobbyAck()
	{
		size = sizeof( MsgLeaveLobbyAck );
		code = MSG_LEAVELOBBY_ACK;
		ZeroMemory( playName, sizeof( playName ) );		
	}
	CHAR playName[ g_PlayerNameLEN ];
};

class MsgEnterRoomReq: public PacketHeader
{
public:
	MsgEnterRoomReq()
	{
		size = sizeof( MsgEnterRoomReq );
		code = MSG_ENTER_ROOM_REQ;
		roomIndex = 0;
		ZeroMemory( playName, sizeof( playName ) );
	}	
	INT roomIndex;
	CHAR playName[ g_PlayerNameLEN ];
};

//class MsgEnterRoomAck: public PacketHeader
//{
//public:
//	MsgEnterRoomAck()
//	{
//		size = sizeof( MsgEnterRoomAck );
//		code = MSG_ENTERGAMEROOM_ACK;		
//		//roomIndex = 0;
//		enterstate = FALSE;	
//	}
//	CHAR roomIndex[10];
//	BOOL enterstate;	
//};

class MsgCreateRoomReq: public PacketHeader
{
public:
	MsgCreateRoomReq()
	{
		size = sizeof( MsgCreateRoomReq );
		code = MSG_CREATEROOM_REQ;		
		maxUserCount = 0;
	//	ZeroMemory( roomName, sizeof( roomName ) );
		ZeroMemory( playName, sizeof( playName ) );
	}
	INT maxUserCount;
	//CHAR roomName[ ROOMNAMELEN ];
	CHAR playName[ g_PlayerNameLEN ];
};

class MsgCreateRoomAck: public PacketHeader
{
public:
	MsgCreateRoomAck()
	{
		size = sizeof( MsgCreateRoomAck );
		code = MSG_CREATEROOM_ACK;
		createRoom = FALSE;
		maxUserCount = 0;
	}
	INT maxUserCount;
	BOOL createRoom;
};

class MsgRoomListAck: public PacketHeader
{
public:
	MsgRoomListAck()
	{
		size = sizeof( MsgRoomListAck );
		code = MSG_ROOMLIST_ACK;
		roomIndex = 0;
		userCount = 0;
		maxUserCount = 0;
		startState = FALSE;
		//mapType = CASTLE1;
		ZeroMemory( roomName, sizeof( roomName ) );
	}
	INT roomIndex;
	INT userCount;
	INT	maxUserCount;
	BOOL startState;
	//MapType mapType;
	CHAR roomName[ g_PlayerNameLEN ];
};

class MsgReadyReq: public PacketHeader
{
public:
	MsgReadyReq()
	{
		size = sizeof( MsgReadyReq );
		code = MSG_READY_REQ;
		readyState = FALSE;
	}
	BOOL readyState;
};

class MsgReadyAck: public PacketHeader
{
public:
	MsgReadyAck()
	{
		size = sizeof( MsgReadyAck );
		code = MSG_READY_ACK;		
		readyState = FALSE;
		ZeroMemory( playName, sizeof( playName ) );

	}	
	BOOL readyState;
	CHAR playName[ g_PlayerNameLEN ];

};

class MsgStartCompleteAck : public PacketHeader
{
public:
	MsgStartCompleteAck()
	{
		size = sizeof( MsgStartCompleteAck );
		code = MSG_STARTCOMPLETE_ACK;
	}
};

// 게임 시작 완료 요청
class MsgStartCompleteReq : public PacketHeader
{
public:
	MsgStartCompleteReq()
	{
		size = sizeof( MsgStartCompleteReq );
		code = MSG_STARTCOMPLETE_REQ;
	}	
};