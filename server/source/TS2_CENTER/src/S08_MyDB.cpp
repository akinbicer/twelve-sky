//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "H01_MainApplication.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_DB
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyDB mDB;
//CREATE
MyDB::MyDB( void )
{
}
//INIT
BOOL MyDB::Init( void )
{
	if(mDB01.set_db_conn_info(mSERVER_INFO.mDB_1_IP[0], mSERVER_INFO.mDB_1_IP[1], mSERVER_INFO.mDB_1_PORT
			, g_env.db_name_str_obj.c_str (), mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0) {
		return false;
	}
	if (!mDB01.connect()) {
		return FALSE;
	}
#ifdef __TK__ 
	if(mDB01.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif

	//Account DB
	if(mDB02.set_db_conn_info(mSERVER_INFO.mDB_2_IP[0], mSERVER_INFO.mDB_2_IP[1], mSERVER_INFO.mDB_2_PORT
			, g_env.db2_name_str_obj.c_str (), mSERVER_INFO.mDB_2_ID, mSERVER_INFO.mDB_2_PASSWORD) < 0) {
		return false;
	}
	if (!mDB02.connect()) {
		return FALSE;
	}
#ifdef __TK__
	if(mDB02.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
	return TRUE;
}
//FREE
void MyDB::Free( void )
{
#ifdef __WIN32__
	CoUninitialize();
#endif
}
//RECONNECT_TO_DATABASE01
BOOL MyDB::RECONNECT_TO_DATABASE01( void )
{
	if( mDB01.IsConnected() )
	{
		return TRUE;
	}
	if( !mDB01.Reconnect() )
	{
		return FALSE;
	}
#ifdef __TK__
	if(mDB01.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
	return TRUE;
}
//RECONNECT_TO_DATABASE02
BOOL MyDB::RECONNECT_TO_DATABASE02( void )
{
	if( mDB02.IsConnected() )
	{
		return TRUE;
	}
	if( !mDB02.Reconnect() )
	{
		return FALSE;
	}
#ifdef __TK__
	if(mDB02.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_01
BOOL MyDB::DB_PROCESS_01( WORLD_INFO *tWorldInfo )
{
	int iAffected;
	int iCounts;
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;

	sprintf( mQUERY, "select mZone38WinTribe,mTribe1Symbol,mTribe2Symbol,mTribe3Symbol,mTribe4Symbol,mMonsterSymbol,mTribe1Point,mTribe2Point,mTribe3Point,mTribe4Point,mCloseTime,mCloseTribe,mPossibleAlliance01Date,mPossibleAlliance01Info,mPossibleAlliance02Date,mPossibleAlliance02Info,mPossibleAlliance03Date,mPossibleAlliance03Info,mPossibleAlliance04Date,mPossibleAlliance04Info,mAlliance0101,mAlliance0102,mAlliance0201,mAlliance0202,mTribe1VoteState,mTribe2VoteState,mTribe3VoteState,mTribe4VoteState,mClose1VoteState,mClose2VoteState,mClose3VoteState,mClose4VoteState,mTribe4QuestDate,mTribe4QuestState,mTribe4QuestName from %s where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, g_env.world_num);
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.ExecuteAndReceive( mQUERY, iAffected ) )
	{
		return FALSE;
	}
	iCounts = 0;
	if( !mDB01.GetResultCounts( iCounts ) )
	{
		return FALSE;
	}
	if( iCounts != 1 )
	{
		return FALSE;
	}
	if(
	  ( !mDB01.GetLong(  0, (long &) tWorldInfo->mZone038WinTribe ) ) ||
	  ( !mDB01.GetLong(  1, (long &) tWorldInfo->mTribe1Symbol ) ) ||
	  ( !mDB01.GetLong(  2, (long &) tWorldInfo->mTribe2Symbol ) ) ||
	  ( !mDB01.GetLong(  3, (long &) tWorldInfo->mTribe3Symbol ) ) ||
	  ( !mDB01.GetLong(  4, (long &) tWorldInfo->mTribe4Symbol ) ) ||
	  ( !mDB01.GetLong(  5, (long &) tWorldInfo->mMonsterSymbol ) ) ||
	  ( !mDB01.GetLong(  6, (long &) tWorldInfo->mTribePoint[0] ) ) ||
	  ( !mDB01.GetLong(  7, (long &) tWorldInfo->mTribePoint[1] ) ) ||
	  ( !mDB01.GetLong(  8, (long &) tWorldInfo->mTribePoint[2] ) ) ||
	  ( !mDB01.GetLong(  9, (long &) tWorldInfo->mTribePoint[3] ) ) ||
	  ( !mDB01.GetLong( 10, (long &) tWorldInfo->mTribeCloseInfo[0] ) ) ||
	  ( !mDB01.GetLong( 11, (long &) tWorldInfo->mTribeCloseInfo[1] ) ) ||
	  ( !mDB01.GetLong( 12, (long &) tWorldInfo->mPossibleAllianceInfo[0][0] ) ) ||
	  ( !mDB01.GetLong( 13, (long &) tWorldInfo->mPossibleAllianceInfo[0][1] ) ) ||
	  ( !mDB01.GetLong( 14, (long &) tWorldInfo->mPossibleAllianceInfo[1][0] ) ) ||
	  ( !mDB01.GetLong( 15, (long &) tWorldInfo->mPossibleAllianceInfo[1][1] ) ) ||
	  ( !mDB01.GetLong( 16, (long &) tWorldInfo->mPossibleAllianceInfo[2][0] ) ) ||
	  ( !mDB01.GetLong( 17, (long &) tWorldInfo->mPossibleAllianceInfo[2][1] ) ) ||
	  ( !mDB01.GetLong( 18, (long &) tWorldInfo->mPossibleAllianceInfo[3][0] ) ) ||
	  ( !mDB01.GetLong( 19, (long &) tWorldInfo->mPossibleAllianceInfo[3][1] ) ) ||
	  ( !mDB01.GetLong( 20, (long &) tWorldInfo->mAllianceState[0][0] ) ) ||
	  ( !mDB01.GetLong( 21, (long &) tWorldInfo->mAllianceState[0][1] ) ) ||
	  ( !mDB01.GetLong( 22, (long &) tWorldInfo->mAllianceState[1][0] ) ) ||
	  ( !mDB01.GetLong( 23, (long &) tWorldInfo->mAllianceState[1][1] ) ) ||
	  ( !mDB01.GetLong( 24, (long &) tWorldInfo->mTribeVoteState[0] ) ) ||
	  ( !mDB01.GetLong( 25, (long &) tWorldInfo->mTribeVoteState[1] ) ) ||
	  ( !mDB01.GetLong( 26, (long &) tWorldInfo->mTribeVoteState[2] ) ) ||
	  ( !mDB01.GetLong( 27, (long &) tWorldInfo->mTribeVoteState[3] ) ) ||
	  ( !mDB01.GetLong( 28, (long &) tWorldInfo->mCloseVoteState[0] ) ) ||
	  ( !mDB01.GetLong( 29, (long &) tWorldInfo->mCloseVoteState[1] ) ) ||
	  ( !mDB01.GetLong( 30, (long &) tWorldInfo->mCloseVoteState[2] ) ) ||
	  ( !mDB01.GetLong( 31, (long &) tWorldInfo->mCloseVoteState[3] ) ) ||
	  ( !mDB01.GetLong( 32, (long &) tWorldInfo->mTribe4QuestDate ) ) ||
	  ( !mDB01.GetLong( 33, (long &) tWorldInfo->mTribe4QuestState ) ) ||
	  ( !mDB01.GetText( 34, tWorldInfo->mTribe4QuestName, MAX_TRIBE4_QUEST_NAME_LENGTH ) )
	  )
	{
		return FALSE;
	}
#else
	if ((iAffected = mDB01.exec_query (mQUERY)) < 0)
	{
		return FALSE;
	}
	LOG_TO_FILE_1 ("%s execute query\n", __FUNCTION__);
	iCounts = 0;
	res = mDB01.get_res();
	if(res == NULL) {
		return false;
	}
	while((row = mysql_fetch_row(res))) {
		LOG_TO_FILE_1 ("Fetch row : %s\n", row[ 0 ]);
		tWorldInfo->mZone038WinTribe = atoi (row[ 0 ]);
		tWorldInfo->mTribe1Symbol = atoi (row[ 1 ]);
		tWorldInfo->mTribe2Symbol = atoi (row[ 2 ]);
		tWorldInfo->mTribe3Symbol = atoi (row[ 3 ]);
		tWorldInfo->mTribe4Symbol = atoi (row[ 4 ]);
		tWorldInfo->mMonsterSymbol = atoi (row[ 5 ]);
		tWorldInfo->mTribePoint[0] = atoi (row[ 6 ]);
		tWorldInfo->mTribePoint[1] = atoi (row[ 7 ]);
		tWorldInfo->mTribePoint[2] = atoi (row[ 8 ]);
		tWorldInfo->mTribePoint[3] = atoi (row[ 9 ]);
		tWorldInfo->mTribeCloseInfo[0] = atoi (row[ 10 ]);
		tWorldInfo->mTribeCloseInfo[1] = atoi (row[ 11 ]);
		tWorldInfo->mPossibleAllianceInfo[0][0] = atoi (row[ 12 ]);
		tWorldInfo->mPossibleAllianceInfo[0][1] = atoi (row[ 13 ]);
		tWorldInfo->mPossibleAllianceInfo[1][0] = atoi (row[ 14 ]);
		tWorldInfo->mPossibleAllianceInfo[1][1] = atoi (row[ 15 ]);
		tWorldInfo->mPossibleAllianceInfo[2][0] = atoi (row[ 16 ]);
		tWorldInfo->mPossibleAllianceInfo[2][1] = atoi (row[ 17 ]);
		tWorldInfo->mPossibleAllianceInfo[3][0] = atoi (row[ 18 ]);
		tWorldInfo->mPossibleAllianceInfo[3][1] = atoi (row[ 19 ]);
		tWorldInfo->mAllianceState[0][0] = atoi (row[ 20 ]);
		tWorldInfo->mAllianceState[0][1] = atoi (row[ 21 ]);
		tWorldInfo->mAllianceState[1][0] = atoi (row[ 22 ]);
		tWorldInfo->mAllianceState[1][1] = atoi (row[ 23 ]);
		tWorldInfo->mTribeVoteState[0] = atoi (row[ 24 ]);
		tWorldInfo->mTribeVoteState[1] = atoi (row[ 25 ]);
		tWorldInfo->mTribeVoteState[2] = atoi (row[ 26 ]);
		tWorldInfo->mTribeVoteState[3] = atoi (row[ 27 ]);
		tWorldInfo->mCloseVoteState[0] = atoi (row[ 28 ]);
		tWorldInfo->mCloseVoteState[1] = atoi (row[ 29 ]);
		tWorldInfo->mCloseVoteState[2] = atoi (row[ 30 ]);
		tWorldInfo->mCloseVoteState[3] = atoi (row[ 31 ]);
		tWorldInfo->mTribe4QuestDate = atoi (row[ 32 ]);
		tWorldInfo->mTribe4QuestState = atoi (row[ 33 ]);
		snprintf (tWorldInfo->mTribe4QuestName, MAX_TRIBE4_QUEST_NAME_LENGTH, "%s", row[ 34]);
		iCounts++;
	}
	//LOG_TO_FILE_2 ("%s Fetch row, iCounts : %d\n", __FUNCTION__, iCounts);
	mDB01.clear_res ();
	if (iCounts  != 1)
	{
		return FALSE;
	}
	//LOG_TO_FILE_1 ("%s end, clear_res\n", __FUNCTION__);
#endif
	return TRUE;
}
//DB_PROCESS_02
BOOL MyDB::DB_PROCESS_02( WORLD_INFO *tWorldInfo )
{
	int iAffected;
	int iCounts;
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;
	//long tTribePoint[4];

	LOG_TO_FILE ("The db process 02 called");
	sprintf( mQUERY, "select mTribe1Point,mTribe2Point,mTribe3Point,mTribe4Point from %s where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, g_env.world_num );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.ExecuteAndReceive( mQUERY, iAffected ) )
	{
		return FALSE;
	}
	iCounts = 0;
	if( !mDB01.GetResultCounts( iCounts ) )
	{
		return FALSE;
	}
	if( iCounts != 1 )
	{
		return FALSE;
	}
	if(
	  ( !mDB01.GetLong( 0, tTribePoint[0] ) ) ||
	  ( !mDB01.GetLong( 1, tTribePoint[1] ) ) ||
	  ( !mDB01.GetLong( 2, tTribePoint[2] ) ) ||
	  ( !mDB01.GetLong( 3, tTribePoint[3] ) )
	  )
	{
		return FALSE;
	}
#else
	if ((iAffected = mDB01.exec_query (mQUERY)) < 0)
	{
		return FALSE;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if(res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res)))
	{
		tWorldInfo->mTribePoint[0] = atoi (row[ 0 ]);
		tWorldInfo->mTribePoint[1] = atoi (row[ 1 ]);
		tWorldInfo->mTribePoint[2] = atoi (row[ 2 ]);
		tWorldInfo->mTribePoint[3] = atoi (row[ 3 ]);
		iCounts++;
	}
	mDB01.clear_res ();
	if (iCounts != 1)
	{
		return FALSE;
	}
#endif	
	return TRUE;
}
//DB_PROCESS_03
BOOL MyDB::DB_PROCESS_03( int tTribe )
{
	int iAffected;

	sprintf( mQUERY, "update %s set mZone38WinTribeDate=now(),mZone38WinTribe=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if ((iAffected = mDB01.exec_query (mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_04
BOOL MyDB::DB_PROCESS_04( int tSort, int tTribe )
{
	int iAffected;

	switch( tSort )
	{
	case 1 :
		sprintf( mQUERY, "update %s set mTribe1SymbolDate=now(),mTribe1Symbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num );
		break;
	case 2 :
		sprintf( mQUERY, "update %s set mTribe2SymbolDate=now(),mTribe2Symbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num );
		break;
	case 3 :
		sprintf( mQUERY, "update %s set mTribe3SymbolDate=now(),mTribe3Symbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num );
		break;
	case 4 :
		sprintf( mQUERY, "update %s set mTribe4SymbolDate=now(),mTribe4Symbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num );
		break;
	case 5 :
		sprintf( mQUERY, "update %s set mMonsterSymbolDate=now(),mMonsterSymbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num );
		break;
	default :
		return FALSE;
	}
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if ((iAffected = mDB01.exec_query (mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_05
BOOL MyDB::DB_PROCESS_05( int tDate, int tTribe )
{
	int iAffected;

	sprintf( mQUERY, "update %s set mCloseTime=%d,mCloseTribe=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tTribe, g_env.world_num );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if ((iAffected = mDB01.exec_query (mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_06
BOOL MyDB::DB_PROCESS_06( int tSort, int tDate, int tValue )
{
	int iAffected;

	switch( tSort )
	{
	case 1 :
		sprintf( mQUERY, "update %s set mPossibleAlliance01Date=%d,mPossibleAlliance01Info=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tValue, g_env.world_num );
		break;
	case 2 :
		sprintf( mQUERY, "update %s set mPossibleAlliance02Date=%d,mPossibleAlliance02Info=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tValue, g_env.world_num );
		break;
	case 3 :
		sprintf( mQUERY, "update %s set mPossibleAlliance03Date=%d,mPossibleAlliance03Info=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tValue, g_env.world_num );
		break;
	case 4 :
		sprintf( mQUERY, "update %s set mPossibleAlliance04Date=%d,mPossibleAlliance04Info=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tValue, g_env.world_num );
		break;
	default :
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	if ((iAffected = mDB01.exec_query (mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_07
BOOL MyDB::DB_PROCESS_07( int tSort, int tAlliance01, int tAlliance02 )
{
	int iAffected;

	switch( tSort )
	{
	case 1 :
		sprintf( mQUERY, "update %s set mAlliance01Date=now(),mAlliance0101=%d,mAlliance0102=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tAlliance01, tAlliance02, g_env.world_num );
		break;
	case 2 :
		sprintf( mQUERY, "update %s set mAlliance02Date=now(),mAlliance0201=%d,mAlliance0202=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tAlliance01, tAlliance02, g_env.world_num );
		break;
	default :
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}

	if ((iAffected = mDB01.exec_query (mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_08
BOOL MyDB::DB_PROCESS_08( int tSort, int tValue )
{
	int iAffected;

	switch( tSort )
	{
	case 1 :
		sprintf( mQUERY, "update %s set mTribe1VoteDate=now(),mTribe1VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num );
		break;
	case 2 :
		sprintf( mQUERY, "update %s set mTribe2VoteDate=now(),mTribe2VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num );
		break;
	case 3 :
		sprintf( mQUERY, "update %s set mTribe3VoteDate=now(),mTribe3VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num );
		break;
	case 4 :
		sprintf( mQUERY, "update %s set mTribe4VoteDate=now(),mTribe4VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num );
		break;
	default :
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	if ((iAffected = mDB01.exec_query (mQUERY), CMySQL::CLEAR) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_09
BOOL MyDB::DB_PROCESS_09( int tSort, int tValue )
{
	int iAffected;

	switch( tSort )
	{
	case 1 :
		sprintf( mQUERY, "update %s set mClose1VoteDate=now(),mClose1VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num );
		break;
	case 2 :
		sprintf( mQUERY, "update %s set mClose2VoteDate=now(),mClose2VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num );
		break;
	case 3 :
		sprintf( mQUERY, "update %s set mClose3VoteDate=now(),mClose3VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num );
		break;
	case 4 :
		sprintf( mQUERY, "update %s set mClose4VoteDate=now(),mClose4VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num );
		break;
	default :
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	if ((iAffected = mDB01.exec_query (mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_10
BOOL MyDB::DB_PROCESS_10( TRIBE_INFO *tTribeInfo )
{
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;
	int index01;
	int index02;
	int index03;
	char tempString01[1000];
	int iAffected;
	int iCounts;
	char mTribeVoteInfo[1041];
	char mTribe01Master[MAX_AVATAR_NAME_LENGTH];
	char mTribe01SubMasterInfo[145];
	char mTribe02Master[MAX_AVATAR_NAME_LENGTH];
	char mTribe02SubMasterInfo[145];
	char mTribe03Master[MAX_AVATAR_NAME_LENGTH];
	char mTribe03SubMasterInfo[145];
	char mTribe04Master[MAX_AVATAR_NAME_LENGTH];
	char mTribe04SubMasterInfo[145];

	sprintf( mQUERY, "select mTribeVoteInfo,mTribe01Master,mTribe01SubMasterInfo,mTribe02Master,mTribe02SubMasterInfo,mTribe03Master,mTribe03SubMasterInfo,mTribe04Master,mTribe04SubMasterInfo from %s where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table02, g_env.world_num );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;

	if ((iAffected = mDB01.exec_query (mQUERY)) < 0)
	{
		return FALSE;
	}
	//LOG_TO_FILE_1 ("%s execute query\n", __FUNCTION__);
	iCounts = 0;
	res = mDB01.get_res ();
	if(res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row (res)))
	{
		snprintf (mTribeVoteInfo, 1041, "%s", row[ 0 ]);
		snprintf (mTribe01Master, MAX_AVATAR_NAME_LENGTH, "%s", row[ 1 ]);
		snprintf (mTribe01SubMasterInfo, 145, "%s", row[ 2 ]);
		snprintf (mTribe02Master, MAX_AVATAR_NAME_LENGTH, "%s", row[ 3 ]);
		snprintf (mTribe02SubMasterInfo, 145, "%s", row[ 4 ]);
		snprintf (mTribe03Master, MAX_AVATAR_NAME_LENGTH, "%s", row[ 5 ]);
		snprintf (mTribe03SubMasterInfo, 145, "%s", row[ 6 ]);
		snprintf (mTribe04Master, MAX_AVATAR_NAME_LENGTH, "%s", row[ 7 ]);
		snprintf (mTribe04SubMasterInfo, 145, "%s", row[ 8 ]);
		iCounts++;
	}
	//LOG_TO_FILE_2 ("%s fetch row, iCounts : %d\n", __FUNCTION__, iCounts);

	mDB01.clear_res ();
	if (iCounts != 1)
	{
		return FALSE;
	}
	//LOG_TO_FILE_1 ("%s end, clear_res \n", __FUNCTION__);

	if( strlen( mTribeVoteInfo ) == 0 )
	{
		strcpy( mTribeVoteInfo, "" );
		for( index01 = 0 ; index01 < ( 4 * MAX_TRIBE_VOTE_AVATAR_NUM ) ; index01++ )
		{
			strcat( mTribeVoteInfo, "@@@@@@@@@@@@00000000000000" );
		}
	}
	if( strlen( mTribeVoteInfo ) != 1040 )
	{
		//LOG_TO_FILE_2("%d %d\n", __LINE__, strlen( mTribeVoteInfo ));
		return FALSE;
	}
	if( strlen( mTribe01SubMasterInfo ) == 0 )
	{
		strcpy( mTribe01SubMasterInfo, "" );
		for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
		{
			strcat( mTribe01SubMasterInfo, "@@@@@@@@@@@@" );
		}
	}
	if( strlen( mTribe01SubMasterInfo ) != 144 )
	{
		//LOG_TO_FILE_2("%d %d\n", __LINE__, strlen( mTribe01SubMasterInfo ));
		return FALSE;
	}
	if( strlen( mTribe02SubMasterInfo ) == 0 )
	{
		strcpy( mTribe02SubMasterInfo, "" );
		for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
		{
			strcat( mTribe02SubMasterInfo, "@@@@@@@@@@@@" );
		}
	}
	if( strlen( mTribe02SubMasterInfo ) != 144 )
	{
		//LOG_TO_FILE_2("%d %d\n", __LINE__, strlen( mTribe02SubMasterInfo ));
		return FALSE;
	}
	if( strlen( mTribe03SubMasterInfo ) == 0 )
	{
		strcpy( mTribe03SubMasterInfo, "" );
		for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
		{
			strcat( mTribe03SubMasterInfo, "@@@@@@@@@@@@" );
		}
	}
	if( strlen( mTribe03SubMasterInfo ) != 144 )
	{
		//LOG_TO_FILE_2("%d %d\n", __LINE__, strlen( mTribe03SubMasterInfo ));
		return FALSE;
	}
	if( strlen( mTribe04SubMasterInfo ) == 0 )
	{
		strcpy( mTribe04SubMasterInfo, "" );
		for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
		{
			strcat( mTribe04SubMasterInfo, "@@@@@@@@@@@@" );
		}
	}
	if( strlen( mTribe04SubMasterInfo ) != 144 )
	{
		//LOG_TO_FILE_2("%d %d\n", __LINE__, strlen( mTribe04SubMasterInfo ));
		return FALSE;
	}
	for( index01 = 0 ; index01 < 4 ; index01++ )
	{
		for( index02 = 0 ; index02 < MAX_TRIBE_VOTE_AVATAR_NUM ; index02++ )
		{
			CopyMemory( &tTribeInfo->mTribeVoteName[index01][index02][0], &mTribeVoteInfo[( ( index01 * MAX_TRIBE_VOTE_AVATAR_NUM + index02 ) * 26 + 0 )], 12 );
			for( index03 = 0 ; index03 < 12 ; index03++ )
			{
				if (::IsDBCSLeadByte (tTribeInfo->mTribeVoteName[index01][index02][index03]) == TRUE) {
					if (index03 != 11) index03++;
					continue;
				}

				if( tTribeInfo->mTribeVoteName[index01][index02][index03] == '@' )
				{
					break;
				}
			}
			tTribeInfo->mTribeVoteName[index01][index02][index03] = '\0';
			CopyMemory( &tempString01[0], &mTribeVoteInfo[( ( index01 * MAX_TRIBE_VOTE_AVATAR_NUM + index02 ) * 26 + 12 )], 2 );
			tempString01[2] = '\0';
			tTribeInfo->mTribeVoteLevel[index01][index02] = atoi( tempString01 );
			CopyMemory( &tempString01[0], &mTribeVoteInfo[( ( index01 * MAX_TRIBE_VOTE_AVATAR_NUM + index02 ) * 26 + 14 )], 6 );
			tempString01[6] = '\0';
			tTribeInfo->mTribeVoteKillOtherTribe[index01][index02] = atoi( tempString01 );
			CopyMemory( &tempString01[0], &mTribeVoteInfo[( ( index01 * MAX_TRIBE_VOTE_AVATAR_NUM + index02 ) * 26 + 20 )], 6 );
			tempString01[6] = '\0';
			tTribeInfo->mTribeVotePoint[index01][index02] = atoi( tempString01 );
		}
	}
	strcpy( tTribeInfo->mTribeMaster[0], mTribe01Master );
	for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
	{
		CopyMemory( &tTribeInfo->mTribeSubMaster[0][index01][0], &mTribe01SubMasterInfo[( index01 * 12 + 0 )], 12 );
		for( index02 = 0 ; index02 < 12 ; index02++ )
		{
			if (::IsDBCSLeadByte (tTribeInfo->mTribeSubMaster[0][index01][index02]) == TRUE) {
				if (index02 != 11) index02++;
				continue;
			}

			if( tTribeInfo->mTribeSubMaster[0][index01][index02] == '@' )
			{
				break;
			}
		}
		tTribeInfo->mTribeSubMaster[0][index01][index02] = '\0';
	}
	strcpy( tTribeInfo->mTribeMaster[1], mTribe02Master );
	for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
	{
		CopyMemory( &tTribeInfo->mTribeSubMaster[1][index01][0], &mTribe02SubMasterInfo[( index01 * 12 + 0 )], 12 );
		for( index02 = 0 ; index02 < 12 ; index02++ )
		{
			if (::IsDBCSLeadByte (tTribeInfo->mTribeSubMaster[1][index01][index02]) == TRUE) {
				if (index02 != 11) index02++;
				continue;
			}

			if( tTribeInfo->mTribeSubMaster[1][index01][index02] == '@' )
			{
				break;
			}
		}
		tTribeInfo->mTribeSubMaster[1][index01][index02] = '\0';
	}
	strcpy( tTribeInfo->mTribeMaster[2], mTribe03Master );
	for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
	{
		CopyMemory( &tTribeInfo->mTribeSubMaster[2][index01][0], &mTribe03SubMasterInfo[( index01 * 12 + 0 )], 12 );
		for( index02 = 0 ; index02 < 12 ; index02++ )
		{
			if (::IsDBCSLeadByte (tTribeInfo->mTribeSubMaster[2][index01][index02]) == TRUE) {
				if (index02 != 11) index02++;
				continue;
			}

			if( tTribeInfo->mTribeSubMaster[2][index01][index02] == '@' )
			{
				break;
			}
		}
		tTribeInfo->mTribeSubMaster[2][index01][index02] = '\0';
	}
	strcpy( tTribeInfo->mTribeMaster[3], mTribe04Master );
	for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
	{
		CopyMemory( &tTribeInfo->mTribeSubMaster[3][index01][0], &mTribe04SubMasterInfo[( index01 * 12 + 0 )], 12 );
		for( index02 = 0 ; index02 < 12 ; index02++ )
		{
			if (::IsDBCSLeadByte (tTribeInfo->mTribeSubMaster[3][index01][index02]) == TRUE) {
				if (index02 != 11) index02++;
				continue;
			}

			if( tTribeInfo->mTribeSubMaster[3][index01][index02] == '@' )
			{
				break;
			}
		}
		tTribeInfo->mTribeSubMaster[3][index01][index02] = '\0';
	}
	return TRUE;
}
//DB_PROCESS_11
BOOL MyDB::DB_PROCESS_11( TRIBE_INFO *tTribeInfo )
{
	int index01;
	int index02;
	char tempString01[1000];
	int iAffected;
	char mTribeVoteInfo[1041];
	char mTribe01SubMasterInfo[145];
	char mTribe02SubMasterInfo[145];
	char mTribe03SubMasterInfo[145];
	char mTribe04SubMasterInfo[145];

	strcpy( mTribeVoteInfo, "" );
	for( index01 = 0 ; index01 < 4 ; index01++ )
	{
		for( index02 = 0 ; index02 < MAX_TRIBE_VOTE_AVATAR_NUM ; index02++ )
		{
			strcpy( tempString01, "@@@@@@@@@@@@" );
			CopyMemory( &tempString01[0], &tTribeInfo->mTribeVoteName[index01][index02][0], strlen( tTribeInfo->mTribeVoteName[index01][index02] ) );
			tempString01[12] = '\0';
			strcat( mTribeVoteInfo, tempString01 );
			sprintf( tempString01, "%02d%06d%06d", ( tTribeInfo->mTribeVoteLevel[index01][index02] % 100 ), ( tTribeInfo->mTribeVoteKillOtherTribe[index01][index02] % 1000000 ), ( tTribeInfo->mTribeVotePoint[index01][index02] % 1000000 ) );
			strcat( mTribeVoteInfo, tempString01 );
		}
	}
	strcpy( mTribe01SubMasterInfo, "" );
	for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
	{
		strcpy( tempString01, "@@@@@@@@@@@@" );
		CopyMemory( &tempString01[0], &tTribeInfo->mTribeSubMaster[0][index01][0], strlen( tTribeInfo->mTribeSubMaster[0][index01] ) );
		tempString01[12] = '\0';
		strcat( mTribe01SubMasterInfo, tempString01 );
	}
	strcpy( mTribe02SubMasterInfo, "" );
	for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
	{
		strcpy( tempString01, "@@@@@@@@@@@@" );
		CopyMemory( &tempString01[0], &tTribeInfo->mTribeSubMaster[1][index01][0], strlen( tTribeInfo->mTribeSubMaster[1][index01] ) );
		tempString01[12] = '\0';
		strcat( mTribe02SubMasterInfo, tempString01 );
	}
	strcpy( mTribe03SubMasterInfo, "" );
	for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
	{
		strcpy( tempString01, "@@@@@@@@@@@@" );
		CopyMemory( &tempString01[0], &tTribeInfo->mTribeSubMaster[2][index01][0], strlen( tTribeInfo->mTribeSubMaster[2][index01] ) );
		tempString01[12] = '\0';
		strcat( mTribe03SubMasterInfo, tempString01 );
	}
	strcpy( mTribe04SubMasterInfo, "" );
	for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
	{
		strcpy( tempString01, "@@@@@@@@@@@@" );
		CopyMemory( &tempString01[0], &tTribeInfo->mTribeSubMaster[3][index01][0], strlen( tTribeInfo->mTribeSubMaster[3][index01] ) );
		tempString01[12] = '\0';
		strcat( mTribe04SubMasterInfo, tempString01 );
	}
	sprintf( mQUERY, "update %s set mUpdateTime=now(),mTribeVoteInfo='%s',mTribe01Master='%s',mTribe01SubMasterInfo='%s',mTribe02Master='%s',mTribe02SubMasterInfo='%s',mTribe03Master='%s',mTribe03SubMasterInfo='%s',mTribe04Master='%s',mTribe04SubMasterInfo='%s' where aWorldNumber = %d",
	mSERVER_INFO.mDB_1_Table02,
	mTribeVoteInfo,
	tTribeInfo->mTribeMaster[0],
	mTribe01SubMasterInfo,
	tTribeInfo->mTribeMaster[1],
	mTribe02SubMasterInfo,
	tTribeInfo->mTribeMaster[2],
	mTribe03SubMasterInfo,
	tTribeInfo->mTribeMaster[3],
	mTribe04SubMasterInfo,
	g_env.world_num);
	iAffected = 0;
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
#ifdef __WIN32__
	if( !mDB01.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if ((iAffected = mDB01.exec_query (mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}

BOOL MyDB::DB_PROCESS_12(int up_check)
{
	int i = 0;
	int nSize = 0;
	int nSize2 = 0;
	int nCount = 0;
	int packetSize = 0;
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;
	rank_kill_t tmp_rank_kill;
	rank_level_t tmp_rank_level;
	list<rank_kill_t>::iterator kill_it;
	list<rank_level_t>::iterator level_it;

	if((!up_check) && (list_rank_level.size() > 0) && (list_rank_kill.size() > 0)) {
		return TRUE;
	}
	sprintf(mQUERY, 
			"(SELECT '1' AS type, aName, aLevel, aTribe, aGeneralExperience "
			"FROM RankInfo  "
			"WHERE aWorldNumber = %d "
			"ORDER BY aLevel DESC, aGeneralExperience DESC "
			"LIMIT 100) "
			"UNION ALL "
			"(SELECT '2' AS type, aName, aKillOtherTribe, aTribe, aGeneralExperience "
			"FROM RankInfo  "
			"WHERE aWorldNumber = %d "
			"ORDER BY aKillOtherTribe DESC, aGeneralExperience DESC "
			"LIMIT 100)", g_env.world_num, g_env.world_num);

	if(!RECONNECT_TO_DATABASE01()) {
		return FALSE;
	}
	if(mDB01.exec_query(mQUERY) < 0) {
		return FALSE;
	}

	//LOG_TO_FILE_1 ("%s execute query\n", __FUNCTION__);
	mGAME.m_rank_kill_size = 0;
	mGAME.m_rank_level_size = 0;
	list_rank_kill.clear();
	list_rank_level.clear();

	res = mDB01.get_res();
	if(res == NULL) {
		return false;
	}
	while((row = mysql_fetch_row(res))) {
		if(*(row[0]) == '1') {
			snprintf(tmp_rank_level.aName, MAX_AVATAR_NAME_LENGTH, "%s", row[1]);
			tmp_rank_level.level = atoi(row[2]);
			tmp_rank_level.tribe = atoi(row[3]); 
			list_rank_level.push_back(tmp_rank_level);
			mGAME.m_rank_level_size += sizeof(tmp_rank_level);
		} else {
			snprintf(tmp_rank_kill.aName, MAX_AVATAR_NAME_LENGTH, "%s", row[1]);
			tmp_rank_kill.kill = atoi(row[2]);
			tmp_rank_kill.tribe = atoi(row[3]); 
			list_rank_kill.push_back(tmp_rank_kill);
			mGAME.m_rank_kill_size += sizeof(tmp_rank_kill);
		}
		nCount++;
	}
	LOG_TO_FILE_2("![%s] : nCount(%d)\n", __FUNCTION__, nCount);
	mDB01.clear_res();

	packetSize = mGAME.m_rank_level_size + mGAME.m_rank_kill_size;
	::memcpy(&mGAME.mBuffer[0], &packetSize, 4);
	::memcpy(&mGAME.mBuffer[4], &mGAME.m_rank_level_size, 4);
	::memcpy(&mGAME.mBuffer[8], &mGAME.m_rank_kill_size, 4);

	for(level_it = (mDB.list_rank_level).begin();
			level_it != (mDB.list_rank_level).end(); ++level_it) {
		nSize = i * sizeof(rank_level_t);
		::memcpy(&mGAME.mBuffer[12] + nSize, (const void *)&(*level_it), sizeof(rank_level_t));
		i++;
	}

	if(i != 0) {
		nSize += (12 + sizeof(rank_level_t));
	} else {
		nSize += 12;
	}

	i = 0;

	for(kill_it = (mDB.list_rank_kill).begin();
			kill_it != (mDB.list_rank_kill).end(); ++kill_it) {
		nSize2 = i * sizeof(rank_kill_t);
		//LOG_TO_FILE_2("%s %d\n", kill_it->aName, kill_it->kill);
		::memcpy(&mGAME.mBuffer[nSize] + nSize2, (const void *)&(*kill_it), sizeof(rank_kill_t));
		i++;
	}

	if(i != 0) {
		mGAME.mBufferSize = (nSize + nSize2 + sizeof(rank_kill_t));
	} else {
		mGAME.mBufferSize = (nSize + nSize2);
	}

	return TRUE;
}

BOOL MyDB::DB_PROCESS_13(const char *aName, rank_info_t *rank_info)
{
#if 0
	int nCount = 0;
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;

	sprintf(mQUERY, 
			"SELECT a.aName, a.aLevel, a.aKillOtherTribe, a.aTribe, "
			"	(SELECT (COUNT(aWorldNumber) + 1) "
			"	FROM RankInfo "
			"	WHERE aGeneralExperience > ( "
			"			SELECT aGeneralExperience "
			"			FROM RankInfo "
			"			WHERE aName = '%s' AND aWorldNumber = %d "
			"	 ) AND aWorldNumber = %d) AS rank "
			"FROM RankInfo a "
			"JOIN MemberInfo b ON a.uID = b.uID "
			"JOIN MemberAuth c on a.uID = c.uID "
			"WHERE a.aName = '%s' AND aWorldNumber = %d AND c.AuthType = 0 "
			, aName, g_env.world_num, g_env.world_num, aName, g_env.world_num);
	//LOG_TO_FILE_1("mQUERY : %s\n", mQUERY);

	if(!RECONNECT_TO_DATABASE02()) {
		return FALSE;
	}
	if(mDB02.exec_query(mQUERY) < 0) {
		return FALSE;
	}

	res = mDB02.get_res();
	if(res == NULL) {
		return false;
	}
	while((row = mysql_fetch_row(res))) {
		snprintf(rank_info->aName, MAX_AVATAR_NAME_LENGTH, "%s", row[0]);
		rank_info->level = atoi(row[1]);
		rank_info->kill = atoi(row[2]);
		rank_info->tribe = atoi(row[3]);
		rank_info->rank = atoi(row[4]);
		nCount++;
	}
	mDB02.clear_res();

	if(nCount != 1) 
		return false;
#endif
	return TRUE;
}
//-------------------------------------------------------------------------------------------------
