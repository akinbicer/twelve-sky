//-------------------------------------------------------------------------------------------------
//MY_SUMMON_SYSTEM_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_SUMMON_SYSTEM_H
#define MY_SUMMON_SYSTEM_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_SUMMON_SYSTEM
//-------------------------------------------------------------------------------------------------
//STRUCTURE-[WORLD_REGION_INFO]
typedef struct
{
	int mVALUE01;
	int mVALUE02;
	int mVALUE03;
	int mVALUE04;
	int mCENTER[3];
	int mRADIUS;
}
WORLD_REGION_INFO;
//DEFINE
class MySummonSystem
{

private :

	void LoadRegionInfo_1( char *tFileName );
	void LoadRegionInfo_2( char *tFileName );

public :

	int mTotalMonsterSummonInfoNum;
	WORLD_REGION_INFO *mMONSTER_SUMMON;
	int mMonsterSummonPostTime[MAX_MONSTER_OBJECT_BASE_1_NUM];
	int mTotalBossMonsterSummonInfoNum;
	WORLD_REGION_INFO *mBOSS_MONSTER_SUMMON;
	int mBossMonsterSummonState;
	DWORD mPostTickCountForBossMonsterSummon;

	MySummonSystem( void );

	void Init( void );
	void Free( void );

	int ReturnSpecialSortNumber( MONSTER_INFO *tMONSTER_INFO );

	void DeleteMonster( void );

	void SummonMonster( void );
	void SummonBossMonster( void );
	void SummonMonsterWithoutTimeLimit( void );
	void SummonMonsterForSpecial( int tMonsterNumber, float tMonsterLocation[3], BOOL tCheckExistMonster, int tUserIndex = -1 ); // tUserIndex - 몬스터 소유자 index
	void SummonGuard( BOOL tCheckZone038, BOOL tCheckFirst );
	void SummonTribeSymbol( void );
    BOOL SummonMonsterForTribeWeapon( int tMonsterNumber, float tMonsterLocation[3] );
	void SummonMonsterWithoutTimeLimitForZone175Type( int tStep );
	void SummonMonsterForZone175Type( void );

};
//INSTANCE
extern MySummonSystem mSUMMON;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
