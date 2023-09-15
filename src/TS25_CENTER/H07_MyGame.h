//-------------------------------------------------------------------------------------------------
//MY_GAME_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_GAME_H
#define MY_GAME_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAME
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyGame
{
public :
	int mBufferSize;
	char mBuffer[5000];
	int m_rank_kill_size;
	int m_rank_level_size;

	ZONE_CONNECTION_INFO mZoneConnectionInfo;

	DWORD mTickCount;

	WORLD_INFO mWorldInfo;
	TRIBE_INFO mTribeInfo;

	MyGame(void);

	BOOL Init(void);
	int CheckPVNumber(int tTribe);
	void Free(void);
};

//INSTANCE
extern MyGame mGAME;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
