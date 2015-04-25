#pragma once

enum eTYPE{
   TYPE_OBJECT,
   TYPE_CHARACTER,
   TYPE_WALL,
   TYPE_NONE
};

enum eMESH_NUM{
	MN_NULL,
	MN_TIGER,
	MN_TERRAIN,
	MN_ENVIRONMENT,
	MN_GRID,
};

enum eTEXTURE_NUM{

};

enum eCAMERA_NUM
{
	CN_DEFAULT,
	CN_MAIN,
	CN_THIRD,
	CN_END,
};

enum eMESH_TYPE
{
	MT_NULL,
	MT_ANI,
	MT_STATIC,
	MT_TEXTURE,
	MT_TERRAIN,
#ifdef _DEBUG
	MT_GRID,
#endif
};

enum eAxis_TYPE
{
	AT_X,
	AT_Y,
	AT_Z,
	AT_MAX,
};

enum eRENDER_TYPE
{
	RTYPE_NONE,
#ifdef _DEBUG
	RTYPE_GRID,
#endif
	RTYPE_ENVIRONMENT,
	RTYPE_ENTITY, 
	RTYPE_TERRAIN,
	RTYPE_EFFECT,
	RTYPE_MAX,
};

enum eSCENE_TYPE
{
	STYPE_LOGO,
	STYPE_MAIN1,
};

enum eLIGHT_TYPE
{
	LIGHT_POINT,
	LIGHT_SPOT,
	LIGHT_DIRECTION,
};

enum eSHADER_KEY
{
	SHADER_NONE,
	SHADER_DEFAULT,

};

enum eBASIC_PASS_KEY
{
	PASS_DEFAULT,
	PASS_NOTEXTURE,
};

enum eMOVE_DIRECTION
{
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT,
};

//정적 로그 출력 순서 및 용도
enum eSTATIC_LOG
{
	LOG_CAMERA_INFO_0,
	LOG_CAMERA_INFO_1,
	LOG_CAMERA_INFO_2,
	LOG_CAMERA_INFO_3,
	LOG_CAMERA_INFO_4,
};
