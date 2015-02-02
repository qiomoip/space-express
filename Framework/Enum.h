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