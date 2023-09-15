//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "H01_MainApplication.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_DB
//-------------------------------------------------------------------------------------------------
//INSTANCE
CLogging *g_mLOG;
CLogging *g_mThreadLOG;
MyDB mDB;
//CREATE
MyDB::MyDB( void )
{
}
//INIT
BOOL MyDB::Init( void )
{
#if 0
	if(!mDB01.connect(mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_PORT
				, g_env.db_name_str_obj.c_str() , mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD)) {
		return FALSE;
	}
#endif
	if(mDB01.set_db_conn_info(mSERVER_INFO.mDB_1_IP[0], mSERVER_INFO.mDB_1_IP[1], mSERVER_INFO.mDB_1_PORT
			, g_env.db_name_str_obj.c_str (), mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0) {
		return FALSE;
	}
	if(!mDB01.connect()) {
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB01.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if(mDB01.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#if 0
	if(!mDB01_FOR_THREAD.connect(mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_PORT
				, g_env.db_name_str_obj.c_str() , mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD)) {
		return FALSE;
	}
#endif
	if(mDB01_FOR_THREAD.set_db_conn_info(mSERVER_INFO.mDB_1_IP[0], mSERVER_INFO.mDB_1_IP[1], mSERVER_INFO.mDB_1_PORT
			, g_env.db_name_str_obj.c_str (), mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0) {
		return false;
	}
	if(!mDB01_FOR_THREAD.connect()) {
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB01_FOR_THREAD.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if(mDB01_FOR_THREAD.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#if 0
	if(!mDB02.connect(mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_PORT
				, g_env.db_name_str_obj.c_str() , mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD)) {
		return FALSE;
	}
#endif

	if(mDB02.set_db_conn_info(mSERVER_INFO.mDB_2_IP[0], mSERVER_INFO.mDB_2_IP[1], mSERVER_INFO.mDB_2_PORT
			, g_env.db2_name_str_obj.c_str (), mSERVER_INFO.mDB_2_ID, mSERVER_INFO.mDB_2_PASSWORD) < 0) {
		return false;
	}
	if(!mDB02.connect()) {
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB02.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if(mDB02.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#if 0
	if(!mDB02_FOR_THREAD.connect(mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_PORT
				, g_env.db_name_str_obj.c_str() , mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD)) {
		return FALSE;
	}
#endif

	if(mDB02_FOR_THREAD.set_db_conn_info(mSERVER_INFO.mDB_2_IP[0], mSERVER_INFO.mDB_2_IP[1], mSERVER_INFO.mDB_2_PORT
			, g_env.db2_name_str_obj.c_str (), mSERVER_INFO.mDB_2_ID, mSERVER_INFO.mDB_2_PASSWORD) < 0) {
		return false;
	}
	if(!mDB02_FOR_THREAD.connect()) {
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB02_FOR_THREAD.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if(mDB02_FOR_THREAD.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
	g_mLOG = new CLogging;
	g_mThreadLOG = new CLogging;
	g_mLOG->set_log_file_path("/user/service/logs/ts2_player_userd/QUERY_LOG_", "a+");
	g_mThreadLOG->set_log_file_path("/user/service/logs/ts2_player_userd/QUERY_FOR_THREAD_LOG_", "a+");

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
		LOG_TO_FILE_1("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB01.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if(mDB01.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
	LOG_TO_FILE_1("![%s] : reconnected\n", __FUNCTION__);
	return TRUE;
}
//RECONNECT_TO_DATABASE01_FOR_THREAD
BOOL MyDB::RECONNECT_TO_DATABASE01_FOR_THREAD( void )
{
	if( mDB01_FOR_THREAD.IsConnected() )
	{
		return TRUE;
	}
	if( !mDB01_FOR_THREAD.Reconnect() )
	{
		LOG_TO_FILE_1("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB01_FOR_THREAD.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if(mDB01_FOR_THREAD.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
	LOG_TO_FILE_1("![%s] : reconnected\n", __FUNCTION__);
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
		LOG_TO_FILE_1("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB02.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if(mDB02.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
	LOG_TO_FILE_1("![%s] : reconnected\n", __FUNCTION__);
	return TRUE;
}
//RECONNECT_TO_DATABASE02_FOR_THREAD
BOOL MyDB::RECONNECT_TO_DATABASE02_FOR_THREAD( void )
{
	if( mDB02_FOR_THREAD.IsConnected() )
	{
		return TRUE;
	}
	if( !mDB02_FOR_THREAD.Reconnect() )
	{
		LOG_TO_FILE_1("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB02_FOR_THREAD.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if(mDB02_FOR_THREAD.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0)  {
		LOG_TO_FILE_2("[%s] DB character false(%s)! \n" , __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
	LOG_TO_FILE_1("![%s] : reconnected\n", __FUNCTION__);
	return TRUE;
}
//MAKE_QUERY_FOR_SAVE
void MyDB::MakeQueryForSave( int tSort, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, int tLoginPremiumPCRoom)
{
	int index01;
	int index02;
	char tempString01[1000];
	char uSaveItem[701];
	char aEquip[326];
	char aInventory[3457];
    char aTrade[201];
	char aStoreItem[1401];
	char aSkill[181];
	char aHotKey[421];
	char aQuestInfo[26];
	char aFriend[121];
	
	switch( tSort )
	{
	case 1 :
		uSaveItem[0] = '\0';
		for( index01 = 0 ; index01 < MAX_SAVE_ITEM_SLOT_NUM ; index01++ )
		{
			sprintf( tempString01, "%05d%03d%09d%08d", ( tAvatarInfo->uSaveItem[index01][0] % 100000 ), ( tAvatarInfo->uSaveItem[index01][1] % 1000 ), ( tAvatarInfo->uSaveItem[index01][2] % 1000000000 ), ( tAvatarInfo->uSaveItem[index01][3] % 100000000 ) );
			strcat( uSaveItem, tempString01 );
		}
		sprintf( mQUERY_FOR_THREAD, 
				"update %s set uSaveMoney=%d,uSaveItem='%s' "
				"where uID='%s' AND aWorldNumber = '%d'; "
				, mSERVER_INFO.mDB_1_Table07, tAvatarInfo->uSaveMoney
				, uSaveItem, tID, g_env.world_num );
		return;
	case 2 :
		aEquip[0] = '\0';
		for( index01 = 0 ; index01 < MAX_EQUIP_SLOT_NUM ; index01++ )
		{
			sprintf( tempString01, "%05d%03d%09d%08d", ( tAvatarInfo->aEquip[index01][0] % 100000 ), ( tAvatarInfo->aEquip[index01][1] % 1000 ), ( tAvatarInfo->aEquip[index01][2] % 1000000000 ), ( tAvatarInfo->aEquip[index01][3] % 100000000 ) );
			strcat( aEquip, tempString01 );
		}
		aInventory[0] = '\0';
		for( index01 = 0 ; index01 < 2 ; index01++ )
		{
			for( index02 = 0 ; index02 < MAX_INVENTORY_SLOT_NUM ; index02++ )
			{
				sprintf( tempString01, "%05d%01d%01d%03d%09d%08d", ( tAvatarInfo->aInventory[index01][index02][0] % 100000 ), ( tAvatarInfo->aInventory[index01][index02][1] % 10 ), ( tAvatarInfo->aInventory[index01][index02][2] % 10 ), ( tAvatarInfo->aInventory[index01][index02][3] % 1000 ), ( tAvatarInfo->aInventory[index01][index02][4] % 1000000000 ), ( tAvatarInfo->aInventory[index01][index02][5] % 100000000 ) );
				strcat( aInventory, tempString01 );
			}
		}
		aTrade[0] = '\0';
		for( index01 = 0 ; index01 < MAX_TRADE_SLOT_NUM ; index01++ )
		{
			sprintf( tempString01, "%05d%03d%09d%08d", ( tAvatarInfo->aTrade[index01][0] % 100000 ), ( tAvatarInfo->aTrade[index01][1] % 1000 ), ( tAvatarInfo->aTrade[index01][2] % 1000000000 ), ( tAvatarInfo->aTrade[index01][3] % 100000000 ) );
			strcat( aTrade, tempString01 );
		}
		aStoreItem[0] = '\0';
		for( index01 = 0 ; index01 < 2 ; index01++ )
		{
			for( index02 = 0 ; index02 < MAX_STORE_ITEM_SLOT_NUM ; index02++ )
			{
				sprintf( tempString01, "%05d%03d%09d%08d", ( tAvatarInfo->aStoreItem[index01][index02][0] % 100000 ), ( tAvatarInfo->aStoreItem[index01][index02][1] % 1000 ), ( tAvatarInfo->aStoreItem[index01][index02][2] % 1000000000 ), ( tAvatarInfo->aStoreItem[index01][index02][3] % 100000000 ) );
				strcat( aStoreItem, tempString01 );
			}
		}
		aSkill[0] = '\0';
		for( index01 = 0 ; index01 < MAX_SKILL_SLOT_NUM ; index01++ )
		{
			sprintf( tempString01, "%03d%03d", ( tAvatarInfo->aSkill[index01][0] % 1000 ), ( tAvatarInfo->aSkill[index01][1] % 1000 ) );
			strcat( aSkill, tempString01 );
		}
		aHotKey[0] = '\0';
		for( index01 = 0 ; index01 < 3 ; index01++ )
		{
			for( index02 = 0 ; index02 < MAX_HOT_KEY_NUM ; index02++ )
			{
				sprintf( tempString01, "%05d%03d%02d", ( tAvatarInfo->aHotKey[index01][index02][0] % 100000 ), ( tAvatarInfo->aHotKey[index01][index02][1] % 1000 ), ( tAvatarInfo->aHotKey[index01][index02][2] % 100 ) );
				strcat( aHotKey, tempString01 );
			}
		}
		aQuestInfo[0] = '\0';
		sprintf( tempString01, "%05d%05d%05d%05d%05d", ( tAvatarInfo->aQuestInfo[0] % 100000 ), ( tAvatarInfo->aQuestInfo[1] % 100000 ), ( tAvatarInfo->aQuestInfo[2] % 100000 ), ( tAvatarInfo->aQuestInfo[3] % 100000 ), ( tAvatarInfo->aQuestInfo[4] % 100000 ) );
		strcat( aQuestInfo, tempString01 );
		//FillMemory( &aFriend[0], ( MAX_FRIEND_NUM * ( MAX_AVATAR_NAME_LENGTH - 1 ) ), '@' );
		memset(aFriend, '@', ( MAX_FRIEND_NUM * ( MAX_AVATAR_NAME_LENGTH - 1 ) ));
		for( index01 = 0 ; index01 < MAX_FRIEND_NUM ; index01++ )
		{
			CopyMemory( &aFriend[( index01 * 12 + 0 )], &tAvatarInfo->aFriend[index01][0], strlen( tAvatarInfo->aFriend[index01] ) );
		}
		aFriend[120] = '\0';
		if(2 == tLoginPremiumPCRoom)
		{
#ifdef __TK__
			sprintf(
				mQUERY_FOR_THREAD, "update %s set aVisibleState=%d,aSpecialState=%d,aPlayTime1=%d,aPlayTime2=%d"
				",aPlayTime3=%d,aKillOtherTribe=%d,aTribe=%d,aGender=%d,aHeadType=%d,aFaceType=%d,aLevel1=%d,aLevel2=%d"
				",aGeneralExperience1=%d,aGeneralExperience2=%d,aVitality=%d,aStrength=%d,aKi=%d,aWisdom=%d,aEatLifePotion=%d"
				",aEatManaPotion=%d,aStateBonusPoint=%d,aSkillPoint=%d,aEquip='%s',aExpandInventoryDate=%d,aMoney=%d"
				",aInventory='%s',aTradeMoney=%d,aTrade='%s',aExpandStoreDate=%d,aStoreMoney=%d,aStoreItem='%s',aSkill='%s'"
				",aHotKey='%s',aQuestInfo='%s',aFriend='%s',aTeacher='%s',aStudent='%s',aTeacherPoint=%d,aGuildMarkNum=%d"
				",aGuildMarkEffect=%d,aLogoutInfo01=%d,aLogoutInfo02=%d,aLogoutInfo03=%d,aLogoutInfo04=%d,aLogoutInfo05=%d"
				",aLogoutInfo06=%d,aProtectForDeath=%d,aProtectForDestroy=%d,aDoubleExpTime1=%d,aDoubleExpTime2=%d"
				",aDoubleExpTime3=%d,aDoubleKillNumTime=%d,aDoubleKillExpTime=%d,aNineTowerKeyNum=%d,aZone101TypeTime=%d"
				",aZone125TypeTime=%d,aKillMonsterNum=%d,aLevelZoneKeyNum=%d,aSearchAndBuyDate=%d,aLifePotionConvertNum=%d"
				",aManaPotionConvertNum=%d,aTribeVoteDate=%d,aUse_AutoPotion_Date=%d,aUse_AutoPotion_Time=%d,aAutoLifeRatio=%d"
				",aAutoManaRatio=%d,aAnimal01=%d,aAnimal02=%d,aAnimal03=%d,aAnimal04=%d,aAnimal05=%d,aAnimal06=%d,aAnimal07=%d"
				",aAnimal08=%d,aAnimal09=%d,aAnimal10=%d,aAnimalIndex=%d,aAnimalTime=%d,aDoubleDropTime=%d, iCriminal_Record=%d"
				",iEnter_The_Prison=%d, iKill_Monster_Count = %d,aEatStrengthPotion=%d,aEatWisdomPotion=%d,aPat_Exp_x2_Time=%d"
				",aPat_User_Exp_x2_Time=%d,aFiveExpTime=%d,aZone84Time=%d, iSilverOrnamentRemainsTime=%d"
				", iGoldOrnamentRemainsTime=%d, iUseOrnament=%d, aPackSilverDate=%d, aPackGoldDate=%d, aPackDiamondDate=%d"
				", aPackSilverDateMobile=%d, aPackGoldDateMobile=%d, aPackDiamondDateMobile=%d, aLevelZoneKeyNum2 = %d"
				", aDoubleKillNumTime2 = %d, aKillMonsterNum2=%d "
#ifdef __GOD__
				", aAddItemValue = %d, aHighItemValue = %d, aDropItemTime = %d, aTribeCallValue = %d "
				", aUpgradeValue = %d, aBonusItemValue = %d, aKillOtherTribeEvent = %d"
				", aTeacherPointEvent = %d, aPlayTimeEvent = %d, aProtectForUpgrade = %d "	
#endif
				"where aName='%s' AND aWorldNumber='%d'; ",
				mSERVER_INFO.mDB_1_Table09,
				tAvatarInfo->aVisibleState,
				tAvatarInfo->aSpecialState,
				tAvatarInfo->aPlayTime1,
				tAvatarInfo->aPlayTime2,
				tAvatarInfo->aPlayTime3,
				tAvatarInfo->aKillOtherTribe,
				tAvatarInfo->aTribe,
				tAvatarInfo->aGender,
				tAvatarInfo->aHeadType,
				tAvatarInfo->aFaceType,
				tAvatarInfo->aLevel1,
				tAvatarInfo->aLevel2,
				tAvatarInfo->aGeneralExperience1,
				tAvatarInfo->aGeneralExperience2,
				tAvatarInfo->aVitality,
				tAvatarInfo->aStrength,
				tAvatarInfo->aKi,
				tAvatarInfo->aWisdom,
				tAvatarInfo->aEatLifePotion,
				tAvatarInfo->aEatManaPotion,
				tAvatarInfo->aStateBonusPoint,
				tAvatarInfo->aSkillPoint,
				aEquip,
				tAvatarInfo->aExpandInventoryDate,
				tAvatarInfo->aMoney,
				aInventory,
				tAvatarInfo->aTradeMoney,
				aTrade,
				tAvatarInfo->aExpandStoreDate,
				tAvatarInfo->aStoreMoney,
				aStoreItem,
				aSkill,
				aHotKey,
				aQuestInfo,
				aFriend,
				tAvatarInfo->aTeacher,
				tAvatarInfo->aStudent,
				tAvatarInfo->aTeacherPoint,
				tAvatarInfo->aGuildMarkNum,
				tAvatarInfo->aGuildMarkEffect,
				tAvatarInfo->aLogoutInfo[0],
				tAvatarInfo->aLogoutInfo[1],
				tAvatarInfo->aLogoutInfo[2],
				tAvatarInfo->aLogoutInfo[3],
				tAvatarInfo->aLogoutInfo[4],
				tAvatarInfo->aLogoutInfo[5],
				tAvatarInfo->aProtectForDeath,
				tAvatarInfo->aProtectForDestroy,
				tAvatarInfo->aDoubleExpTime1,
				tAvatarInfo->aDoubleExpTime2,
				tAvatarInfo->aDoubleExpTime3,
				tAvatarInfo->aDoubleKillNumTime,
				tAvatarInfo->aDoubleKillExpTime,
				tAvatarInfo->aNineTowerKeyNum,
				tAvatarInfo->aZone101TypeTime,
				tAvatarInfo->aZone125TypeTime,
				tAvatarInfo->aKillMonsterNum,
				tAvatarInfo->aLevelZoneKeyNum,
				tAvatarInfo->aSearchAndBuyDate,
				tAvatarInfo->aLifePotionConvertNum,
				tAvatarInfo->aManaPotionConvertNum,
				tAvatarInfo->aTribeVoteDate,
				tAvatarInfo->aUse_AutoPotion_Date,
				tAvatarInfo->aUse_AutoPotion_Time,
				tAvatarInfo->aAutoLifeRatio,
				tAvatarInfo->aAutoManaRatio,
				tAvatarInfo->aAnimal[0],
				tAvatarInfo->aAnimal[1],
				tAvatarInfo->aAnimal[2],
				tAvatarInfo->aAnimal[3],
				tAvatarInfo->aAnimal[4],
				tAvatarInfo->aAnimal[5],
				tAvatarInfo->aAnimal[6],
				tAvatarInfo->aAnimal[7],
				tAvatarInfo->aAnimal[8],
				tAvatarInfo->aAnimal[9],
				tAvatarInfo->aAnimalIndex,
				tAvatarInfo->aAnimalTime,
				tAvatarInfo->aDoubleDropTime,

				//@{ auto quiz
				tAvatarInfo->iCriminal_Record,
				tAvatarInfo->iEnter_The_Prison,
				tAvatarInfo->iKill_Monster_Count,
				//@}
				tAvatarInfo->aEatStrengthPotion,
				tAvatarInfo->aEatWisdomPotion,
				tAvatarInfo->aPat_Exp_x2_Time,
				tAvatarInfo->aPat_User_Exp_x2_Time,
				tAvatarInfo->aFiveExpTime,
				tAvatarInfo->aZone84Time,

				/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
				tAvatarInfo -> iSilverOrnamentRemainsTime,
				tAvatarInfo -> iGoldOrnamentRemainsTime,
				tAvatarInfo -> iUseOrnament,					
				/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
				/** 2009. 11. 23 : 패키지 아이템개발 (wolf) */
				tAvatarInfo -> aPackSilverDate,
				tAvatarInfo -> aPackGoldDate,
				tAvatarInfo -> aPackDiamondDate,
				tAvatarInfo -> aPackSilverDateMobile,
				tAvatarInfo -> aPackGoldDateMobile,
				tAvatarInfo -> aPackDiamondDateMobile,
				/** 2009. 11. 23 : 패키지 아이템개발 (wolf) */
				tAvatarInfo -> aLevelZoneKeyNum2, 
				tAvatarInfo -> aDoubleKillNumTime2,
				tAvatarInfo->aKillMonsterNum2
#ifdef __GOD__
				, tAvatarInfo->aAddItemValue, tAvatarInfo->aHighItemValue, tAvatarInfo->aDropItemTime
				, tAvatarInfo->aTribeCallValue, tAvatarInfo->aUpgradeValue
				, tAvatarInfo->aBonusItemValue, tAvatarInfo->aKillOtherTribeEvent, tAvatarInfo->aTeacherPointEvent
				,	tAvatarInfo->aPlayTimeEvent, tAvatarInfo->aProtectForUpgrade
#endif

				,tAvatarInfo->aName
				,g_env.world_num
				);
#else
		sprintf(
				mQUERY_FOR_THREAD, "update %s set aVisibleState=%d,aSpecialState=%d,aPlayTime1=%d,aPlayTime2=%d"
				",aPlayTime3=%d,aKillOtherTribe=%d,aTribe=%d,aGender=%d,aHeadType=%d,aFaceType=%d,aLevel1=%d,aLevel2=%d"
				",aGeneralExperience1=%d,aGeneralExperience2=%d,aVitality=%d,aStrength=%d,aKi=%d,aWisdom=%d,aEatLifePotion=%d"
				",aEatManaPotion=%d,aStateBonusPoint=%d,aSkillPoint=%d,aEquip='%s',aExpandInventoryDate=%d,aMoney=%d"
				",aInventory='%s',aTradeMoney=%d,aTrade='%s',aExpandStoreDate=%d,aStoreMoney=%d,aStoreItem='%s',aSkill='%s'"
				",aHotKey='%s',aQuestInfo='%s',aFriend='%s',aTeacher='%s',aStudent='%s',aTeacherPoint=%d,aGuildMarkNum=%d"
				",aGuildMarkEffect=%d,aLogoutInfo01=%d,aLogoutInfo02=%d,aLogoutInfo03=%d,aLogoutInfo04=%d,aLogoutInfo05=%d"
				",aLogoutInfo06=%d,aProtectForDeath=%d,aProtectForDestroy=%d,aDoubleExpTime1=%d,aDoubleExpTime2=%d"
				",aDoubleExpTime3=%d,aDoubleKillNumTime=%d,aDoubleKillExpTime=%d,aNineTowerKeyNum=%d,aZone101TypeTime=%d"
				",aZone125TypeTime=%d,aKillMonsterNum=%d,aLevelZoneKeyNum=%d,aSearchAndBuyDate=%d,aLifePotionConvertNum=%d"
				",aManaPotionConvertNum=%d,aTribeVoteDate=%d,aUse_AutoPotion_Date=%d,aUse_AutoPotion_Time=%d"
				",aAutoLifeRatio=%d,aAutoManaRatio=%d,aAnimal01=%d,aAnimal02=%d,aAnimal03=%d,aAnimal04=%d,aAnimal05=%d"
				",aAnimal06=%d,aAnimal07=%d,aAnimal08=%d,aAnimal09=%d,aAnimal10=%d,aAnimalIndex=%d,aAnimalTime=%d"
				",aDoubleDropTime=%d, iCriminal_Record=%d,iEnter_The_Prison=%d, iKill_Monster_Count = %d"
				",aEatStrengthPotion=%d,aEatWisdomPotion=%d,aPat_Exp_x2_Time=%d,aPat_User_Exp_x2_Time=%d,aFiveExpTime=%d"
				",aZone84Time=%d, iSilverOrnamentRemainsTime = %d, iGoldOrnamentRemainsTime = %d, iUseOrnament = %d"
				", aLevelZoneKeyNum2 = %d, aDoubleKillNumTime2 = %d, aKillMonsterNum2=%d "
#ifdef __GOD__
				", aAddItemValue = %d, aHighItemValue = %d, aDropItemTime = %d, aTribeCallValue = %d "
				", aUpgradeValue = %d, aBonusItemValue = %d, aKillOtherTribeEvent = %d"
				", aTeacherPointEvent = %d, aPlayTimeEvent = %d, aProtectForUpgrade = %d "	
#endif
				"where aName='%s' AND aWorldNumber = '%d'; ",
				mSERVER_INFO.mDB_1_Table09,
				tAvatarInfo->aVisibleState,
				tAvatarInfo->aSpecialState,
				tAvatarInfo->aPlayTime1,
				tAvatarInfo->aPlayTime2,
				tAvatarInfo->aPlayTime3,
				tAvatarInfo->aKillOtherTribe,
				tAvatarInfo->aTribe,
				tAvatarInfo->aGender,
				tAvatarInfo->aHeadType,
				tAvatarInfo->aFaceType,
				tAvatarInfo->aLevel1,
				tAvatarInfo->aLevel2,
				tAvatarInfo->aGeneralExperience1,
				tAvatarInfo->aGeneralExperience2,
				tAvatarInfo->aVitality,
				tAvatarInfo->aStrength,
				tAvatarInfo->aKi,
				tAvatarInfo->aWisdom,
				tAvatarInfo->aEatLifePotion,
				tAvatarInfo->aEatManaPotion,
				tAvatarInfo->aStateBonusPoint,
				tAvatarInfo->aSkillPoint,
				aEquip,
				tAvatarInfo->aExpandInventoryDate,
				tAvatarInfo->aMoney,
				aInventory,
				tAvatarInfo->aTradeMoney,
				aTrade,
				tAvatarInfo->aExpandStoreDate,
				tAvatarInfo->aStoreMoney,
				aStoreItem,
				aSkill,
				aHotKey,
				aQuestInfo,
				aFriend,
				tAvatarInfo->aTeacher,
				tAvatarInfo->aStudent,
				tAvatarInfo->aTeacherPoint,
				tAvatarInfo->aGuildMarkNum,
				tAvatarInfo->aGuildMarkEffect,
				tAvatarInfo->aLogoutInfo[0],
				tAvatarInfo->aLogoutInfo[1],
				tAvatarInfo->aLogoutInfo[2],
				tAvatarInfo->aLogoutInfo[3],
				tAvatarInfo->aLogoutInfo[4],
				tAvatarInfo->aLogoutInfo[5],
				tAvatarInfo->aProtectForDeath,
				tAvatarInfo->aProtectForDestroy,
				tAvatarInfo->aDoubleExpTime1,
				tAvatarInfo->aDoubleExpTime2,
				tAvatarInfo->aDoubleExpTime3,
				tAvatarInfo->aDoubleKillNumTime,
				tAvatarInfo->aDoubleKillExpTime,
				tAvatarInfo->aNineTowerKeyNum,
				tAvatarInfo->aZone101TypeTime,
				tAvatarInfo->aZone125TypeTime,
				tAvatarInfo->aKillMonsterNum,
				tAvatarInfo->aLevelZoneKeyNum,
				tAvatarInfo->aSearchAndBuyDate,
				tAvatarInfo->aLifePotionConvertNum,
				tAvatarInfo->aManaPotionConvertNum,
				tAvatarInfo->aTribeVoteDate,
				tAvatarInfo->aUse_AutoPotion_Date,
				tAvatarInfo->aUse_AutoPotion_Time,
				tAvatarInfo->aAutoLifeRatio,
				tAvatarInfo->aAutoManaRatio,
				tAvatarInfo->aAnimal[0],
				tAvatarInfo->aAnimal[1],
				tAvatarInfo->aAnimal[2],
				tAvatarInfo->aAnimal[3],
				tAvatarInfo->aAnimal[4],
				tAvatarInfo->aAnimal[5],
				tAvatarInfo->aAnimal[6],
				tAvatarInfo->aAnimal[7],
				tAvatarInfo->aAnimal[8],
				tAvatarInfo->aAnimal[9],
				tAvatarInfo->aAnimalIndex,
				tAvatarInfo->aAnimalTime,
				tAvatarInfo->aDoubleDropTime,

				//@{ auto quiz
				tAvatarInfo->iCriminal_Record,
				tAvatarInfo->iEnter_The_Prison,
				tAvatarInfo->iKill_Monster_Count,
				//@}
				tAvatarInfo->aEatStrengthPotion,
				tAvatarInfo->aEatWisdomPotion,
				tAvatarInfo->aPat_Exp_x2_Time,
				tAvatarInfo->aPat_User_Exp_x2_Time,
				tAvatarInfo->aFiveExpTime,
				tAvatarInfo->aZone84Time,

				/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
				tAvatarInfo -> iSilverOrnamentRemainsTime,
				tAvatarInfo -> iGoldOrnamentRemainsTime,
				tAvatarInfo -> iUseOrnament,					
				/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */

				tAvatarInfo -> aLevelZoneKeyNum2, 
				tAvatarInfo -> aDoubleKillNumTime2,
				tAvatarInfo->aKillMonsterNum2
#ifdef __GOD__
				, tAvatarInfo->aAddItemValue, tAvatarInfo->aHighItemValue, tAvatarInfo->aDropItemTime
				, tAvatarInfo->aTribeCallValue, tAvatarInfo->aUpgradeValue
				, tAvatarInfo->aBonusItemValue, tAvatarInfo->aKillOtherTribeEvent, tAvatarInfo->aTeacherPointEvent
				,	tAvatarInfo->aPlayTimeEvent, tAvatarInfo->aProtectForUpgrade
#endif
				,tAvatarInfo->aName
				,g_env.world_num
				);
#endif			
		}
		else{
#ifdef __TK__
			sprintf(
				mQUERY_FOR_THREAD, "update %s set aVisibleState=%d,aSpecialState=%d,aPlayTime1=%d,aPlayTime2=%d,aPlayTime3=%d"
				",aKillOtherTribe=%d,aTribe=%d,aGender=%d,aHeadType=%d,aFaceType=%d,aLevel1=%d,aLevel2=%d"
				",aGeneralExperience1=%d,aGeneralExperience2=%d,aVitality=%d,aStrength=%d,aKi=%d,aWisdom=%d"
				",aEatLifePotion=%d,aEatManaPotion=%d,aStateBonusPoint=%d,aSkillPoint=%d,aEquip='%s',aExpandInventoryDate=%d"
				",aMoney=%d,aInventory='%s',aTradeMoney=%d,aTrade='%s',aExpandStoreDate=%d,aStoreMoney=%d,aStoreItem='%s'"
				",aSkill='%s',aHotKey='%s',aQuestInfo='%s',aFriend='%s',aTeacher='%s',aStudent='%s',aTeacherPoint=%d"
				",aGuildMarkNum=%d,aGuildMarkEffect=%d,aLogoutInfo01=%d,aLogoutInfo02=%d,aLogoutInfo03=%d,aLogoutInfo04=%d"
				",aLogoutInfo05=%d,aLogoutInfo06=%d,aProtectForDeath=%d,aProtectForDestroy=%d,aDoubleExpTime1=%d"
				",aDoubleExpTime2=%d,aDoubleExpTime3=%d,aDoubleKillNumTime=%d,aDoubleKillExpTime=%d,aNineTowerKeyNum=%d"
				",aZone101TypeTime=%d,aZone125TypeTime=%d,aZone126TypeTime=%d,aKillMonsterNum=%d,aLevelZoneKeyNum=%d"
				",aSearchAndBuyDate=%d,aLifePotionConvertNum=%d,aManaPotionConvertNum=%d,aTribeVoteDate=%d"
				",aUse_AutoPotion_Date=%d,aUse_AutoPotion_Time=%d,aAutoLifeRatio=%d,aAutoManaRatio=%d,aAnimal01=%d"
				",aAnimal02=%d,aAnimal03=%d,aAnimal04=%d,aAnimal05=%d,aAnimal06=%d,aAnimal07=%d,aAnimal08=%d,aAnimal09=%d"
				",aAnimal10=%d,aAnimalIndex=%d,aAnimalTime=%d,aDoubleDropTime=%d, iCriminal_Record=%d,iEnter_The_Prison=%d"
				", iKill_Monster_Count = %d,aEatStrengthPotion=%d,aEatWisdomPotion=%d,aPat_Exp_x2_Time=%d"
				",aPat_User_Exp_x2_Time=%d,aFiveExpTime=%d,aZone84Time=%d, iSilverOrnamentRemainsTime=%d"
				", iGoldOrnamentRemainsTime=%d, iUseOrnament=%d, aPackSilverDate=%d, aPackGoldDate=%d, aPackDiamondDate=%d"
				", aPackSilverDateMobile=%d, aPackGoldDateMobile=%d, aPackDiamondDateMobile=%d, aLevelZoneKeyNum2 = %d"
				", aDoubleKillNumTime2 = %d, aKillMonsterNum2=%d "
#ifdef __GOD__
				", aAddItemValue = %d, aHighItemValue = %d, aDropItemTime = %d, aTribeCallValue = %d "
				", aUpgradeValue = %d, aBonusItemValue = %d, aKillOtherTribeEvent = %d"
				", aTeacherPointEvent = %d, aPlayTimeEvent = %d, aProtectForUpgrade = %d "	
#endif
				" where aName='%s' AND aWorldNumber = '%d'; ",
				mSERVER_INFO.mDB_1_Table09,
				tAvatarInfo->aVisibleState,
				tAvatarInfo->aSpecialState,
				tAvatarInfo->aPlayTime1,
				tAvatarInfo->aPlayTime2,
				tAvatarInfo->aPlayTime3,
				tAvatarInfo->aKillOtherTribe,
				tAvatarInfo->aTribe,
				tAvatarInfo->aGender,
				tAvatarInfo->aHeadType,
				tAvatarInfo->aFaceType,
				tAvatarInfo->aLevel1,
				tAvatarInfo->aLevel2,
				tAvatarInfo->aGeneralExperience1,
				tAvatarInfo->aGeneralExperience2,
				tAvatarInfo->aVitality,
				tAvatarInfo->aStrength,
				tAvatarInfo->aKi,
				tAvatarInfo->aWisdom,
				tAvatarInfo->aEatLifePotion,
				tAvatarInfo->aEatManaPotion,
				tAvatarInfo->aStateBonusPoint,
				tAvatarInfo->aSkillPoint,
				aEquip,
				tAvatarInfo->aExpandInventoryDate,
				tAvatarInfo->aMoney,
				aInventory,
				tAvatarInfo->aTradeMoney,
				aTrade,
				tAvatarInfo->aExpandStoreDate,
				tAvatarInfo->aStoreMoney,
				aStoreItem,
				aSkill,
				aHotKey,
				aQuestInfo,
				aFriend,
				tAvatarInfo->aTeacher,
				tAvatarInfo->aStudent,
				tAvatarInfo->aTeacherPoint,
				tAvatarInfo->aGuildMarkNum,
				tAvatarInfo->aGuildMarkEffect,
				tAvatarInfo->aLogoutInfo[0],
				tAvatarInfo->aLogoutInfo[1],
				tAvatarInfo->aLogoutInfo[2],
				tAvatarInfo->aLogoutInfo[3],
				tAvatarInfo->aLogoutInfo[4],
				tAvatarInfo->aLogoutInfo[5],
				tAvatarInfo->aProtectForDeath,
				tAvatarInfo->aProtectForDestroy,
				tAvatarInfo->aDoubleExpTime1,
				tAvatarInfo->aDoubleExpTime2,
				tAvatarInfo->aDoubleExpTime3,
				tAvatarInfo->aDoubleKillNumTime,
				tAvatarInfo->aDoubleKillExpTime,
				tAvatarInfo->aNineTowerKeyNum,
				tAvatarInfo->aZone101TypeTime,
				tAvatarInfo->aZone125TypeTime,
				tAvatarInfo->aZone126TypeTime,
				tAvatarInfo->aKillMonsterNum,
				tAvatarInfo->aLevelZoneKeyNum,
				tAvatarInfo->aSearchAndBuyDate,
				tAvatarInfo->aLifePotionConvertNum,
				tAvatarInfo->aManaPotionConvertNum,
				tAvatarInfo->aTribeVoteDate,
				tAvatarInfo->aUse_AutoPotion_Date,
				tAvatarInfo->aUse_AutoPotion_Time,
				tAvatarInfo->aAutoLifeRatio,
				tAvatarInfo->aAutoManaRatio,
				tAvatarInfo->aAnimal[0],
				tAvatarInfo->aAnimal[1],
				tAvatarInfo->aAnimal[2],
				tAvatarInfo->aAnimal[3],
				tAvatarInfo->aAnimal[4],
				tAvatarInfo->aAnimal[5],
				tAvatarInfo->aAnimal[6],
				tAvatarInfo->aAnimal[7],
				tAvatarInfo->aAnimal[8],
				tAvatarInfo->aAnimal[9],
				tAvatarInfo->aAnimalIndex,
				tAvatarInfo->aAnimalTime,
				tAvatarInfo->aDoubleDropTime,
				//@{ auto quiz
				tAvatarInfo->iCriminal_Record,
				tAvatarInfo->iEnter_The_Prison,
				tAvatarInfo->iKill_Monster_Count,
				//@}
				tAvatarInfo->aEatStrengthPotion,
				tAvatarInfo->aEatWisdomPotion,
				tAvatarInfo->aPat_Exp_x2_Time,
				tAvatarInfo->aPat_User_Exp_x2_Time,
				tAvatarInfo->aFiveExpTime,
				tAvatarInfo->aZone84Time,

				/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
				tAvatarInfo -> iSilverOrnamentRemainsTime, 
				tAvatarInfo -> iGoldOrnamentRemainsTime, 
				tAvatarInfo -> iUseOrnament,
				/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
				/** 2009. 11. 23 : 패키지 아이템 개발 (wolf) */
				tAvatarInfo -> aPackSilverDate,
				tAvatarInfo -> aPackGoldDate,
				tAvatarInfo -> aPackDiamondDate,
				tAvatarInfo -> aPackSilverDateMobile,
				tAvatarInfo -> aPackGoldDateMobile,
				tAvatarInfo -> aPackDiamondDateMobile,
				/** 2009. 11. 23 : 패키지 아이템 개발 (wolf) */

				tAvatarInfo -> aLevelZoneKeyNum2, 
				tAvatarInfo -> aDoubleKillNumTime2,
				tAvatarInfo->aKillMonsterNum2
#ifdef __GOD__
				, tAvatarInfo->aAddItemValue, tAvatarInfo->aHighItemValue, tAvatarInfo->aDropItemTime
				, tAvatarInfo->aTribeCallValue, tAvatarInfo->aUpgradeValue
				, tAvatarInfo->aBonusItemValue, tAvatarInfo->aKillOtherTribeEvent, tAvatarInfo->aTeacherPointEvent
				,	tAvatarInfo->aPlayTimeEvent, tAvatarInfo->aProtectForUpgrade
#endif
				,tAvatarInfo->aName
				,g_env.world_num
				);
#else
			sprintf(
				mQUERY_FOR_THREAD, "update %s set aVisibleState=%d,aSpecialState=%d,aPlayTime1=%d,aPlayTime2=%d"
				",aPlayTime3=%d,aKillOtherTribe=%d,aTribe=%d,aGender=%d,aHeadType=%d,aFaceType=%d,aLevel1=%d,aLevel2=%d"
				",aGeneralExperience1=%d,aGeneralExperience2=%d,aVitality=%d,aStrength=%d,aKi=%d,aWisdom=%d"
				",aEatLifePotion=%d,aEatManaPotion=%d,aStateBonusPoint=%d,aSkillPoint=%d,aEquip='%s',aExpandInventoryDate=%d"
				",aMoney=%d,aInventory='%s',aTradeMoney=%d,aTrade='%s',aExpandStoreDate=%d,aStoreMoney=%d,aStoreItem='%s'"
				",aSkill='%s',aHotKey='%s',aQuestInfo='%s',aFriend='%s',aTeacher='%s',aStudent='%s',aTeacherPoint=%d"
				",aGuildMarkNum=%d,aGuildMarkEffect=%d,aLogoutInfo01=%d,aLogoutInfo02=%d,aLogoutInfo03=%d,aLogoutInfo04=%d"
				",aLogoutInfo05=%d,aLogoutInfo06=%d,aProtectForDeath=%d,aProtectForDestroy=%d,aDoubleExpTime1=%d"
				",aDoubleExpTime2=%d,aDoubleExpTime3=%d,aDoubleKillNumTime=%d,aDoubleKillExpTime=%d,aNineTowerKeyNum=%d"
				",aZone101TypeTime=%d,aZone125TypeTime=%d,aZone126TypeTime=%d,aKillMonsterNum=%d,aLevelZoneKeyNum=%d"
				",aSearchAndBuyDate=%d,aLifePotionConvertNum=%d,aManaPotionConvertNum=%d,aTribeVoteDate=%d"
				",aUse_AutoPotion_Date=%d,aUse_AutoPotion_Time=%d,aAutoLifeRatio=%d,aAutoManaRatio=%d,aAnimal01=%d"
				",aAnimal02=%d,aAnimal03=%d,aAnimal04=%d,aAnimal05=%d,aAnimal06=%d,aAnimal07=%d,aAnimal08=%d,aAnimal09=%d"
				",aAnimal10=%d,aAnimalIndex=%d,aAnimalTime=%d,aDoubleDropTime=%d, iCriminal_Record=%d,iEnter_The_Prison=%d"
				", iKill_Monster_Count = %d,aEatStrengthPotion=%d,aEatWisdomPotion=%d,aPat_Exp_x2_Time=%d"
				",aPat_User_Exp_x2_Time=%d,aFiveExpTime=%d,aZone84Time=%d, iSilverOrnamentRemainsTime = %d"
				", iGoldOrnamentRemainsTime = %d, iUseOrnament = %d, aLevelZoneKeyNum2 = %d, aDoubleKillNumTime2 = %d"
				", aKillMonsterNum2=%d "
#ifdef __GOD__
				", aAddItemValue = %d, aHighItemValue = %d, aDropItemTime = %d, aTribeCallValue = %d "
				", aUpgradeValue = %d, aBonusItemValue = %d, aKillOtherTribeEvent = %d"
				", aTeacherPointEvent = %d, aPlayTimeEvent = %d, aProtectForUpgrade = %d "	
#endif
				" where aName='%s' AND aWorldNumber = '%d'; ",
				mSERVER_INFO.mDB_1_Table09,
				tAvatarInfo->aVisibleState,
				tAvatarInfo->aSpecialState,
				tAvatarInfo->aPlayTime1,
				tAvatarInfo->aPlayTime2,
				tAvatarInfo->aPlayTime3,
				tAvatarInfo->aKillOtherTribe,
				tAvatarInfo->aTribe,
				tAvatarInfo->aGender,
				tAvatarInfo->aHeadType,
				tAvatarInfo->aFaceType,
				tAvatarInfo->aLevel1,
				tAvatarInfo->aLevel2,
				tAvatarInfo->aGeneralExperience1,
				tAvatarInfo->aGeneralExperience2,
				tAvatarInfo->aVitality,
				tAvatarInfo->aStrength,
				tAvatarInfo->aKi,
				tAvatarInfo->aWisdom,
				tAvatarInfo->aEatLifePotion,
				tAvatarInfo->aEatManaPotion,
				tAvatarInfo->aStateBonusPoint,
				tAvatarInfo->aSkillPoint,
				aEquip,
				tAvatarInfo->aExpandInventoryDate,
				tAvatarInfo->aMoney,
				aInventory,
				tAvatarInfo->aTradeMoney,
				aTrade,
				tAvatarInfo->aExpandStoreDate,
				tAvatarInfo->aStoreMoney,
				aStoreItem,
				aSkill,
				aHotKey,
				aQuestInfo,
				aFriend,
				tAvatarInfo->aTeacher,
				tAvatarInfo->aStudent,
				tAvatarInfo->aTeacherPoint,
				tAvatarInfo->aGuildMarkNum,
				tAvatarInfo->aGuildMarkEffect,
				tAvatarInfo->aLogoutInfo[0],
				tAvatarInfo->aLogoutInfo[1],
				tAvatarInfo->aLogoutInfo[2],
				tAvatarInfo->aLogoutInfo[3],
				tAvatarInfo->aLogoutInfo[4],
				tAvatarInfo->aLogoutInfo[5],
				tAvatarInfo->aProtectForDeath,
				tAvatarInfo->aProtectForDestroy,
				tAvatarInfo->aDoubleExpTime1,
				tAvatarInfo->aDoubleExpTime2,
				tAvatarInfo->aDoubleExpTime3,
				tAvatarInfo->aDoubleKillNumTime,
				tAvatarInfo->aDoubleKillExpTime,
				tAvatarInfo->aNineTowerKeyNum,
				tAvatarInfo->aZone101TypeTime,
				tAvatarInfo->aZone125TypeTime,
				tAvatarInfo->aZone126TypeTime,
				tAvatarInfo->aKillMonsterNum,
				tAvatarInfo->aLevelZoneKeyNum,
				tAvatarInfo->aSearchAndBuyDate,
				tAvatarInfo->aLifePotionConvertNum,
				tAvatarInfo->aManaPotionConvertNum,
				tAvatarInfo->aTribeVoteDate,
				tAvatarInfo->aUse_AutoPotion_Date,
				tAvatarInfo->aUse_AutoPotion_Time,
				tAvatarInfo->aAutoLifeRatio,
				tAvatarInfo->aAutoManaRatio,
				tAvatarInfo->aAnimal[0],
				tAvatarInfo->aAnimal[1],
				tAvatarInfo->aAnimal[2],
				tAvatarInfo->aAnimal[3],
				tAvatarInfo->aAnimal[4],
				tAvatarInfo->aAnimal[5],
				tAvatarInfo->aAnimal[6],
				tAvatarInfo->aAnimal[7],
				tAvatarInfo->aAnimal[8],
				tAvatarInfo->aAnimal[9],
				tAvatarInfo->aAnimalIndex,
				tAvatarInfo->aAnimalTime,
				tAvatarInfo->aDoubleDropTime,

				//@{ auto quiz
				tAvatarInfo->iCriminal_Record,
				tAvatarInfo->iEnter_The_Prison,
				tAvatarInfo->iKill_Monster_Count,
				//@}
				tAvatarInfo->aEatStrengthPotion,
				tAvatarInfo->aEatWisdomPotion,
				tAvatarInfo->aPat_Exp_x2_Time,
				tAvatarInfo->aPat_User_Exp_x2_Time,
				tAvatarInfo->aFiveExpTime,
				tAvatarInfo->aZone84Time,

				/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
				tAvatarInfo -> iSilverOrnamentRemainsTime, 
				tAvatarInfo -> iGoldOrnamentRemainsTime, 
				tAvatarInfo -> iUseOrnament,
				/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */

				tAvatarInfo -> aLevelZoneKeyNum2, 
				tAvatarInfo -> aDoubleKillNumTime2,
				tAvatarInfo->aKillMonsterNum2

				
#ifdef __GOD__
				, tAvatarInfo->aAddItemValue, tAvatarInfo->aHighItemValue, tAvatarInfo->aDropItemTime
				, tAvatarInfo->aTribeCallValue, tAvatarInfo->aUpgradeValue
				, tAvatarInfo->aBonusItemValue, tAvatarInfo->aKillOtherTribeEvent, tAvatarInfo->aTeacherPointEvent
				,	tAvatarInfo->aPlayTimeEvent, tAvatarInfo->aProtectForUpgrade
#endif
				,tAvatarInfo->aName
				,g_env.world_num
				);
#endif
		}
		return;
	case 3 :
		sprintf( mQUERY_FOR_THREAD, "update %s set uLoginState=0, uUpdateTime=now() where uID='%s'; "
				, mSERVER_INFO.mDB_2_Table01, tID );
		return;
	default :
		strcpy( mQUERY_FOR_THREAD, "" );
		return;
	}
}
//DB_PROCESS_01
BOOL MyDB::DB_PROCESS_01( char tID[MAX_USER_ID_LENGTH], char *tIp )
{
	int iAffected;

	sprintf( mQUERY, "update %s set uLoginState=1,uUpdateTime=now(),uIP='%s' where uID='%s'; "
			, mSERVER_INFO.mDB_2_Table01, tIp, tID );
	if( !RECONNECT_TO_DATABASE02() )
	{
		return FALSE;
	}
	iAffected = 0;

	if(mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB02.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif

	return TRUE;
}
//DB_PROCESS_02
BOOL MyDB::DB_PROCESS_02( char tID[MAX_USER_ID_LENGTH])
{
	int iAffected;

	sprintf( mQUERY, "update %s set uLoginState=0, uUpdateTime=now() where uID='%s'; ", mSERVER_INFO.mDB_2_Table01, tID );
	if( !RECONNECT_TO_DATABASE02() )
	{
		WRITE_FOR_DB_LOG_FOR_QUERY();
		return FALSE;
	}
	iAffected = 0;

	if(mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		WRITE_FOR_DB_LOG_FOR_QUERY();
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB02.exec_query("commit", CMySQL::CLEAR) != 0) {
		WRITE_FOR_DB_LOG_FOR_QUERY();
		return FALSE;
	}
#endif

	return TRUE;
}
//DB_PROCESS_03
BOOL MyDB::DB_PROCESS_03( int tSort, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, AUTH_INFO *tAuthInfo, int tLoginPremiumPCRoom )
{
	int iAffected;
	int iCounts;
	long tAvatarNameNum;
	long tIDNum;
	char tQuery[MAX_QUERY_BUFFER_SIZE];
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;

	MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
	if( !RECONNECT_TO_DATABASE01_FOR_THREAD() )
	{
		MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iAffected = 0;

	if(mDB01_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
		LOG_TO_FILE_3("![%s] : %s - [%d]\n", __FUNCTION__, mDB01_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB01_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
	//LOG_TO_FILE_1("====> 1 result %s\n", mDB02_FOR_THREAD.get_error_msg().c_str());

	MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);

	if( !RECONNECT_TO_DATABASE01_FOR_THREAD() )
	{
		MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iAffected = 0;

	if(mDB01_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
		LOG_TO_FILE_3("![%s] : %s - [%d]\n", __FUNCTION__, mDB01_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB01_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif

	sprintf( mQUERY_FOR_THREAD, "SELECT count(uID) FROM %s WHERE uID='%s';", mSERVER_INFO.mDB_2_Table02, tID);
	//LOG_TO_FILE_1("====> 5 %s\n", mQUERY_FOR_THREAD);
	if( !RECONNECT_TO_DATABASE02_FOR_THREAD() )
	{
		MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iAffected = 0;
	if((iAffected = mDB02_FOR_THREAD.exec_query(mQUERY_FOR_THREAD)) < 0) {
		LOG_TO_FILE_3("![%s] : %s - [%d]\n", __FUNCTION__, mDB02_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iCounts = 0;
	res = mDB02_FOR_THREAD.get_res();
	if(res == NULL) {
		return false;
	}
	while((row = mysql_fetch_row(res))) {
		tIDNum = atol(row[0]);
		iCounts++;
	}
	mDB02_FOR_THREAD.clear_res();

	if(iCounts != 1) {
		LOG_TO_FILE_3("![%s] : %s - [%d]\n", __FUNCTION__, mDB02_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}

	if( tIDNum == 0 )
	{
		sprintf( mQUERY_FOR_THREAD, 
				"insert into %s values ('%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);"
				, mSERVER_INFO.mDB_2_Table02, tID,
				tAuthInfo->AuthType, tAuthInfo->FindFlag, tAuthInfo->MoveFlag, tAuthInfo->MoveZoneFlag, tAuthInfo->CallFlag,
				tAuthInfo->HideFlag, tAuthInfo->ShowFlag, tAuthInfo->KickFlag, tAuthInfo->BlockFlag, tAuthInfo->MonCallFlag, tAuthInfo->EquipFlag,
				tAuthInfo->UnequipFlag, tAuthInfo->YchatFlag, tAuthInfo->NchatFlag, tAuthInfo->NoticeFlag, tAuthInfo->ItemFlag, tAuthInfo->MoneyFlag,
				tAuthInfo->ExpFlag, tAuthInfo->DieFlag, tAuthInfo->GodFlag, tAuthInfo->ChatFlag, tAuthInfo->TradeFlag, tAuthInfo->ShopFlag, 
				tAuthInfo->PShopFlag, tAuthInfo->GItemFlag, tAuthInfo->DItemFlag, tAuthInfo->AttackFlag, tAuthInfo->UZonemoveFlag );
	}
	else
	{
		sprintf( mQUERY_FOR_THREAD,
				"update %s set AuthType=%d,FindFlag=%d,MoveFlag=%d,MoveZoneFlag=%d,CallFlag=%d,HideFlag=%d,ShowFlag=%d,KickFlag=%d,BlockFlag=%d,MonCallFlag=%d"
				",EquipFlag=%d,UnequipFlag=%d,YchatFlag=%d,NchatFlag=%d,NoticeFlag=%d,ItemFlag=%d,MoneyFlag=%d,ExpFlag=%d,DieFlag=%d,GodFlag=%d,ChatFlag=%d"
				",TradeFlag=%d,ShopFlag=%d,PShopFlag=%d,GItemFlag=%d,DItemFlag=%d,AttackFlag=%d,UZonemoveFlag=%d"
				" where uID='%s';"
				, mSERVER_INFO.mDB_2_Table02, tAuthInfo->AuthType, tAuthInfo->FindFlag, tAuthInfo->MoveFlag, tAuthInfo->MoveZoneFlag, tAuthInfo->CallFlag,
				tAuthInfo->HideFlag, tAuthInfo->ShowFlag, tAuthInfo->KickFlag, tAuthInfo->BlockFlag, tAuthInfo->MonCallFlag, tAuthInfo->EquipFlag,
				tAuthInfo->UnequipFlag, tAuthInfo->YchatFlag, tAuthInfo->NchatFlag, tAuthInfo->NoticeFlag, tAuthInfo->ItemFlag, tAuthInfo->MoneyFlag,
				tAuthInfo->ExpFlag, tAuthInfo->DieFlag, tAuthInfo->GodFlag, tAuthInfo->ChatFlag, tAuthInfo->TradeFlag, tAuthInfo->ShopFlag, 
				tAuthInfo->PShopFlag, tAuthInfo->GItemFlag, tAuthInfo->DItemFlag, tAuthInfo->AttackFlag, tAuthInfo->UZonemoveFlag,
				tID );
	}
	//LOG_TO_FILE_1("query [%s]\n",mQUERY_FOR_THREAD);
	CopyMemory(tQuery, mQUERY_FOR_THREAD, sizeof (mQUERY_FOR_THREAD));
	//LOG_TO_FILE_1("====> 6 %s\n", mQUERY_FOR_THREAD);
	if( !RECONNECT_TO_DATABASE02_FOR_THREAD() )
	{
		MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		CopyMemory(mQUERY_FOR_THREAD, tQuery, sizeof(tQuery));
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iAffected = 0;

	if(mDB02_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
		LOG_TO_FILE_3("![%s] : %s - [%d]\n", __FUNCTION__, mDB02_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		CopyMemory(mQUERY_FOR_THREAD, tQuery, sizeof(tQuery));
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB02_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
	//LOG_TO_FILE_1("====> 2 result %s\n", mDB02_FOR_THREAD.get_error_msg().c_str());
	if( tSort == 1 ) {
		/* MIR */
		MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		if( !RECONNECT_TO_DATABASE02_FOR_THREAD() )
		{
			MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			//LOG_TO_FILE_1("====> 3-1 result %s\n", mDB01_FOR_THREAD.get_error_msg().c_str());
			return FALSE;
		}
		iAffected = 0;
		if(mDB02_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
			LOG_TO_FILE_3("![%s] : %s - [%d]\n", __FUNCTION__, mDB02_FOR_THREAD.get_error_msg().c_str(), __LINE__);
			MakeQueryForSave( 1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			MakeQueryForSave( 2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			MakeQueryForSave( 3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			//LOG_TO_FILE_2("!====> 3 result %s %s\n", mDB02_FOR_THREAD.get_error_msg().c_str(), mQUERY_FOR_THREAD);
			return FALSE;
		}
#ifdef __COMMIT__
		if(mDB02_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
			return FALSE;
		}
#endif
	}
	if( tAvatarInfo->aLevel1 >= 113 && tAuthInfo->AuthType != 1)
	{
		sprintf( mQUERY_FOR_THREAD, 
				"SELECT count(aName) "
				"FROM %s "
				"WHERE aName='%s' AND aWorldNumber = '%d' "
				, mSERVER_INFO.mDB_2_Table04
				, tAvatarInfo->aName
				, g_env.world_num);
		//LOG_TO_FILE_1("====> 5 %s\n", mQUERY_FOR_THREAD);
		if( !RECONNECT_TO_DATABASE01_FOR_THREAD() )
		{
			return TRUE;
		}
		iAffected = 0;
		if((iAffected = mDB01_FOR_THREAD.exec_query(mQUERY_FOR_THREAD)) < 0) {
			return TRUE;
		}
		iCounts = 0;
		res = mDB01_FOR_THREAD.get_res();
		if(res == NULL) {
			return false;
		}
		while((row = mysql_fetch_row(res))) {
			tAvatarNameNum = atol(row[0]);
			iCounts++;
		}
		mDB01_FOR_THREAD.clear_res();

		if(iCounts != 1) {
			return TRUE;
		}

		if( tAvatarNameNum == 0 )
		{
#ifdef __GOD__
			if( tAvatarInfo->aLevel2 < 1 ) {	
#endif		
				sprintf( mQUERY_FOR_THREAD, 
						"insert into %s values ( now(),now(),'%s','%d','%s',%d,%d,%d,%d,'%s',%d )"
						, mSERVER_INFO.mDB_2_Table04, tID
						, g_env.world_num, tAvatarInfo->aName
						, tAvatarInfo->aTribe, tAvatarInfo->aPreviousTribe
						, tAvatarInfo->aLevel1 + tAvatarInfo->aLevel2, tAvatarInfo->aGeneralExperience1
						, tAvatarInfo->aGuildName, tAvatarInfo->aKillOtherTribe );
#ifdef __GOD__
			} else {
				sprintf( mQUERY_FOR_THREAD, 
						"insert into %s values ( now(),now(),'%s','%d','%s',%d,%d,%d,%d,'%s',%d )"
						, mSERVER_INFO.mDB_2_Table04, tID
						, g_env.world_num, tAvatarInfo->aName
						, tAvatarInfo->aTribe, tAvatarInfo->aPreviousTribe
						, tAvatarInfo->aLevel1 + tAvatarInfo->aLevel2, tAvatarInfo->aGeneralExperience2
						, tAvatarInfo->aGuildName, tAvatarInfo->aKillOtherTribe );
			}
#endif
		}
		else
		{
#ifdef __GOD__
			if(tAvatarInfo->aLevel2 < 1) {
#endif
				sprintf( mQUERY_FOR_THREAD, 
						"update %s "
						"set aUpdateTime=now(),uID='%s',aTribe=%d,aPreviousTribe=%d "
						"	,aLevel=%d,aGeneralExperience=%d,aGuildName='%s',aKillOtherTribe=%d "
						"where aName='%s' AND aWorldNumber = '%d'; "
						, mSERVER_INFO.mDB_2_Table04, tID, tAvatarInfo->aTribe, tAvatarInfo->aPreviousTribe
						, tAvatarInfo->aLevel1 + tAvatarInfo->aLevel2, tAvatarInfo->aGeneralExperience1, tAvatarInfo->aGuildName
						, tAvatarInfo->aKillOtherTribe, tAvatarInfo->aName, g_env.world_num );
#ifdef __GOD__
			} else {

				sprintf( mQUERY_FOR_THREAD, 
						"update %s "
						"set aUpdateTime=now(),uID='%s',aTribe=%d,aPreviousTribe=%d "
						"	,aLevel=%d,aGeneralExperience=%d,aGuildName='%s',aKillOtherTribe=%d "
						"where aName='%s' AND aWorldNumber = '%d'; "
						, mSERVER_INFO.mDB_2_Table04, tID, tAvatarInfo->aTribe, tAvatarInfo->aPreviousTribe
						, tAvatarInfo->aLevel1 + tAvatarInfo->aLevel2, tAvatarInfo->aGeneralExperience2, tAvatarInfo->aGuildName
						, tAvatarInfo->aKillOtherTribe, tAvatarInfo->aName, g_env.world_num );
			}
#endif
		}
		//LOG_TO_FILE_1("====> 6 %s\n", mQUERY_FOR_THREAD);
		if( !RECONNECT_TO_DATABASE01_FOR_THREAD() )
		{
			return TRUE;
		}
		iAffected = 0;

		if(mDB01_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
			LOG_TO_FILE_3("![%s] : %s - [%d]\n", __FUNCTION__, mDB01_FOR_THREAD.get_error_msg().c_str(), __LINE__);
			return TRUE;
		}
#ifdef __COMMIT__
		if(mDB01_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
			return TRUE;
		}
#endif
	}
	return TRUE;
}
//DB_PROCESS_04
void MyDB::DB_PROCESS_04( char tID[MAX_USER_ID_LENGTH], char tHackName[MAX_HACK_NAME_LENGTH], int tHackSize, int *tResult )
{
	MYSQL_ROW row;
	MYSQL_RES *res;
	int iAffected;
	int iCounts;
	long hSize;

	sprintf( mQUERY, "select hSize from %s where hName='%s'", mSERVER_INFO.mDB_1_Table02, tHackName );
	if( !RECONNECT_TO_DATABASE01() )
	{
		*tResult = 2;
		return;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB01.ExecuteAndReceive( mQUERY, iAffected ) )
	{
		*tResult = 2;
		return;
	}
	iCounts = 0;
	if( !mDB01.GetResultCounts( iCounts ) )
	{
		*tResult = 2;
		return;
	}
	if( iCounts == 0 )
	{
		*tResult = 0;
		return;
	}
	if( !mDB01.GetLong( 0, hSize ) )
	{
		*tResult = 2;
		return;
	}
#else
	if((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		*tResult = 2;
		return;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if(res == NULL) {
		*tResult = 2;
		return;
	}
	while((row = mysql_fetch_row(res))) {
		hSize = atol(row[0]);
		iCounts++;
	}

	mDB01.clear_res();

	if(iCounts != 1) {
		*tResult = 0;
		return;
	}
#endif
	if( ( hSize > 0 ) && ( hSize != (long) tHackSize ) )
	{
		*tResult = 0;
		return;
	}
	DB_PROCESS_07( &tID[0], 0, &tHackName[0] );
	*tResult = 1;
	return;
}
//DB_PROCESS_05
BOOL MyDB::DB_PROCESS_05( int tUserNum )
{
	int iAffected;

	sprintf( mQUERY, "update %s set mMaxUserNum=%d WHERE aWorldNumber = '%d'; "
			, mSERVER_INFO.mDB_1_Table01, tUserNum, g_env.world_num );
	if( !RECONNECT_TO_DATABASE02() )
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB02.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if(mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB02.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
#endif

	return TRUE;
}
//DB_PROCESS_06
BOOL MyDB::DB_PROCESS_06( char tID[MAX_USER_ID_LENGTH], int tSort, char tHackName[MAX_HACK_NAME_LENGTH] )
{
	int iAffected;

	sprintf( mQUERY, "insert into %s values ( now(),'%s',%d,'%s' )", mSERVER_INFO.mDB_1_Table04, tID, tSort, tHackName );
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
	if(mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB01.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
#endif
	sprintf( mQUERY, "update %s set uBlockInfo=99999999 where uID='%s'; ", mSERVER_INFO.mDB_2_Table01, tID );
	if( !RECONNECT_TO_DATABASE02() )
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB02.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if(mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB02.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
#endif
	return TRUE;
}
//DB_PROCESS_07
BOOL MyDB::DB_PROCESS_07( char tID[MAX_USER_ID_LENGTH], int tSort, char tHackName[MAX_HACK_NAME_LENGTH] )
{
	MYSQL_ROW row;
	MYSQL_RES *res;
	int iAffected;
	int iCounts;
	long tIDNum;

	sprintf( mQUERY, "insert into %s values ( now(),'%s',%d,'%s' )", mSERVER_INFO.mDB_1_Table04, tID, tSort, tHackName );
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
	if(mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#ifdef __COMMIT__
	if(mDB01.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
#endif
	sprintf( mQUERY, "select count(uID) from %s where uID='%s'", mSERVER_INFO.mDB_1_Table03, tID );
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
	if( !mDB01.GetLong( 0, tIDNum ) )
	{
		return FALSE;
	}
#else
	if((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		return TRUE;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if(res == NULL) {
		return false;
	}
	while((row = mysql_fetch_row(res))) {
		tIDNum = atol(row[0]);
		iCounts++;
	}
	mDB01.clear_res();

	if(iCounts != 1) {
		return TRUE;
	}
#endif
	if( tIDNum == 0 )
	{
		sprintf( mQUERY, "insert into %s values ( now(),'%s',1 )", mSERVER_INFO.mDB_1_Table03, tID );
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
		if(mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			return TRUE;
		}
#ifdef __COMMIT__
		if(mDB01.exec_query("commit", CMySQL::CLEAR) != 0) {
			return TRUE;
		}
#endif
#endif
		return TRUE;
	}
	sprintf( mQUERY, "update %s set uWarningNum=uWarningNum+1 where uID='%s'; ", mSERVER_INFO.mDB_1_Table03, tID );
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
	if(mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return TRUE;
	}
#ifdef __COMMIT__
	if(mDB01.exec_query("commit", CMySQL::CLEAR) != 0) {
		return TRUE;
	}
#endif
#endif
	return TRUE;
}
//DB_PROCESS_08
BOOL MyDB::DB_PROCESS_08( char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tWorldNumber, int tZoneNumber )
{
	int iAffected;

	sprintf( mQUERY, "insert into %s values ( now(),1,'%s','%s',%d,%d )", mSERVER_INFO.mDB_1_Table10, tID, tAvatarName, tWorldNumber, tZoneNumber );
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
	if(mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return TRUE;
	}
#ifdef __COMMIT__
	if(mDB01.exec_query("commit", CMySQL::CLEAR) != 0) {
		return TRUE;
	}
#endif
#endif
	return TRUE;
}
//DB_PROCESS_09
void MyDB::DB_PROCESS_09( char tID[MAX_USER_ID_LENGTH], int tSort )
{
	int iAffected;

	sprintf( mQUERY, "insert into %s values ( '%s',0,0 )", mSERVER_INFO.mDB_1_Table06, tID );
	RECONNECT_TO_DATABASE01();
	iAffected = 0;
#ifdef __WIN32__
	mDB01.Execute( mQUERY, iAffected );
#else
	mDB01.exec_query(mQUERY, CMySQL::CLEAR);
#ifdef __COMMIT__
	mDB01.exec_query("commit", CMySQL::CLEAR);
#endif
#endif
	switch( tSort )
	{
		case 1 :
			sprintf( mQUERY, "update %s set uEventNum01=uEventNum01+1 where uID='%s'; ", mSERVER_INFO.mDB_1_Table06, tID );
			RECONNECT_TO_DATABASE01();
			iAffected = 0;
#ifdef __WIN32__
			mDB01.Execute( mQUERY, iAffected );
#else
			mDB01.exec_query(mQUERY, CMySQL::CLEAR);
#ifdef __COMMIT__
			mDB01.exec_query("commit", CMySQL::CLEAR);
#endif
#endif
			return;
		case 2 :
			sprintf( mQUERY, "update %s set uEventNum02=uEventNum02+1 where uID='%s'; ", mSERVER_INFO.mDB_1_Table06, tID );
			RECONNECT_TO_DATABASE01();
			iAffected = 0;
#ifdef __WIN32__
			mDB01.Execute( mQUERY, iAffected );
#else
			mDB01.exec_query(mQUERY, CMySQL::CLEAR);
#ifdef __COMMIT__
			mDB01.exec_query("commit", CMySQL::CLEAR);
#endif
#endif
			return;
	}
}

bool MyDB::DB_COMPARE_AUTH_KEY (char tID[MAX_USER_ID_LENGTH], char szAuthKey[MAX_MOUSE_PASSWORD_LENGTH], BYTE& bResult)
{
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;
	int iAffected = 0, iCounts = 0;
	char StoredAuthKey[MAX_MOUSE_PASSWORD_LENGTH] = {0, };

	bResult = 1;

	sprintf (mQUERY, "SELECT uMousePassword FROM %s WHERE uID = '%s'", mSERVER_INFO.mDB_2_Table01, tID);
	if( !RECONNECT_TO_DATABASE02() )
	{
		return false;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB02.ExecuteAndReceive( mQUERY, iAffected ) )
	{
		return false;
	}
	iCounts = 0;
	if( !mDB02.GetResultCounts( iCounts ) )
	{
		return false;
	}
	if( iCounts != 1 )
	{
		return false;
	}
	if( !mDB02.GetText( 0, StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH - 1 ) )
	{
		return false;
	}
#else
	if((iAffected = mDB02.exec_query(mQUERY)) < 0) {
		return false;
	}
	iCounts = 0;
	res = mDB02.get_res();
	if(res == NULL) {
		return false;
	}
	while((row = mysql_fetch_row(res))) {
		snprintf(StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH, "%s", row[0]);
		iCounts++;
	}

	mDB02.clear_res();

	//LOG_TO_FILE_4("***********************%s %s %s %d\n", mQUERY, StoredAuthKey, szAuthKey, iCounts);
	if(iCounts != 1) {
		return false;
	}

#endif
	if (strncmp (szAuthKey, StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH - 1) == 0)
		bResult = 0;

	return true;
}

bool MyDB::DB_UPDATE_AUTH_KEY (char tID[MAX_USER_ID_LENGTH], char szAuthKey[3][MAX_MOUSE_PASSWORD_LENGTH], BYTE& bResult)
{
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;
	int iAffected = 0, iCounts = 0;
	char StoredAuthKey[MAX_MOUSE_PASSWORD_LENGTH] = {0, };

	bResult = 1;

	sprintf (mQUERY, "SELECT uMousePassword FROM %s WHERE uID = '%s'", mSERVER_INFO.mDB_2_Table01, tID);
	if( !RECONNECT_TO_DATABASE02() )
	{
		return false;
	}
	iAffected = 0;
#ifdef __WIN32__
	if( !mDB02.ExecuteAndReceive( mQUERY, iAffected ) )
	{
		return false;
	}
	iCounts = 0;
	if( !mDB02.GetResultCounts( iCounts ) )
	{
		return false;
	}
	if( iCounts != 1 )
	{
		return false;
	}
	if( !mDB02.GetText( 0, StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH - 1 ) )
	{
		return false;
	}
#else 
	if((iAffected = mDB02.exec_query(mQUERY)) < 0) {
		return false;
	}
	iCounts = 0;
	res = mDB02.get_res();
	if(res == NULL) {
		return false;
	}
	while((row = mysql_fetch_row(res))) {
		snprintf(StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH, "%s", row[0]);
		iCounts++;
	}

	mDB02.clear_res();

	//LOG_TO_FILE_4("***********************%s %s %s %d\n", mQUERY, StoredAuthKey, szAuthKey, iCounts);
	if(iCounts != 1) {
		return false;
	}
#endif
	if (strncmp (szAuthKey[0], StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH - 1) == 0) {
		sprintf (mQUERY, "UPDATE %s SET uMousePassword = '%s' WHERE uID = '%s'", mSERVER_INFO.mDB_2_Table01, szAuthKey[1], tID);
		RECONNECT_TO_DATABASE02 ();
		iAffected = 0;
	
		if(mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			return false;
		}
#ifdef __COMMIT__
		if(mDB02.exec_query("commit", CMySQL::CLEAR) != 0) {
			return false;
		}
#endif
		bResult = 0;
	}

	return true;
}
//DB_PROCESS_10
BOOL MyDB::DB_PROCESS_10( TRIBE_INFO *tTribeInfo )
{
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
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;

	sprintf( mQUERY, "select mTribeVoteInfo,mTribe01Master,mTribe01SubMasterInfo,mTribe02Master,mTribe02SubMasterInfo,mTribe03Master,mTribe03SubMasterInfo,mTribe04Master,mTribe04SubMasterInfo from %s WHERE aWorldNumber = %d", mSERVER_INFO.mDB_1_Table08, mSERVER_INFO.mWorldNumber);
	if( !RECONNECT_TO_DATABASE01() )
	{
		LOG_TO_FILE_2 ("!Unable to connect to the database[%s] in %s method.\n", 
				mSERVER_INFO.mDB_1_Table08, __FUNCTION__);
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB01.exec_query (mQUERY)) < 0) {
		LOG_TO_FILE_1 ("!The query execution failed in %s.\n", __FUNCTION__);
		LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		return FALSE;
	}
	iCounts = 0;
	res = mDB01.get_res ();
	if (res == NULL) {
		LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		return FALSE;
	}
	while (row = mysql_fetch_row(res)){
		::strncpy (mTribeVoteInfo, row [0], 1041);
		::strncpy (mTribe01Master, row [1], MAX_AVATAR_NAME_LENGTH - 1);
		::strncpy (mTribe01SubMasterInfo, row [2], 145);
		::strncpy (mTribe02Master, row [3], MAX_AVATAR_NAME_LENGTH - 1);
		::strncpy (mTribe02SubMasterInfo, row [4], 145);
		::strncpy (mTribe03Master, row [5], MAX_AVATAR_NAME_LENGTH - 1);
		::strncpy (mTribe03SubMasterInfo, row [6], 145);
		::strncpy (mTribe04Master, row [7], MAX_AVATAR_NAME_LENGTH - 1);
		::strncpy (mTribe04SubMasterInfo, row [8], 145);
		++iCounts;
	}
	mDB01.clear_res ();
	if (1 != iCounts){
		LOG_TO_FILE ("!As a result of a number of rows is not returned by the query.\n");
		LOG_TO_FILE_1 ("\t\t\tRow counts = %d.\n", iCounts);
		return FALSE;
	}
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
		LOG_TO_FILE_1 ("!TribeVoteInfo, the length of the problem was different in %s.\n",
				__FUNCTION__);
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
		LOG_TO_FILE_1 ("!Tribe01SubMasterInfo, the length of the problem was different in %s.\n",
				__FUNCTION__);
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
		LOG_TO_FILE_1 ("!Tribe02SubMasterInfo, the length of the problem was different in %s.\n",
				__FUNCTION__);
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
		LOG_TO_FILE_1 ("!Tribe03SubMasterInfo, the length of the problem was different in %s.\n",
				__FUNCTION__);
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
		LOG_TO_FILE_1 ("!Tribe04SubMasterInfo, the length of the problem was different in %s.\n",
				__FUNCTION__);
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
			if (::IsDBCSLeadByte (tTribeInfo->mTribeSubMaster[0][index01][index02]) == TRUE) {\
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
	strcpy( tTribeInfo->mTribeMaster[1], mTribe01Master );
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
	strcpy( tTribeInfo->mTribeMaster[2], mTribe01Master );
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
	strcpy( tTribeInfo->mTribeMaster[3], mTribe01Master );
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
void MyDB::DB_PROCESS_11( char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tChangeAvatarName[MAX_AVATAR_NAME_LENGTH], int *tResult )
{
	int tAvatarPost;
	int iAffected;

	DB_PROCESS_12(tID, tAvatarName, &tAvatarPost);
	if(-1 == tAvatarPost){
		*tResult = 1;
		return;
	}

	sprintf( mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tChangeAvatarName, tAvatarName );
	if( !RECONNECT_TO_DATABASE02() )
	{
		*tResult = 2;
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
		*tResult = 3;
		return ;
	}
	sprintf( mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table09, tChangeAvatarName, tAvatarName, mSERVER_INFO.mWorldNumber);
	if( !RECONNECT_TO_DATABASE01() )
	{
		sprintf( mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName );
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 4;
			return ;
		}
		*tResult = 2;
		return;
	}
	iAffected = 0;
	if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
		sprintf( mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName );
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 5;
			return ;
		}
		*tResult = 2;
		return;
	}
	switch( tAvatarPost )
	{
		case 0 :
			sprintf( mQUERY, "update %s set aName01='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table07, tChangeAvatarName, tID, mSERVER_INFO.mWorldNumber);
			break;
		case 1 :
			sprintf( mQUERY, "update %s set aName02='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table07, tChangeAvatarName, tID, mSERVER_INFO.mWorldNumber);
			break;
		case 2 :
			sprintf( mQUERY, "update %s set aName03='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table07, tChangeAvatarName, tID, mSERVER_INFO.mWorldNumber);
			break;
		default :
			sprintf( mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table09, tAvatarName, tChangeAvatarName, mSERVER_INFO.mWorldNumber);
			RECONNECT_TO_DATABASE01();
			iAffected = 0;
			if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
				*tResult = 6;
				return ;
			}
			sprintf( mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName );
			RECONNECT_TO_DATABASE02();
			iAffected = 0;
			if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
				*tResult = 7;
				return ;
			}
			*tResult = 2;
			return;
	}
	if( !RECONNECT_TO_DATABASE01() )
	{
		sprintf( mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table09, tAvatarName, tChangeAvatarName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
		if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 8;
			return ;
		}
		sprintf( mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName );
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 9;
			return ;
		}
		*tResult = 2;
		return;
	}
	iAffected = 0;
	if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
		sprintf( mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table09, tAvatarName, tChangeAvatarName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
		if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 10;
			return ;
		}
		sprintf( mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName );
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 10;
			return ;
		}
		*tResult = 2;
		return;
	}
	*tResult = 0;
}
//DB_PROCESS_12
void MyDB::DB_PROCESS_12(char *tID, char *tAvatarName, int *tResult)
{
	MYSQL_ROW row;
	MYSQL_RES *res;
	int iAffected;
	int iCounts;

	char tName01[MAX_AVATAR_NAME_LENGTH];
	char tName02[MAX_AVATAR_NAME_LENGTH];
	char tName03[MAX_AVATAR_NAME_LENGTH];
	*tResult = -1;

	sprintf( mQUERY, "select aName01, aName02, aName03 from %s where uID ='%s' AND aWorldNumber = '%d';", mSERVER_INFO.mDB_1_Table07, tID, mSERVER_INFO.mWorldNumber );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return;
	}
	iAffected = 0;
	if((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		return;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if(res == NULL) {
		return;
	}
	while((row = mysql_fetch_row(res))) {
		snprintf(tName01, MAX_AVATAR_NAME_LENGTH, "%s", row[0]);
		snprintf(tName02, MAX_AVATAR_NAME_LENGTH, "%s", row[1]);
		snprintf(tName03, MAX_AVATAR_NAME_LENGTH, "%s", row[2]);
		iCounts++;
	}

	mDB01.clear_res();

	if(iCounts != 1) {
		return;
	}
	if(0 == strcmp(tName01, tAvatarName)){
		*tResult = 0;
	}
	else if(0 == strcmp(tName02, tAvatarName)){
		*tResult = 1;
	}
	else if(0 == strcmp(tName03, tAvatarName)){
		*tResult = 2;
	}
	else;
}
//DB_PROCESS_13
void MyDB::DB_PROCESS_13(char *tID, int *tResult)
{
	MYSQL_ROW row;
	MYSQL_RES *res;
	int iAffected;
	int iCounts;
	char tBonus100Money;
	*tResult = 0;

	sprintf( mQUERY, "select uBonus100Money from %s where uID ='%s' AND aWorldNumber = '%d';", mSERVER_INFO.mDB_2_Table01, tID, mSERVER_INFO.mWorldNumber );
	if( !RECONNECT_TO_DATABASE02() )
	{
		*tResult = 1;
		return;
	}
	iAffected = 0;
	if((iAffected = mDB02.exec_query(mQUERY)) < 0) {
		*tResult = 2;
		return;
	}
	iCounts = 0;
	res = mDB02.get_res();
	if(res == NULL) {
		*tResult = 3;
		return;
	}
	while((row = mysql_fetch_row(res))) {
		tBonus100Money = *row[0];
		iCounts++;
	}

	mDB02.clear_res();

	if(iCounts != 1) {
		*tResult = 3;
		return;
	}
	if('1' == tBonus100Money){
		*tResult = 4;
		return;
	}
}
//DB_PROCESS_14
void MyDB::DB_PROCESS_14( char tID[MAX_USER_ID_LENGTH], int *tResult )
{
	int iAffected;

	mDB.DB_PROCESS_13(tID, tResult);
	if(0 != tResult){
		return;
	}

	sprintf( mQUERY, "update %s set uBonus100Money='%c' where uID='%s';", mSERVER_INFO.mDB_2_Table01, '1', tID );
	if( !RECONNECT_TO_DATABASE02() )
	{
		*tResult = 5;
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
		*tResult = 6;
		return ;
	}
	sprintf( mQUERY, "update %s set uBonusCash=uBonusCash+%d where uID='%s';", mSERVER_INFO.mDB_2_Table01, 100, tID);
	if( !RECONNECT_TO_DATABASE02() )
	{
		sprintf( mQUERY, "update %s set uBonus100Money='%c' where uID='%s';", mSERVER_INFO.mDB_2_Table01, '0', tID );
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 7;
			return ;
		}
		*tResult = 8;
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
		sprintf( mQUERY, "update %s set uBonus100Money='%c' where uID='%s';", mSERVER_INFO.mDB_2_Table01, '0', tID );
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 9;
			return ;
		}
		*tResult = 10;
		return;
	}
	*tResult = 0;
}
#ifdef __EVENT_KILL__
//DB_PROCESS_15
void MyDB::DB_PROCESS_15(char *tID, char *tName, int tTribe, int tKillNum)
{
	MYSQL_ROW row;
	MYSQL_RES *res;
	int iAffected;
	int iCounts;
	char tCnt = 0;

	sprintf( mQUERY, "select count(*) from %s where aWorldNumber = %d and aName = '%s';", mSERVER_INFO.mDB_1_Table05, mSERVER_INFO.mWorldNumber, tName );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return;
	}
	iAffected = 0;
	if((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		return;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if(res == NULL) {
		return;
	}
	while((row = mysql_fetch_row(res))) {
		tCnt = ::atol(row[0]);
		iCounts++;
	}

	mDB01.clear_res();

	if(iCounts != 1) {
		return;
	}

	if(0 == tCnt){
		sprintf( mQUERY, "insert into %s values (%d, '%s', '%s', %d, %d);",
				mSERVER_INFO.mDB_1_Table05, mSERVER_INFO.mWorldNumber, tName, tID, tTribe, tKillNum);
		if( !RECONNECT_TO_DATABASE01() )
		{
			return;
		}
		iAffected = 0;
		if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			return ;
		}
	}
	else{
		sprintf( mQUERY, "update %s set aKillOtherTribe = aKillOtherTribe + %d where aWorldNumber = %d and aName = '%s';",
				mSERVER_INFO.mDB_1_Table05, tKillNum, mSERVER_INFO.mWorldNumber, tName );
		if( !RECONNECT_TO_DATABASE01() )
		{
			return;
		}
		iAffected = 0;
		if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			return ;
		}
	}
}
#elif __EVENT_GOLD_PHONE__
//DB_PROCESS_15
void MyDB::DB_PROCESS_15(char *tID, char *tName)
{
	MYSQL_ROW row;
	MYSQL_RES *res;
	int iAffected;
	int iCounts;
	char tCnt = 0;

	sprintf( mQUERY, "select count(*) from %s where aWorldNumber = %d and aName = '%s';", mSERVER_INFO.mDB_1_Table05, mSERVER_INFO.mWorldNumber, tName );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return;
	}
	iAffected = 0;
	if((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		return;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if(res == NULL) {
		return;
	}
	while((row = mysql_fetch_row(res))) {
		tCnt = ::atol(row[0]);
		iCounts++;
	}

	mDB01.clear_res();

	if(iCounts != 1) {
		return;
	}

	if(0 == tCnt){
		sprintf( mQUERY, "insert into %s values (%d, '%s', '%s', 1);",
				mSERVER_INFO.mDB_1_Table05, mSERVER_INFO.mWorldNumber, tName, tID);
		if( !RECONNECT_TO_DATABASE01() )
		{
			return;
		}
		iAffected = 0;
		if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			return ;
		}
	}
	else{
		sprintf( mQUERY, "update %s set UsedCnt = UsedCnt + 1 where aWorldNumber = %d and aName = '%s';",
				mSERVER_INFO.mDB_1_Table05, mSERVER_INFO.mWorldNumber, tName );
		if( !RECONNECT_TO_DATABASE01() )
		{
			return;
		}
		iAffected = 0;
		if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
			return ;
		}
	}
}
#endif

BOOL MyDB::DB_PROCESS_16( char tID[MAX_USER_ID_LENGTH], int tCashValue)
{

	sprintf( mQUERY, "update MemberInfo set uBonusCash = uBonusCash + %d where aWorldNumber = %d and uID = '%s';",
			tCashValue, mSERVER_INFO.mWorldNumber, tID );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	if (mDB01.exec_query (mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
	
	return TRUE;
}
//WRITE_FOR_DB_LOG_FOR_QUERY
void MyDB::WRITE_FOR_DB_LOG_FOR_QUERY( void )
{
	g_mLOG->log_to_file("!%s\n", mQUERY);
}
//WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD
void MyDB::WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD( void )
{
	g_mThreadLOG->log_to_file("!%s\n", mQUERY_FOR_THREAD);
}
//-------------------------------------------------------------------------------------------------
