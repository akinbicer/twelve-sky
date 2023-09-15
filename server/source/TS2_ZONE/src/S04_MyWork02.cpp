//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "H01_MainApplication.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//INSTANCE
WORKER_FUNCTION W_FUNCTION[256];
//W_TEMP_REGISTER_SEND

void W_TEMP_REGISTER_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( mUSER[tUserIndex].mCheckTempRegister )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tID[MAX_USER_ID_LENGTH];
	int tribe;
	CopyMemory( &tID[0], &tPacket[1], MAX_USER_ID_LENGTH );
	tID[( MAX_USER_ID_LENGTH - 1 )] = '\0';
	CopyMemory( &tribe, &tPacket[( 1 + MAX_USER_ID_LENGTH )], 4 );

	int index01;
	int tTribeNum[4];

	switch( mSERVER_INFO.mServerNumber )
	{
	case  49 :
	case  51 :
	case  53 :
	case 146 :
	case 147 :
	case 148 :
	case 149 :
	case 150 :
	case 151 :
	case 152 :
	case 153 :
#ifdef __GOD__
	case 267 :
#endif
		if( ( tribe < 0 ) || ( tribe > 2 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tTribeNum[0] = 0;
		tTribeNum[1] = 0;
		tTribeNum[2] = 0;
		for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
		{
			if( !mUSER[index01].mCheckConnectState )
			{
				continue;
			}
			if( !mUSER[index01].mCheckTempRegister )
			{
				continue;
			}
			tTribeNum[mUSER[index01].mTempRegisterTribe]++;
		}
		if( tTribeNum[tribe] >= ( mSERVER.mMAX_USER_NUM / 3 ) )
		{
			mTRANSFER.B_TEMP_REGISTER_RECV( 1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		break;
	case 154 :
	case 155 :
	case 156 :
	case 157 :
	case 158 :
	case 159 :
	case 160 :
	case 161 :
	case 162 :
	case 163 :
	case 164 :
#ifdef __GOD__
	case 120 :
	case 121 :
	case 122 :
	case 268 :
	case 269 :
#endif
		if( ( tribe < 0 ) || ( tribe > 3 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tTribeNum[0] = 0;
		tTribeNum[1] = 0;
		tTribeNum[2] = 0;
		tTribeNum[3] = 0;
		for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
		{
			if( !mUSER[index01].mCheckConnectState )
			{
				continue;
			}
			if( !mUSER[index01].mCheckTempRegister )
			{
				continue;
			}
			tTribeNum[mUSER[index01].mTempRegisterTribe]++;
		}
		if( tTribeNum[tribe] >= ( mSERVER.mMAX_USER_NUM / 4 ) )
		{
			mTRANSFER.B_TEMP_REGISTER_RECV( 1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		break;
#ifdef __GOD__
	case 194 :
			if( ( tribe < 0 ) || ( tribe > 3 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tTribeNum[0] = 0;
			tTribeNum[1] = 0;
			tTribeNum[2] = 0;
			tTribeNum[3] = 0;
			for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
			{
				if( !mUSER[index01].mCheckConnectState )
				{
					continue;
				}
				if( !mUSER[index01].mCheckTempRegister )
				{
					continue;
				}
				tTribeNum[mUSER[index01].mTempRegisterTribe]++;
			}
			if( tTribeNum[tribe] >= 25 )
			{
				mTRANSFER.B_TEMP_REGISTER_RECV( 1 );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			break;
#endif
	}
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_0_SEND( &tID[0] );
	//LOG_TO_FILE_2("<================= %d %s\n", mPLAYUSER_COM.mRecv_Result, tID);
	if( mPLAYUSER_COM.mRecv_Result != 0 )
	{
	//	LOG_TO_FILE_2("![%s] : U_REGISTER_USER_FOR_ZONE_0_SEND failed(%d)\n"
	//			, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mTRANSFER.B_TEMP_REGISTER_RECV( 0 );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mUSER[tUserIndex].mCheckTempRegister = TRUE;
	mUSER[tUserIndex].mTempRegisterTribe = tribe;
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mPlayUserIndex = mPLAYUSER_COM.mRecv_PlayUserIndex;
	strncpy( mUSER[tUserIndex].uID, tID, MAX_USER_ID_LENGTH );
    mUSER[tUserIndex].mHeartCheckTime = ::time(NULL);
}
//W_REGISTER_AVATAR_SEND
void W_REGISTER_AVATAR_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( ( !mUSER[tUserIndex].mCheckTempRegister ) || ( mUSER[tUserIndex].mCheckValidState ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tID[MAX_USER_ID_LENGTH];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	ACTION_INFO tAction;
	CopyMemory( &tID[0], &tPacket[1], MAX_USER_ID_LENGTH );
	tID[( MAX_USER_ID_LENGTH - 1 )] = '\0';
	CopyMemory( &tAvatarName[0], &tPacket[( 1 + MAX_USER_ID_LENGTH )], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	CopyMemory( &tAction, &tPacket[( 1 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH )], sizeof( ACTION_INFO ) );
	if( ( strcmp( tID, mUSER[tUserIndex].uID ) != 0 ) || ( tAction.aType != 0 ) || ( ( tAction.aSort != 0 ) && ( tAction.aSort != 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	int tLogoutInfo[6];
	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int iTemp_Auto_time;

	time_t tCountSeconds;
	struct tm *tPresentTime;
	char cDate[100];
	unsigned int iDate = 0;

	time( &tCountSeconds );
	tPresentTime = localtime( &tCountSeconds );

	tLogoutInfo[0] = mSERVER_INFO.mServerNumber;
	tLogoutInfo[1] = (int) tAction.aLocation[0];
	tLogoutInfo[2] = (int) tAction.aLocation[1];
	tLogoutInfo[3] = (int) tAction.aLocation[2];
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_1_SEND( mUSER[tUserIndex].mPlayUserIndex, &tID[0], &tAvatarName[0], &tLogoutInfo[0] );
	if( mPLAYUSER_COM.mRecv_Result != 0 )
	{
		//LOG_TO_FILE_2("![%s] : U_REGISTER_USER_FOR_ZONE_1_SEND failed(%d)\n"
		//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	//-------------------//
	//EXAMINE_TRIBE_STATE//
	//-------------------//
	switch( mPLAYUSER_COM.mRecv_AvatarInfo.aTribe )
	{
		case 0 :
			if( mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 0 )
			{
				//LOG_TO_FILE_3("![%s] : mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe failed(%d)-%d\n"
				//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result, mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1 :
			if( mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 1 )
			{
				//LOG_TO_FILE_2("![%s] : mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe failed(%d)\n"
				//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2 :
			if( mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 2 )
			{
				//LOG_TO_FILE_2("![%s] : mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe failed(%d)\n"
				//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3 :
			if( ( mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 0 ) && ( mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 1 ) && ( mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 2 ) )
			{
				//LOG_TO_FILE_2("![%s] : mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe failed(%d)\n"
				//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default :
			//LOG_TO_FILE_2("![%s] : mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe failed(%d)\n"
			//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
	}
	//-------------------//
	//-------------------//
	//-------------------//
	if(mPLAYUSER_COM.mRecv_AuthInfo.AuthType == 0)
	{
#ifdef __GOD__
		if( ( (mPLAYUSER_COM.mRecv_AvatarInfo.aLevel1 + mPLAYUSER_COM.mRecv_AvatarInfo.aLevel2) < mZONEMAININFO.ReturnMinZoneLevelInfo( mSERVER_INFO.mServerNumber ) ) || ( mPLAYUSER_COM.mRecv_AvatarInfo.aLevel1 > mZONEMAININFO.ReturnMaxZoneLevelInfo( mSERVER_INFO.mServerNumber ) ) )
#else
		if( ( mPLAYUSER_COM.mRecv_AvatarInfo.aLevel1  < mZONEMAININFO.ReturnMinZoneLevelInfo( mSERVER_INFO.mServerNumber ) ) || ( mPLAYUSER_COM.mRecv_AvatarInfo.aLevel1 > mZONEMAININFO.ReturnMaxZoneLevelInfo( mSERVER_INFO.mServerNumber ) ) )
#endif
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mGAME.mCheckZone101TypeServer )
		{
#ifdef __GOD__
			if(mPLAYUSER_COM.mRecv_AvatarInfo.aLevel2 > 0)
			{
#endif
				if( mPLAYUSER_COM.mRecv_AvatarInfo.aZone101TypeTime < 1 )
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				mPLAYUSER_COM.mRecv_AvatarInfo.aZone101TypeTime--;
#ifdef __GOD__
			}
#endif
		}
		if( mGAME.mCheckZone125Server )
		{
			if( mPLAYUSER_COM.mRecv_AvatarInfo.aZone125TypeTime < 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aZone125TypeTime--;
		}
		if( mGAME.mCheckZone126TypeServer )
		{
			if( mPLAYUSER_COM.mRecv_LoginPremiumPCRoom != 2 )
			{
				if( mPLAYUSER_COM.mRecv_AvatarInfo.aZone126TypeTime < 1 )
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				mPLAYUSER_COM.mRecv_AvatarInfo.aZone126TypeTime--;
			}
		}
		if( mGAME.mCheckZone175TypeServer )
		{
			if( mGAME.mWorldInfo.mZone175TypeState[mGAME.mZone175TypeZoneIndex1][mGAME.mZone175TypeZoneIndex2] != 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mPLAYUSER_COM.mRecv_AvatarInfo.aNineTowerKeyNum < 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aNineTowerKeyNum--;
		}
		if(84 == mSERVER_INFO.mServerNumber){
			if( (mPLAYUSER_COM.mRecv_AvatarInfo.aZone84Time & 0x0000000F) < 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			--mPLAYUSER_COM.mRecv_AvatarInfo.aZone84Time;
		}
	}
	if(NULL != tPresentTime){
		::memset(cDate, 0, 100);
		snprintf (cDate, 100, "%04d%02d%02d", tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
		iDate = ::atoi(cDate);

		if(iDate != (mPLAYUSER_COM.mRecv_AvatarInfo.aZone84Time >> 4)){
			mPLAYUSER_COM.mRecv_AvatarInfo.aZone84Time = mPLAYUSER_COM.mRecv_AvatarInfo.aZone84Time & 0xFFFFFFF0;
		}
	}

	mUSER[tUserIndex].mCheckValidState = TRUE;
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].uUserSort = mPLAYUSER_COM.mRecv_UserSort;
	mUSER[tUserIndex].uGoodFellow =  mPLAYUSER_COM.mRecv_GoodFellow;
	mUSER[tUserIndex].uLoginPlace =  mPLAYUSER_COM.mRecv_LoginPlace;
	mUSER[tUserIndex].uLoginPremium =  mPLAYUSER_COM.mRecv_LoginPremium;
	mUSER[tUserIndex].uLoginPremiumPCRoom =  mPLAYUSER_COM.mRecv_LoginPremiumPCRoom;
	mUSER[tUserIndex].uTraceState =  mPLAYUSER_COM.mRecv_TraceState;
	mUSER[tUserIndex].uBonus100Money = mPLAYUSER_COM.mRecv_Bonus100Money;
	mUSER[tUserIndex].uPremiumServerExpirationDate = mPLAYUSER_COM.mRecv_PremiumServerExpirationDate; // ÇÁ¸®¹Ì¾ö ¼­¹ö(¿ùµå) ÀÔÀå±Ç À¯È¿ ±âÇÑ(YYYYMMDD ÇüÅÂÀÇ Á¤¼ö) ¼³Á¤. // @_Premium_Server_@
	CopyMemory( &mUSER[tUserIndex].mAvatarInfo, &mPLAYUSER_COM.mRecv_AvatarInfo, sizeof( AVATAR_INFO ) );
#ifdef __IVEN_BUG_FIX__
	int iPage = 0;
	int iIndex = 0;
	int iNewPage = 0;
	int iNewIndex = 0;
	bool bItemMove = false;
	ITEM_INFO *pItemInfo = NULL;

	for(iPage = 0; iPage < 2; iPage++) {
		for(iIndex = 0; iIndex < MAX_INVENTORY_SLOT_NUM; iIndex++) {
			bItemMove = false;
			if(((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] >= 7)
						|| (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] >= 7))
					|| ((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] < 0)
						|| (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] < 0))) {
				pItemInfo = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0]);
				if(pItemInfo == NULL) {
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][5] = 0;
					continue;
				}

				if((pItemInfo->iSort != 2) && (pItemInfo->iSort != 7) && (pItemInfo->iSort != 11)) {
					bItemMove = true;
				} else if(((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] >= 8)
							|| (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] >= 8))
						|| ((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] < 0)
							|| (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] < 0))) {
					bItemMove = true;
				}
				if(bItemMove) {
					if(mUTIL.FindEmptyInvenForItem(tUserIndex, pItemInfo, iNewPage, iNewIndex)) {
						if(iNewPage == iPage) {
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][1]
								= iNewIndex % 8;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][2]
								= iNewIndex / 8;

						} else {
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][0] 
								= mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][1]
								= iNewIndex % 8;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][2]
								= iNewIndex / 8;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][3]
								= mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][3];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][4]
								= mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][4];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][5]
								= mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][5];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][3] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][4] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][5] = 0;
						}
#if 0
						LOG_TO_FILE_4("%d %d %d %d\n"
								, mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][0]
								, mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][1]
								, mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][2]
								, mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][3]);
#endif
					}
				}
			}
		}
	}
#endif
	if( mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] < 1 )
	{
		mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] = 1;
	}
	CopyMemory( mUSER[tUserIndex].mEffectValue, mPLAYUSER_COM.mRecv_EffectValue, ( MAX_AVATAR_EFFECT_SORT_NUM * 8 ) );
	switch( mPLAYUSER_COM.mRecv_LoginPremiumPCRoom )
	{
		case 2 :
			mUSER[tUserIndex].mGeneralExperienceUpRatio = 0.2f;
			mUSER[tUserIndex].mItemDropUpRatio = 0.5f;
			mUSER[tUserIndex].mGeneralExperienceDownRatio = 0.5f;
			mUSER[tUserIndex].mSupportSkillTimeUpRatio = 1;
			break;
		default :
			mUSER[tUserIndex].mGeneralExperienceUpRatio = 0.0f;
			mUSER[tUserIndex].mItemDropUpRatio = 0.0f;
			mUSER[tUserIndex].mGeneralExperienceDownRatio = 1.0f;
			mUSER[tUserIndex].mSupportSkillTimeUpRatio = 1;
			break;
	}
	if( mUSER[tUserIndex].mAvatarInfo.aPlayTime2 < 1 )
	{
		mUSER[tUserIndex].mCheckHealthState = FALSE;
		mUSER[tUserIndex].mHealthState = 1;
	}
	else
	{
		mUSER[tUserIndex].mCheckHealthState = TRUE;
		mUSER[tUserIndex].mHealthState = mUTIL.ReturnHealthState( mUSER[tUserIndex].mAvatarInfo.aPlayTime2 );
	}

	/** 2009. 10. 26 : DarkAttack Potion add (wolf)*/
    mUSER[tUserIndex].mTickCountForDarkAttack = 0;
    mUSER[tUserIndex].iKindDarkAttack = 0;
    /** 2009. 10. 26 : DarkAttack Potion add (wolf)*/

	mUSER[tUserIndex].mTickCountFor01Second = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01SecondForProtect = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor30Second = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01MinuteForHealth = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01Minute = mGAME.mTickCount;

	mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor03Second = mGAME.mTickCount;

	mUSER[tUserIndex].mCheckMaxAttackPacketNum = 1;
#ifdef __GOD__
	mUSER[tUserIndex].mAttackPacketSort = 0;
#endif
	mUSER[tUserIndex].mMaxAttackPacketNum = 0;
	mUSER[tUserIndex].mNowAttackPacketNum = 0;
	mUSER[tUserIndex].mAutoCheckState = 0;
	mUSER[tUserIndex].mHackCheckTime = GetTickCount();
	mUSER[tUserIndex].mMoveZoneResult = 0;
	CopyMemory( &mUSER[tUserIndex].mAuthInfo, &mPLAYUSER_COM.mRecv_AuthInfo, sizeof( AUTH_INFO ) );

	//@{ auto quiz
	if((ZONE_BASE_JUNG == mSERVER_INFO.mServerNumber) || 
			(ZONE_BASE_SA == mSERVER_INFO.mServerNumber) || 
			(ZONE_BASE_MA == mSERVER_INFO.mServerNumber) || 
			(ZONE_BASE_NANG == mSERVER_INFO.mServerNumber)) {
		mUSER[ tUserIndex ].mAvatarInfo.iEnter_The_Prison = 0;
	}
	//@}

	//---------//
	//N-PROTECT//
	//---------//
#ifdef __N_PROTECT__
	mUSER[tUserIndex].mCheckNPROTECT = FALSE;
#endif
	//---------//
	//---------//
	//---------//
	mTRANSFER.B_REGISTER_AVATAR_RECV( &mUSER[tUserIndex].mAvatarInfo, mUSER[tUserIndex].mEffectValue, mUSER[tUserIndex].uPremiumServerExpirationDate ); // mUSER[tUserIndex].uPremiumServerExpirationDate Ãß°¡. // @_Premium_Server_@
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mTRANSFER.B_BROADCAST_WORLD_INFO( &mGAME.mWorldInfo, &mGAME.mTribeInfo );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mAVATAR_OBJECT[tUserIndex].mCheckValidState = TRUE;
	mAVATAR_OBJECT[tUserIndex].mUniqueNumber = mGAME.mAvatarObjectUniqueNumber;
	mGAME.mAvatarObjectUniqueNumber++;
	mAVATAR_OBJECT[tUserIndex].mDATA.aVisibleState = (unsigned char)mUSER[tUserIndex].mAvatarInfo.aVisibleState;
	mAVATAR_OBJECT[tUserIndex].mDATA.aSpecialState = (unsigned char)mUSER[tUserIndex].mAvatarInfo.aSpecialState;
	mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
	mAVATAR_OBJECT[tUserIndex].mDATA.uGoodFellow = mUSER[tUserIndex].uGoodFellow;
	strncpy( mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, mUSER[tUserIndex].mAvatarInfo.aGuildName, MAX_GUILD_NAME_LENGTH );
	mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = mUSER[tUserIndex].mAvatarInfo.aGuildRole;
	strncpy( mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, mUSER[tUserIndex].mAvatarInfo.aCallName, MAX_CALL_NAME_LENGTH );
	mAVATAR_OBJECT[tUserIndex].mDATA.aGuildMarkEffect = mUSER[tUserIndex].mAvatarInfo.aGuildMarkEffect;
	strncpy( mAVATAR_OBJECT[tUserIndex].mDATA.aName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH );
	mAVATAR_OBJECT[tUserIndex].mDATA.aTribe = mUSER[tUserIndex].mAvatarInfo.aTribe;
	mAVATAR_OBJECT[tUserIndex].mDATA.aPreviousTribe = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
	mAVATAR_OBJECT[tUserIndex].mDATA.aGender = mUSER[tUserIndex].mAvatarInfo.aGender;
	mAVATAR_OBJECT[tUserIndex].mDATA.aHeadType = mUSER[tUserIndex].mAvatarInfo.aHeadType;
	mAVATAR_OBJECT[tUserIndex].mDATA.aFaceType = mUSER[tUserIndex].mAvatarInfo.aFaceType;
	mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 = mUSER[tUserIndex].mAvatarInfo.aLevel1;
	mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
	for( index01 = 0 ; index01 < MAX_EQUIP_SLOT_NUM ; index01++ )
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[index01][0] = mUSER[tUserIndex].mAvatarInfo.aEquip[index01][0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[index01][1] = mUSER[tUserIndex].mAvatarInfo.aEquip[index01][2];
	}
	CopyMemory( &mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof( ACTION_INFO ) );
	mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4];
	mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[5];

	for( index01 = 0 ; index01 < MAX_AVATAR_EFFECT_SORT_NUM ; index01++ )
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[index01] = mUSER[tUserIndex].mEffectValue[index01][0];
	}

#ifdef __ANIMAL__
	if( ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM ) && ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= ( MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1 ) ) )
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = mUSER[tUserIndex].mAvatarInfo.aAnimal[( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - MAX_AVATAR_ANIMAL_NUM )];
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = 0;
	}
#endif



	strncpy( mAVATAR_OBJECT[tUserIndex].mDATA.aPartyName, mUSER[tUserIndex].mAvatarInfo.aPartyName, MAX_PARTY_NAME_LENGTH );
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[1] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[2] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState = 0;
	mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion = TRUE;
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
    // # Defense Hack # {
    mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
    mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
    mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
    // # }
	mAVATAR_OBJECT[tUserIndex].mUpdateTimeForBroadcast = GetTickCount();
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	mAVATAR_OBJECT[tUserIndex].mGod = 0;
	mAVATAR_OBJECT[tUserIndex].mChat = 0;
	if( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue )
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
	}
	if( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue )
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
	}
	mTRANSFER.B_AVATAR_ACTION_RECV( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1 );
	if( mUSER[tUserIndex].mAvatarInfo.aVisibleState == 0 )
	{
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	}
	else
	{
		mUSER[tUserIndex].Send (TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
	}
	if( ( mUSER[tUserIndex].mAvatarInfo.aVisibleState == 1 ) && ( mPLAYUSER_COM.mRecv_CheckFirstZone == 1 ) && ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) != 0 ) )
	{
		tSort = 110;
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
		mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
	}
	iTemp_Auto_time = mGAME.Check_Use_Auto_Day(tUserIndex);
	if(0 == iTemp_Auto_time){
		mUSER[tUserIndex].mAvatarInfo.aAutoLifeRatio = 0;
		mUSER[tUserIndex].mAvatarInfo.aAutoManaRatio = 0;
	}
	mTRANSFER.B_AVATAR_CHANGE_INFO_2( 29, iTemp_Auto_time );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//---------//
	//N-PROTECT//
	//---------//
#ifdef __N_PROTECT__
	if( mUSER[tUserIndex].mNPROTECT->GetAuthQuery() != 0 )
	{
		mUSER[tUserIndex].mCheckNPROTECT = FALSE;
		mGAMELOG.GL_642_N_PROTECT( tUserIndex, 101 );
	}
	else
	{
		mUSER[tUserIndex].mCheckNPROTECT = TRUE;
		mUSER[tUserIndex].mNumberForNPROTECT = 1;
		mUSER[tUserIndex].mTickCountForNPROTECT = GetTickCount();
		mTRANSFER.B_CHECK_N_PROTECT_1( &mUSER[tUserIndex].mNPROTECT->m_AuthQuery );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	}
#endif
	//---------//
	//---------//
	//---------//
#ifdef __PARTY_VER_2__
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, "" ) != 0 ){
		::memset(tData, 0, MAX_BROADCAST_DATA_SIZE);
		CopyMemory( tData, mUSER[tUserIndex].mAvatarInfo.aPartyName, MAX_PARTY_NAME_LENGTH );
		CopyMemory( &tData[MAX_PARTY_NAME_LENGTH], mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH );
		mRELAY_COM.U_DEMAND_BROADCAST_DATA( 108, tData);
	}
#endif
	mTRANSFER.B_AVATAR_CHANGE_INFO_2( 42, mUSER[tUserIndex].mAvatarInfo.aZone84Time);
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );

    mUSER[tUserIndex].mHeartCheckTime = ::time(NULL);
	
	/** 2009. 11. 23 : ÆÐÅ°Áö ¾ÆÀÌÅÛ °³¹ß (wolf) */
#ifdef __TK__
	// ÆÐÅ°Áö ¾ÆÀÌÅÛÁß ´Ü ÇÏ³ª¶óµµ »ç¿ë½Ã »ç¿ëÁßÀÌ¶ó°í Ç¥½Ã.
	if( mUSER[tUserIndex].mAvatarInfo.aPackSilverDate >= mUTIL.ReturnNowDate()
		|| mUSER[tUserIndex].mAvatarInfo.aPackSilverDateMobile >= mUTIL.ReturnNowDate() )
	{
		mUSER[tUserIndex].mGeneralExperienceUpRatio =+ 0.2f;
		mUSER[tUserIndex].mItemDropUpRatio =+ 0.2f;
		mUSER[tUserIndex].mSelfPatExperienceUpRatio = 0.1f;
		mUSER[tUserIndex].bUsePackItem = true;
	}
	else if( mUSER[tUserIndex].mAvatarInfo.aPackGoldDate >= mUTIL.ReturnNowDate() 
		|| mUSER[tUserIndex].mAvatarInfo.aPackGoldDateMobile >= mUTIL.ReturnNowDate() )
	{
		mUSER[tUserIndex].mGeneralExperienceUpRatio =+ 0.3f;
		mUSER[tUserIndex].mItemDropUpRatio =+ 0.3f;
		mUSER[tUserIndex].mSelfPatExperienceUpRatio = 0.2f;
		mUSER[tUserIndex].bUsePackItem = true;
	}
	else if( mUSER[tUserIndex].mAvatarInfo.aPackDiamondDate >= mUTIL.ReturnNowDate() 
		|| mUSER[tUserIndex].mAvatarInfo.aPackDiamondDateMobile >= mUTIL.ReturnNowDate() )
	{
		mUSER[tUserIndex].mGeneralExperienceUpRatio =+ 0.6f;
		mUSER[tUserIndex].mItemDropUpRatio =+ 0.5f;
		mUSER[tUserIndex].mSelfPatExperienceUpRatio = 0.3f;
		mUSER[tUserIndex].bUsePackItem = true;
	}
	
#endif
	/** 2009. 11. 23 : ÆÐÅ°Áö ¾ÆÀÌÅÛ °³¹ß (wolf) */


    mUSER[tUserIndex].mMoveItemInfo = mPLAYUSER_COM.mRecv_MoveItemInfo;
    // ÀÌµ¿¼­¸¦ »ç¿ëÇØ¼­ Á¸ ÀÌµ¿À» ÇÑ °æ¿ì.
    if (((mUSER[tUserIndex].mMoveItemInfo.mInvenPage > -1) && (mUSER[tUserIndex].mMoveItemInfo.mInvenPage < 2)) &&
    	((mUSER[tUserIndex].mMoveItemInfo.mInvenIndex > -1) && (mUSER[tUserIndex].mMoveItemInfo.mInvenIndex < MAX_INVENTORY_SLOT_NUM)) &&
        ((mUSER[tUserIndex].mMoveItemInfo.mInvenX > -1) && (mUSER[tUserIndex].mMoveItemInfo.mInvenX < 8)) &&
        ((mUSER[tUserIndex].mMoveItemInfo.mInvenY > -1) && (mUSER[tUserIndex].mMoveItemInfo.mInvenY < 8)))
    {
        // ÀÌµ¿¼­ »ç¿ë Ã³¸®.
        int tPage = mUSER[tUserIndex].mMoveItemInfo.mInvenPage;
        int tIndex = mUSER[tUserIndex].mMoveItemInfo.mInvenIndex;
        if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != 1109)) {
            mGAMELOG.GL_701_CHEAT_USER(tUserIndex, 1);
            mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
            return;
        }

        mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );

        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;
        if( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1 )
        {
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
        }
        mTRANSFER.B_AVATAR_CHANGE_INFO_2( 203, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] );
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );

        ::memset(&mUSER[tUserIndex].mMoveItemInfo, -1, sizeof(MOVE_ITEM_INFO));
        mPLAYUSER_COM.U_SET_MOVE_ITEM_FOR_ZONE_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].mMoveItemInfo);
    }
}
//W_CLIENT_OK_FOR_ZONE_SEND
void W_CLIENT_OK_FOR_ZONE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if( mUSER[tUserIndex].mMoveZoneResult == 1 ) {
		return;
	}

	int tTribe;
	time_t tCurrentTime = ::time(NULL);
	CopyMemory( &tTribe, &tPacket[1], 4 );

	if( mUSER[tUserIndex].mAvatarInfo.aTribe != tTribe )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if((tCurrentTime - mUSER[tUserIndex].mHeartCheckTime) <= 3) {
		mUSER[tUserIndex].mHeartCheckCount++;
		if(mUSER[tUserIndex].mHeartCheckCount > 10) {
			LOG_TO_FILE_4("![HACK] : %s, %s, %d, %d\n"
					, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName
					, (tCurrentTime - mUSER[tUserIndex].mHeartCheckTime), mUSER[tUserIndex].mHeartCheckCount);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		}
		return;
	}
	mUSER[tUserIndex].mHeartCheckCount = 0;
	mUSER[tUserIndex].mHeartCheckTime = tCurrentTime;

}
//W_AUTO_CHECK_ASK_RECV
void W_AUTO_CHECK_ASK_RECV( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tAnswer;
	CopyMemory( &tAnswer, &tPacket[1], 4 );

	switch( mUSER[tUserIndex].mAutoCheckState )
	{
		case 0 :
			return;
		case 1 :
			mUSER[tUserIndex].mAutoCheckState = 0;
			mUSER[tUserIndex].mAvatarInfo.aKillMonsterNum = 0;
			if( mUSER[tUserIndex].mAutoCheckAnswer == tAnswer )
			{
				return;
			}
			mPLAYUSER_COM.U_ADD_AUTO_USER_LIST_SEND( &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], mSERVER_INFO.mWorldNumber, mSERVER_INFO.mServerNumber );
			mTRANSFER.B_RETURN_TO_AUTO_ZONE();
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
	}
}
//W_AVATAR_ACTION_SEND
void W_AVATAR_ACTION_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	ACTION_INFO tAction;
	CopyMemory( &tAction, &tPacket[1], sizeof( ACTION_INFO ) );

	int index01;
	int index02;
	int tSkillSort;
	int tUseManaValue;
	int tReduceManaRatio;
	//LOG_TO_FILE("=>1\n");
#ifdef __GOD__
	if( !mWORK.CheckValidCharacterMotionForSend( tAction.aType, tAction.aSort, tAction.aSkillNumber, &tSkillSort, &mUSER[tUserIndex].mCheckMaxAttackPacketNum , &mUSER[tUserIndex].mAttackPacketSort , &mUSER[tUserIndex].mMaxAttackPacketNum ) )
#else
	if( !mWORK.CheckValidCharacterMotionForSend( tAction.aType, tAction.aSort, tAction.aSkillNumber, &tSkillSort, &mUSER[tUserIndex].mCheckMaxAttackPacketNum , &mUSER[tUserIndex].mMaxAttackPacketNum ) )
#endif
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	//LOG_TO_FILE_1("=>2 %d\n", tSkillSort);
	mUSER[tUserIndex].mNowAttackPacketNum = 0;
	tUseManaValue = 0;
	switch( tSkillSort )
	{
		case 1 :
			for( index01 = 0 ; index01 < 3 ; index01++ )
			{
				for( index02 = 0 ; index02 < MAX_HOT_KEY_NUM ; index02++ )
				{
					if( ( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] == 1 ) && ( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == tAction.aSkillNumber ) && ( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] == tAction.aSkillGradeNum1 ) )
					{
						break;
					}
				}
				if( index02 < MAX_HOT_KEY_NUM )
				{
					break;
				}
			}
			if( index01 == 3 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue( tAction.aSkillNumber ) != tAction.aSkillGradeNum2 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2 :
			for( index01 = 0 ; index01 < 3 ; index01++ )
			{
				for( index02 = 0 ; index02 < MAX_HOT_KEY_NUM ; index02++ )
				{
					if( ( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] == 1 ) && ( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == tAction.aSkillNumber ) && ( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] == tAction.aSkillGradeNum1 ) )
					{
						break;
					}
				}
				if( index02 < MAX_HOT_KEY_NUM )
				{
					break;
				}
			}
			if( index01 == 3 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue( tAction.aSkillNumber ) != tAction.aSkillGradeNum2 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tUseManaValue = (int) mSKILL.ReturnSkillValue( tAction.aSkillNumber, tAction.aSkillGradeNum1, 1 );
			tReduceManaRatio = mAVATAR_OBJECT[tUserIndex].GetReduceManaRatio();
#if 0
			if( mUSER[tUserIndex].mAvatarInfo.aHalfManaTime > 0  )
			{
				tUseManaValue = tUseManaValue / 2;
			} 
#endif
			if( tReduceManaRatio > 0 )
			{
				tUseManaValue -= ( ( tUseManaValue * tReduceManaRatio ) / 100 );
			}
			if( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue < tUseManaValue )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
	}
	//LOG_TO_FILE_2("=>3 %d %d\n", mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort, tAction.aSort);
	switch( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort )
	{
		case 11 :
			return;
		case 12 :
			if( tAction.aSort != 0 )
			{
				return;
			}
			break;
	}
	if( tUseManaValue > 0 )
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue -= tUseManaValue;
	}

    if (tAction.aSkillNumber != 0)
    {
    	// µ¿Çà¹«°øÀº °Ë»ç¿¡¼­ Á¦¿Ü.
        if ((tAction.aSkillNumber != 76) && (tAction.aSkillNumber != 77) && (tAction.aSkillNumber != 78) && (tAction.aSkillNumber != 79) && (tAction.aSkillNumber != 80) && (tAction.aSkillNumber != 81))
        {
            if ( (tAction.aSkillGradeNum1 > mUSER[tUserIndex].GetMaxSkillGradeNum(tAction.aSkillNumber)) || (tAction.aSkillGradeNum2 > mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber)) )
            {
                mGAMELOG.GL_702_CHEAT_AVATAR_ACTION(tUserIndex, tAction.aSkillNumber, tAction.aSkillGradeNum1, tAction.aSkillGradeNum2, tAction.aSkillValue);
                mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_1_SEND( 605, &mUSER[tUserIndex].uID[0] );
                mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
                return ;
            }
        }
    }

    // # Defense Hack # {
    float fRange = 0.0f;
    fRange = mUTIL.ReturnLengthXYZ(&tAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0]);

    if((fRange > 666.0f) && !mAVATAR_OBJECT[tUserIndex].mCheckDeath
            && (mUSER[tUserIndex].mAuthInfo.AuthType == 0) && (mAVATAR_OBJECT[tUserIndex].mCheckCount < 1)
            && (!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer)) {
            //&& ((mUSER[tUserIndex].mAvatarInfo.aAutoStart == 0))) { // .... Auto .. ... ... .. ..
        mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 4, fRange);
        tAction.aLocation[0] = mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0];
        tAction.aLocation[1] = mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[1];
        tAction.aLocation[2] = mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[2];
        CopyMemory( &mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof( ACTION_INFO ) );
        mTRANSFER.B_AVATAR_ACTION_RECV( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 0 );
    } else {
        CopyMemory( &mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof( ACTION_INFO ) );
        mTRANSFER.B_AVATAR_ACTION_RECV( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1 );
    }
    mAVATAR_OBJECT[tUserIndex].mCheckCount--;
    mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();

    // # }
	//CopyMemory( &mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof( ACTION_INFO ) );
	//mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
	//mTRANSFER.B_AVATAR_ACTION_RECV( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1 );
	if( mUSER[tUserIndex].mAvatarInfo.aVisibleState == 0 )
	{
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	}
	else
	{
		mUSER[tUserIndex].Send (TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
	}
	//LOG_TO_FILE_2("=>4 %d %d\n", mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort, tAction.aSort);
	if( tAction.aSort != 0 )
	{
		return;
	}
	mUSER[tUserIndex].mTickCountFor01SecondForProtect = mGAME.mTickCount;
	mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = ( mAVATAR_OBJECT[tUserIndex].GetMaxLife() / 3 ) + 1;
	//LOG_TO_FILE_2("===> %d %d\n", mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue, ( mAVATAR_OBJECT[tUserIndex].GetMaxLife() / 3 ) + 1);
	mTRANSFER.B_AVATAR_CHANGE_INFO_2( 10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//CHECK_VALID_CHARACTER_MOTION_FOR_SEND
#ifdef __GOD__
BOOL MyWork::CheckValidCharacterMotionForSend( int tType, int tSort, int tSkillNumber, int *tSkillSort, int *tCheckMaxAttackPacketNum, int *tAttackPacketSort, int *tMaxAttackPacketNum )
#else
BOOL MyWork::CheckValidCharacterMotionForSend( int tType, int tSort, int tSkillNumber, int *tSkillSort, int *tCheckMaxAttackPacketNum, int *tMaxAttackPacketNum )
#endif
{
	*tSkillSort = 0;
	*tCheckMaxAttackPacketNum = 1;
	*tMaxAttackPacketNum = 0;
#ifdef __GOD__
	*tAttackPacketSort = 0;
#endif
	switch( tSort )
	{
		case  0 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case  1 :
			switch( tType )
			{
				case 0 :
				case 1 :
				case 2 :
				case 3 :
				case 4 :
				case 5 :
				case 6 :
				case 7 :
					return TRUE;
			}
			break;
		case  2 :
			switch( tType )
			{
				case 0 :
				case 1 :
				case 2 :
				case 3 :
				case 4 :
				case 5 :
				case 6 :
				case 7 :
					return TRUE;
			}
			break;
		case  3 :
			switch( tType )
			{
				case 0 :
				case 2 :
				case 4 :
				case 6 :
					return TRUE;
			}
			break;
		case  4 :
			switch( tType )
			{
				case 1 :
				case 3 :
				case 5 :
				case 7 :
					return TRUE;
			}
			break;
		case  5 :
			*tMaxAttackPacketNum = 1;
#ifdef __GOD__
			*tSkillSort = 0;
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 1;
#endif
			switch( tType )
			{
				case 1 :
				case 3 :
				case 5 :
				case 7 :
					return TRUE;
			}
			break;
		case  6 :
			*tMaxAttackPacketNum = 2;
#ifdef __GOD__
			*tSkillSort = 0;
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 1;
#endif
			switch( tType )
			{
				case 1 :
				case 3 :
				case 5 :
				case 7 :
					return TRUE;
			}
			break;
		case  7 :
			*tMaxAttackPacketNum = 3;
#ifdef __GOD__
			*tSkillSort = 0;
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 1;
#endif
			switch( tType )
			{
				case 1 :
				case 3 :
				case 5 :
				case 7 :
					return TRUE;
			}
			break;
		case  9 :
			switch( tType )
			{
				case 1 :
				case 3 :
				case 5 :
				case 7 :
					return TRUE;
			}
			break;
		case 10 :
			switch( tType )
			{
				case 0 :
				case 1 :
				case 2 :
				case 3 :
				case 4 :
				case 5 :
				case 6 :
				case 7 :
					return TRUE;
			}
			break;
		case 13 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 14 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 15 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 16 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 17 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 18 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 20 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 21 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 22 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 23 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 30 :
			*tSkillSort = 1;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 32 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
				case 1 :
				case 2 :
				case 3 :
				case 4 :
				case 5 :
				case 6 :
				case 7 :
					return TRUE;
			}
			break;
		case 33 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 38 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 1;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 2;
#endif
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 39 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 1;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 2;
#endif
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 40 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 41 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 42 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 1;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 43 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 3;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 44 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 5;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 45 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 1;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 46 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 3;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 48 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 1;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 49 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 3;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 50 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 5;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 51 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 1;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 52 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 3;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 54 :
			*tSkillSort = 2;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 4;
			*tMaxAttackPacketNum = 1;
#else
			*tCheckMaxAttackPacketNum = 0;
#endif
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 55 :
			*tSkillSort = 2;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 4;
			*tMaxAttackPacketNum = 3;
#else
			*tCheckMaxAttackPacketNum = 0;
#endif
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 56 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 5;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 57 :
			*tSkillSort = 2;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 4;
			*tMaxAttackPacketNum = 1;
#else
			*tCheckMaxAttackPacketNum = 0;
#endif
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 58 :
			*tSkillSort = 2;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 4;
			*tMaxAttackPacketNum = 3;
#else
			*tCheckMaxAttackPacketNum = 0;
#endif
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 60 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 61 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 62 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 63 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 64 :
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 65 :
#ifdef __GOD__
			*tSkillSort = 0;
			*tAttackPacketSort = 5;
			*tMaxAttackPacketNum = 1;
#endif
			*tCheckMaxAttackPacketNum = 0;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 66 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 67 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 68 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 69 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 1;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 70 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 3;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 71 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 1;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 72 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 3;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 73 :
			*tSkillSort = 2;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 4;
			*tMaxAttackPacketNum = 3;
#else
			*tCheckMaxAttackPacketNum = 0;
#endif
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 74 :
			*tSkillSort = 2;
			*tCheckMaxAttackPacketNum = 0;
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 75 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 76 :
			*tSkillSort = 2;
			switch( tType )
			{
				case 0 :
					return TRUE;
			}
			break;
		case 81 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 5;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 82 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 5;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 83 :
			*tSkillSort = 2;
			*tMaxAttackPacketNum = 5;
#ifdef __GOD__
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
#endif
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
#ifdef __GOD__
		case 85 :
			*tSkillSort = 2;
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
			*tMaxAttackPacketNum = 1;
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 86 :
			*tSkillSort = 2;
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
			*tMaxAttackPacketNum = 3;
			switch( tType )
			{
				case 3 :
					return TRUE;
			}
			break;
		case 87 :
			*tSkillSort = 2;
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
			*tMaxAttackPacketNum = 1;
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 88 :
			*tSkillSort = 2;
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 3;
			*tMaxAttackPacketNum = 3;
			switch( tType )
			{
				case 5 :
					return TRUE;
			}
			break;
		case 89 :
			*tSkillSort = 2;
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 4;
			*tMaxAttackPacketNum = 1;
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 90 :
			*tSkillSort = 2;
			*tCheckMaxAttackPacketNum = 1;
			*tAttackPacketSort = 4;
			*tMaxAttackPacketNum = 3;
			switch( tType )
			{
				case 7 :
					return TRUE;
			}
			break;
		case 255 :
			*tSkillSort = 3;
			switch( tType )
			{
				case 0 :
				case 1 :
				case 2 :
				case 3 :
				case 4 :
				case 5 :
				case 6 :
				case 7 :
					return TRUE;
			}
			break;
#endif
			
	}
	return FALSE;
}
//W_UPDATE_AVATAR_ACTION
void W_UPDATE_AVATAR_ACTION( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	//LOG_TO_FILE_1("111 ---> %d\n", mUSER[tUserIndex].mMoveZoneResult);
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	ACTION_INFO tAction;
	CopyMemory( &tAction, &tPacket[1], sizeof( ACTION_INFO ) );
	//LOG_TO_FILE_1("11122 ---> %d\n", tAction.aSort);
	switch( tAction.aSort )
	{
		case  1 :
			mAVATAR_OBJECT[tUserIndex].ProcessForCreateEffectValue( &tAction );
			break;
		case  2 :
			break;
		case 19 :
			if( tAction.aType != 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 31 :
			if( tAction.aType != 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 32 :
			break;
		case 64 :
			if( tAction.aType != 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default :
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
	}
    // # Defense Hack # {
    mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
    mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
    mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
    // # }

    if (tAction.aSkillNumber != 0)
    {
        // µ¿Çà¹«°øÀº °Ë»ç¿¡¼­ Á¦¿Ü.
        if ((tAction.aSkillNumber != 76) && (tAction.aSkillNumber != 77) && (tAction.aSkillNumber != 78) && (tAction.aSkillNumber != 79) && (tAction.aSkillNumber != 80) && (tAction.aSkillNumber != 81))
        {
            if ( (tAction.aSkillGradeNum1 > mUSER[tUserIndex].GetMaxSkillGradeNum(tAction.aSkillNumber)) || (tAction.aSkillGradeNum2 > mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber)) )
            {
                mGAMELOG.GL_702_CHEAT_AVATAR_ACTION(tUserIndex, tAction.aSkillNumber, tAction.aSkillGradeNum1, tAction.aSkillGradeNum2, tAction.aSkillValue);
                mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_1_SEND( 605, &mUSER[tUserIndex].uID[0] );
                mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
                return ;
            }
        }
    }
	CopyMemory( &mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof( ACTION_INFO ) );
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
}
//W_GENERAL_NOTICE_SEND
void W_GENERAL_NOTICE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}
		LOG_TO_FILE("notice 2.\n");
	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory( &tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	if(mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if(mUSER[tUserIndex].mAuthInfo.NoticeFlag == 0){
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	tSort = 102;
	CopyMemory( &tData[0], &tContent[0], MAX_CHAT_CONTENT_LENGTH );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
}
//W_PROCESS_ATTACK_SEND
void W_PROCESS_ATTACK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	ATTACK_FOR_PROTOCOL tAttackInfo;
	CopyMemory( &tAttackInfo, &tPacket[1], sizeof( ATTACK_FOR_PROTOCOL ) );

	switch( tAttackInfo.mCase )
	{
		case 1 : //[ºñ¹«]
			if( ( tAttackInfo.mServerIndex1 == tUserIndex ) && ( tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber ) )
			{
				if( mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1 )
				{
					mUSER[tUserIndex].mNowAttackPacketNum++;
					if( mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum )
					{
						return;
					}
					if( tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort )
					{
						return;
					}
				}
			}
			mGAME.ProcessAttack01( tUserIndex, &tAttackInfo );
			return;
		case 2 : //[¼¼·Â]
			if( ( tAttackInfo.mServerIndex1 == tUserIndex ) && ( tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber ) )
			{
				if( mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1 )
				{
					mUSER[tUserIndex].mNowAttackPacketNum++;
					if( mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum )
					{
						return;
					}
					if( tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort )
					{
						return;
					}
				}
			}
			mGAME.ProcessAttack02( tUserIndex, &tAttackInfo );
			return;
		case 3 : //[Ä³¸¯ÅÍ->¸ó½ºÅÍ]
			if( ( tAttackInfo.mServerIndex1 == tUserIndex ) && ( tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber ) )
			{
				if( mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1 )
				{
					mUSER[tUserIndex].mNowAttackPacketNum++;
					if( mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum )
					{
						return;
					}
					if( tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort )
					{
						return;
					}
				}
			}
			mGAME.ProcessAttack03( tUserIndex, &tAttackInfo );
			return;
		case 4 : //[¸ó½ºÅÍ->Ä³¸¯ÅÍ]
			mGAME.ProcessAttack04( tUserIndex, &tAttackInfo );
			return;
		case 5 : //[Á¡Ç÷]
			if( ( tAttackInfo.mServerIndex1 == tUserIndex ) && ( tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber ) )
			{
				if( mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1 )
				{
					mUSER[tUserIndex].mNowAttackPacketNum++;
					if( mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum )
					{
						return;
					}
					if( tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort )
					{
						return;
					}
				}
			}
			mGAME.ProcessAttack05( tUserIndex, &tAttackInfo );
			return;
		case 6 : //[ÇØÇ÷]
			if( ( tAttackInfo.mServerIndex1 == tUserIndex ) && ( tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber ) )
			{
				if( mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1 )
				{
					mUSER[tUserIndex].mNowAttackPacketNum++;
					if( mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum )
					{
						return;
					}
					if( tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort )
					{
						return;
					}
				}
			}
			mGAME.ProcessAttack06( tUserIndex, &tAttackInfo );
			return;
		default :
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
	}
}
//W_PROCESS_DATA_SEND
void W_PROCESS_DATA_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tData[0], &tPacket[5], MAX_BROADCAST_DATA_SIZE );

	mWORK.ProcessForData( tUserIndex, tSort, &tData[0] );
}
//W_DEMAND_ZONE_SERVER_INFO_2
void W_DEMAND_ZONE_SERVER_INFO_2( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int nCount = 0;
	int tZoneNumber;
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tZoneNumber, &tPacket[5], 4 );

	if( ( tZoneNumber < MIN_VALID_ZONE_NUMBER ) || ( tZoneNumber > MAX_VALID_ZONE_NUMBER ) || ( tZoneNumber == mSERVER_INFO.mServerNumber ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

    // ÀÌµ¿¼­ ¾ÆÀÌÅÛÀ» »ç¿ëÇÑ »óÅÂ¿¡¼­ ´Ù¸¥ ¹æ½ÄÀÇ Á¸ ÀÌµ¿ ÆÐÅ¶ÀÌ µé¾î¿ÔÀ» °æ¿ì ½ÇÆÐ·Î Ã³¸®.
    if (mUSER[tUserIndex].mMoveItemInfo.mZoneNumber > 0)
    {
        if (tSort != 9)
        {
            ::memset(&mUSER[tUserIndex].mMoveItemInfo, -1, sizeof(MOVE_ITEM_INFO));
            mPLAYUSER_COM.U_SET_MOVE_ITEM_FOR_ZONE_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].mMoveItemInfo);
            mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT( 1, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
            mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
            LOG_TO_FILE_1("!MoveItem not match sort(%d).\n", tSort);
            return ;
        }
    }

	switch( tSort )
	{
		case  2 : //[GM]::[MOVEZONE]
			if(mUSER[tUserIndex].mAuthInfo.AuthType == 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if(mUSER[tUserIndex].mAuthInfo.MoveZoneFlag == 0){
				return;
			}
			break;
		case  3 : //[DEATH]
			break;
		case  4 : //[PORTAL]
			break;
		case  5 : //[NPC(MONEY)]
			break;
		case  6 : //[NPC(MOVE)]
			break;
		case  7 : //[RETURN]
			break;
		case  8 : //[RETURN(ITEM)]
			break;
		case  9 : //[MOVE(ITEM)] // ÀÌµ¿¼­
            if (mUSER[tUserIndex].mMoveItemInfo.mZoneNumber == tZoneNumber) // ÀÌµ¿¼­ ¾ÆÀÌÅÛÀ» ÅëÇÑ Á¸ ÀÌµ¿ÀÏ °æ¿ì.
            {
                int tResult = mGAME.CheckMoveZoneForMoveZoneItem(mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mMoveItemInfo.mZoneNumber);
                if (tResult != 0)
                {
                    mGAMELOG.GL_701_CHEAT_USER(tUserIndex, 1);
                    mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
                    return;
                }
            }
            else
            {
                mGAMELOG.GL_701_CHEAT_USER(tUserIndex, 1);
                mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
                return;
            }
			break;
		case 10 : //[NPC(ÁöÁ¸¾ËÇö)]
			break;
		case 11 : //[AUTO_TO_ZONE_037]
			break;
		case 12 ://Zone 84
			break;
		default :
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
	}
	if(1 == mUSER[tUserIndex].mAuthInfo.UZonemoveFlag){
		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT( 1, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	} 
	
	if(!strcmp( mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )], "0.0.0.0" )) {
		mCENTER_COM.W_ZONE_OTHER_CONNECTION_INFO(tZoneNumber);
		while(1) {
			if(strcmp(mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)], "0.0.0.0") != 0) {
				goto RESULT;
			}
			if(nCount > 100) {
				break;
			}
			nCount++;
			usleep(10);
		}
		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT( 1, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
RESULT :
	if(mUSER[tUserIndex].m_bIsSend_Question) {
		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT( 2, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[0] = mSERVER_INFO.mServerNumber;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[1] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[2] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[3] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] = mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[5] = mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_3_SEND( mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo, mUSER[tUserIndex].mEffectValue,	&mUSER[tUserIndex].mAuthInfo);
	if( mPLAYUSER_COM.mRecv_Result != 0 )
	{
		//LOG_TO_FILE_2("![%s] : U_REGISTER_USER_FOR_ZONE_3_SEND failed(%d)\n"
		//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if(84 == tZoneNumber){
		if(50 > mUSER[tUserIndex].mAvatarInfo.aLevel1){
			mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT( 3, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if(0 >= (mUSER[tUserIndex].mAvatarInfo.aZone84Time & 0x0000000F)){
			mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT( 4, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
#if 0
		mPLAYUSER_COM.U_ZONE_84_FOR_ZONE_SEND(mUSER[tUserIndex].mPlayUserIndex, 0);
		if(0 != mPLAYUSER_COM.mRecv_Result){
			mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT( 5, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
#endif
	}

	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mMoveZoneResult = 1;
	mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT( 0, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );

	mUSER[tUserIndex].m_bUDPActivated = false;
	mUSER[tUserIndex].m_bUDPArrivedAtClient = false;
}
//W_FAIL_MOVE_ZONE_2_SEND
void W_FAIL_MOVE_ZONE_2_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mMoveZoneResult = 0;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[0] = mSERVER_INFO.mServerNumber;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[1] = (int) mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[2] = (int) mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[3] = (int) mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] = mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[5] = mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_2_SEND( mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo, mUSER[tUserIndex].mEffectValue,	&mUSER[tUserIndex].mAuthInfo);
	if( mPLAYUSER_COM.mRecv_Result != 0 )
	{
		//LOG_TO_FILE_2("![%s] : U_REGISTER_USER_FOR_ZONE_2_SEND failed(%d)\n"
		//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mRegisterTime = GetTickCount();

	// ÀÌµ¿¼­ ¾ÆÀÌÅÛ »ç¿ë ÈÄ Á¸ ÀÌµ¿ ½ÇÆÐ ½Ã Ã³¸®.
	if (mUSER[tUserIndex].mMoveItemInfo.mZoneNumber > 0)
    {
        ::memset(&mUSER[tUserIndex].mMoveItemInfo, -1, sizeof(MOVE_ITEM_INFO));
        mPLAYUSER_COM.U_SET_MOVE_ITEM_FOR_ZONE_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].mMoveItemInfo);
    }
}
//W_USE_HOTKEY_ITEM_SEND
void W_USE_HOTKEY_ITEM_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
    if( mAVATAR_OBJECT[tUserIndex].mDATA.bStateDarkAttack )
    {
        return;
    }
    /** 2009. 10. 26 : DarkAttack Potion add (wolf) */


	int tPage;
	int tIndex;
	CopyMemory( &tPage, &tPacket[1], 4 );
	CopyMemory( &tIndex, &tPacket[5], 4 );
	if( ( tPage < 0 ) || ( tPage > 2 ) || ( tIndex < 0 ) || ( tIndex > ( MAX_HOT_KEY_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO *tITEM_INFO;
	int tGainLifeValue;
	int tGainManaValue;
	int tGainPatActivityValue;
	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
    int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];
    /** 2009. 10. 26 : DarkAttack Potion add (wolf) */

	switch( mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] )
	{
		case 3 :
			if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12 ) || ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 38 ) )
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			tITEM_INFO = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] );
			if( tITEM_INFO == NULL )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( tITEM_INFO->iSort != 2 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tGainLifeValue = 0;
			tGainManaValue = 0;
			tGainPatActivityValue = 0;
			switch( tITEM_INFO->iPotionType[0] )
			{
				case 1 :
					if( !mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					if( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue >= mAVATAR_OBJECT[tUserIndex].GetMaxLife() )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					tGainLifeValue = tITEM_INFO->iPotionType[1];
					if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue ) > mAVATAR_OBJECT[tUserIndex].GetMaxLife() )
					{
						tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
					}
					break;
				case 2 :
					if( !mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					if( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue >= mAVATAR_OBJECT[tUserIndex].GetMaxLife() )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					tGainLifeValue = (int) ( (float) ( mAVATAR_OBJECT[tUserIndex].GetMaxLife() * tITEM_INFO->iPotionType[1] ) * 0.01f );
					if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue ) > mAVATAR_OBJECT[tUserIndex].GetMaxLife() )
					{
						tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
					}
					break;
				case 3 :
					if( !mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					if( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue >= mAVATAR_OBJECT[tUserIndex].GetMaxMana() )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					tGainManaValue = tITEM_INFO->iPotionType[1];
					if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue + tGainManaValue ) > mAVATAR_OBJECT[tUserIndex].GetMaxMana() )
					{
						tGainManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana() - mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
					}
					break;
				case 4 :
					if( !mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					if( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue >= mAVATAR_OBJECT[tUserIndex].GetMaxMana() )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					tGainManaValue = (int) ( (float) ( mAVATAR_OBJECT[tUserIndex].GetMaxMana() * tITEM_INFO->iPotionType[1] ) * 0.01f );
					if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue + tGainManaValue ) > mAVATAR_OBJECT[tUserIndex].GetMaxMana() )
					{
						tGainManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana() - mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
					}
					break;
				case 5 :
					if( !mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue >= mAVATAR_OBJECT[tUserIndex].GetMaxLife() ) && ( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue >= mAVATAR_OBJECT[tUserIndex].GetMaxMana() ) )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					tGainLifeValue = (int) ( (float) ( mAVATAR_OBJECT[tUserIndex].GetMaxLife() * tITEM_INFO->iPotionType[1] ) * 0.01f );
					if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue ) > mAVATAR_OBJECT[tUserIndex].GetMaxLife() )
					{
						tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
					}
					tGainManaValue = (int) ( (float) ( mAVATAR_OBJECT[tUserIndex].GetMaxMana() * tITEM_INFO->iPotionType[1] ) * 0.01f );
					if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue + tGainManaValue ) > mAVATAR_OBJECT[tUserIndex].GetMaxMana() )
					{
						tGainManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana() - mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
					}
					break;
				case 6 :
					if( mUSER[tUserIndex].mAvatarInfo.aEquip[8][0] < 1 )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					if( mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] >= MAX_PAT_ACTIVITY_SIZE )
					{
						mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 1, tPage, tIndex );
						mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
						return;
					}
					tGainPatActivityValue = tITEM_INFO->iPotionType[1];
					if( ( mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] + tGainPatActivityValue ) >= MAX_PAT_ACTIVITY_SIZE )
					{
						tGainPatActivityValue = MAX_PAT_ACTIVITY_SIZE - mUSER[tUserIndex].mAvatarInfo.aEquip[8][1];
					}
					break;
				case 9 :
					break;
					/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
                case 12 :
                {
                    if( mUSER[tUserIndex].iKindDarkAttack == 2 )
                    {
                        mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 2, tPage, tIndex );
                        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
                        //LOG_TO_FILE_2("![%s] : %d \n",__FUNCTION__,__LINE__);
                        return;
                    }
                    else
                    {
                        mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
                        if( mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1 )
                        {
                            mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
                            mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
                            mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
                        }
                        mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 3, tPage, tIndex );
                        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );

                        mUSER[tUserIndex].mEffectValue[15][0] = 3;
                        mUSER[tUserIndex].mEffectValue[15][1] = 10;
                        mUSER[tUserIndex].iKindDarkAttack = 1;
                        mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[15] = mUSER[tUserIndex].mEffectValue[15][0];
                        tEffectValueState[15] = 1;
                        mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0] );
                        mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1 );
                    }
                }
                return;
				case 13 :
                {
                    if( mUSER[tUserIndex].iKindDarkAttack == 1 )
                    {
                        mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 2, tPage, tIndex );
                        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
                        //LOG_TO_FILE_2("![%s] : %d \n",__FUNCTION__,__LINE__);
                        return;
                    }
                    else
                    {
                        mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
                        if( mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1 )
                        {
                            mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
                            mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
                            mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
                        }
                        mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 4, tPage, tIndex );
                        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );


                        mUSER[tUserIndex].mEffectValue[15][0] = 3;
                        mUSER[tUserIndex].mEffectValue[15][1] = 30;
                        mUSER[tUserIndex].iKindDarkAttack = 2;
                        mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[15] = mUSER[tUserIndex].mEffectValue[15][0];
                        tEffectValueState[15] = 1;
                        mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0] );
                        mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1 );
                    }
                }
                return;
				/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
					
				default :
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
			}
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if( mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1 )
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 0, tPage, tIndex );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			if( tGainLifeValue > 0 )
			{
				mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue += tGainLifeValue;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2( 10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			}
			if( tGainManaValue > 0 )
			{
				mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue += tGainManaValue;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2( 11, mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			}
			if( tGainPatActivityValue > 0 )
			{
				mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] += tGainPatActivityValue;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2( 12, mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			}
			return;
		case 13 :
                {
                    if( mUSER[tUserIndex].iKindDarkAttack == 1 )
                    {
                        mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 2, tPage, tIndex );
                        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
                        //LOG_TO_FILE_2("![%s] : %d \n",__FUNCTION__,__LINE__);
                        return;
                    }
                    else
                    {
                        mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
                        if( mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1 )
                        {
                            mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
                            mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
                            mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
                        }
                        mTRANSFER.B_USE_HOTKEY_ITEM_RECV( 4, tPage, tIndex );
                        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );


                        mUSER[tUserIndex].mEffectValue[15][0] = 3;
                        mUSER[tUserIndex].mEffectValue[15][1] = 30;
                        mUSER[tUserIndex].iKindDarkAttack = 2;
                        mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[15] = mUSER[tUserIndex].mEffectValue[15][0];
                        tEffectValueState[15] = 1;
                        mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0] );
                        mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1 );
                    }
                }
                return;

		default :
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
	}
}
//W_USE_INVENTORY_ITEM_SEND
void W_USE_INVENTORY_ITEM_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage;
	int tIndex;
	int tValue;
	int bParam_1 = 0;
	int bParam_2 = 0;

	CopyMemory( &tPage, &tPacket[1], 4 );
	CopyMemory( &tIndex, &tPacket[5], 4 );
	CopyMemory( &tValue, &tPacket[9], 4 );
	CopyMemory( &bParam_1, &tPacket[ 13 ], 1 );
	CopyMemory( &bParam_2, &tPacket[ 14 ], 1 );
	
	// 2009.11.23 : ±è¼º¼ö :µð¹ö±ëÀ» À§ÇÑ ³Ö¾î¶² ÄÚµå	
	// LOG_TO_FILE_3("![INFO] tPage = %d  , tIndex = %d , tValue = %d \n",tPage ,tIndex ,tValue  );

	if( ( tPage < 0 ) || ( tPage > 1 ) || ( tIndex < 0 ) || ( tIndex > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	int index02;
	ITEM_INFO *tITEM_INFO;
	SKILL_INFO *tSKILL_INFO;
	int tEquipIndex;
	int tEquip[4];
	int tItemLLevel;
	int tItemHLevel;
	int tTribeItemList[9];
	int tRandomValue;
	int tItemType;
	int tItemSort;
	int tSearchNum;
	int tMoney;
	int iInvenSlot = 0;
	int tItemListNum = 5;
	int iPage = 0;
	int iInvenIndex = 0;
	int tItemCount = 0;
	int tPageList[tItemListNum];
	int tInvenSlotList[tItemListNum];
	int tInvenIndexList[tItemListNum];
	int tItemList[tItemListNum][2];
	//int tItemCountList[tItemListNum];
	int tItemValueList[tItemListNum];
	int tItemRecognitionList[tItemListNum];
	int temp_AddTime = 0;
	int tDumyPageList[tItemListNum];
	int tDumyInvenSlotList[tItemListNum];
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	time_t tCountSeconds;
	struct tm *tPresentTime;
	char cDate[100];
	unsigned int iDate = 0;
	unsigned int tZone84Date = 0;
	int tProtectIS = 0;
	int tItemNumber = 0; // »ç¿ëÇÒ ¾ÆÀÌÅÛ ¹øÈ£ ÀúÀå¿ë º¯¼ö.

	ZeroMemory(tBroadcastInfoData, sizeof (tBroadcastInfoData));

	if( tPage == 1 )
	{
		if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] );
	if( tITEM_INFO == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	tItemNumber = tITEM_INFO->iIndex;

	switch( tITEM_INFO->iSort )
	{
		case  5 : //[¹«°øºñ±Þ]
			if( tITEM_INFO->iEquipInfo[0] != 1 )
			{
				if( mUSER[tUserIndex].mAvatarInfo.aPreviousTribe != ( tITEM_INFO->iEquipInfo[0] - 2 ) )
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
#ifdef __GOD__
			if( (mUSER[tUserIndex].mAvatarInfo.aLevel1 +mUSER[tUserIndex].mAvatarInfo.aLevel2) < (tITEM_INFO->iLevelLimit+ tITEM_INFO->iMartialLevelLimit) )
#else
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < tITEM_INFO->iLevelLimit )
#endif
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			for( index01 = 0 ; index01 < MAX_SKILL_SLOT_NUM ; index01++ )
			{
				if( mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == tITEM_INFO->iGainSkillNumber )
				{
					break;
				}
			}
			if( index01 < MAX_SKILL_SLOT_NUM )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tSKILL_INFO = mSKILL.Search( tITEM_INFO->iGainSkillNumber );
			if( tSKILL_INFO == NULL )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aSkillPoint < tSKILL_INFO->sLearnSkillPoint )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			switch( tSKILL_INFO->sType )
			{
				case 1 :
					for( index01 = 0 ; index01 < 10 ; index01++ )
					{
						if( mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1 )
						{
							break;
						}
					}
					if( index01 == 10 )
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					break;
				case 2 :
					for( index01 = 20 ; index01 < 30 ; index01++ )
					{
						if( mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1 )
						{
							break;
						}
					}
					if( index01 == 30 )
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					break;
				case 3 :
					for( index01 = 10 ; index01 < 20 ; index01++ )
					{
						if( mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1 )
						{
							break;
						}
					}
					if( index01 == 20 )
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					break;
				case 4 :
					for( index01 = 10 ; index01 < 20 ; index01++ )
					{
						if( mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1 )
						{
							break;
						}
					}
					if( index01 == 20 )
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					break;
				default :
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
			}
			mUSER[tUserIndex].mAvatarInfo.aSkillPoint -= tSKILL_INFO->sLearnSkillPoint;
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = tSKILL_INFO->sIndex;
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = tSKILL_INFO->sLearnSkillPoint;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  6 : //[Àå½Ä]
		case  7 : //[¸ñ°ÉÀÌ]
		case  8 : //[¸ÁÅä]
		case  9 : //[º¹Àå]
		case 10 : //[Àå°©]
		case 11 : //[¹ÝÁö]
		case 12 : //[½Å¹ß]
		case 13 : //[°Ë]
		case 14 : //[µµ]
		case 15 : //[Åõ¿Á]
		case 16 : //[ÅÂµµ]
		case 17 : //[½Ö±Ø]
		case 18 : //[ºñÆÄ]
		case 19 : //[¹Úµµ]
		case 20 : //[ÀåÃ¢]
		case 21 : //[±Ý°­Àú]
		case 22 : //[¿µ¹°]
			if( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( !mUTIL.CheckPossibleEquipItem( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0]
				, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, -1
#ifdef __GOD__
				,( mUSER[tUserIndex].mAvatarInfo.aLevel1+ mUSER[tUserIndex].mAvatarInfo.aLevel2 )
#else
				, mUSER[tUserIndex].mAvatarInfo.aLevel1 
#endif
				) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tEquipIndex = tITEM_INFO->iEquipInfo[1] - 2;
			if( ( tEquipIndex < 0 ) || ( tEquipIndex > ( MAX_EQUIP_SLOT_NUM - 1 ) ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tEquip[0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0];
			tEquip[1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1];
			tEquip[2] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2];
			tEquip[3] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3];
			mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0];
			mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
			mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
			mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
			mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0];
			mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tEquip[0];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tEquip[1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tEquip[2];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tEquip[3];
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType = (unsigned char)mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2;
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			if( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].GetMaxLife() )
			{
				mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
			}
			if( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].GetMaxMana() )
			{
				mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
			}
			if( tEquipIndex == 7 )
			{
				mAVATAR_OBJECT[tUserIndex].ProcessForDeleteEffectValue();
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
	}
	
	// 2009.11.23 : ±è¼º¼ö :µð¹ö±ëÀ» À§ÇÑ ³Ö¾î¶² ÄÚµå
	//LOG_TO_FILE_1("![INFO] Use Item Num = %d \n", tITEM_INFO->iIndex);
	
	switch( tITEM_INFO->iIndex )
	{
		case  1017 : //[È°·Â´Ü]
			if( mUSER[tUserIndex].mAvatarInfo.aEatLifePotion >= 100 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aEatLifePotion++;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0  );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1018 : //[³»°ø´Ü]
			if( mUSER[tUserIndex].mAvatarInfo.aEatManaPotion >= 100 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aEatManaPotion++;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1092 : //[...]
			if( mUSER[tUserIndex].mAvatarInfo.aEatStrengthPotion >= 100 )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aEatStrengthPotion++;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1093 : //[...]
			if( mUSER[tUserIndex].mAvatarInfo.aEatWisdomPotion >= 100 )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aEatWisdomPotion++;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1026 : //[±ÍÈ¯¼­]
			if(124 == mSERVER_INFO.mServerNumber)
				return;
            if( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1 ) {
                mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
            }

			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;
			if( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1 )
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			}
            mAVATAR_OBJECT[tUserIndex].mCheckDeath = true;
            mAVATAR_OBJECT[tUserIndex].mCheckCount = 9;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1027 : //[È¯¿øÁø°æ]
			for( index01 = 0 ; index01 < MAX_SKILL_SLOT_NUM ; index01++ )
			{
				if( mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1 )
				{
					continue;
				}
				mUSER[tUserIndex].mAvatarInfo.aSkillPoint += mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1];
				mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = 0;
			}
			for( index01 = 0 ; index01 < 3 ; index01++ )
			{
				for( index02 = 0 ; index02 < MAX_HOT_KEY_NUM ; index02++ )
				{
					if( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1 )
					{
						continue;
					}
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
				}
			}
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1028 : //[Ç÷¸ÆÅ¸Åë]
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4 );
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1035 : //[Çà¿î±Ç]
			
#ifdef __GOD__
			if( mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1 )
			{
#endif
				tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
				if( tItemLLevel < 1 )
				{
					tItemLLevel = 1;
				}
				tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
				if( tItemHLevel > MAX_LIMIT_LEVEL_NUM )
				{
					tItemHLevel = MAX_LIMIT_LEVEL_NUM;
				}
#ifdef __GOD__
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}

#endif
			switch( mUSER[tUserIndex].mAvatarInfo.aPreviousTribe )
			{
				case 0 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 13;
					tTribeItemList[7] = 14;
					tTribeItemList[8] = 15;
					break;
				case 1 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 16;
					tTribeItemList[7] = 17;
					tTribeItemList[8] = 18;
					break;
				case 2 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 19;
					tTribeItemList[7] = 20;
					tTribeItemList[8] = 21;
					break;
			}
			tRandomValue = rand_mir() % 10000;
			if( tRandomValue < 1 )
			{
				tItemType = 4;
			}
			else if( tRandomValue < 300 )
			{
				tItemType = 3;
			}
			else if( tRandomValue < 9000 )
			{
				tItemType = 2;
			}
			else
			{
				tItemType = 1;
			}
			tRandomValue = rand_mir();
			tItemSort = tTribeItemList[tRandomValue % 9];
			tSearchNum = 0;
			while( tSearchNum < 10 )
			{
				tRandomValue = rand_mir();
				tITEM_INFO = mITEM.Return( ( tItemLLevel + ( tRandomValue % ( tItemHLevel - tItemLLevel + 1 ) ) ), tItemType, tItemSort );
				if( tITEM_INFO )
				{
					if( ( ( tITEM_INFO->iEquipInfo[0] == 1 ) || ( ( tITEM_INFO->iEquipInfo[0] - 2 ) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe ) ) && ( tITEM_INFO->iCheckMonsterDrop == 2 ) )
					{
						break;
					}
					tITEM_INFO = NULL;
					tSearchNum++;
				}
				else
				{
					tSearchNum++;
				}
			}
			if( tITEM_INFO == NULL )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			tValue = tITEM_INFO->iIndex;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000001 );
			if( tITEM_INFO->iType == 4 )
			{
				mGAMELOG.GL_607_GAIN_SIN_ITEM( tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000001 );
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000001;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1036 : //[´ë¿î±Ç]
#ifdef __GOD__
			if( mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1 )
			{
#endif
				tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
				if( tItemLLevel < 1 )
				{
					tItemLLevel = 1;
				}
				tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
				if( tItemHLevel > MAX_LIMIT_LEVEL_NUM )
				{
					tItemHLevel = MAX_LIMIT_LEVEL_NUM;
				}
#ifdef __GOD__
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}

#endif

			switch( mUSER[tUserIndex].mAvatarInfo.aPreviousTribe )
			{
				case 0 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 13;
					tTribeItemList[7] = 14;
					tTribeItemList[8] = 15;
					break;
				case 1 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 16;
					tTribeItemList[7] = 17;
					tTribeItemList[8] = 18;
					break;
				case 2 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 19;
					tTribeItemList[7] = 20;
					tTribeItemList[8] = 21;
					break;
			}
			tRandomValue = rand_mir() % 10000;
			if( tRandomValue < 2 )
			{
				tItemType = 4;
			}
			else if( tRandomValue < 400 )
			{
				tItemType = 3;
			}
			else if( tRandomValue < 9000 )
			{
				tItemType = 2;
			}
			else
			{
				tItemType = 1;
			}
			tRandomValue = rand_mir();
			tItemSort = tTribeItemList[(tRandomValue  % 9 )];
			tSearchNum = 0;
			while( tSearchNum < 10 )
			{
				tRandomValue = rand_mir();
				tITEM_INFO = mITEM.Return( ( tItemLLevel + ( tRandomValue % ( tItemHLevel - tItemLLevel + 1 ) ) ), tItemType, tItemSort );
				if( tITEM_INFO )
				{
					if( ( ( tITEM_INFO->iEquipInfo[0] == 1 ) || ( ( tITEM_INFO->iEquipInfo[0] - 2 ) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe ) ) && ( tITEM_INFO->iCheckMonsterDrop == 2 ) )
					{
						break;
					}
					tITEM_INFO = NULL;
					tSearchNum++;
				}
				else
				{
					tSearchNum++;
				}
			}
			if( tITEM_INFO == NULL )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			tValue = tITEM_INFO->iIndex;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000002 );
			if( tITEM_INFO->iType == 4 )
			{
				mGAMELOG.GL_607_GAIN_SIN_ITEM( tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000002 );
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000002;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1037 : //[Ãµ¿î±Ç]
#ifdef __GOD__
			if( mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1 )
			{
#endif
				tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
				if( tItemLLevel < 1 )
				{
					tItemLLevel = 1;
				}
				tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
				if( tItemHLevel > MAX_LIMIT_LEVEL_NUM )
				{
					tItemHLevel = MAX_LIMIT_LEVEL_NUM;
				}
#ifdef __GOD__
			}
			else
			{
				tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
				tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			}

#endif
			switch( mUSER[tUserIndex].mAvatarInfo.aPreviousTribe )
			{
				case 0 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 13;
					tTribeItemList[7] = 14;
					tTribeItemList[8] = 15;
					break;
				case 1 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 16;
					tTribeItemList[7] = 17;
					tTribeItemList[8] = 18;
					break;
				case 2 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 19;
					tTribeItemList[7] = 20;
					tTribeItemList[8] = 21;
					break;
			}
			tRandomValue = rand_mir() % 10000;
			if( tRandomValue < 3 )
			{
				tItemType = 4;
			}
			else if( tRandomValue < 500 )
			{
				tItemType = 3;
			}
			else if( tRandomValue < 9000 )
			{
				tItemType = 2;
			}
			else
			{
				tItemType = 1;
			}
			tRandomValue = rand_mir();
			tItemSort = tTribeItemList[( tRandomValue % 9 )];
			tSearchNum = 0;
			while( tSearchNum < 10 )
			{
				tRandomValue = rand_mir();
				tITEM_INFO = mITEM.Return( ( tItemLLevel + ( tRandomValue % ( tItemHLevel - tItemLLevel + 1 ) ) ), tItemType, tItemSort );
				if( tITEM_INFO )
				{
					if( ( ( tITEM_INFO->iEquipInfo[0] == 1 ) || ( ( tITEM_INFO->iEquipInfo[0] - 2 ) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe ) ) && ( tITEM_INFO->iCheckMonsterDrop == 2 ) )
					{
						break;
					}
					tITEM_INFO = NULL;
					tSearchNum++;
				}
				else
				{
					tSearchNum++;
				}
			}
			if( tITEM_INFO == NULL )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			tValue = tITEM_INFO->iIndex;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000003 );
			if( tITEM_INFO->iType == 4 )
			{
				mGAMELOG.GL_607_GAIN_SIN_ITEM( tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000003 );
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000003;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1041 : //[Áö°¢È¯]
			mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime2 += 180;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1043 :
			tRandomValue = rand_mir() % 1000;
			if( tRandomValue < 334 )
			{
				tValue = 1021;
			}
			else if( tRandomValue < 667 )
			{
				tValue = 1022;
			}
			else
			{
				tValue = 1023;
			}
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1045 : //[Àü³¶]
			tMoney = ( 1000 + rand_mir() % 4001 ) * 1000;
			if( mUTIL.CheckOverMaximum( mUSER[tUserIndex].mAvatarInfo.aMoney, tMoney ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aMoney += tMoney;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 1, tMoney, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMoney );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1047 : //[ÃÊ°æ°èºÎ]
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 30 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 30;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 30;
			mUSER[tUserIndex].mAvatarInfo.aZone101TypeTime += 180;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			/** 2009. 12. 18 : ±â¿©µµ °ü·Ã ·Î±× Ãß°¡ (wolf) */ 
			mGAMELOG.GL_800_USE_KILLNUM_TO_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe + 30, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
			/** 2009. 12. 18 : ±â¿©µµ °ü·Ã ·Î±× Ãß°¡ (wolf) */
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1048 : //[¹Ì±Ã¿­¼è]
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aNineTowerKeyNum++;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1049 : //[È¯Ãµ°æºÎ]
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aZone125TypeTime += 180;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1066 : //[ºÐÈ¯Áø°æ]
			if( ( tValue < 0 ) || ( tValue > ( MAX_SKILL_SLOT_NUM - 1 ) ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] < 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			for( index01 = 0 ; index01 < 3 ; index01++ )
			{
				for( index02 = 0 ; index02 < MAX_HOT_KEY_NUM ; index02++ )
				{
					if( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1 )
					{
						continue;
					}
					if( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] )
					{
						mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
						mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
						mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
					}
				}
			}
			mUSER[tUserIndex].mAvatarInfo.aSkillPoint += mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1];
			mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1] = 0;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1103 : //[¹æÆÄºÎ]
			if(65535 <= ((mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy & 0x0000FFFF) + 1)){
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy++;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case 1124:
			if(888 < (mUSER[tUserIndex].mAvatarInfo.aZone126TypeTime + 88)){
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			if(2 == mUSER[tUserIndex].uLoginPremiumPCRoom){
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 2, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aZone126TypeTime += 88;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			tValue = mUSER[tUserIndex].mAvatarInfo.aZone126TypeTime;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
        case  1125 :
            #ifdef __GOD__
			if( mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1 )
			{
#endif
				tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
				if( tItemLLevel < 1 )
				{
					tItemLLevel = 1;
				}
				tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
				if( tItemHLevel > MAX_LIMIT_LEVEL_NUM )
				{
					tItemHLevel = MAX_LIMIT_LEVEL_NUM;
				}
#ifdef __GOD__
			}
			else
			{
				tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
				tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			}

#endif
			switch( mUSER[tUserIndex].mAvatarInfo.aPreviousTribe )
			{
				case 0 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 13;
					tTribeItemList[7] = 14;
					tTribeItemList[8] = 15;
					break;
				case 1 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 16;
					tTribeItemList[7] = 17;
					tTribeItemList[8] = 18;
					break;
				case 2 :
					tTribeItemList[0] =  7;
					tTribeItemList[1] =  8;
					tTribeItemList[2] =  9;
					tTribeItemList[3] = 10;
					tTribeItemList[4] = 11;
					tTribeItemList[5] = 12;
					tTribeItemList[6] = 19;
					tTribeItemList[7] = 20;
					tTribeItemList[8] = 21;
					break;
			}
			tRandomValue = rand_mir() % 10000;
			if( tRandomValue < 3 )
			{
				tItemType = 4;
			}
			else if( tRandomValue < 500 )
			{
				tItemType = 3;
			}
			else if( tRandomValue < 9000 )
			{
				tItemType = 2;
			}
			else
			{
				tItemType = 1;
			}
			tRandomValue = rand_mir();
			tItemSort = tTribeItemList[( tRandomValue % 9 )];
			tSearchNum = 0;
			while( tSearchNum < 10 )
			{
				tRandomValue = rand_mir();
				tITEM_INFO = mITEM.Return( ( tItemLLevel + ( tRandomValue % ( tItemHLevel - tItemLLevel + 1 ) ) ), tItemType, tItemSort );
				if( tITEM_INFO )
				{
					if( ( ( tITEM_INFO->iEquipInfo[0] == 1 ) || ( ( tITEM_INFO->iEquipInfo[0] - 2 ) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe ) ) && ( tITEM_INFO->iCheckMonsterDrop == 2 ) )
					{
						break;
					}
					tITEM_INFO = NULL;
					tSearchNum++;
				}
				else
				{
					tSearchNum++;
				}
			}
			if( tITEM_INFO == NULL )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			tValue = tITEM_INFO->iIndex;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000003 );
			if( tITEM_INFO->iType == 4 )
			{
				mGAMELOG.GL_607_GAIN_SIN_ITEM( tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000003 );
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000003;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
            return;
		case  1129 : //[¼±¼úÇà³¶]
			tValue = mUTIL.ReturnAddDate( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 30 );
			if( tValue == -1 )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate = tValue;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1130 : //[º°°üÇÔ]
			tValue = mUTIL.ReturnAddDate( mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 30 );
			if( tValue == -1 )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate = tValue;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1104 : //[È¯¿ø¼ú¼­]
			for( index01 = 0 ; index01 < MAX_SKILL_SLOT_NUM ; index01++ )
			{
				if( mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1 )
				{
					continue;
				}
				mUSER[tUserIndex].mAvatarInfo.aSkillPoint += ( mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] - 1 );
				mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = 1;
			}
			for( index01 = 0 ; index01 < 3 ; index01++ )
			{
				for( index02 = 0 ; index02 < MAX_HOT_KEY_NUM ; index02++ )
				{
					if( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1 )
					{
						continue;
					}
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
				}
			}
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1105 : //[ºÐÈ¯¼ú¼­]
			if( ( tValue < 0 ) || ( tValue > ( MAX_SKILL_SLOT_NUM - 1 ) ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] < 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			for( index01 = 0 ; index01 < 3 ; index01++ )
			{
				for( index02 = 0 ; index02 < MAX_HOT_KEY_NUM ; index02++ )
				{
					if( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1 )
					{
						continue;
					}
					if( mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] )
					{
						mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
						mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
						mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
					}
				}
			}
			mUSER[tUserIndex].mAvatarInfo.aSkillPoint += ( mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1] - 1 );
			mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1] = 1;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1134 : //[Ç÷¸ÆÅ¸Åë(¼Ò)]
			if( ( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 1 ) || ( mUSER[tUserIndex].mAvatarInfo.aLevel1 > 99 ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
#ifdef __GOD__
			if( mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
#endif
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4 );
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1135 : //[Ç÷¸ÆÅ¸Åë(Áß)]
			if( ( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100 ) || ( mUSER[tUserIndex].mAvatarInfo.aLevel1 > 112 ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4 );
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1136 : //[Ç÷¸ÆÅ¸Åë(´ë)]
			if( ( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113 ) || ( mUSER[tUserIndex].mAvatarInfo.aLevel1 > 145 ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4 );
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
#ifdef __GOD__
		case  1142 :
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4 );
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
#endif
		case  1137 : //[ºÐÈ¯Å¸Åë(¼Ò)]
			if( ( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 1 ) || ( mUSER[tUserIndex].mAvatarInfo.aLevel1 > 99 ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			if( ( tValue < 1 ) || ( tValue > 4 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			switch( tValue )
			{
				case 1 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aStrength - 1 );
					mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
					break;
				case 2 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aWisdom - 1 );
					mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
					break;
				case 3 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality - 1 );
					mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
					break;
				case 4 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aKi - 1 );
					mUSER[tUserIndex].mAvatarInfo.aKi = 1;
					break;
			}
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1138 : //[ºÐÈ¯Å¸Åë(Áß)]
			if( ( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100 ) || ( mUSER[tUserIndex].mAvatarInfo.aLevel1 > 112 ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
#ifdef __GOD__
			if( mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
#endif
			if( ( tValue < 1 ) || ( tValue > 4 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			switch( tValue )
			{
				case 1 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aStrength - 1 );
					mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
					break;
				case 2 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aWisdom - 1 );
					mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
					break;
				case 3 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality - 1 );
					mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
					break;
				case 4 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aKi - 1 );
					mUSER[tUserIndex].mAvatarInfo.aKi = 1;
					break;
			}
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1139 : //[ºÐÈ¯Å¸Åë(´ë)]
			if( ( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113 ) || ( mUSER[tUserIndex].mAvatarInfo.aLevel1 > 145 ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
#ifdef __GOD__
			if( mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
#endif
			if( ( tValue < 1 ) || ( tValue > 4 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			switch( tValue )
			{
				case 1 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aStrength - 1 );
					mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
					break;
				case 2 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aWisdom - 1 );
					mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
					break;
				case 3 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality - 1 );
					mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
					break;
				case 4 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aKi - 1 );
					mUSER[tUserIndex].mAvatarInfo.aKi = 1;
					break;
			}
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
#ifdef __GOD__
		case  1143 :
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( ( tValue < 1 ) || ( tValue > 4 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			switch( tValue )
			{
				case 1 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aStrength - 1 );
					mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
					break;
				case 2 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aWisdom - 1 );
					mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
					break;
				case 3 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality - 1 );
					mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
					break;
				case 4 :
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aKi - 1 );
					mUSER[tUserIndex].mAvatarInfo.aKi = 1;
					break;
			}
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
#endif
		case  1075 : //[¹ß¼®Â÷(¹é)]
			if( ( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aTribe != 0 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( ( mSERVER_INFO.mServerNumber != 2 ) && ( mSERVER_INFO.mServerNumber != 3 ) && ( mSERVER_INFO.mServerNumber != 4 ) && ( mSERVER_INFO.mServerNumber != 7 ) && ( mSERVER_INFO.mServerNumber != 8 ) && ( mSERVER_INFO.mServerNumber != 9 ) && ( mSERVER_INFO.mServerNumber != 12 ) && ( mSERVER_INFO.mServerNumber != 13 ) && ( mSERVER_INFO.mServerNumber != 14 ) && ( mSERVER_INFO.mServerNumber != 141 ) && ( mSERVER_INFO.mServerNumber != 142 ) && ( mSERVER_INFO.mServerNumber != 143 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( !mSUMMON.SummonMonsterForTribeWeapon( 543, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1076 : //[¹ß¼®Â÷(ÆÐ)]
			if( ( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aTribe != 1 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( ( mSERVER_INFO.mServerNumber != 2 ) && ( mSERVER_INFO.mServerNumber != 3 ) && ( mSERVER_INFO.mServerNumber != 4 ) && ( mSERVER_INFO.mServerNumber != 7 ) && ( mSERVER_INFO.mServerNumber != 8 ) && ( mSERVER_INFO.mServerNumber != 9 ) && ( mSERVER_INFO.mServerNumber != 12 ) && ( mSERVER_INFO.mServerNumber != 13 ) && ( mSERVER_INFO.mServerNumber != 14 ) && ( mSERVER_INFO.mServerNumber != 141 ) && ( mSERVER_INFO.mServerNumber != 142 ) && ( mSERVER_INFO.mServerNumber != 143 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( !mSUMMON.SummonMonsterForTribeWeapon( 544, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1077 : //[¹ß¼®Â÷(Ç÷)]
			if( ( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aTribe != 2 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( ( mSERVER_INFO.mServerNumber != 2 ) && ( mSERVER_INFO.mServerNumber != 3 ) && ( mSERVER_INFO.mServerNumber != 4 ) && ( mSERVER_INFO.mServerNumber != 7 ) && ( mSERVER_INFO.mServerNumber != 8 ) && ( mSERVER_INFO.mServerNumber != 9 ) && ( mSERVER_INFO.mServerNumber != 12 ) && ( mSERVER_INFO.mServerNumber != 13 ) && ( mSERVER_INFO.mServerNumber != 14 ) && ( mSERVER_INFO.mServerNumber != 141 ) && ( mSERVER_INFO.mServerNumber != 142 ) && ( mSERVER_INFO.mServerNumber != 143 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( !mSUMMON.SummonMonsterForTribeWeapon( 545, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1078 : //[¹ß¼®Â÷(³¶)]
			if( ( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aTribe != 3 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( ( mSERVER_INFO.mServerNumber != 2 ) && ( mSERVER_INFO.mServerNumber != 3 ) && ( mSERVER_INFO.mServerNumber != 4 ) && ( mSERVER_INFO.mServerNumber != 7 ) && ( mSERVER_INFO.mServerNumber != 8 ) && ( mSERVER_INFO.mServerNumber != 9 ) && ( mSERVER_INFO.mServerNumber != 12 ) && ( mSERVER_INFO.mServerNumber != 13 ) && ( mSERVER_INFO.mServerNumber != 14 ) && ( mSERVER_INFO.mServerNumber != 141 ) && ( mSERVER_INFO.mServerNumber != 142 ) && ( mSERVER_INFO.mServerNumber != 143 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( !mSUMMON.SummonMonsterForTribeWeapon( 546, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1108 : //[¼öÈ£ºÎ]
			mUSER[tUserIndex].mAvatarInfo.aProtectForDeath++;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1120 : //[Àü½ÅºÎ]
			mUSER[tUserIndex].mAvatarInfo.aDoubleKillExpTime += 30;
			mUSER[tUserIndex].mAvatarInfo.aDoubleKillNumTime += 30;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1119 : //[´ÉÅõºÎ]
			mUSER[tUserIndex].mAvatarInfo.aDoubleKillExpTime += 30;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1118 : //[Åõ½ÅºÎ]
			mUSER[tUserIndex].mAvatarInfo.aDoubleKillNumTime += 30;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1083 : //[¹®È­»óÇ°±Ç_ÃßÃ·±Ç]
			mPLAYUSER_COM.U_USER_SEND_CASH( 50, &mUSER[tUserIndex].uID[0] );
			//mPLAYUSER_COM.U_EVENT_INFO_SEND( &mUSER[tUserIndex].uID[0], 1 );
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1084 : //[¹ÌÀÌ¶ó3_¿¹¸Å±Ç_ÃßÃ·±Ç]
			mPLAYUSER_COM.U_USER_SEND_CASH( 100, &mUSER[tUserIndex].uID[0] );
			//mPLAYUSER_COM.U_EVENT_INFO_SEND( &mUSER[tUserIndex].uID[0], 2 );
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1085 : //[µ¿¸Þ´Þ]
			mPLAYUSER_COM.U_USER_SEND_CASH( 500, &mUSER[tUserIndex].uID[0] );
			//mPLAYUSER_COM.U_EVENT_INFO_SEND( &mUSER[tUserIndex].uID[0], 2 );
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1086 : //[Antique Box]
			tRandomValue = rand_mir() % 100;
			if( tRandomValue < 25 )
			{
				tValue = 1210;
			}
			else if( tRandomValue < 50 )
			{
				tValue = 1211;
			}
			else if( tRandomValue < 75 )
			{
				tValue = 1212;
			}
			else
			{
				tValue = 1213;
			}
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case  1087 : //[Legendary Box]
			tRandomValue = rand_mir() % 100;
			if( tRandomValue < 3 )
			{
				tValue = 183;
			}
			else if( tRandomValue < 10 )
			{
				tValue = 1400;
			}
			else if( tRandomValue < 15 )
			{
				tValue = 1407;
			}
			else if( tRandomValue < 20 )
			{
				tValue = 1418;
			}
			else if( tRandomValue < 25 )
			{
				tValue = 1419;
			}
			else if( tRandomValue < 30 )
			{
				tValue = 1103;
			}
			else if( tRandomValue < 35 )
			{
				tValue = 1103;
			}
			else if( tRandomValue < 40 )
			{
				tValue = 1083;
			}
			else if( tRandomValue < 45 )
			{
				tValue = 1084;
			}
			else if( tRandomValue < 50 )
			{
				tValue = 1085;
			}
			else if( tRandomValue < 55 )
			{
				tValue = 1083;
			}
			else if( tRandomValue < 60 )
			{
				tValue = 1073;
			}
			else if( tRandomValue < 65 )
			{
				tValue = 1072;
			}
			else if( tRandomValue < 70 )
			{
				tValue = 1103;
			}
			else if( tRandomValue < 75 )
			{
				tValue = 168;
			}
			else if( tRandomValue < 80 )
			{
				tValue = 171;
			}
			else if( tRandomValue < 85 )
			{
				tValue = 174;
			}
			else if( tRandomValue < 90 )
			{
				tValue = 177;
			}
			else if( tRandomValue < 95 )
			{
				tValue = 180;
			}
			else
			{
				tValue = 1012;
			}
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case 1301: // .. .. ... (45 ~ 54)
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 45 && mUSER[tUserIndex].mAvatarInfo.aLevel1 <= 54) {
				ITEM_INFO* pItemPtr = mITEM.ReturnRareItem (mUSER[tUserIndex].mAvatarInfo.aTribe, 45);
				if (pItemPtr != NULL) {
					index01 = mUTIL.ReturnItemRecognitionNumber( pItemPtr->iType );
					mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], pItemPtr->iIndex, 0, 0, index01);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = pItemPtr -> iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, pItemPtr -> iIndex );
					mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
					return;
				}
			}
			// ... . ... .. ... ... ....
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return ;
		case 1302: // .. .. ... (55 ~ 64)
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 55 && mUSER[tUserIndex].mAvatarInfo.aLevel1 <= 64) {
				ITEM_INFO* pItemPtr = mITEM.ReturnRareItem (mUSER[tUserIndex].mAvatarInfo.aTribe, 55);
				if (pItemPtr != NULL) {
					index01 = mUTIL.ReturnItemRecognitionNumber( pItemPtr->iType );
					mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], pItemPtr->iIndex, 0, 0, index01);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = pItemPtr -> iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, pItemPtr -> iIndex );
					mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
					return;
				}
			}
			// ... . ... .. ... ... ....
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return ;
		case 1303: // .. .. ... (65 ~ 74)
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 65 && mUSER[tUserIndex].mAvatarInfo.aLevel1 <= 74) {
				ITEM_INFO* pItemPtr = mITEM.ReturnRareItem (mUSER[tUserIndex].mAvatarInfo.aTribe, 65);
				if (pItemPtr != NULL) {
					index01 = mUTIL.ReturnItemRecognitionNumber( pItemPtr->iType );
					mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], pItemPtr->iIndex, 0, 0, index01);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = pItemPtr -> iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, pItemPtr -> iIndex );
					mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
					return;
				}
			}
			// ... . ... .. ... ... ....
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return ;
		case 1304: // .. .. ... (75 ~ 84)
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 75 && mUSER[tUserIndex].mAvatarInfo.aLevel1 <= 84) {
				ITEM_INFO* pItemPtr = mITEM.ReturnRareItem (mUSER[tUserIndex].mAvatarInfo.aTribe, 75);
				if (pItemPtr != NULL) {
					index01 = mUTIL.ReturnItemRecognitionNumber( pItemPtr->iType );
					mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], pItemPtr->iIndex, 0, 0, index01);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = pItemPtr -> iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01; 
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, pItemPtr -> iIndex );
					mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
					return;
				}
			}
			// ... . ... .. ... ... ....
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return ;
		case 1305: // .. .. ... (85 ~ 94)
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 85 && mUSER[tUserIndex].mAvatarInfo.aLevel1 <= 94) {
				ITEM_INFO* pItemPtr = mITEM.ReturnRareItem (mUSER[tUserIndex].mAvatarInfo.aTribe, 85);
				if (pItemPtr != NULL) {
					index01 = mUTIL.ReturnItemRecognitionNumber( pItemPtr->iType );
					mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], pItemPtr->iIndex, 0, 0, index01);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = pItemPtr -> iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, pItemPtr -> iIndex );
					mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
					return;
				}
			}
			// ... . ... .. ... ... ....
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return ;
		case 1306: // .. .. ... (95 ~ 104)
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 95 && mUSER[tUserIndex].mAvatarInfo.aLevel1 <= 104) {
				ITEM_INFO* pItemPtr = mITEM.ReturnRareItem (mUSER[tUserIndex].mAvatarInfo.aTribe, 95);
				if (pItemPtr != NULL) {
					index01 = mUTIL.ReturnItemRecognitionNumber( pItemPtr->iType );
					mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], pItemPtr->iIndex, 0, 0, index01);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = pItemPtr -> iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, pItemPtr -> iIndex );
					mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
					return;
				}
			}
			// ... . ... .. ... ... ....
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return ;
		case 1307: // .. .. ... (105 ~ 112)
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 105 && mUSER[tUserIndex].mAvatarInfo.aLevel1 <= 112) {
				ITEM_INFO* pItemPtr = mITEM.ReturnRareItem (mUSER[tUserIndex].mAvatarInfo.aTribe, 105);
				if (pItemPtr != NULL) {
					index01 = mUTIL.ReturnItemRecognitionNumber( pItemPtr->iType );
					mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], pItemPtr->iIndex, 0, 0, index01);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = pItemPtr -> iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, pItemPtr -> iIndex );
					mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
					return;
				}
			}
			// ... . ... .. ... ... ....
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return ;
		case 1308:
			tRandomValue = rand_mir() % 100;
			if(20 > tRandomValue){
				tMoney = 10000;
			}
			else if(40 > tRandomValue){
				tMoney = 20000;
			}
			else if(60 > tRandomValue){
				tMoney = 30000;
			}
			else if(80 > tRandomValue){
				tMoney = 40000;
			}
			else if(100 > tRandomValue){
				tMoney = 50000;
			}
			if( mUTIL.CheckOverMaximum( mUSER[tUserIndex].mAvatarInfo.aMoney, tMoney ) )
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aMoney += tMoney;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 1, tMoney, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMoney );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
#if 0
		case 1308: // Gigabyte (.....) ....
			tITEM_INFO = mITEM.GetResultItemPtrByGigabyteItem ();
			if (tITEM_INFO != NULL) {
				mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO -> iIndex;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 10;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tITEM_INFO -> iIndex );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return ;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return ;
#endif
		case 1309: // 1. .....
			return ;
			tITEM_INFO = mITEM.GetMoneyBy1WonLuckyBag ();
			if (tITEM_INFO != NULL) {
				mGAMELOG.GL_605_USE_CASH_ITEM (tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO -> iIndex;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tITEM_INFO -> iIndex );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			// .. . .. .... .. ... .. ... .. ... ......
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return ;

		case 1110:	// 2008 11 26 ..- .. ...
			if (  mUSER[ tUserIndex ].mAvatarInfo.aGender == 0 )		mUSER[ tUserIndex ].mAvatarInfo.aGender = 1;
			else																						mUSER[ tUserIndex ].mAvatarInfo.aGender = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aHeadType	= bParam_1;
			mUSER[ tUserIndex ].mAvatarInfo.aFaceType	= bParam_2;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 0 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 1 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 2 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 3 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 4 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 5 ] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);	

			mAVATAR_OBJECT[ tUserIndex ].mDATA.aGender = mUSER[ tUserIndex ].mAvatarInfo.aGender;
			mAVATAR_OBJECT[ tUserIndex ].mDATA.aHeadType = mUSER[ tUserIndex ].mAvatarInfo.aHeadType;
			mAVATAR_OBJECT[ tUserIndex ].mDATA.aFaceType = mUSER[ tUserIndex ].mAvatarInfo.aFaceType;

			mTRANSFER.B_AVATAR_CHANGE_INFO_1( mAVATAR_OBJECT[ tUserIndex ].mIndex,
					mAVATAR_OBJECT[ tUserIndex ].mUniqueNumber, 
					90, 
					mUSER[ tUserIndex ].mAvatarInfo.aGender, 
					mUSER[ tUserIndex ].mAvatarInfo.aHeadType, 
					mUSER[ tUserIndex ].mAvatarInfo.aFaceType );
			mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[ tUserIndex ].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false );

			return;

		case 1315:	// 2008 11 26 ..- ... 2. (.)
		case 1316:	// 2008 11 26 ..- ... 2. (.)
		case 1317:	// 2008 11 26 ..- ... 2. (.)
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) /// # if - 1
			{
				switch( tITEM_INFO->iIndex )
				{
					case 1315: temp_AddTime = 20;	break;
					case 1316: temp_AddTime = 40;	break;
					case 1317: temp_AddTime = 60;	break;
				}
				int iCurrentTime = mUSER[tUserIndex].mAvatarInfo.aDoubleDropTime & 0xFFFF;
				int iPart2Time = mUSER[tUserIndex].mAvatarInfo.aDoubleDropTime & 0xFFFF0000;
				if ( iCurrentTime + temp_AddTime <= 300 )	/// # if - 2
				{
					tValue = iCurrentTime + temp_AddTime;
					mUSER[ tUserIndex ].mAvatarInfo.aDoubleDropTime = iPart2Time + tValue;
					mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
					mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 0 ] = 0;
					mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 1 ] = 0;
					mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 2 ] = 0;
					mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 3 ] = 0;
					mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 4 ] = 0;
					mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 5 ] = 0;
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
				}
				else /// # if - 2  else				
				{
					// .. .. ... .... ... . .. ...
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV ( 2, tPage, tIndex, 0);
			}
		}
		else /// # if - 1 else
		{
			// ... .. .. ... . .. ...
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV ( 1, tPage, tIndex, 0); 
		}
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return;
	case 1318:	// 2008 11 26 .. - ... 2. (.)
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 == 145) && (mUSER[tUserIndex].mAvatarInfo.aLevel2 == 4) && (mUSER[tUserIndex].mAvatarInfo.aManaPotionConvertNum < 12) && (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe >= 50000) && (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == 1082238285))  /// # if - 1
		{
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50000;
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
			mUSER[tUserIndex].mAvatarInfo.aManaPotionConvertNum += 1;
			mUSER[tUserIndex].mAvatarInfo.aSkillPoint +=50;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 50000;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 0 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 1 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 2 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 3 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 4 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 5 ] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);			
			
			
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		} 
		else /// # if - 1 else
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV (1, tPage, tIndex, 0); 
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		}
		
		return;
	case 1320:
	case 1321:
	case 1322:
		if( mUSER[tUserIndex].mHealthState > 3 ) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 10, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		switch(tITEM_INFO->iIndex) {
			case 1320:
				temp_AddTime = 20;
				break;
			case 1321:
				temp_AddTime = 40;
				break;
			case 1322:
				temp_AddTime = 60;
				break;
		}
		if(mUSER[ tUserIndex ].mAvatarInfo.aPat_Exp_x2_Time + temp_AddTime <= 300) {
			tValue = mUSER[ tUserIndex ].mAvatarInfo.aPat_Exp_x2_Time + temp_AddTime;
			mUSER[ tUserIndex ].mAvatarInfo.aPat_Exp_x2_Time = tValue;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 0 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 1 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 2 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 3 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 4 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 5 ] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
		} else {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV (2, tPage, tIndex, 0);
		}
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return;
	case 1323:
	case 1324:
	case 1325:
		if( mUSER[tUserIndex].mHealthState > 3 ) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 10, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		if(mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) {
			switch(tITEM_INFO->iIndex) {
				case 1323:
					temp_AddTime = 25;
					break;
				case 1324:
					temp_AddTime = 45;
					break;
				case 1325:
					temp_AddTime = 70;
					break;
			}
			int iCurrentTime = mUSER[tUserIndex].mAvatarInfo.aPat_User_Exp_x2_Time & 0xFFFF;
			int iPart2Time = mUSER[tUserIndex].mAvatarInfo.aPat_User_Exp_x2_Time & 0xFFFF0000;
			if(iCurrentTime + temp_AddTime <= 300) {
				tValue = iCurrentTime + temp_AddTime;
				mUSER[tUserIndex].mAvatarInfo.aPat_User_Exp_x2_Time = iPart2Time + tValue;
				mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 0 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 1 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 2 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 3 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 4 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 5 ] = 0;
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
			} else {
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV (2, tPage, tIndex, 0);
			}
		} else {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV (1, tPage, tIndex, 0);
		}
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return;
	case 1326:
		if( mUSER[tUserIndex].mHealthState > 3 ) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 10, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		if(mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 113) {
			int iCurrentTime = mUSER[tUserIndex].mAvatarInfo.aPat_User_Exp_x2_Time >> 16;
			int iPart2Time = mUSER[tUserIndex].mAvatarInfo.aPat_User_Exp_x2_Time & 0xFFFF;
			if (iCurrentTime + 70 <= 300) {
				tValue = ((iCurrentTime + 70) << 16) + iPart2Time;
				mUSER[tUserIndex].mAvatarInfo.aPat_User_Exp_x2_Time = tValue;
				mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 0 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 1 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 2 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 3 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 4 ] = 0;
				mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 5 ] = 0;
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
			} else {
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV (2, tPage, tIndex, 0);
			}
		} else {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV (1, tPage, tIndex, 0);
		}
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return;
    case 1310: // .. ... (.)
    case 1311: // .. ... (.)
    case 1312: // .. ... (.)
        if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) {
            switch (tITEM_INFO -> iIndex) {
                case 1310:  tMoney = 20;    break;
                case 1311:  tMoney = 40;    break;
                case 1312:  tMoney = 60;    break;
            }

            int iCurrentTime = mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime1 & 0xFFFF;
            int iPart2Time = mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime1 & 0xFFFF0000;
            if (iCurrentTime + tMoney <= 600) {
                tValue = iCurrentTime + tMoney;
                mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime1 = iPart2Time + tValue;
				mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
                mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
            } else {
                // .. .. ... .... ... . .. ...
                mTRANSFER.B_USE_INVENTORY_ITEM_RECV (2, tPage, tIndex, 0);
            }
        } else {
            // ... .. .. ... . .. ...
            mTRANSFER.B_USE_INVENTORY_ITEM_RECV (1, tPage, tIndex, 0); 
        }

        mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
        return ;
    case 1313: // .. ... (.)
        if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 113) {
            int iCurrentTime = mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime1 >> 16;
            int iPart2Time = mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime1 & 0xFFFF;
            if (iCurrentTime + 20 <= 600) {
                tValue = ((iCurrentTime + 20) << 16) + iPart2Time;
                mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime1 = tValue;
				mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
                mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
            } else {
                // .. .. ... .... ... . .. ...
                mTRANSFER.B_USE_INVENTORY_ITEM_RECV (2, tPage, tIndex, 0);
            }
        } else {
            // ... .. .. ... . .. ...
            mTRANSFER.B_USE_INVENTORY_ITEM_RECV (1, tPage, tIndex, 0); 
        }
        mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
        return ;
    case 1126: // ....
        if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF) < 100) {
            int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF;
            int iSaveImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFFFFFF00;
            tValue = iSaveImproveValue + iImproveValue + 1;
            mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum = tValue;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
            mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
        } else {
            // .. .. .. ... ...
            mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0);
        }
        mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
        return ;

		/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	case 1938: // [°­È­ºÎ-Æ¯]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF) < 100) {
			int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF;
			int iSaveImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFFFFFF00;
			tValue = iSaveImproveValue + iImproveValue + 1;
			mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 = tValue;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
		} else {
			// .. .. .. ... ...
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0);
		}
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return ;
		/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */

    case 1127: // ....
        if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF00) < 25600) {
            int iCompoundValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF00) >> 8);
            int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF;
            int iSaveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF0000;
            tValue = iSaveValue + ((iCompoundValue + 1) << 8) + iImproveValue;
            mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum = tValue;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
            mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
        } else {
            // .. .. .. ... ...
            mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0);
        }
        mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
        return ;

		/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	case 1940: // Á¶ÇÕºÎ-Æ¯
		if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF00) < 25600) {
			int iCompoundValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF00) >> 8);
			int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF;
			int iSaveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF0000;
			tValue = iSaveValue + ((iCompoundValue + 1) << 8) + iImproveValue;
			mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 = tValue;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
		} else {
			// .. .. .. ... ...
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0);
		}
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return;
		/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */

    case 1128: // ....
        if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF0000) < 6553600) {
            int iCompoundValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF00;
            int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF;
            int iPromotionValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF0000) >> 16);
            tValue = ((iPromotionValue + 1) << 16) + iCompoundValue + iImproveValue;
            mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum = tValue;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
            mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
            mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
        } else {
            // .. .. .. ... ...
            mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0);
        }
        mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
        return ;

		/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	case 1939: // ½Â±ÞºÎ
		if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF0000) < 6553600) {
			int iCompoundValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF00;
			int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF;
			int iPromotionValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF0000) >> 16);
			tValue = ((iPromotionValue + 1) << 16) + iCompoundValue + iImproveValue;
			mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 = tValue;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);
		} else {
			// .. .. .. ... ...
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0);
		}
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return ;
		/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */

    case 1314: // . ...
        mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime2 += 180;
        mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
        mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        return;
	case 1327: //aDoubleTime3 
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 <= 30) {
			if(270 < mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime3){
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0 );
			}
			else{
				mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime3 += 60;
				mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			}
		}
		else{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0 );
		}
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 1432:
		if(50 > mUSER[tUserIndex].mAvatarInfo.aLevel1){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		time( &tCountSeconds );
		tPresentTime = localtime( &tCountSeconds );
		if(NULL == tPresentTime){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 2, tPage, tIndex, 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		::memset(cDate, 0, 100);
		snprintf (cDate, 100, "%04d%02d%02d", tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
		iDate = ::atoi(cDate);

		tZone84Date = mUSER[tUserIndex].mAvatarInfo.aZone84Time >> 4;


		if(iDate == tZone84Date){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 3, tPage, tIndex, 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}

		iDate = iDate << 4;
		mUSER[tUserIndex].mAvatarInfo.aZone84Time = iDate + 12;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aZone84Time );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 1331:
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 112)|| (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 115)){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if(10 > mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 10;
		index01 = mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1);
		mUTIL.ProcessForExperience( tUserIndex, (int) ceilf((float) (index01 / 100)), 0, 0 );
		
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 1333:
		if(112 != mUSER[tUserIndex].mAvatarInfo.aLevel1){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if(MAX_NUMBER_SIZE < mUSER[tUserIndex].mAvatarInfo.aFiveExpTime + 30){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 2, tPage, tIndex, 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aFiveExpTime += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	//Auto Potion.
	case 1334:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__); // ÀÚµ¿¹°¾à ±â´É Á¦°Å·Î ÀÎÇØ ÇØ´ç ÆÐÅ¶À» ¸·½À´Ï´Ù. 2009.09.24
		return;
		if ( TRUE == mGAME.Add_Use_Auto_Day( tUserIndex, 7 ) )
		{
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 0 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 1 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 2 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 3 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 4 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 5 ] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		}
		else
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		}
		return;
	case 1335:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__); // ÀÚµ¿¹°¾à ±â´É Á¦°Å·Î ÀÎÇØ ÇØ´ç ÆÐÅ¶À» ¸·½À´Ï´Ù. 2009.09.24
		return;
		if ( TRUE == mGAME.Add_Use_Auto_Day( tUserIndex, 30 ) )
		{
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 0 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 1 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 2 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 3 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 4 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 5 ] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);	
		}
		else
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		}
		return;
	case 1336:
	case 1337:
	case 1338:
	case 1339:
	case 1340:
	case 1341:
	case 1342:
	case 1343:
	case 1344:
		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 0;
		switch(tITEM_INFO->iIndex){
			case 1336:
				if((5 > mUSER[tUserIndex].mAvatarInfo.aLevel1) || (15 <= mUSER[tUserIndex].mAvatarInfo.aLevel1)){
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
					mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
					return;
				}
				tItemList[0][0] = 1337;
				tItemList[0][1] = 0;
				tItemList[1][0] = 1327;
				tItemList[1][1] = 0;
				tItemList[2][0] = 1327;
				tItemList[2][1] = 0;
				tItemList[3][0] = 2;
				tItemList[3][1] = 99;
				tItemList[4][0] = 26;
				tItemList[4][1] = 99;
				tItemCount = 4;
				break;
			case 1337:
				if((15 > mUSER[tUserIndex].mAvatarInfo.aLevel1) || (25 <= mUSER[tUserIndex].mAvatarInfo.aLevel1)){
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
					mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
					return;
				}
				tItemList[0][0] = 1338;
				tItemList[0][1] = 0;
				tItemList[1][0] = 1327;
				tItemList[1][1] = 0;
				tItemList[2][0] = 1327;
				tItemList[2][1] = 0;
				tItemList[3][0] = 3;
				tItemList[3][1] = 99;
				tItemList[4][0] = 27;
				tItemList[4][1] = 99;
				tItemCount = 4;
				break;
			case 1338:
				if((25 > mUSER[tUserIndex].mAvatarInfo.aLevel1) || (35 <= mUSER[tUserIndex].mAvatarInfo.aLevel1)){
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
					mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
					return;
				}
				tItemList[0][0] = 1339;
				tItemList[0][1] = 0;
				tItemList[1][0] = 1327;
				tItemList[1][1] = 0;
				tItemList[2][0] = 1327;
				tItemList[2][1] = 0;
				tRandomValue = rand_mir() % 100;
				if(5 > tRandomValue){
					tItemList[3][0] = 1045;
					tItemList[3][1] = 0;
					tItemList[4][0] = 1045;
					tItemList[4][1] = 0;
				}
				else if(25 > tRandomValue){
					tItemList[3][0] = 1035;
					tItemList[3][1] = 0;
				}
				else if(45 > tRandomValue){
					tItemList[3][0] = 1019;
					tItemList[3][1] = 0;
					tItemList[4][0] = 1019;
					tItemList[4][1] = 0;
				}
				else if(70 > tRandomValue){
					tItemList[3][0] = 1025;
					tItemList[3][1] = 0;
					tItemList[4][0] = 1025;
					tItemList[4][1] = 0;
				}
				else if(100 > tRandomValue){
					tItemList[3][0] = 32;
					tItemList[3][1] = 99;
				}
				tItemCount = 5;
				break;
			case 1339:
				if((35 > mUSER[tUserIndex].mAvatarInfo.aLevel1) || (45 <= mUSER[tUserIndex].mAvatarInfo.aLevel1)){
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
					mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
					return;
				}
				tItemList[0][0] = 1340;
				tItemList[0][1] = 0;
				tRandomValue = rand_mir() % 100;
				if(1 > tRandomValue){
					tItemList[1][0] = 1301;
					tItemList[1][1] = 0;
				}
				else if(10 > tRandomValue){
					tItemList[1][0] = 1045;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1045;
					tItemList[2][1] = 0;
				}
				else if(30 > tRandomValue){
					tItemList[1][0] = 1024;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1024;
					tItemList[2][1] = 0;
				}
				else if(60 > tRandomValue){
					tItemList[1][0] = 1025;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1025;
					tItemList[2][1] = 0;
				}
				else if(100 > tRandomValue){
					tItemList[1][0] = 1019;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1019;
					tItemList[2][1] = 0;
				}
				tItemCount = 3;
				break;
			case 1340:
				if((45 > mUSER[tUserIndex].mAvatarInfo.aLevel1) || (55 <= mUSER[tUserIndex].mAvatarInfo.aLevel1)){
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
					mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
					return;
				}
				tItemList[0][0] = 1341;
				tItemList[0][1] = 0;
				tRandomValue = rand_mir() % 100;
				if(1 > tRandomValue){
					tItemList[1][0] = 1302;
					tItemList[1][1] = 0;
				}
				else if(10 > tRandomValue){
					tItemList[1][0] = 1036;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1036;
					tItemList[2][1] = 0;
				}
				else if(25 > tRandomValue){
					tItemList[1][0] = 1045;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1045;
					tItemList[2][1] = 0;
				}
				else if(45 > tRandomValue){
					tItemList[1][0] = 1024;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1024;
					tItemList[2][1] = 0;
				}
				else if(70 > tRandomValue){
					tItemList[1][0] = 1020;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1020;
					tItemList[2][1] = 0;
				}
				else if(100 > tRandomValue){
					tItemList[1][0] = 1025;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1025;
					tItemList[2][1] = 0;
				}
				tItemCount = 3;
				break;
			case 1341:
				if((55 > mUSER[tUserIndex].mAvatarInfo.aLevel1) || (65 <= mUSER[tUserIndex].mAvatarInfo.aLevel1)){
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
					mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
					return;
				}
				tItemList[0][0] = 1342;
				tItemList[0][1] = 0;
				tRandomValue = rand_mir() % 100;
				if(1 > tRandomValue){
					tItemList[1][0] = 1303;
					tItemList[1][1] = 0;
				}
				else if(10 > tRandomValue){
					tItemList[1][0] = 1021;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1021;
					tItemList[2][1] = 0;
				}
				else if(25 > tRandomValue){
					tItemList[1][0] = 1036;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1036;
					tItemList[2][1] = 0;
				}
				else if(45 > tRandomValue){
					tItemList[1][0] = 1024;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1024;
					tItemList[2][1] = 0;
				}
				else if(70 > tRandomValue){
					tItemList[1][0] = 1045;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1045;
					tItemList[2][1] = 0;
				}
				else if(100 > tRandomValue){
					tItemList[1][0] = 1020;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1020;
					tItemList[2][1] = 0;
				}
				tItemCount = 3;
				break;
			case 1342:
				if((65 > mUSER[tUserIndex].mAvatarInfo.aLevel1) || (75 <= mUSER[tUserIndex].mAvatarInfo.aLevel1)){
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
					mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
					return;
				}
				tItemList[0][0] = 1343;
				tItemList[0][1] = 0;
				tRandomValue = rand_mir() % 100;
				if(1 > tRandomValue){
					tItemList[1][0] = 1129;
					tItemList[1][1] = 0;
				}
				else if(10 > tRandomValue){
					tItemList[1][0] = 1021;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1021;
					tItemList[2][1] = 0;
				}
				else if(25 > tRandomValue){
					tItemList[1][0] = 1036;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1036;
					tItemList[2][1] = 0;
				}
				else if(45 > tRandomValue){
					tItemList[1][0] = 1024;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1024;
					tItemList[2][1] = 0;
				}
				else if(70 > tRandomValue){
					tItemList[1][0] = 1045;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1045;
					tItemList[2][1] = 0;
				}
				else if(100 > tRandomValue){
					tItemList[1][0] = 1020;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1020;
					tItemList[2][1] = 0;
				}
				tItemCount = 3;
				break;
			case 1343:
				if((75 > mUSER[tUserIndex].mAvatarInfo.aLevel1) || (85 <= mUSER[tUserIndex].mAvatarInfo.aLevel1)){
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
					mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
					return;
				}
				tItemList[0][0] = 1344;
				tItemList[0][1] = 0;
				tRandomValue = rand_mir() % 100;
				if(1 > tRandomValue){
					tItemList[1][0] = 1129;
					tItemList[1][1] = 0;
				}
				else if(10 > tRandomValue){
					tItemList[1][0] = 1022;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1022;
					tItemList[2][1] = 0;
				}
				else if(25 > tRandomValue){
					tItemList[1][0] = 1021;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1021;
					tItemList[2][1] = 0;
				}
				else if(45 > tRandomValue){
					tItemList[1][0] = 1036;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1036;
					tItemList[2][1] = 0;
				}
				else if(70 > tRandomValue){
					tItemList[1][0] = 1024;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1024;
					tItemList[2][1] = 0;
				}
				else if(100 > tRandomValue){
					tItemList[1][0] = 1045;
					tItemList[1][1] = 0;
					tItemList[2][0] = 1045;
					tItemList[2][1] = 0;
				}
				tItemCount = 3;
				break;
			case 1344:
				if((85 > mUSER[tUserIndex].mAvatarInfo.aLevel1) || (95 <= mUSER[tUserIndex].mAvatarInfo.aLevel1)){
					mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
					mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
					return;
				}
				tRandomValue = rand_mir() % 100;
				if(1 > tRandomValue){
					tItemList[0][0] = 1129;
					tItemList[0][1] = 0;
				}
				else if(5 > tRandomValue){
					tItemList[0][0] = 1023;
					tItemList[0][1] = 0;
					tItemList[1][0] = 1023;
					tItemList[1][1] = 0;
				}
				else if(20 > tRandomValue){
					tItemList[0][0] = 1022;
					tItemList[0][1] = 0;
					tItemList[1][0] = 1022;
					tItemList[1][1] = 0;
				}
				else if(40 > tRandomValue){
					tItemList[0][0] = 1021;
					tItemList[0][1] = 0;
					tItemList[1][0] = 1021;
					tItemList[1][1] = 0;
				}
				else if(70 > tRandomValue){
					tItemList[0][0] = 1037;
					tItemList[0][1] = 0;
					tItemList[1][0] = 1037;
					tItemList[1][1] = 0;
				}
				else if(100 > tRandomValue){
					tItemList[0][0] = 1045;
					tItemList[0][1] = 0;
					tItemList[1][0] = 1045;
					tItemList[1][1] = 0;
				}
				tItemCount = 2;
				break;
		}
		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(1336);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0; 
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0; 
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return;
	case 1346:
		if(65535 <= ((mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy & 0x0000FFFF) + 1)){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy++;
		mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 1347:
		tRandomValue = rand_mir() % 1000;
		if( tRandomValue < 3 ){
			tValue = 1801 + (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe * 3) + (rand_mir() % 3);
		}
		else if( tRandomValue < 6 ){
			tValue = 1810 + (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe * 3) + (rand_mir() % 3);
		}
		else if( tRandomValue < 8 ){
			tValue = 1819 + (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe * 3) + (rand_mir() % 3);
		}
		else if(tRandomValue < 10){
			tValue = 1828 + (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe * 3) + (rand_mir() % 3);
		}
		else if(tRandomValue < 11){
			tValue = 1837 + (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe * 3) + (rand_mir() % 3);
		}
		else if(tRandomValue < 12){
			tValue = 1846 + (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe * 3) + (rand_mir() % 3);
		}
		else if(tRandomValue < 13){
			tValue = 1136;
		}
		else if(tRandomValue < 15){
			tValue = 1135;
		}
		else if(tRandomValue < 25){
			tValue = 1002;
		}
		else if(tRandomValue < 35){
			tValue = 1003;
		}
		else if(tRandomValue < 45){
			tValue = 1004;
		}
		else if(tRandomValue < 55){
			tValue = 1005;
		}
		else if(tRandomValue < 60){
			tValue = 1103;
		}
		else if(tRandomValue < 95){
			tValue = 1041;
		}
		else if(tRandomValue < 295){
			tValue = 1022;
		}
		else if(tRandomValue < 695){
			tValue = 1021;
		}
		else if(tRandomValue < 765){
			tValue = 1020;
		}
		else if(tRandomValue < 915){
			tValue = 1120;
		}
		else if(tRandomValue < 950){
			tValue = 1037;
		}
		else{ 
			tValue = 1036;
		}
		tITEM_INFO = mITEM.Search(tValue);
		if( tITEM_INFO == NULL )
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		index01 = mUTIL.ReturnItemRecognitionNumber(tITEM_INFO->iType);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tITEM_INFO->iIndex, 0, 0, index01 );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 1348:
		tRandomValue = rand_mir() % 10000;
		tItemCount = 0;
		index01 = 0;
		if(5 > tRandomValue){
			tValue = 1;
			tItemCount = 10000000;
		}
		else if(10 > tRandomValue){
			tValue = 1;
			tItemCount = 5000000;
		}
		else if(60 > tRandomValue){
			tValue = 1;
			tItemCount = 2000000;
		}
		else if(510 > tRandomValue){
			tValue = 1;
			tItemCount = 1000000;
		}
		else if(1500 > tRandomValue){
			tValue = 1;
			tItemCount = 500000;
		}
		else if(2000 > tRandomValue){
			tValue = 1022;
		}
		else if(6000 > tRandomValue){
			tValue = 1021;
		}
		else{
			tValue = 1020;
		}
		if(1 == tValue){
			if( mUTIL.CheckOverMaximum( mUSER[tUserIndex].mAvatarInfo.aMoney, tItemCount ) ){
				tItemCount = MAX_NUMBER_SIZE - mUSER[tUserIndex].mAvatarInfo.aMoney;
				mUSER[tUserIndex].mAvatarInfo.aMoney = MAX_NUMBER_SIZE;
			}
			else{
				mUSER[tUserIndex].mAvatarInfo.aMoney += tItemCount;
			}
			mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 1, tItemCount, 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMoney );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		tITEM_INFO = mITEM.Search(tValue);
		if( tITEM_INFO == NULL )
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		index01 = mUTIL.ReturnItemRecognitionNumber(tITEM_INFO->iType);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tITEM_INFO->iIndex, 0, 0, index01 );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tITEM_INFO->iIndex );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 1350:
		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 3;
		tRandomValue = rand_mir() % 1000;
		if(10 > tRandomValue){
			tItemList[0][0] = 1136;
		}
		else if(110 > tRandomValue){
			tItemList[0][0] = 1331;
		}
		else if(210 > tRandomValue){
			tItemList[0][0] = 1135;
		}
		else if(340 > tRandomValue){
			tItemList[0][0] = 1022;
			tItemList[1][0] = 1022;
		}
		else if(489 > tRandomValue){
			tItemList[0][0] = 1314;
		}
		else if(639 > tRandomValue){
			tItemList[0][0] = 1119;
			tItemList[1][0] = 1119;
			tItemList[2][0] = 1119;
		}
		else if(819 > tRandomValue){
			tItemList[0][0] = 1021;
			tItemList[1][0] = 1021;
		}
		else{
			tItemList[0][0] = 1020;
			tItemList[1][0] = 1020;
			tItemList[2][0] = 1020;
		}
		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(1350);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0; 
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0; 
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		
		if(1136 == tItemList[0][0]){
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 112;
			CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
			CopyMemory( &tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
			mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
			//--------------//
			//--------------//
			//--------------//
		}
		return;
	case 1351:
		tRandomValue = rand_mir() % 10000;
		if(50 > tRandomValue){
			tValue = 1054;
		}
		else if(100 > tRandomValue){
			tValue = 1055;
		}
		else if(200 > tRandomValue){
			tValue = 1056;
		}
		else if(300 > tRandomValue){
			tValue = 1057;
		}
		else if(380 > tRandomValue){
			tValue = 1058;
		}
		else if(580 > tRandomValue){
			tValue = 1059;
		}
		else if(780 > tRandomValue){
			tValue = 1060;
		}
		else if(1000 > tRandomValue){
			tValue = 1061;
		}
		else if(1080 > tRandomValue){
			tValue = 1062;
		}
		else if(1280 > tRandomValue){
			tValue = 1063;
		}
		else if(1480 > tRandomValue){
			tValue = 1064;
		}
		else if(1700 > tRandomValue){
			tValue = 1065;
		}
		else if(2500 > tRandomValue){
			tValue = 1127;
		}
		else if(3300 > tRandomValue){
			tValue = 1128;
		}
		else if(4200 > tRandomValue){
			tValue = 1108;
		}
		else if(5500 > tRandomValue){
			tValue = 1314;
		}
		else if(6800 > tRandomValue){
			tValue = 1138;
		}
		else if(7800 > tRandomValue){
			tValue = 1022;
		}
		else if(8900 > tRandomValue){
			tValue = 1020;
		}
		else{
			tValue = 1025;
		}
		tITEM_INFO = mITEM.Search(tValue);
		if( tITEM_INFO == NULL )
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		index01 = mUTIL.ReturnItemRecognitionNumber(tITEM_INFO->iType);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tITEM_INFO->iIndex, 0, 0, index01 );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tITEM_INFO->iIndex );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;

#ifdef __ANIMAL__
	case ANIMAL_BAB:
		for( index01 = 0 ; index01 < MAX_AVATAR_ANIMAL_NUM ; index01++ )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] != 0 )
			{
				break;
			}
		}
		if( index01 == MAX_AVATAR_ANIMAL_NUM )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = mUSER[tUserIndex].mAvatarInfo.aAnimalTime + 180;
		mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
		mUSER[tUserIndex].mAvatarInfo.aAnimalTime = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case ANIMAL_NUM_BAKHO:
	case ANIMAL_NUM_DONWHOANG:
	case ANIMAL_NUM_CHUNLOK:
#if MAX_LIMIT_LEVEL_NUM+MAX_LIMIT_HIGH_LEVEL_NUM > 145
	case ANIMAL_NUM_CHUNGHO:
	case ANIMAL_NUM_TWODON:
	case ANIMAL_NUM_BAIKLOK:
#if MAX_LIMIT_LEVEL_NUM+MAX_LIMIT_HIGH_LEVEL_NUM > 156
	case ANIMAL_NUM_CHUKHO:
	case ANIMAL_NUM_SUNGDON:
	case ANIMAL_NUM_SHINLOK:
#endif
#endif
	case ANIMAL_NUM_CRISTMAS:
		for( index01 = 0 ; index01 < MAX_AVATAR_ANIMAL_NUM ; index01++ )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex )
			{
				break;
			}
		}
		if( index01 < MAX_AVATAR_ANIMAL_NUM )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for( index01 = 0 ; index01 < MAX_AVATAR_ANIMAL_NUM ; index01++ )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0 )
			{
				break;
			}
		}
		if( index01 == MAX_AVATAR_ANIMAL_NUM )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		
		// 2009.11.23 : ±è¼º¼ö
		// ¿µ¼ö »ç¿ë Àü¹®À» ¹Þ¾ÒÀ» °æ¿ì Á¤º¸ Ãâ·Â
		// µð¹ö±ëÀ» À§ÇÑ ³Ö¾ú´ø ÄÚµå
		//LOG_TO_FILE_2("![INFO] Use animal success!. animal_num = %d , ID = %s\n",tITEM_INFO->iIndex , mUSER[tUserIndex].uID);
		return;
#endif

	case 1414:
		if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != tITEM_INFO->iIndex) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			return;
		}
		
		tRandomValue = rand_mir () % 1000;

		if (tRandomValue < 2) 
		{
			tITEM_INFO = mITEM.Search (1074); //  Gold Coins Ticket(L) 
		} 
		else if (tRandomValue < 5) 
		{
			tITEM_INFO = mITEM.Search (1073); //  Gold Coins Ticket(M) 
		} 
		else if (tRandomValue < 14) 
		{
			tITEM_INFO = mITEM.Search (1072); //  Gold Coins Ticket(S) 
		}
		else if (tRandomValue < 24) 
		{
			tITEM_INFO = mITEM.Search (1103); //  Kirin Scale 
		}
		else if (tRandomValue < 29) 
		{
			tITEM_INFO = mITEM.Search (1129); //  8 Trigram Bag 
		}
		else if (tRandomValue < 39) 
		{
			tITEM_INFO = mITEM.Search (1130); //  Trigram Box 
		}
		else if (tRandomValue < 99) 
		{
			tITEM_INFO = mITEM.Search (1126); //  Reinforce Talisman 
		}
		else if (tRandomValue < 199) 
		{
			tITEM_INFO = mITEM.Search (1127); //  Combine Talisman 
		}
		else if (tRandomValue < 249) 
		{
			tITEM_INFO = mITEM.Search (1128); //  Upgrade Talisman 
		}
		else if (tRandomValue < 264) 
		{
			tITEM_INFO = mITEM.Search (1938); //  Reinforce Talisman(SP) 
		}
		else if (tRandomValue < 289) 
		{
			tITEM_INFO = mITEM.Search (1940); //  Combine Talisman(SP) 
		}
		else if (tRandomValue < 299) 
		{
			tITEM_INFO = mITEM.Search (1939); //  Upgrade Talisman(SP) 
		}
		else if (tRandomValue < 399) 
		{
			tITEM_INFO = mITEM.Search (1019); //  Smelting Flint 
		}
		else if (tRandomValue < 499) 
		{
			tITEM_INFO = mITEM.Search (1020); //  Smelting Coal 
		}
		else if (tRandomValue < 599) 
		{
			tITEM_INFO = mITEM.Search (1021); //  Smelting Iron 
		}
		else if (tRandomValue < 699) 
		{
			tITEM_INFO = mITEM.Search (1022); //  Smelting Gold  
		}
		else if (tRandomValue < 799) 
		{
			tITEM_INFO = mITEM.Search (1023); //  Smelting Platinum 
		} 
		else if (tRandomValue < 899) 
		{
			tITEM_INFO = mITEM.Search (1210); //  Amazon Stone 
		} 
		else if (tRandomValue < 949) 
		{
			tITEM_INFO = mITEM.Search (1211); //  Amazon Stone 
		}
		else
		{
			tITEM_INFO = mITEM.Search (1025); //  Celestine Stone
		}

        // 지급해야 할 아이템이 없는 경우 일단 그냥 빠져 나온다 (일어나서는 안 되는 경우이므로).
        if (tITEM_INFO == NULL) break;

        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO -> iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tITEM_INFO -> iIndex == 1156 ? 99 : 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

        mTRANSFER.B_USE_INVENTORY_ITEM_RECV (0, tPage, tIndex, tITEM_INFO -> iIndex);
        mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);

        return;
#if 0
		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 1;
		tRandomValue = rand_mir() % 1000;
		if(30 > tRandomValue){
			tItemList[0][0] = 1017;
			tItemList[0][1] = 0;
		}
		else if(70 > tRandomValue){
			tItemList[0][0] = 1018;
			tItemList[0][1] = 0;
		}
		else if(120 > tRandomValue){
			tItemList[0][0] = 1041;
			tItemList[0][1] = 0;
		}
		else if(170 > tRandomValue){
			tItemList[0][0] = 1102;
			tItemList[0][1] = 0;
		}
		else if(220 > tRandomValue){
			tItemList[0][0] = 1043;
			tItemList[0][1] = 0;
		}
		else if(270 > tRandomValue){
			tItemList[0][0] = 1103;
			tItemList[0][1] = 0;
		}
		else if(370 > tRandomValue){
			tItemList[0][0] = 1118;
			tItemList[0][1] = 0;
		}
		else if(580 > tRandomValue){
			tItemList[0][0] = 1119;
			tItemList[0][1] = 0;
		}
		else if(790 > tRandomValue){
			tItemList[0][0] = 1108;
			tItemList[0][1] = 0;
		}
		else {
			tItemList[0][0] = 1126;
			tItemList[0][1] = 0;
		}
		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(1414);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return;
#endif
	case 1415: // ¼º·¹º§ ¿µ¹°º¹±Ç
		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 2;

		// 2009.07.20
		tRandomValue = rand_mir() % 1000;
		if(tRandomValue < 2  ){
			tItemList[0][0] = 1016;
			tItemList[0][1] = 0;
		}
		else if(tRandomValue < 7){
			tItemList[0][0] = 1012;
			tItemList[0][1] = 0;
		}
		else if(tRandomValue < 49){
			tItemList[0][0] = 1015;
			tItemList[0][1] = 0;
		}
		else if(tRandomValue < 99){
			tItemList[0][0] = 1014;
			tItemList[0][1] = 0;
		}
		else if(tRandomValue < 199){
			tItemList[0][0] = 1013;
			tItemList[0][1] = 0;
		}
		else if(tRandomValue < 299){
			tItemList[0][0] = 1011;
			tItemList[0][1] = 0;
		}
		else if(tRandomValue < 399){
			tItemList[0][0] = 1010;
			tItemList[0][1] = 0;
		}
		else if(tRandomValue < 499){
			tItemList[0][0] = 1009;
			tItemList[0][1] = 0;
		}

		else if(tRandomValue < 599){
			tItemList[0][0] = 1008;
			tItemList[0][1] = 0;
		}

		else if(tRandomValue < 699){
			tItemList[0][0] = 1007;
			tItemList[0][1] = 0;
		}
		
		else if(tRandomValue < 799){
			tItemList[0][0] = 1006;
			tItemList[0][1] = 0;
		}
		
		else if(tRandomValue < 849){
			tItemList[0][0] = 1005;
			tItemList[0][1] = 0;
		}
		
		else if(tRandomValue < 899){
			tItemList[0][0] = 1004;
			tItemList[0][1] = 0;
		}
		
		else if(tRandomValue < 949){
			tItemList[0][0] = 1003;
			tItemList[0][1] = 0;
		}
		else {
			tItemList[0][0] = 1002;
			tItemList[0][1] = 0;
		}
		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(1415);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return;
	case 1437: // °©·¹º§ ¿µ¹°º¹±Ç
		if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != tITEM_INFO->iIndex) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			return;
		}
		
		tRandomValue = rand_mir () % 1000;

		if (tRandomValue < 2) 
		{
			tITEM_INFO = mITEM.Search (1400); //  White Tiger 
		} 
		else if (tRandomValue < 9) 
		{
			tITEM_INFO = mITEM.Search (1407); //  Grey Hog 
		} 
		else if (tRandomValue < 19) 
		{
			tITEM_INFO = mITEM.Search (1420); //  White Stag 
		}
		else if (tRandomValue < 24) 
		{
			tITEM_INFO = mITEM.Search (1072); //  Gold Coins Ticket(S) 
		}
		else if (tRandomValue < 29) 
		{
			tITEM_INFO = mITEM.Search (1103); //  Kirin Scale 
		}
		else if (tRandomValue < 39) 
		{
			tITEM_INFO = mITEM.Search (1130); //  Trigram Box 
		} 
		else if (tRandomValue < 99) 
		{
			tITEM_INFO = mITEM.Search (1126); //  Reinforce Talisman 
		}
		else if (tRandomValue < 199) 
		{
			tITEM_INFO = mITEM.Search (1127); //  Combine Talisman 
		}
		else if (tRandomValue < 249) 
		{
			tITEM_INFO = mITEM.Search (1128); //  Upgrade Talisman 
		}
		else if (tRandomValue < 264) 
		{
			tITEM_INFO = mITEM.Search (1938); //  Reinforce Talisman(SP) 
		}
		else if (tRandomValue < 289) 
		{
			tITEM_INFO = mITEM.Search (1940); //  Combine Talisman(SP) 
		}
		else if (tRandomValue < 299) 
		{
			tITEM_INFO = mITEM.Search (1939); //  Upgrade Talisman(SP) 
		}
		else if (tRandomValue < 399) 
		{
			tITEM_INFO = mITEM.Search (1083); //  Smelting Flint 
		}
		else if (tRandomValue < 499) 
		{
			tITEM_INFO = mITEM.Search (1020); //  Smelting Coal 
		}
		else if (tRandomValue < 599) 
		{
			tITEM_INFO = mITEM.Search (1021); //  Smelting Iron 
		}
		else if (tRandomValue < 699) 
		{
			tITEM_INFO = mITEM.Search (1022); //  Smelting Gold  
		}
		else if (tRandomValue < 799) 
		{
			tITEM_INFO = mITEM.Search (1023); //  Smelting Platinum 
		}
		else if (tRandomValue < 899) 
		{
			tITEM_INFO = mITEM.Search (1024); //  Amazon Stone 
		}
		else
		{
			tITEM_INFO = mITEM.Search (1025); //  Celestine Stone
		}

        // 지급해야 할 아이템이 없는 경우 일단 그냥 빠져 나온다 (일어나서는 안 되는 경우이므로).
        if (tITEM_INFO == NULL) break;

        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO -> iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tITEM_INFO -> iIndex == 1156 ? 99 : 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

        mTRANSFER.B_USE_INVENTORY_ITEM_RECV (0, tPage, tIndex, tITEM_INFO -> iIndex);
        mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);

        return;
	case 1417 :
if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != tITEM_INFO->iIndex) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			return;
		}



		//night_kutu

		//LOG_TO_FILE_2("%s %d",&mUSER[tUserIndex].uID[0] ,1);


		
		tRandomValue = rand_mir () % 1000;

		if (tRandomValue < 2) 
		{
			tITEM_INFO = mITEM.Search (1418); //  Blue Tiger
		} 
		else if (tRandomValue < 5) 
		{
			tITEM_INFO = mITEM.Search (1419); //  Black Hog 
		} 
		else if (tRandomValue < 14) 
		{
			tITEM_INFO = mITEM.Search (1420); //  White Stag 
		}
		else if (tRandomValue < 24) 
		{
			tITEM_INFO = mITEM.Search (1400); //  White Tiger 
		}
		else if (tRandomValue < 29) 
		{
			tITEM_INFO = mITEM.Search (1407); //  Grey Hog 
		}
		else if (tRandomValue < 89) 
		{
			tITEM_INFO = mITEM.Search (1408); //  Brown Stag 
		}
		else if (tRandomValue < 189) 
		{
			tITEM_INFO = mITEM.Search (1103); //  Kirin Scale 
		}
		else if (tRandomValue < 249) 
		{
			tITEM_INFO = mITEM.Search (1129); //  8 Trigram Bag 
		}
		else if (tRandomValue < 299) 
		{
			tITEM_INFO = mITEM.Search (1130); //  Trigram Box 
		}
		else if (tRandomValue < 399) 
		{
			tITEM_INFO = mITEM.Search (1126); //  Reinforce Talisman 
		}
		else if (tRandomValue < 499) 
		{
			tITEM_INFO = mITEM.Search (1127); //  Combine Talisman 
		}
		else if (tRandomValue < 599) 
		{
			tITEM_INFO = mITEM.Search (1128); //  Upgrade Talisman 
		}
		else if (tRandomValue < 649) 
		{
			tITEM_INFO = mITEM.Search (1938); //  Reinforce Talisman(SP) 
		}
		else if (tRandomValue < 699) 
		{
			tITEM_INFO = mITEM.Search (1939); //  Upgrade Talisman(SP) 
		}
		else if (tRandomValue < 749) 
		{
			tITEM_INFO = mITEM.Search (1940); //  Combine Talisman(SP) 
		} 
		else if (tRandomValue < 849) 
		{
			tITEM_INFO = mITEM.Search (1144); //  Gold Scroll 
		}
		else
		{
			tITEM_INFO = mITEM.Search (1085); //  Cash [500]
		}

        // 지급해야 할 아이템이 없는 경우 일단 그냥 빠져 나온다 (일어나서는 안 되는 경우이므로).
        if (tITEM_INFO == NULL) break;

        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO -> iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tITEM_INFO -> iIndex == 1156 ? 99 : 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

        mTRANSFER.B_USE_INVENTORY_ITEM_RECV (0, tPage, tIndex, tITEM_INFO -> iIndex);
        mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);

        return;
	case 1429 : // Á¦·Ã¼®
		tProtectIS = mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy >> 16;
		if(65535 <= (tProtectIS + 1)){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy = ((++tProtectIS) << 16) + (mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy & 0x0000FFFF);
		mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;


		/** 2009. 11. 18 : Àå½Ä ÇØ¹æ ½Ã½ºÅÛ (wolf) */
	case 1357: // ÀºÀå¼­ ¾ÆÀÌÅÛ »ç¿ë.
		if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != tITEM_INFO->iIndex) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.iSilverOrnamentRemainsTime += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM (tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0],
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], 
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5],
			0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV (0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.iSilverOrnamentRemainsTime);
		mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);
		return;

	case 1144: // ±ÝÀå¼­ ¾ÆÀÌÅÛ »ç¿ë.
		if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != tITEM_INFO->iIndex) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime += 240;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM (tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0],
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], 
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5],
			0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV (0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime);
		mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);
		return;

		/** 2009. 11. 18 : Àå½Ä ÇØ¹æ ½Ã½ºÅÛ (wolf) */

		/** 2009. 12. 16 : ±Í¸êºÎ ¾ÆÀÌÅÛ °³¹ß (wolf) */
	case  1157 : // ±Í¸êºÎ
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 == 145) && (mUSER[tUserIndex].mAvatarInfo.aLevel2 == 4) && (mUSER[tUserIndex].mAvatarInfo.aManaPotionConvertNum < 12) && (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe >= 10000) && (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == 1082238285))  /// # if - 1
		{
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 10000;
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
			mUSER[tUserIndex].mAvatarInfo.aManaPotionConvertNum += 1;
			mUSER[tUserIndex].mAvatarInfo.aSkillPoint +=50;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 10000;
			mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 0 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 1 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 2 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 3 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 4 ] = 0;
			mUSER[ tUserIndex ].mAvatarInfo.aInventory[ tPage ][ tIndex ][ 5 ] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue);			
			
			
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		} 
		else /// # if - 1 else
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV (1, tPage, tIndex, 0); 
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		}
		
		return;

	case 1406: 
		if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != tITEM_INFO->iIndex) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			return;
		}
		
		tRandomValue = rand_mir () % 1000;

		if (tRandomValue < 5) 
		{
			tITEM_INFO = mITEM.Search (ANIMAL_NUM_BAKHO); // ¹éÈ£
		} 
		else if (tRandomValue < 25) 
		{
			tITEM_INFO = mITEM.Search (1092); // ±Ù·Â´Ü
		} 
		else if (tRandomValue < 65) 
		{
			tITEM_INFO = mITEM.Search (1017); // È®·Â´Ü
		}
		else if (tRandomValue < 105) 
		{
			tITEM_INFO = mITEM.Search (1018); // ³»°ø´Ü
		}
		else if (tRandomValue < 145) 
		{
			tITEM_INFO = mITEM.Search (1093); // ¹ÎÃ¸´Ü
		}
		else if (tRandomValue < 420) 
		{
			tITEM_INFO = mITEM.Search (1156); // ¸ÁÈ¥ºÎ
		} 
		else if (tRandomValue < 710) 
		{
			tITEM_INFO = mITEM.Search (1128); // ½Â±ÞºÎ
		}
		else
		{
			tITEM_INFO = mITEM.Search (1127); // Á¶ÇÕºÎ
		}

        // Áö±ÞÇØ¾ß ÇÒ ¾ÆÀÌÅÛÀÌ ¾ø´Â °æ¿ì ÀÏ´Ü ±×³É ºüÁ® ³ª¿Â´Ù (ÀÏ¾î³ª¼­´Â ¾È µÇ´Â °æ¿ìÀÌ¹Ç·Î).
        if (tITEM_INFO == NULL) break;

        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO -> iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tITEM_INFO -> iIndex == 1156 ? 99 : 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

        mTRANSFER.B_USE_INVENTORY_ITEM_RECV (0, tPage, tIndex, tITEM_INFO -> iIndex);
        mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);

        return;
	
	
#ifdef __TK__
	case 1413: // ¿µ¼ö º¹ÁÖ¸Ó´Ï.
#else
	case 1410: // ¿µ¼ö º¹ÁÖ¸Ó´Ï.
#endif
		if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != tITEM_INFO->iIndex) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			return;
		}
		
		tRandomValue = rand_mir () % 1000;

		if (tRandomValue < 4) 
		{
			tITEM_INFO = mITEM.Search (1401); // Warlord Cape
		} 
		else if (tRandomValue < 14) 
		{
			tITEM_INFO = mITEM.Search (1103); // Kirin Scale
		} 
		else if (tRandomValue < 34) 
		{
			tITEM_INFO = mITEM.Search (1072); // Gold Coins Ticket(S)
		}
		else if (tRandomValue < 44) 
		{
			tITEM_INFO = mITEM.Search (1130); //Trigram Box
		}
		else if (tRandomValue < 74) 
		{
			tITEM_INFO = mITEM.Search (1017); //Snow Elixir 
		}
		else if (tRandomValue < 104) 
		{
			tITEM_INFO = mITEM.Search (1018); //Heart Elixir
		} 
		else if (tRandomValue < 134) 
		{
			tITEM_INFO = mITEM.Search (1092); //Fire Elixir
		} 
		else if (tRandomValue < 164) 
		{
			tITEM_INFO = mITEM.Search (1093); //Wind Elixir
		} 
		else if (tRandomValue < 249) 
		{
			tITEM_INFO = mITEM.Search (1024); //Amazon Stone
		} 
		else if (tRandomValue < 399) 
		{
			tITEM_INFO = mITEM.Search (1127); //Combine Talisman
		}
		else
		{
			tITEM_INFO = mITEM.Search (1156); //Acupoints strike
		}

        // 지급해야 할 아이템이 없는 경우 일단 그냥 빠져 나온다 (일어나서는 안 되는 경우이므로).
        if (tITEM_INFO == NULL) break;

        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO -> iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tITEM_INFO -> iIndex == 1156 ? 99 : 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

        mTRANSFER.B_USE_INVENTORY_ITEM_RECV (0, tPage, tIndex, tITEM_INFO -> iIndex);
        mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);

        return;
	//---------------------------------------------------------------------------------------------------------------------------

#ifdef __TK__
	case 1418:
		// ÇöÀç ÀÌ ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» ¾²°í ÀÖ°Å³ª ¾Æ¹«·± ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» »ç¿ëÇÏÁö ¾ÊÀ»¶§¸¸ »ç¿ëÇØ¾ß ÇÑ´Ù.
		if( mUSER[tUserIndex].bUsePackItem == true && mUSER[tUserIndex].mAvatarInfo.aPackSilverDate < mUTIL.ReturnNowDate() )
		{
			LOG_TO_BOTH_2("![%s] : %d \n",__FUNCTION__,__LINE__);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 2;

		tItemList[0][0] = 1129; // ¼±¼úÇà³¶
		tItemList[0][1] = 0;
		tItemList[1][0] = 1414; // º¹ÁÖ¸Ó´Ï
		tItemList[1][1] = 0;
		
		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(1418);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

		tValue = mUTIL.ReturnAddDate( mUSER[tUserIndex].mAvatarInfo.aPackSilverDate, 30 );
		mUSER[tUserIndex].mAvatarInfo.aPackSilverDate = tValue;
		mUSER[tUserIndex].mGeneralExperienceUpRatio =+ 0.2f;
		mUSER[tUserIndex].mItemDropUpRatio =+ 0.2f;
		mUSER[tUserIndex].mSelfPatExperienceUpRatio = 0.1f;
		mUSER[tUserIndex].bUsePackItem = true;

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

        if( !mEXTRA_COM.U_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0], tItemNumber, &mUSER[tUserIndex].mAvatarInfo.aName[0] ) )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, -1);
        }
        if( mEXTRA_COM.mRecv_Result != 0 )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, mEXTRA_COM.mRecv_Result);
        }
		return;

	case 1419:
		// ÇöÀç ÀÌ ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» ¾²°í ÀÖ°Å³ª ¾Æ¹«·± ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» »ç¿ëÇÏÁö ¾ÊÀ»¶§¸¸ »ç¿ëÇØ¾ß ÇÑ´Ù.
		if( mUSER[tUserIndex].bUsePackItem == true && mUSER[tUserIndex].mAvatarInfo.aPackGoldDate < mUTIL.ReturnNowDate() )
		{
			LOG_TO_BOTH_2("![%s] : %d \n",__FUNCTION__,__LINE__);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 3;

		tItemList[0][0] = 1129; // ¼±¼úÇà³¶
		tItemList[0][1] = 0;
		tItemList[1][0] = 1414; // º¹ÁÖ¸Ó´Ï
		tItemList[1][1] = 0;
		tItemList[2][0] = 1124; // º¹ÁÖ¸Ó´Ï
		tItemList[2][1] = 0;

		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(14180);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

		tValue = mUTIL.ReturnAddDate( mUSER[tUserIndex].mAvatarInfo.aPackGoldDate, 30 );
		mUSER[tUserIndex].mAvatarInfo.aPackGoldDate = tValue;
		mUSER[tUserIndex].mGeneralExperienceUpRatio =+ 0.3f;
		mUSER[tUserIndex].mItemDropUpRatio =+ 0.3f;
		mUSER[tUserIndex].mSelfPatExperienceUpRatio = 0.2f;
		mUSER[tUserIndex].bUsePackItem = true;

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

        if( !mEXTRA_COM.U_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0], tItemNumber, &mUSER[tUserIndex].mAvatarInfo.aName[0] ) )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, -1);
        }
        if( mEXTRA_COM.mRecv_Result != 0 )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, mEXTRA_COM.mRecv_Result);
        }
		return;

	case 1420:
		// ÇöÀç ÀÌ ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» ¾²°í ÀÖ°Å³ª ¾Æ¹«·± ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» »ç¿ëÇÏÁö ¾ÊÀ»¶§¸¸ »ç¿ëÇØ¾ß ÇÑ´Ù.
		if( mUSER[tUserIndex].bUsePackItem == true && mUSER[tUserIndex].mAvatarInfo.aPackDiamondDate < mUTIL.ReturnNowDate() )
		{
			LOG_TO_BOTH_2("![%s] : %d \n",__FUNCTION__,__LINE__);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 4;

		tItemList[0][0] = 1129; // ¼±¼úÇà³¶
		tItemList[0][1] = 0;
		tItemList[1][0] = 1414; // º¹ÁÖ¸Ó´Ï
		tItemList[1][1] = 0;
		tItemList[2][0] = 1124; // ¼öÇàºÎ
		tItemList[2][1] = 0;
		tItemList[3][0] = 1103; // ¹æÆÄºÎ
		tItemList[3][1] = 0;

		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(1420);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

		tValue = mUTIL.ReturnAddDate( mUSER[tUserIndex].mAvatarInfo.aPackDiamondDate, 30 );
		mUSER[tUserIndex].mAvatarInfo.aPackDiamondDate = tValue;
		mUSER[tUserIndex].mGeneralExperienceUpRatio =+ 0.6f;
		mUSER[tUserIndex].mItemDropUpRatio =+ 0.5f;
		mUSER[tUserIndex].mSelfPatExperienceUpRatio = 0.3f;
		mUSER[tUserIndex].bUsePackItem = true;


		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

        if( !mEXTRA_COM.U_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0], tItemNumber, &mUSER[tUserIndex].mAvatarInfo.aName[0] ) )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, -1);
        }
        if( mEXTRA_COM.mRecv_Result != 0 )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, mEXTRA_COM.mRecv_Result);
        }
		return;

	case 1421:
		// ÇöÀç ÀÌ ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» ¾²°í ÀÖ°Å³ª ¾Æ¹«·± ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» »ç¿ëÇÏÁö ¾ÊÀ»¶§¸¸ »ç¿ëÇØ¾ß ÇÑ´Ù.
		if( mUSER[tUserIndex].bUsePackItem == true && mUSER[tUserIndex].mAvatarInfo.aPackSilverDateMobile < mUTIL.ReturnNowDate() )
		{
			LOG_TO_BOTH_2("![%s] : %d \n",__FUNCTION__,__LINE__);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 2;

		tItemList[0][0] = 1129; // ¼±¼úÇà³¶
		tItemList[0][1] = 0;
		tItemList[1][0] = 1414; // º¹ÁÖ¸Ó´Ï
		tItemList[1][1] = 0;

		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(1421);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

		tValue = mUTIL.ReturnAddDate( mUSER[tUserIndex].mAvatarInfo.aPackSilverDateMobile, 30 );
		mUSER[tUserIndex].mAvatarInfo.aPackSilverDateMobile = tValue;
		mUSER[tUserIndex].mGeneralExperienceUpRatio =+ 0.2f;
		mUSER[tUserIndex].mItemDropUpRatio =+ 0.2f;
		mUSER[tUserIndex].mSelfPatExperienceUpRatio = 0.1f;
		mUSER[tUserIndex].bUsePackItem = true;

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

        if( !mEXTRA_COM.U_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0], tItemNumber, &mUSER[tUserIndex].mAvatarInfo.aName[0] ) )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, -1);
        }
        if( mEXTRA_COM.mRecv_Result != 0 )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, mEXTRA_COM.mRecv_Result);
        }
		return;

	case 1422:
		// ÇöÀç ÀÌ ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» ¾²°í ÀÖ°Å³ª ¾Æ¹«·± ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» »ç¿ëÇÏÁö ¾ÊÀ»¶§¸¸ »ç¿ëÇØ¾ß ÇÑ´Ù.
		if( mUSER[tUserIndex].bUsePackItem == true && mUSER[tUserIndex].mAvatarInfo.aPackGoldDateMobile < mUTIL.ReturnNowDate() )
		{
			LOG_TO_BOTH_2("![%s] : %d \n",__FUNCTION__,__LINE__);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 2;

		tItemList[0][0] = 1414; // º¹ÁÖ¸Ó´Ï
		tItemList[0][1] = 0;
		tItemList[1][0] = 1124; // ¼öÇàºÎ
		tItemList[1][1] = 0;

		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(1422);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

		tValue = mUTIL.ReturnAddDate( mUSER[tUserIndex].mAvatarInfo.aPackGoldDateMobile, 15 );
		mUSER[tUserIndex].mAvatarInfo.aPackGoldDateMobile = tValue;
		mUSER[tUserIndex].mGeneralExperienceUpRatio =+ 0.3f;
		mUSER[tUserIndex].mItemDropUpRatio =+ 0.3f;
		mUSER[tUserIndex].mSelfPatExperienceUpRatio = 0.2f;
		mUSER[tUserIndex].bUsePackItem = true;


		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

        if( !mEXTRA_COM.U_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0], tItemNumber, &mUSER[tUserIndex].mAvatarInfo.aName[0] ) )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, -1);
        }
        if( mEXTRA_COM.mRecv_Result != 0 )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, mEXTRA_COM.mRecv_Result);
        }
		return;

	case 1423:
		// ÇöÀç ÀÌ ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» ¾²°í ÀÖ°Å³ª ¾Æ¹«·± ÆÐÅ°Áö ¾ÆÀÌÅÛÀ» »ç¿ëÇÏÁö ¾ÊÀ»¶§¸¸ »ç¿ëÇØ¾ß ÇÑ´Ù.
		if( mUSER[tUserIndex].bUsePackItem == true && mUSER[tUserIndex].mAvatarInfo.aPackDiamondDateMobile < mUTIL.ReturnNowDate() )
		{
			LOG_TO_BOTH_2("![%s] : %d \n",__FUNCTION__,__LINE__);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		for(index01 = 0; index01 < tItemListNum; ++index01){
			tItemList[index01][0] = 0;
			tItemList[index01][1] = 0;
			tPageList[index01] = -1;
			tInvenSlotList[index01] = -1;
			tInvenIndexList[index01] = -1;
			tDumyPageList[index01] = -1;
			tDumyInvenSlotList[index01] = -1;
		}
		tItemCount = 2;

		tItemList[0][0] = 1414; // º¹ÁÖ¸Ó´Ï
		tItemList[0][1] = 0;
		tItemList[1][0] = 1124; // º¹ÁÖ¸Ó´Ï
		tItemList[1][1] = 0;

		for(index01 = 0; index01 < tItemCount; ++index01){
			tITEM_INFO = mITEM.Search(1423);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			tDumyPageList[index01] = iPage;
			tDumyInvenSlotList[index01] = iInvenSlot;
		}
		for(index02 = 0; index02 < tItemCount; ++index02){
			if(-1 == tDumyPageList[index02]){
				break;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tDumyPageList[index02]][tDumyInvenSlotList[index02]][5] = 0;
		}
		if(index01 != tItemCount){
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}

		tItemCount = 0;
		for(index01 = 0; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				continue;
			}
			tITEM_INFO = mITEM.Search(tItemList[index01][0]);
			if (tITEM_INFO == NULL) {
				break;
			}
			if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) != true) {
				break;
			}
			iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
			if (iInvenSlot == -1) {
				break;
			}
			++tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemList[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );
			tPageList[index01] = iPage;
			tInvenSlotList[index01] = iInvenSlot;
			tInvenIndexList[index01] = iInvenIndex;
			tItemValueList[index01] = 0;
			tItemRecognitionList[index01] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5];
		}
		if(tItemListNum != index01)
		{
			for(index02 = 0; index02 < tItemListNum; ++index02){
				if(-1 == tPageList[index02]){
					break;
				}
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index02]][tInvenSlotList[index02]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 1, tPage, tIndex, tValue );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[0]][tInvenSlotList[0]][5]  );

		for(index01 = 1; index01 < tItemListNum; ++index01){
			if(0 == tItemList[index01][0]){
				break;
			}
			mGAMELOG.GL_658_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPageList[index01]][tInvenSlotList[index01]][5], index01 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

		tValue = mUTIL.ReturnAddDate( mUSER[tUserIndex].mAvatarInfo.aPackDiamondDateMobile, 7 );
		mUSER[tUserIndex].mAvatarInfo.aPackDiamondDateMobile = tValue;
		mUSER[tUserIndex].mGeneralExperienceUpRatio =+ 0.6f;
		mUSER[tUserIndex].mItemDropUpRatio =+ 0.5f;
		mUSER[tUserIndex].mSelfPatExperienceUpRatio = 0.3f;
		mUSER[tUserIndex].bUsePackItem = true;


		mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mTRANSFER.B_ITEM_LIKE_1336_RECV(&tItemCount, tPageList, tInvenSlotList, tInvenIndexList, tItemList, tItemValueList, tItemRecognitionList );
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

        if( !mEXTRA_COM.U_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0], tItemNumber, &mUSER[tUserIndex].mAvatarInfo.aName[0] ) )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, -1);
        }
        if( mEXTRA_COM.mRecv_Result != 0 )
        {
            mGAMELOG.GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(tUserIndex, tITEM_INFO->iIndex, mEXTRA_COM.mRecv_Result);
        }
		return;
#endif
	//---------
	case 1109 : // ÀÌµ¿¼­
        if( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1 ) {
            mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
            return ;
        }
        // Á¸ ÀÌµ¿ °ËÁõ Ã³¸® - W_DEMAND_ZONE_SERVER_INFO_2¿¡¼­ ÃÖÁ¾ÀûÀ¸·Î ÇÑ¹ø ´õ ÇÕ´Ï´Ù.
        {
        	int tResult = mGAME.CheckMoveZoneForMoveZoneItem(mUSER[tUserIndex].mAvatarInfo.aTribe
        	, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2, tValue);
            if (tResult != 0)
            {
                mTRANSFER.B_USE_INVENTORY_ITEM_RECV( tResult, tPage, tIndex, tValue );
                mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
                return ;
            }
        }
        // Á¸ ÀÌµ¿ ¼º°ø ÈÄ ÀÌµ¿¼­ ¾ÆÀÌÅÛ »ç¿ë Ã³¸®¸¦ ÇÏ±âÀ§ÇÑ ¼³Á¤.
        mUSER[tUserIndex].mMoveItemInfo.mZoneNumber = tValue;
        mUSER[tUserIndex].mMoveItemInfo.mInvenPage = tPage;
        mUSER[tUserIndex].mMoveItemInfo.mInvenIndex = tIndex;
        mUSER[tUserIndex].mMoveItemInfo.mInvenX = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1];
        mUSER[tUserIndex].mMoveItemInfo.mInvenY = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2];
        mPLAYUSER_COM.U_SET_MOVE_ITEM_FOR_ZONE_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].mMoveItemInfo);

        mAVATAR_OBJECT[tUserIndex].mCheckDeath = true;
        mAVATAR_OBJECT[tUserIndex].mCheckCount = 9;
        mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        return ;

/** 2010. 1. 5. : Animal Lucky Pocket add (wolf) */
#ifndef __TK__
	case 1411:
		if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != tITEM_INFO->iIndex) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			return;
		}
		
		tRandomValue = rand_mir () % 1000;

		if (tRandomValue < 4) 
		{
			tITEM_INFO = mITEM.Search (1400); //White Tiger
		} 
		else if (tRandomValue < 14) 
		{
			tITEM_INFO = mITEM.Search (1407); // Grey Hog
		} 
		else if (tRandomValue < 29) 
		{
			tITEM_INFO = mITEM.Search (1408); // Brown Stag
		}
		else if (tRandomValue < 34) 
		{
			tITEM_INFO = mITEM.Search (1018); // Kirin Scale
		}
		else if (tRandomValue < 44) 
		{
			tITEM_INFO = mITEM.Search (1072); // Gold Coins Ticket(S)
		}
		else if (tRandomValue < 49) 
		{
			tITEM_INFO = mITEM.Search (1130); //  Trigram Box 
		}
		else if (tRandomValue < 74) 
		{
			tITEM_INFO = mITEM.Search (1017); //  Snow Elixir 
		}
		else if (tRandomValue < 104) 
		{
			tITEM_INFO = mITEM.Search (1018); //  Heart Elixir 
		}
		else if (tRandomValue < 134) 
		{
			tITEM_INFO = mITEM.Search (1092); //  Fire Elixir 
		}
		else if (tRandomValue < 164) 
		{
			tITEM_INFO = mITEM.Search (1093); //  Wind Elixir 
		}
		else if (tRandomValue < 239) 
		{
			tITEM_INFO = mITEM.Search (1024); //  Amazon Stone 
		}
		else if (tRandomValue < 299) 
		{
			tITEM_INFO = mITEM.Search (1025); //  Celestine Stone 
		}
		else if (tRandomValue < 349) 
		{
			tITEM_INFO = mITEM.Search (1127); //  Combine Talisman 
		}
		else if (tRandomValue < 379) 
		{
			tITEM_INFO = mITEM.Search (1126); //  Reinforce Talisman 
		} 
		else if (tRandomValue < 399) 
		{
			tITEM_INFO = mITEM.Search (1128); //  Upgrade Talisman 
		}
		else if (tRandomValue < 549) 
		{
			tITEM_INFO = mITEM.Search (1210); //  Ancient Parchment
		}
		else if (tRandomValue < 749) 
		{
			tITEM_INFO = mITEM.Search (1211); //  Mysterious Stone 
		}
		else if (tRandomValue < 799) 
		{
			tITEM_INFO = mITEM.Search (1084); //  Cash [100]
		}
		else
		{
			tITEM_INFO = mITEM.Search (1156); //  Acupoints strike
		}

        // 지급해야 할 아이템이 없는 경우 일단 그냥 빠져 나온다 (일어나서는 안 되는 경우이므로).
        if (tITEM_INFO == NULL) break;

        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO -> iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tITEM_INFO -> iIndex == 1156 ? 99 : 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

        mTRANSFER.B_USE_INVENTORY_ITEM_RECV (0, tPage, tIndex, tITEM_INFO -> iIndex);
        mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);

        return;
    case 1412:
        if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != tITEM_INFO->iIndex) {
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			return;
		}
		
		tRandomValue = rand_mir () % 1000;

		if (tRandomValue < 2) 
		{
			tITEM_INFO = mITEM.Search (1418); //  Blue Tiger 
		} 
		else if (tRandomValue < 5) 
		{
			tITEM_INFO = mITEM.Search (1419); //  Black Hog 
		} 
		else if (tRandomValue < 14) 
		{
			tITEM_INFO = mITEM.Search (1420); //  White Stag 
		}
		else if (tRandomValue < 24) 
		{
			tITEM_INFO = mITEM.Search (1400); //  White Tiger 
		}
		else if (tRandomValue < 29) 
		{
			tITEM_INFO = mITEM.Search (1407); //  Grey Hog 
		}
		else if (tRandomValue < 89) 
		{
			tITEM_INFO = mITEM.Search (1408); //  Brown Stag 
		}
		else if (tRandomValue < 199) 
		{
			tITEM_INFO = mITEM.Search (1127); //  Combine Talisman 
		}
		else if (tRandomValue < 379) 
		{
			tITEM_INFO = mITEM.Search (1126); //  Reinforce Talisman 
		} 
		else if (tRandomValue < 399) 
		{
			tITEM_INFO = mITEM.Search (1128); //  Upgrade Talisman 
		}
		else
		{
			tITEM_INFO = mITEM.Search (1109); //  Teleport Scroll
		}

        // 지급해야 할 아이템이 없는 경우 일단 그냥 빠져 나온다 (일어나서는 안 되는 경우이므로).
        if (tITEM_INFO == NULL) break;

        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tITEM_INFO -> iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tITEM_INFO -> iIndex == 1109 ? 1 : 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
        mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

        mTRANSFER.B_USE_INVENTORY_ITEM_RECV (0, tPage, tIndex, tITEM_INFO -> iIndex);
        mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);

        return;
#else
	case 1416:
        tRandomValue = rand_mir() % 1000;
        if( tRandomValue < 3 )
        {
            tValue = 1406;
        }
        else if( tRandomValue < 43 )
        {
            tValue = 1017;
        }
        else if( tRandomValue < 83 )
        {
            tValue = 1018;
        }
        else if( tRandomValue < 103 )
        {
            tValue = 1092;
        }
        else if( tRandomValue < 143 )
        {
            tValue = 1093;
        }
        else if( tRandomValue < 420 )
        {
            tValue = 1156;
        }
        else if( tRandomValue < 710 )
        {
            tValue = 1128;
        }
        else
        {
            tValue = 1127;
        }
        mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 0 );
		
		//(100112 ÀÌ½ÂÇö) ÅÍÅ° ¿µ¼öº¹ÁÖ¸Ó´Ï ¸ÁÈ¥ºÎ °³¼ö 1 -> 99
		if ( tValue == 1156 )
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 99;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		//end 100112 }

        mTRANSFER.B_USE_INVENTORY_ITEM_RECV( 0, tPage, tIndex, tValue );
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        return;

#endif
/** 2010. 1. 5. : Animal Lucky Pocket add (wolf) */

	default : //[¿À·ù]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_IMPROVE_ITEM_SEND
void W_IMPROVE_ITEM_SEND( int tUserIndex )
{
	unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory( &tPage1, &tPacket[1], 4 );
	CopyMemory( &tIndex1, &tPacket[5], 4 );
	CopyMemory( &tPage2, &tPacket[9], 4 );
	CopyMemory( &tIndex2, &tPacket[13], 4 );
	if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO *tITEM_INFO1;
	ITEM_INFO *tITEM_INFO2;
	int tCost;
	int iValue;
	int tProbability1;
	int tProbability2;
	int tProtectIS = 0;

	if( ( tPage1 == 1 ) || ( tPage2 == 1 ) )
	{
		if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] );
	if( tITEM_INFO1 == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO1->iSort != 7 ) && ( tITEM_INFO1->iSort != 8 ) && ( tITEM_INFO1->iSort != 9 ) && ( tITEM_INFO1->iSort != 10 ) && ( tITEM_INFO1->iSort != 11 ) && ( tITEM_INFO1->iSort != 12 ) && ( tITEM_INFO1->iSort != 13 ) && ( tITEM_INFO1->iSort != 14 ) && ( tITEM_INFO1->iSort != 15 ) && ( tITEM_INFO1->iSort != 16 ) && ( tITEM_INFO1->iSort != 17 ) && ( tITEM_INFO1->iSort != 18 ) && ( tITEM_INFO1->iSort != 19 ) && ( tITEM_INFO1->iSort != 20 ) && ( tITEM_INFO1->iSort != 21 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( tITEM_INFO1->iCheckImprove != 2 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) >= MAX_IMPROVE_ITEM_NUM )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] );
	if( tITEM_INFO2 == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO2->iIndex != 1019 ) && ( tITEM_INFO2->iIndex != 1020 ) && ( tITEM_INFO2->iIndex != 1021 ) && ( tITEM_INFO2->iIndex != 1022 ) && ( tITEM_INFO2->iIndex != 1023 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] )
	{
	case 1019 :
		tCost = 10000;
		iValue = 1;
		break;
	case 1020 :
		tCost = 30000;
		iValue = 2;
		break;
	case 1021 :
		tCost = 50000;
		iValue = 3;
		break;
	case 1022 :
		tCost = 70000;
		iValue = 4;
		break;
	case 1023 :
		tCost = 90000;
		iValue = 5;
		break;
	}
	if( mUSER[tUserIndex].mAvatarInfo.aMoney < tCost )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) + iValue ) >= MAX_IMPROVE_ITEM_NUM )
	{
		iValue = MAX_IMPROVE_ITEM_NUM - mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] );
	}
	tProbability1 =  103 - ( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) + iValue ) * 3 +  (int) ( (float) mAVATAR_OBJECT[tUserIndex].GetLuck() / 100.0f );
	if( tProbability1 < 5 )
	{
		tProbability1 = 5;
	}

	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF) > 0) { // ... ...
		int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF;
		int iSaveImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFFFFFF00;
		tProbability1 += 10;
		mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 = iSaveImproveValue + iImproveValue - 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2 (64, mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2);
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	}
	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	else if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF) > 0) { // ... ...
		int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF;
		int iSaveImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFFFFFF00;
		tProbability1 += 5;
		mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum = iSaveImproveValue + iImproveValue - 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2 (26, mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum);
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	}

	tProbability2 = - 57 + ( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) + iValue ) * 3 -  (int) ( (float) mAVATAR_OBJECT[tUserIndex].GetLuck() / 100.0f );
	if( tProbability2 < 0 )
	{
		tProbability2 = 0;
	}
	tRandom = rand_mir();
	if( ( tRandom % 100 ) < (unsigned int)tProbability1 )
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue );
		mGAMELOG.GL_608_IMPROVE_ITEM( tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_IMPROVE_ITEM_RECV( 0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		if( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == MAX_IMPROVE_ITEM_NUM ){
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 111;
			CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
			CopyMemory( &tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
			mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
			//--------------//
			//--------------//
			//--------------//
		}
		return;
	}
	tRandom = rand_mir();
	if( ( tRandom % 100 ) < (unsigned int)tProbability2 )
	{
		if( (mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy & 0x0000FFFF) > 0 )
		{
			mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2( 15, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			if( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) > 0 )
			{
				tProtectIS = mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy >> 16;
				if((0 < tProtectIS) && (30 >=  mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) + iValue )){
					mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy = ((--tProtectIS) << 16) + (mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy & 0x0000FFFF);
					mTRANSFER.B_AVATAR_CHANGE_INFO_2( 43, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy );
					mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				}
				else{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], -1 );
				}
			}
			mGAMELOG.GL_608_IMPROVE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_IMPROVE_ITEM_RECV( 1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mGAMELOG.GL_608_IMPROVE_ITEM( tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_IMPROVE_ITEM_RECV( 2, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	if( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) > 0 )
	{
		tProtectIS = mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy >> 16;
		if((0 < tProtectIS) && (30 >=  mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) + iValue )){
			mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy = ((--tProtectIS) << 16) + (mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy & 0x0000FFFF);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2( 43, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
		else{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], -1 );
		}
	}
	mGAMELOG.GL_608_IMPROVE_ITEM( tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost );
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mTRANSFER.B_IMPROVE_ITEM_RECV( 1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_ADD_ITEM_SEND
void W_ADD_ITEM_SEND( int tUserIndex )
{
	unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory( &tPage1, &tPacket[1], 4 );
	CopyMemory( &tIndex1, &tPacket[5], 4 );
	CopyMemory( &tPage2, &tPacket[9], 4 );
	CopyMemory( &tIndex2, &tPacket[13], 4 );
	if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO *tITEM_INFO1;
	ITEM_INFO *tITEM_INFO2;
	int tCost;
	int tProbability;

	if( ( tPage1 == 1 ) || ( tPage2 == 1 ) )
	{
		if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] );
	if( tITEM_INFO1 == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO1->iType != 3 ) && ( tITEM_INFO1->iType != 4 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO1->iSort != 7 ) && ( tITEM_INFO1->iSort != 8 ) && ( tITEM_INFO1->iSort != 9 ) && ( tITEM_INFO1->iSort != 10 ) && ( tITEM_INFO1->iSort != 11 ) && ( tITEM_INFO1->iSort != 12 ) && ( tITEM_INFO1->iSort != 13 ) && ( tITEM_INFO1->iSort != 14 ) && ( tITEM_INFO1->iSort != 15 ) && ( tITEM_INFO1->iSort != 16 ) && ( tITEM_INFO1->iSort != 17 ) && ( tITEM_INFO1->iSort != 18 ) && ( tITEM_INFO1->iSort != 19 ) && ( tITEM_INFO1->iSort != 20 ) && ( tITEM_INFO1->iSort != 21 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( tITEM_INFO1->iCheckHighImprove != 2 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUTIL.ReturnIUValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) >= MAX_ADD_ITEM_NUM )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] );
	if( tITEM_INFO2 == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( tITEM_INFO2->iType != 3 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO2->iSort != 7 ) && ( tITEM_INFO2->iSort != 8 ) && ( tITEM_INFO2->iSort != 9 ) && ( tITEM_INFO2->iSort != 10 ) && ( tITEM_INFO2->iSort != 11 ) && ( tITEM_INFO2->iSort != 12 ) && ( tITEM_INFO2->iSort != 13 ) && ( tITEM_INFO2->iSort != 14 ) && ( tITEM_INFO2->iSort != 15 ) && ( tITEM_INFO2->iSort != 16 ) && ( tITEM_INFO2->iSort != 17 ) && ( tITEM_INFO2->iSort != 18 ) && ( tITEM_INFO2->iSort != 19 ) && ( tITEM_INFO2->iSort != 20 ) && ( tITEM_INFO2->iSort != 21 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] ) > 0 ) || ( mUTIL.ReturnIUValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] ) > 0 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( tITEM_INFO1->iSort != tITEM_INFO2->iSort )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch( tITEM_INFO1->iType )
	{
	case 3 :
#ifdef __GOD__
		if( ( tITEM_INFO2->iLevel + tITEM_INFO2->iMartialLevel ) != ( tITEM_INFO1->iLevel + tITEM_INFO1->iMartialLevel ) )
#else
		if( tITEM_INFO2->iLevel != tITEM_INFO1->iLevel )
#endif
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 4 :
		switch( tITEM_INFO1->iLevel )
		{
		case 100 :
			if( tITEM_INFO2->iLevel != 95 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 110 :
			if( tITEM_INFO2->iLevel != 105 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 115 :
			if( tITEM_INFO2->iLevel != 114 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 118 :
			if( tITEM_INFO2->iLevel != 117 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 121 :
			if( tITEM_INFO2->iLevel != 120 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 124 :
			if( tITEM_INFO2->iLevel != 123 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 127 :
			if( tITEM_INFO2->iLevel != 126 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 130 :
			if( tITEM_INFO2->iLevel != 129 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 133 :
			if( tITEM_INFO2->iLevel != 132 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 136 :
			if( tITEM_INFO2->iLevel != 135 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 139 :
			if( tITEM_INFO2->iLevel != 138 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 142 :
			if( tITEM_INFO2->iLevel != 141 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 145 :
#ifdef __GOD__
			if( tITEM_INFO1->iMartialLevel < 1 )
			{
#endif
				if( ( tITEM_INFO2->iLevel != 144 ) && ( tITEM_INFO2->iLevel != 145 ) )
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
#ifdef __GOD__
			}
			else
			{
				if( ( tITEM_INFO2->iLevel + tITEM_INFO2->iMartialLevel ) != ( tITEM_INFO1->iLevel + tITEM_INFO1->iMartialLevel ) )
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
#endif
			break;
		}
		break;
	}
	switch( mUTIL.ReturnIUValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) )
	{
	case  0 :
		tCost = 1000000;
		tProbability = 65;
		break;
	case  1 :
		tCost = 1500000;
		tProbability = 60;
		break;
	case  2 :
		tCost = 2000000;
		tProbability = 55;
		break;
	case  3 :
		tCost = 2500000;
		tProbability = 50;
		break;
	case  4 :
		tCost = 3000000;
		tProbability = 45;
		break;
	case  5 :
		tCost = 3500000;
		tProbability = 40;
		break;
	case  6 :
		tCost = 4000000;
		tProbability = 35;
		break;
	case  7 :
		tCost = 4500000;
		tProbability = 30;
		break;
	case  8 :
		tCost = 5000000;
		tProbability = 25;
		break;
	case  9 :
		tCost = 5500000;
		tProbability = 20;
		break;
	case 10 :
		tCost = 6000000;
		tProbability = 15;
		break;
	case 11 :
		tCost = 6500000;
		tProbability = 10;
		break;
	}
	if( mUSER[tUserIndex].mAvatarInfo.aMoney < tCost )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF00) > 0) { // ... ...
		tProbability += 10; // 5% ...
		int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF;
		int iCompountValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF00) >> 8);
		int iPromotionValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF0000;
		int iTotal = iPromotionValue + ((iCompountValue - 1) << 8) + iImproveValue;
		mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 = iTotal;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2 (65, mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2);
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	}
	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	else if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF00) > 0) { // ... ...
		tProbability += 5; // 5% ...
		int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF;
		int iCompountValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF00) >> 8);
		int iPromotionValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF0000;
		int iTotal = iPromotionValue + ((iCompountValue - 1) << 8) + iImproveValue;
		mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum = iTotal;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2 (27, mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum);
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	}
	tProbability += (int) ( (float) mAVATAR_OBJECT[tUserIndex].GetLuck() / 300.0f );
	tRandom = rand_mir();
	if( ( tRandom % 100 ) < (unsigned int)tProbability )
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1 );
		mGAMELOG.GL_634_ADD_ITEM( tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost );
		mGAMELOG.GL_634_ADD_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5], tCost );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ADD_ITEM_RECV( 0, tCost );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	mGAMELOG.GL_634_ADD_ITEM( tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost );
	mTRANSFER.B_ADD_ITEM_RECV( 1, tCost );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_EXCHANGE_ITEM_SEND
void W_EXCHANGE_ITEM_SEND( int tUserIndex )
{
	unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage;
	int tIndex;
	CopyMemory( &tPage, &tPacket[1], 4 );
	CopyMemory( &tIndex, &tPacket[5], 4 );
	if( ( tPage < 0 ) || ( tPage > 1 ) || ( tIndex < 0 ) || ( tIndex > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO *tITEM_INFO1;
	ITEM_INFO *tITEM_INFO2;
	int tCost;
	int tTribeItemList[9];
	int tValue[6];

	if( tPage == 1 )
	{
		if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] );
	if( tITEM_INFO1 == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( tITEM_INFO1->iType != 3 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO1->iSort != 7 ) && ( tITEM_INFO1->iSort != 8 ) && ( tITEM_INFO1->iSort != 9 ) && ( tITEM_INFO1->iSort != 10 ) && ( tITEM_INFO1->iSort != 11 ) && ( tITEM_INFO1->iSort != 12 ) && ( tITEM_INFO1->iSort != 13 ) && ( tITEM_INFO1->iSort != 14 ) && ( tITEM_INFO1->iSort != 15 ) && ( tITEM_INFO1->iSort != 16 ) && ( tITEM_INFO1->iSort != 17 ) && ( tITEM_INFO1->iSort != 18 ) && ( tITEM_INFO1->iSort != 19 ) && ( tITEM_INFO1->iSort != 20 ) && ( tITEM_INFO1->iSort != 21 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( tITEM_INFO1->iCheckExchange != 2 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch( tITEM_INFO1->iLevel )
	{
	case  45 :
		tCost = 1000000;
		break;
	case  55 :
		tCost = 1200000;
		break;
	case  65 :
		tCost = 1400000;
		break;
	case  75 :
		tCost = 1600000;
		break;
	case  85 :
		tCost = 1800000;
		break;
	case  95 :
		tCost = 2000000;
		break;
	case 105 :
		tCost = 2200000;
		break;
	case 114 :
		tCost = 2400000;
		break;
	case 117 :
		tCost = 2600000;
		break;
	case 120 :
		tCost = 2800000;
		break;
	case 123 :
		tCost = 3000000;
		break;
	case 126 :
		tCost = 3200000;
		break;
	case 129 :
		tCost = 3400000;
		break;
	case 132 :
		tCost = 3600000;
		break;
	case 135 :
		tCost = 3800000;
		break;
	case 138 :
		tCost = 4000000;
		break;
	case 141 :
		tCost = 4200000;
		break;
	case 144 :
		tCost = 4400000;
		break;
	case 145 :
#ifdef __GOD__
		switch( tITEM_INFO1->iMartialLevel )
			{
				case  0 :
#endif
					tCost = 4600000;
					break;
#ifdef __GOD__
				case  1 :
					tCost = 4800000;
					break;
				case  2 :
					tCost = 5000000;
					break;
				case  3 :
					tCost = 5200000;
					break;
				case  4 :
					tCost = 5400000;
					break;
				case  5 :
					tCost = 5600000;
					break;
				case  6 :
					tCost = 5800000;
					break;
				case  7 :
					tCost = 6000000;
					break;
				case  8 :
					tCost = 6200000;
					break;
				case  9 :
					tCost = 6400000;
					break;
				case 10 :
					tCost = 6600000;
					break;
				case 11 :
					tCost = 6800000;
					break;
				case 12 :
					tCost = 7000000;
					break;
			}
			break;
#endif
	}
	if( mUSER[tUserIndex].mAvatarInfo.aMoney < tCost )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch( mUSER[tUserIndex].mAvatarInfo.aPreviousTribe )
	{
	case 0 :
		tTribeItemList[0] =  7;
		tTribeItemList[1] =  8;
		tTribeItemList[2] =  9;
		tTribeItemList[3] = 10;
		tTribeItemList[4] = 11;
		tTribeItemList[5] = 12;
		tTribeItemList[6] = 13;
		tTribeItemList[7] = 14;
		tTribeItemList[8] = 15;
		break;
	case 1 :
		tTribeItemList[0] =  7;
		tTribeItemList[1] =  8;
		tTribeItemList[2] =  9;
		tTribeItemList[3] = 10;
		tTribeItemList[4] = 11;
		tTribeItemList[5] = 12;
		tTribeItemList[6] = 16;
		tTribeItemList[7] = 17;
		tTribeItemList[8] = 18;
		break;
	case 2 :
		tTribeItemList[0] =  7;
		tTribeItemList[1] =  8;
		tTribeItemList[2] =  9;
		tTribeItemList[3] = 10;
		tTribeItemList[4] = 11;
		tTribeItemList[5] = 12;
		tTribeItemList[6] = 19;
		tTribeItemList[7] = 20;
		tTribeItemList[8] = 21;
		break;
	}
	tRandom = rand_mir();
#ifdef __GOD__
	tITEM_INFO2 = mITEM.Return( ( tITEM_INFO1->iLevel + tITEM_INFO1->iMartialLevel ), tITEM_INFO1->iType, tTribeItemList[( rand() % 9 )], tITEM_INFO1 );
#else
	tITEM_INFO2 = mITEM.Return( tITEM_INFO1->iLevel, tITEM_INFO1->iType, tTribeItemList[( tRandom % 9 )], tITEM_INFO1 );
#endif
	
	if( ( tITEM_INFO2 == NULL ) || ( tITEM_INFO2->iIndex == tITEM_INFO1->iIndex ) )
	{
		mGAMELOG.GL_637_EXCHANGE_ITEM( tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tCost );
		mTRANSFER.B_EXCHANGE_ITEM_RECV( 1, tCost, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	tValue[0] = tITEM_INFO2->iIndex;
	tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1];
	tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2];
	tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
	tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
	tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
	mGAMELOG.GL_637_EXCHANGE_ITEM( tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tCost );
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tValue[5];
	mGAMELOG.GL_637_EXCHANGE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tCost );
	mTRANSFER.B_EXCHANGE_ITEM_RECV( 0, tCost, &tValue[0] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_HIGH_ITEM_SEND
void W_HIGH_ITEM_SEND( int tUserIndex )
{
	unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory( &tPage1, &tPacket[1], 4 );
	CopyMemory( &tIndex1, &tPacket[5], 4 );
	CopyMemory( &tPage2, &tPacket[9], 4 );
	CopyMemory( &tIndex2, &tPacket[13], 4 );
	if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO *tITEM_INFO1;
	ITEM_INFO *tITEM_INFO2;
	ITEM_INFO *tITEM_INFO3;
	int tCost;
	int tItemLevel;
	int tProbability;
	int tValue[6];

	if( ( tPage1 == 1 ) || ( tPage2 == 1 ) )
	{
		if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] );
	if( tITEM_INFO1 == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO1->iType != 3 ) && ( tITEM_INFO1->iType != 4 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO1->iSort != 7 ) && ( tITEM_INFO1->iSort != 8 ) && ( tITEM_INFO1->iSort != 9 ) && ( tITEM_INFO1->iSort != 10 ) && ( tITEM_INFO1->iSort != 11 ) && ( tITEM_INFO1->iSort != 12 ) && ( tITEM_INFO1->iSort != 13 ) && ( tITEM_INFO1->iSort != 14 ) && ( tITEM_INFO1->iSort != 15 ) && ( tITEM_INFO1->iSort != 16 ) && ( tITEM_INFO1->iSort != 17 ) && ( tITEM_INFO1->iSort != 18 ) && ( tITEM_INFO1->iSort != 19 ) && ( tITEM_INFO1->iSort != 20 ) && ( tITEM_INFO1->iSort != 21 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( tITEM_INFO1->iCheckHighItem != 2 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	
	//geridon
	if( ( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) < 40 ) || ( mUTIL.ReturnIUValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) < 1 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#ifdef __GOD__
	if( tITEM_INFO1->iMartialLevel >= 12 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#else
	switch( tITEM_INFO1->iType )
	{
	case 3 :
		if( tITEM_INFO1->iLevel >= 145 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 4 :
		if( tITEM_INFO1->iLevel >= 145 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}
#endif
	tITEM_INFO2 = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] );
	if( tITEM_INFO2 == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO2->iIndex != 1024 ) && ( tITEM_INFO2->iIndex != 1025 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch( tITEM_INFO1->iType )
	{
	case 3 :
		switch( tITEM_INFO1->iLevel )
		{
		case  45 :
			tCost = 100000;
			tItemLevel = 55;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 520;
			}
			else
			{
				tProbability = 570;
			}
			break;
		case  55 :
			tCost = 200000;
			tItemLevel = 65;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 490;
			}
			else
			{
				tProbability = 540;
			}
			break;
		case  65 :
			tCost = 300000;
			tItemLevel = 75;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 460;
			}
			else
			{
				tProbability = 510;
			}
			break;
		case  75 :
			tCost = 400000;
			tItemLevel = 85;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 430;
			}
			else
			{
				tProbability = 480;
			}
			break;
		case  85 :
			tCost = 500000;
			tItemLevel = 95;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 400;
			}
			else
			{
				tProbability = 450;
			}
			break;
		case  95 :
			tCost = 600000;
			tItemLevel = 105;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 370;
			}
			else
			{
				tProbability = 420;
			}
			break;
		case 105 :
			tCost = 700000;
			tItemLevel = 114;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 340;
			}
			else
			{
				tProbability = 390;
			}
			break;
		case 114 :
			tCost = 800000;
			tItemLevel = 117;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 310;
			}
			else
			{
				tProbability = 360;
			}
			break;
		case 117 :
			tCost = 900000;
			tItemLevel = 120;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 280;
			}
			else
			{
				tProbability = 330;
			}
			break;
		case 120 :
			tCost = 1000000;
			tItemLevel = 123;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 250;
			}
			else
			{
				tProbability = 300;
			}
			break;
		case 123 :
			tCost = 1100000;
			tItemLevel = 126;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 220;
			}
			else
			{
				tProbability = 270;
			}
			break;
		case 126 :
			tCost = 1200000;
			tItemLevel = 129;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 190;
			}
			else
			{
				tProbability = 240;
			}
			break;
		case 129 :
			tCost = 1300000;
			tItemLevel = 132;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 160;
			}
			else
			{
				tProbability = 210;
			}
			break;
		case 132 :
			tCost = 1400000;
			tItemLevel = 135;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 130;
			}
			else
			{
				tProbability = 180;
			}
			break;
		case 135 :
			tCost = 1500000;
			tItemLevel = 138;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 100;
			}
			else
			{
				tProbability = 150;
			}
			break;
		case 138 :
			tCost = 1600000;
			tItemLevel = 141;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 70;
			}
			else
			{
				tProbability = 120;
			}
			break;
		case 141 :
			tCost = 1700000;
			tItemLevel = 144;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 40;
			}
			else
			{
				tProbability = 90;
			}
			break;
		case 144 :
			tCost = 1800000;
			tItemLevel = 145;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 10;
			}
			else
			{
				tProbability = 60;
			}
			break;
#ifdef __GOD__
		case 145 :
			switch( tITEM_INFO1->iMartialLevel )
			{
				case  0 :
					tCost = 1900000;
					tItemLevel = 146;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case  1 :
					tCost = 2000000;
					tItemLevel = 147;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case  2 :
					tCost = 2100000;
					tItemLevel = 148;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case  3 :
					tCost = 2200000;
					tItemLevel = 149;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case  4 :
					tCost = 2300000;
					tItemLevel = 150;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case  5 :
					tCost = 2400000;
					tItemLevel = 151;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case  6 :
					tCost = 2500000;
					tItemLevel = 152;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case  7 :
					tCost = 2600000;
					tItemLevel = 153;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case  8 :
					tCost = 2700000;
					tItemLevel = 154;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case  9 :
					tCost = 2800000;
					tItemLevel = 155;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case 10 :
					tCost = 2900000;
					tItemLevel = 156;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
				case 11 :
					tCost = 3000000;
					tItemLevel = 157;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 10;
					}
					else
					{
						tProbability = 20;
					}
					break;
			}
			break;
#endif
		}
		break;
	case 4 :
		switch( tITEM_INFO1->iLevel )
		{
		case 100 :
			tCost = 1000000;
			tItemLevel = 110;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 340;
			}
			else
			{
				tProbability = 390;
			}
			break;
		case 110 :
			tCost = 2000000;
			tItemLevel = 115;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 310;
			}
			else
			{
				tProbability = 360;
			}
			break;
		case 115 :
			tCost = 3000000;
			tItemLevel = 118;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 280;
			}
			else
			{
				tProbability = 330;
			}
			break;
		case 118 :
			tCost = 4000000;
			tItemLevel = 121;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 250;
			}
			else
			{
				tProbability = 300;
			}
			break;
		case 121 :
			tCost = 5000000;
			tItemLevel = 124;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 220;
			}
			else
			{
				tProbability = 270;
			}
			break;
		case 124 :
			tCost = 6000000;
			tItemLevel = 127;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 190;
			}
			else
			{
				tProbability = 240;
			}
			break;
		case 127 :
			tCost = 7000000;
			tItemLevel = 130;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 160;
			}
			else
			{
				tProbability = 210;
			}
			break;
		case 130 :
			tCost = 8000000;
			tItemLevel = 133;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 130;
			}
			else
			{
				tProbability = 180;
			}
			break;
		case 133 :
			tCost = 9000000;
			tItemLevel = 136;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 100;
			}
			else
			{
				tProbability = 150;
			}
			break;
		case 136 :
			tCost = 10000000;
			tItemLevel = 139;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 70;
			}
			else
			{
				tProbability = 120;
			}
			break;
		case 139 :
			tCost = 11000000;
			tItemLevel = 142;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 40;
			}
			else
			{
				tProbability = 90;
			}
			break;
		case 142 :
			tCost = 12000000;
			tItemLevel = 145;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 1;
			}
			else
			{
				tProbability = 1;
			}
			break;
#ifdef __GOD__
		case 145 :
			switch( tITEM_INFO1->iMartialLevel )
			{
				
				//upgrade_oranlar©¥
				case  0 :
					tCost = 13000000;
					tItemLevel = 146;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  1 :
					tCost = 14000000;
					tItemLevel = 147;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  2 :
					tCost = 15000000;
					tItemLevel = 148;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  3 :
					tCost = 16000000;
					tItemLevel = 149;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  4 :
					tCost = 17000000;
					tItemLevel = 150;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 1;
					}
					break;
				case  5 :
					tCost = 18000000;
					tItemLevel = 151;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 2;
					}
					else
					{
						tProbability = 4;
					}
					break;
				case  6 :
					tCost = 19000000;
					tItemLevel = 152;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 2;
					}
					else
					{
						tProbability = 4;
					}
					break;
				case  7 :
					tCost = 20000000;
					tItemLevel = 153;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 2;
					}
					else
					{
						tProbability = 4;
					}
					break;
				case  8 :
					tCost = 21000000;
					tItemLevel = 154;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 2;
					}
					else
					{
						tProbability = 4;
					}
					break;
				case  9 :
					tCost = 22000000;
					tItemLevel = 155;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 2;
					}
					else
					{
						tProbability = 4;
					}
					break;
				case 10 :
					tCost = 23000000;
					tItemLevel = 156;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 2;
					}
					else
					{
						tProbability = 4;
					}
					break;
				case 11 :
					tCost = 24000000;
					tItemLevel = 157;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 2;
					}
					else
					{
						tProbability = 4;
					}
					break;
			}
			break;
#endif
		}
		break;
	}
	if( mUSER[tUserIndex].mAvatarInfo.aMoney < tCost )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF0000) > 0) { // ... ...
		//2010.1.18 : ±è¼º¼ö : ½Â±Þ È®·ü ¸Â°Ô ¼öÁ¤ (100 -> 1000À¸·Î º¯°æ¿¡ µû¸£ ¼öÄ¡ º¯°æ) __GOD__
		tProbability += 100; // 10% Upgrade Talisman
		int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF;
		int iCompountValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF00;
		int iPromotionValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF0000) >> 16);
		int iTotal = ((iPromotionValue - 1) << 16) + iCompountValue + iImproveValue;
		mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 = iTotal;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2 (66, mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2);
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	}
	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	else if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF0000) > 0) { // ... ...
		//2010.1.18 : ±è¼º¼ö : ½Â±Þ È®·ü ¸Â°Ô ¼öÁ¤ (100 -> 1000À¸·Î º¯°æ¿¡ µû¸£ ¼öÄ¡ º¯°æ) __GOD__
		tProbability += 50; // 5% Upgrade Talisman
		int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF;
		int iCompountValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF00;
		int iPromotionValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF0000) >> 16);
		int iTotal = ((iPromotionValue - 1) << 16) + iCompountValue + iImproveValue;
		mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum = iTotal;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2 (28, mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum);
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	}
#ifdef __GOD__
	tITEM_INFO3 = mITEM.Return_1( tItemLevel, tITEM_INFO1 );
#else
	tITEM_INFO3 = mITEM.Return( tItemLevel, tITEM_INFO1 );
#endif
	if( tITEM_INFO3 == NULL )
	{
		mGAMELOG.GL_635_HIGH_ITEM( tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex );
		mTRANSFER.B_HIGH_ITEM_RECV( 2, tCost, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tProbability += (int) ( (float) mAVATAR_OBJECT[tUserIndex].GetLuck() / 300.0f );
#ifdef __GOD__
	if( mUSER[tUserIndex].mAvatarInfo.aHighItemValue > 0 )
	{
		mUSER[tUserIndex].mAvatarInfo.aHighItemValue--;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2( 29, mUSER[tUserIndex].mAvatarInfo.aHighItemValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mGAMELOG.GL_635_HIGH_ITEM( tUserIndex, 4, 0, 0, 0, 0, 0, 0 );
		tProbability += 50;
	}
#endif	
	tRandom = rand_mir();
	//2010.1.18 : ±è¼º¼ö : ½Â±Þ È®·ü ¸Â°Ô ¼öÁ¤ (100 -> 1000À¸·Î º¯°æ¿¡ µû¸£ ¼öÄ¡ º¯°æ) __GOD__
	if( ( tRandom % 1000 ) < (unsigned int)tProbability )
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = tITEM_INFO3->iIndex;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		tValue[4] = mUTIL.SetISIUValue( ( mUTIL.ReturnISValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) - 40 ), ( mUTIL.ReturnIUValue( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] ) - 1 ) ); //Yukseltmedeki dusus oranı
		tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		mGAMELOG.GL_635_HIGH_ITEM( tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mGAMELOG.GL_635_HIGH_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_HIGH_ITEM_RECV( 0, tCost, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	mGAMELOG.GL_635_HIGH_ITEM( tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex );
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mTRANSFER.B_HIGH_ITEM_RECV( 1, tCost, &tValue[0] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_LOW_ITEM_SEND
void W_LOW_ITEM_SEND( int tUserIndex )
{
	unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory( &tPage1, &tPacket[1], 4 );
	CopyMemory( &tIndex1, &tPacket[5], 4 );
	CopyMemory( &tPage2, &tPacket[9], 4 );
	CopyMemory( &tIndex2, &tPacket[13], 4 );
	if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO *tITEM_INFO1;
	ITEM_INFO *tITEM_INFO2;
	ITEM_INFO *tITEM_INFO3;
	int tCost;
	int tItemLevel;
	int tProbability;
	int tValue[6];

	if( ( tPage1 == 1 ) || ( tPage2 == 1 ) )
	{
		if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] );
	if( tITEM_INFO1 == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO1->iType != 3 ) && ( tITEM_INFO1->iType != 4 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO1->iSort != 7 ) && ( tITEM_INFO1->iSort != 8 ) && ( tITEM_INFO1->iSort != 9 ) && ( tITEM_INFO1->iSort != 10 ) && ( tITEM_INFO1->iSort != 11 ) && ( tITEM_INFO1->iSort != 12 ) && ( tITEM_INFO1->iSort != 13 ) && ( tITEM_INFO1->iSort != 14 ) && ( tITEM_INFO1->iSort != 15 ) && ( tITEM_INFO1->iSort != 16 ) && ( tITEM_INFO1->iSort != 17 ) && ( tITEM_INFO1->iSort != 18 ) && ( tITEM_INFO1->iSort != 19 ) && ( tITEM_INFO1->iSort != 20 ) && ( tITEM_INFO1->iSort != 21 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( tITEM_INFO1->iCheckLowItem != 2 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch( tITEM_INFO1->iType )
	{
	case 3 :
		if( tITEM_INFO1->iLevel <= 45 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 4 :
		if( tITEM_INFO1->iLevel <= 100 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}
	tITEM_INFO2 = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] );
	if( tITEM_INFO2 == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( tITEM_INFO2->iIndex != 1024 ) && ( tITEM_INFO2->iIndex != 1025 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch( tITEM_INFO1->iType )
	{
	case 3 :
		switch( tITEM_INFO1->iLevel )
		{
		case  55 :
			tCost = 100000;
			tItemLevel = 45;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 52;
			}
			else
			{
				tProbability = 57;
			}
			break;
		case  65 :
			tCost = 200000;
			tItemLevel = 55;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 49;
			}
			else
			{
				tProbability = 54;
			}
			break;
		case  75 :
			tCost = 300000;
			tItemLevel = 65;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 46;
			}
			else
			{
				tProbability = 51;
			}
			break;
		case  85 :
			tCost = 400000;
			tItemLevel = 75;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 43;
			}
			else
			{
				tProbability = 48;
			}
			break;
		case  95 :
			tCost = 500000;
			tItemLevel = 85;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 40;
			}
			else
			{
				tProbability = 45;
			}
			break;
		case 105 :
			tCost = 600000;
			tItemLevel = 95;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 37;
			}
			else
			{
				tProbability = 42;
			}
			break;
		case 114 :
			tCost = 700000;
			tItemLevel = 105;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 34;
			}
			else
			{
				tProbability = 39;
			}
			break;
		case 117 :
			tCost = 800000;
			tItemLevel = 114;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 31;
			}
			else
			{
				tProbability = 36;
			}
			break;
		case 120 :
			tCost = 900000;
			tItemLevel = 117;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 28;
			}
			else
			{
				tProbability = 33;
			}
			break;
		case 123 :
			tCost = 1000000;
			tItemLevel = 120;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 25;
			}
			else
			{
				tProbability = 30;
			}
			break;
		case 126 :
			tCost = 1100000;
			tItemLevel = 123;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 22;
			}
			else
			{
				tProbability = 27;
			}
			break;
		case 129 :
			tCost = 1200000;
			tItemLevel = 126;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 19;
			}
			else
			{
				tProbability = 24;
			}
			break;
		case 132 :
			tCost = 1300000;
			tItemLevel = 129;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 16;
			}
			else
			{
				tProbability = 21;
			}
			break;
		case 135 :
			tCost = 1400000;
			tItemLevel = 132;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 13;
			}
			else
			{
				tProbability = 18;
			}
			break;
		case 138 :
			tCost = 1500000;
			tItemLevel = 135;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 10;
			}
			else
			{
				tProbability = 15;
			}
			break;
		case 141 :
			tCost = 1600000;
			tItemLevel = 138;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 7;
			}
			else
			{
				tProbability = 12;
			}
			break;
		case 144 :
			tCost = 1700000;
			tItemLevel = 141;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 4;
			}
			else
			{
				tProbability = 9;
			}
			break;
		case 145 :
#ifdef __GOD__
			switch( tITEM_INFO1->iMartialLevel )
			{
				case  0 :
#endif
				tCost = 1800000;
				tItemLevel = 144;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 6;
				}
				break;
#ifdef __GOD__
			case  1 :
				tCost = 1900000;
				tItemLevel = 145;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  2 :
				tCost = 2000000;
				tItemLevel = 146;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  3 :
				tCost = 2100000;
				tItemLevel = 147;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  4 :
				tCost = 2200000;
				tItemLevel = 148;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  5 :
				tCost = 2300000;
				tItemLevel = 149;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  6 :
				tCost = 2400000;
				tItemLevel = 150;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  7 :
				tCost = 2500000;
				tItemLevel = 151;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  8 :
				tCost = 2600000;
				tItemLevel = 152;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  9 :
				tCost = 2700000;
				tItemLevel = 153;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 10 :
				tCost = 2800000;
				tItemLevel = 154;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 11 :
				tCost = 2900000;
				tItemLevel = 155;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 12 :
				tCost = 3000000;
				tItemLevel = 156;
				if( tITEM_INFO2->iIndex == 1024 )
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
		}
		break;
#endif
		}
		break;
	case 4 :
		switch( tITEM_INFO1->iLevel )
		{
		case 110 :
			tCost = 1000000;
			tItemLevel = 100;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 34;
			}
			else
			{
				tProbability = 39;
			}
			break;
		case 115 :
			tCost = 2000000;
			tItemLevel = 110;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 31;
			}
			else
			{
				tProbability = 36;
			}
			break;
		case 118 :
			tCost = 3000000;
			tItemLevel = 115;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 28;
			}
			else
			{
				tProbability = 33;
			}
			break;
		case 121 :
			tCost = 4000000;
			tItemLevel = 118;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 25;
			}
			else
			{
				tProbability = 30;
			}
			break;
		case 124 :
			tCost = 5000000;
			tItemLevel = 121;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 22;
			}
			else
			{
				tProbability = 27;
			}
			break;
		case 127 :
			tCost = 6000000;
			tItemLevel = 124;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 19;
			}
			else
			{
				tProbability = 24;
			}
			break;
		case 130 :
			tCost = 7000000;
			tItemLevel = 127;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 16;
			}
			else
			{
				tProbability = 21;
			}
			break;
		case 133 :
			tCost = 8000000;
			tItemLevel = 130;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 13;
			}
			else
			{
				tProbability = 18;
			}
			break;
		case 136 :
			tCost = 9000000;
			tItemLevel = 133;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 10;
			}
			else
			{
				tProbability = 15;
			}
			break;
		case 139 :
			tCost = 10000000;
			tItemLevel = 136;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 7;
			}
			else
			{
				tProbability = 12;
			}
			break;
		case 142 :
			tCost = 11000000;
			tItemLevel = 139;
			if( tITEM_INFO2->iIndex == 1024 )
			{
				tProbability = 4;
			}
			else
			{
				tProbability = 9;
			}
			break;
		case 145 :
#ifdef __GOD__
			switch( tITEM_INFO1->iMartialLevel )
			{
				case  0 :
#endif
					tCost = 12000000;
					tItemLevel = 142;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 6;
					}
					break;
#ifdef __GOD__
				case  1 :
					tCost = 13000000;
					tItemLevel = 145;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  2 :
					tCost = 14000000;
					tItemLevel = 146;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  3 :
					tCost = 15000000;
					tItemLevel = 147;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  4 :
					tCost = 16000000;
					tItemLevel = 148;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  5 :
					tCost = 17000000;
					tItemLevel = 149;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  6 :
					tCost = 18000000;
					tItemLevel = 150;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  7 :
					tCost = 19000000;
					tItemLevel = 151;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  8 :
					tCost = 20000000;
					tItemLevel = 152;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case  9 :
					tCost = 21000000;
					tItemLevel = 153;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case 10 :
					tCost = 22000000;
					tItemLevel = 154;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case 11 :
					tCost = 23000000;
					tItemLevel = 155;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
				case 12 :
					tCost = 24000000;
					tItemLevel = 156;
					if( tITEM_INFO2->iIndex == 1024 )
					{
						tProbability = 1;
					}
					else
					{
						tProbability = 2;
					}
					break;
			}
			break;
#endif
		}
		break;
	}
	if( mUSER[tUserIndex].mAvatarInfo.aMoney < tCost )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF0000) > 0) { // ... ...
		tProbability += 10; // 5% ...
		int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF;
		int iCompountValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF00;
		int iPromotionValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 & 0xFF0000) >> 16);
		int iTotal = ((iPromotionValue - 1) << 16) + iCompountValue + iImproveValue;
		mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2 = iTotal;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2 (66, mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum2);
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	}
	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	else if ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF0000) > 0) { // ... ...
		tProbability += 5; // 5% ...
		int iImproveValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF;
		int iCompountValue = mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF00;
		int iPromotionValue = ((mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum & 0xFF0000) >> 16);
		int iTotal = ((iPromotionValue - 1) << 16) + iCompountValue + iImproveValue;
		mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum = iTotal;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2 (28, mUSER[tUserIndex].mAvatarInfo.aLevelZoneKeyNum);
		mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	}
#ifdef __GOD__
	tITEM_INFO3 = mITEM.Return_2( tItemLevel, tITEM_INFO1 );
#else
	tITEM_INFO3 = mITEM.Return( tItemLevel, tITEM_INFO1 );
#endif
	if( tITEM_INFO3 == NULL )
	{
		mGAMELOG.GL_636_LOW_ITEM( tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex );
		mTRANSFER.B_LOW_ITEM_RECV( 2, tCost, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tProbability += (int) ( (float) mAVATAR_OBJECT[tUserIndex].GetLuck() / 300.0f );
	tRandom = rand_mir();
	if( ( tRandom % 100 ) < (unsigned int)tProbability )
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = tITEM_INFO3->iIndex;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		mGAMELOG.GL_636_LOW_ITEM( tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mGAMELOG.GL_636_LOW_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_LOW_ITEM_RECV( 0, tCost, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	mGAMELOG.GL_636_LOW_ITEM( tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex );
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mTRANSFER.B_LOW_ITEM_RECV( 1, tCost, &tValue[0] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_MAKE_ITEM_SEND
void W_MAKE_ITEM_SEND( int tUserIndex )
{
	unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tPage1, &tPacket[5], 4 );
	CopyMemory( &tIndex1, &tPacket[9], 4 );
	CopyMemory( &tPage2, &tPacket[13], 4 );
	CopyMemory( &tIndex2, &tPacket[17], 4 );
	CopyMemory( &tPage3, &tPacket[21], 4 );
	CopyMemory( &tIndex3, &tPacket[25], 4 );
	CopyMemory( &tPage4, &tPacket[29], 4 );
	CopyMemory( &tIndex4, &tPacket[33], 4 );

	int tRandomNumber;
	int tValue[6];

	switch( tSort )
	{
	case  0 : //[ÁÖ¼®]+[ÁÖ¼®]+[ÁÖ¼®]+[ÁÖ¼®] -> [(?)°­È­¼®]
		if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage3 < 0 ) || ( tPage3 > 1 ) || ( tIndex3 < 0 ) || ( tIndex3 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage4 < 0 ) || ( tPage4 > 1 ) || ( tIndex4 < 0 ) || ( tIndex4 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( ( tPage1 == 1 ) || ( tPage2 == 1 ) || ( tPage3 == 1 ) || ( tPage4 == 1 ) )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if( ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1088 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1089 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1090 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1091 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandom = rand_mir();
		switch( ( tRandom % 4 ) )
		{
		case 0 :
			tValue[0] = 1414;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber( 0 );
			break;
		case 1 :
			tValue[0] = 1414;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber( 0 );
			break;
		case 2 :
			tValue[0] = 1414;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber( 0 );
			break;
		case 3 :
			tValue[0] = 1414;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber( 0 );
			break;
		}
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_ITEM_RECV( 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  1 : //[ÀÚ¿Á¼º¼®]+[ÀÚ¿Á¼º¼®] -> [Àû¸í¿Á¼®]
	if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage3 < 0 ) || ( tPage3 > 1 ) || ( tIndex3 < 0 ) || ( tIndex3 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage4 < 0 ) || ( tPage4 > 1 ) || ( tIndex4 < 0 ) || ( tIndex4 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( ( tPage1 == 1 ) || ( tPage2 == 1 ) || ( tPage3 == 1 ) || ( tPage4 == 1 ) )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if( ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1401 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1401 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1401 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1401 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		
		tValue[0] = 1403;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = mUTIL.ReturnItemRecognitionNumber( 0 );
		
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_ITEM_RECV( 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  2 : //[µ¿]+[µ¿]+[µ¿]+[µ¿] -> [Àº]
		if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage3 < 0 ) || ( tPage3 > 1 ) || ( tIndex3 < 0 ) || ( tIndex3 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage4 < 0 ) || ( tPage4 > 1 ) || ( tIndex4 < 0 ) || ( tIndex4 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( ( tPage1 == 1 ) || ( tPage2 == 1 ) || ( tPage3 == 1 ) || ( tPage4 == 1 ) )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if( ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1211 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1211 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1211 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1210 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = 1212;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = 0;
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_ITEM_RECV( 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  3 : //[Àº]+[Àº]+[Àº]+[Àº] -> [±Ý]
		if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage3 < 0 ) || ( tPage3 > 1 ) || ( tIndex3 < 0 ) || ( tIndex3 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage4 < 0 ) || ( tPage4 > 1 ) || ( tIndex4 < 0 ) || ( tIndex4 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( ( tPage1 == 1 ) || ( tPage2 == 1 ) || ( tPage3 == 1 ) || ( tPage4 == 1 ) )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if( ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1212 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1212 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1212 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1212 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = 1213;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = 0;
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_ITEM_RECV( 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  4 : //[±Ý]+[±Ý]+[±Ý]+[±Ý] -> [?]
		if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage3 < 0 ) || ( tPage3 > 1 ) || ( tIndex3 < 0 ) || ( tIndex3 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage4 < 0 ) || ( tPage4 > 1 ) || ( tIndex4 < 0 ) || ( tIndex4 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( ( tPage1 == 1 ) || ( tPage2 == 1 ) || ( tPage3 == 1 ) || ( tPage4 == 1 ) )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if( ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1213 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1213 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1213 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1213 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandomNumber = rand_mir() % 100;
		if( tRandomNumber < 53 )
		{
			tValue[0] = 1087;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
		}
		else if( tRandomNumber < 93 )
		{
			tValue[0] = 1087;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
		}
		else if( tRandomNumber < 98 )
		{
			tValue[0] = 1087;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
		}
		else
		{
			tValue[0] = 1087;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
		}
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] );
		mGAMELOG.GL_638_MAKE_ITEM( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_ITEM_RECV( 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	default :
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_MAKE_SKILL_SEND
void W_MAKE_SKILL_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tPage1, &tPacket[5], 4 );
	CopyMemory( &tIndex1, &tPacket[9], 4 );
	CopyMemory( &tPage2, &tPacket[13], 4 );
	CopyMemory( &tIndex2, &tPacket[17], 4 );
	CopyMemory( &tPage3, &tPacket[21], 4 );
	CopyMemory( &tIndex3, &tPacket[25], 4 );
	CopyMemory( &tPage4, &tPacket[29], 4 );
	CopyMemory( &tIndex4, &tPacket[33], 4 );

	int tValue[6];

	switch( tSort )
	{
	case 0 : //[È­·æ°á]+[³ú½Å°á]+[º®·É°á]+[ÅÂ¾ç°á]->[´ë±Ø¹æÅº¼¼]
		if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage3 < 0 ) || ( tPage3 > 1 ) || ( tIndex3 < 0 ) || ( tIndex3 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage4 < 0 ) || ( tPage4 > 1 ) || ( tIndex4 < 0 ) || ( tIndex4 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( ( tPage1 == 1 ) || ( tPage2 == 1 ) || ( tPage3 == 1 ) || ( tPage4 == 1 ) )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if( ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1054 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1055 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1056 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1057 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = 90567;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = mUTIL.ReturnItemRecognitionNumber( 0 );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_SKILL_RECV( 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 1 : //[¼³¿ÕÀü±â]+[ºÏÇ³Àü±â]+[»ç½ÅÀü±â]+[¿ù¶ûÀü±â]->[Ãµ¹®¿ª±Ù°ø]
		if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage3 < 0 ) || ( tPage3 > 1 ) || ( tIndex3 < 0 ) || ( tIndex3 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage4 < 0 ) || ( tPage4 > 1 ) || ( tIndex4 < 0 ) || ( tIndex4 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( ( tPage1 == 1 ) || ( tPage2 == 1 ) || ( tPage3 == 1 ) || ( tPage4 == 1 ) )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if( ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1058 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1059 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1060 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1061 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = 90568;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = mUTIL.ReturnItemRecognitionNumber( 0 );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_SKILL_RECV( 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 2 : //[Ç÷Ãµ·Ï]+[±Í¹®·Ï]+[ÁÖ°æ·Ï]+[¸¶½Å·Ï]->[Å»¸Á¼ÒÈ¥¿ª]
		if( ( tPage1 < 0 ) || ( tPage1 > 1 ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage3 < 0 ) || ( tPage3 > 1 ) || ( tIndex3 < 0 ) || ( tIndex3 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPage4 < 0 ) || ( tPage4 > 1 ) || ( tIndex4 < 0 ) || ( tIndex4 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( ( tPage1 == 1 ) || ( tPage2 == 1 ) || ( tPage3 == 1 ) || ( tPage4 == 1 ) )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if( ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1062 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1063 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1064 ) || ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1065 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = 90569;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = mUTIL.ReturnItemRecognitionNumber( 0 );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] );
		mGAMELOG.GL_639_MAKE_SKILL( tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_SKILL_RECV( 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	default :
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_START_PSHOP_SEND
void W_START_PSHOP_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if(124 == mSERVER_INFO.mServerNumber)
		return;

	PSHOP_INFO tPShopInfo;
	CopyMemory( &tPShopInfo, &tPacket[1], sizeof( PSHOP_INFO ) );
	
	if(1 == mUSER[tUserIndex].mAuthInfo.PShopFlag){
		mTRANSFER.B_START_PSHOP_RECV( 1, &tPShopInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}

	int index01;
	int index02;
	ITEM_INFO *tITEM_INFO;

	if( mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( !mWORK.CheckPossiblePShopRegion( mUSER[tUserIndex].mAvatarInfo.aTribe, mSERVER_INFO.mServerNumber, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( strcmp( tPShopInfo.mName, "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for( index01 = 0 ; index01 < MAX_PSHOP_PAGE_NUM ; index01++ )
	{
		for( index02 = 0 ; index02 < MAX_PSHOP_SLOT_NUM ; index02++ )
		{
			if( tPShopInfo.mItemInfo[index01][index02][0] > 0 )
			{
				break;
			}
		}
		if( index02 < MAX_PSHOP_SLOT_NUM )
		{
			break;
		}
	}
	if( index01 == MAX_PSHOP_PAGE_NUM )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for( index01 = 0 ; index01 < MAX_PSHOP_PAGE_NUM ; index01++ )
	{
		for( index02 = 0 ; index02 < MAX_PSHOP_SLOT_NUM ; index02++ )
		{
			if( tPShopInfo.mItemInfo[index01][index02][0] < 1 )
			{
				continue;
			}
			tITEM_INFO = mITEM.Search( tPShopInfo.mItemInfo[index01][index02][0] );
			if( tITEM_INFO == NULL )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( tITEM_INFO->iCheckAvatarShop == 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( ( tPShopInfo.mItemInfo[index01][index02][5] < 0 ) || ( tPShopInfo.mItemInfo[index01][index02][5] > 1 ) || ( tPShopInfo.mItemInfo[index01][index02][6] < 0 ) || ( tPShopInfo.mItemInfo[index01][index02][6] > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tPShopInfo.mItemInfo[index01][index02][7] < 0 ) || ( tPShopInfo.mItemInfo[index01][index02][7] > 7 ) || ( tPShopInfo.mItemInfo[index01][index02][8] < 0 ) || ( tPShopInfo.mItemInfo[index01][index02][8] > 7 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( tPShopInfo.mItemInfo[index01][index02][5] == 1 )
			{
				if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if( ( tPShopInfo.mItemInfo[index01][index02][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][0] ) || ( tPShopInfo.mItemInfo[index01][index02][1] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][3] ) || ( tPShopInfo.mItemInfo[index01][index02][2] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][4] ) || ( tPShopInfo.mItemInfo[index01][index02][3] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][5] ) || ( tPShopInfo.mItemInfo[index01][index02][7] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][1] ) || ( tPShopInfo.mItemInfo[index01][index02][8] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][2] ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( ( tPShopInfo.mItemInfo[index01][index02][4] < 1 ) || ( tPShopInfo.mItemInfo[index01][index02][4] > 999999999 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
	}
	mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState = 1;
	strncpy( mAVATAR_OBJECT[tUserIndex].mDATA.aPShopName, tPShopInfo.mName, MAX_PSHOP_NAME_LENGTH );
	CopyMemory( &mAVATAR_OBJECT[tUserIndex].mPShopInfo, &tPShopInfo, sizeof( PSHOP_INFO ) );
	mAVATAR_OBJECT[tUserIndex].mPShopInfo.mUniqueNumber = mGAME.mAvatarPShopUniqueNumber;
	mGAME.mAvatarPShopUniqueNumber++;
	mTRANSFER.B_START_PSHOP_RECV( 0, &tPShopInfo );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//CHECK_POSSIBLE_PSHOP_REGION
BOOL MyWork::CheckPossiblePShopRegion( int tTribe, int tZoneNumber, float tCoord[3] )
{
	float tCenter[3];
	float tRadius;

	switch( tZoneNumber )
	{
	case   1 :
		if( tTribe != 0 )
		{
			return FALSE;
		}
		tCenter[0] = 4.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = -2.0f;
		tRadius = 1000.0f;
		if( mUTIL.GetLengthXYZ( &tCoord[0], &tCenter[0] ) < tRadius )
		{
			return TRUE;
		}
		return FALSE;
	case   6 :
		if( tTribe != 1 )
		{
			return FALSE;
		}
		tCenter[0] = -189.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = 1150.0f;
		tRadius = 1000.0f;
		if( mUTIL.GetLengthXYZ( &tCoord[0], &tCenter[0] ) < tRadius )
		{
			return TRUE;
		}
		return FALSE;
	case  11 :
		if( tTribe != 2 )
		{
			return FALSE;
		}
		tCenter[0] = 449.0f;
		tCenter[1] = 1.0f;
		tCenter[2] = 439.0f;
		tRadius = 1000.0f;
		if( mUTIL.GetLengthXYZ( &tCoord[0], &tCenter[0] ) < tRadius )
		{
			return TRUE;
		}
		return FALSE;
	case 140 :
		if( tTribe != 3 )
		{
			return FALSE;
		}
		tCenter[0] = 452.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = 487.0f;
		tRadius = 1000.0f;
		if( mUTIL.GetLengthXYZ( &tCoord[0], &tCenter[0] ) < tRadius )
		{
			return TRUE;
		}
		return FALSE;
	case  37 :
		tCenter[0] = 1.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = -1478.0f;
		tRadius = 1000.0f;
		if( mUTIL.GetLengthXYZ( &tCoord[0], &tCenter[0] ) < tRadius )
		{
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
//W_END_PSHOP_SEND
void W_END_PSHOP_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	if( mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState != 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState = 0;
	mTRANSFER.B_END_PSHOP_RECV();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_DEMAND_PSHOP_SEND
void W_DEMAND_PSHOP_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );

	int tOtherAvatarIndex;

	tOtherAvatarIndex = mUTIL.SearchAvatar( &tAvatarName[0], tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mTRANSFER.B_DEMAND_PSHOP_RECV( 1, &mAVATAR_OBJECT[0].mPShopInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		mTRANSFER.B_DEMAND_PSHOP_RECV( 1, &mAVATAR_OBJECT[0].mPShopInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aPShopState != 1 )
	{
		mTRANSFER.B_DEMAND_PSHOP_RECV( 2, &mAVATAR_OBJECT[0].mPShopInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mTRANSFER.B_DEMAND_PSHOP_RECV( 0, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_PSHOP_ITEM_INFO_SEND
void W_PSHOP_ITEM_INFO_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tSort1;
	int tSort2;
	CopyMemory( &tSort1, &tPacket[1], 4 );
	CopyMemory( &tSort2, &tPacket[5], 4 );
}
//W_BUY_PSHOP_SEND
void W_BUY_PSHOP_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	DWORD tUniqueNumber;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tPage1;
	int tIndex1;
	int tQuantity1;
	int tPage2;
	int tIndex2;
	int tXPost2;
	int tYPost2;
	CopyMemory( &tUniqueNumber, &tPacket[1], 4 );
	CopyMemory( &tAvatarName[0], &tPacket[5], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tPage1, &tPacket[( 5 + MAX_AVATAR_NAME_LENGTH )], 4 );
	CopyMemory( &tIndex1, &tPacket[( 9 + MAX_AVATAR_NAME_LENGTH )], 4 );
	CopyMemory( &tQuantity1, &tPacket[( 13 + MAX_AVATAR_NAME_LENGTH )], 4 );
	CopyMemory( &tPage2, &tPacket[( 17 + MAX_AVATAR_NAME_LENGTH )], 4 );
	CopyMemory( &tIndex2, &tPacket[( 21 + MAX_AVATAR_NAME_LENGTH )], 4 );
	CopyMemory( &tXPost2, &tPacket[( 25 + MAX_AVATAR_NAME_LENGTH )], 4 );
	CopyMemory( &tYPost2, &tPacket[( 29 + MAX_AVATAR_NAME_LENGTH )], 4 );
	if( ( tPage1 < 0 ) || ( tPage1 > ( MAX_PSHOP_PAGE_NUM - 1 ) ) || ( tIndex1 < 0 ) || ( tIndex1 > ( MAX_PSHOP_SLOT_NUM - 1 ) ) || ( tPage2 < 0 ) || ( tPage2 > 1 ) || ( tIndex2 < 0 ) || ( tIndex2 > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tXPost2 < 0 ) || ( tXPost2 > 7 ) || ( tYPost2 < 0 ) || ( tYPost2 > 7 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tOtherAvatarIndex;
	int tItemInfo[9];
	int tValue[6];
    // # Defense Hack #
    float fRange = 0.0f;
    fRange = mUTIL.ReturnLengthXYZ(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[1]);

    if(fRange > 10000.0f) {
        mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 8, fRange);
        mGAMELOG.GL_659_AUTO_CHECK(tOtherAvatarIndex, 8, fRange);
        mTRANSFER.B_BUY_PSHOP_RECV( 8, 0, 0, 0, &tValue[0] );
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        return;
    }

    if(1 == mUSER[tUserIndex].mAuthInfo.PShopFlag){
        mTRANSFER.B_BUY_PSHOP_RECV( 8, 0, 0, 0, &tValue[0] );
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        return;
    } // # }

	tOtherAvatarIndex = mUTIL.SearchAvatar( &tAvatarName[0], tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mTRANSFER.B_BUY_PSHOP_RECV( 1, 0, 0, 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		mTRANSFER.B_BUY_PSHOP_RECV( 1, 0, 0, 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aPShopState != 1 )
	{
		mTRANSFER.B_BUY_PSHOP_RECV( 2, 0, 0, 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mUniqueNumber != tUniqueNumber )
	{
		mTRANSFER.B_BUY_PSHOP_RECV( 7, 0, 0, 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if(1 == mUSER[tOtherAvatarIndex].mAuthInfo.PShopFlag){
		mTRANSFER.B_BUY_PSHOP_RECV( 9, 0, 0, 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}

	CopyMemory( &tItemInfo[0], &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][0], 36 );
	if( tItemInfo[0] < 1 )
	{
		mTRANSFER.B_BUY_PSHOP_RECV( 3, 0, 0, 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mTRANSFER.B_DEMAND_PSHOP_RECV( 0, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][0] != tItemInfo[0] ) || ( mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][1] != tItemInfo[7] ) || ( mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][2] != tItemInfo[8] ) || ( mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][3] != tItemInfo[1] ) || ( mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][4] != tItemInfo[2] ) || ( mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][5] != tItemInfo[3] ) )
	{
		mTRANSFER.B_BUY_PSHOP_RECV( 4, 0, 0, 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mUTIL.CheckOverMaximum( mUSER[tOtherAvatarIndex].mAvatarInfo.aMoney, tItemInfo[4] ) )
	{
		mTRANSFER.B_BUY_PSHOP_RECV( 5, 0, 0, 0, &tValue[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( tPage2 == 1 )
	{
		if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if( mUSER[tUserIndex].mAvatarInfo.aMoney < tItemInfo[4] )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tValue[0] = tItemInfo[0];
	tValue[1] = tXPost2;
	tValue[2] = tYPost2;
	tValue[3] = tItemInfo[1];
	tValue[4] = tItemInfo[2];
	tValue[5] = tItemInfo[3];
	mGAMELOG.GL_609_PSHOP_ITEM( tUserIndex, 1, tItemInfo[0], tItemInfo[1], tItemInfo[2], tItemInfo[3], tItemInfo[4] );
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tItemInfo[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = tValue[5];
	mTRANSFER.B_BUY_PSHOP_RECV( 0, tItemInfo[4], tPage2, tIndex2, &tValue[0] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mGAMELOG.GL_609_PSHOP_ITEM( tOtherAvatarIndex, 2, tItemInfo[0], tItemInfo[1], tItemInfo[2], tItemInfo[3], tItemInfo[4] );
	mUSER[tOtherAvatarIndex].mAvatarInfo.aMoney += tItemInfo[4];
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][0] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][1] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][2] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][3] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][4] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][5] = 0;
	mTRANSFER.B_BUY_PSHOP_RECV( 6, tItemInfo[4], tItemInfo[5], tItemInfo[6], &tValue[0] );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][0] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][1] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][2] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][3] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][4] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][5] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][6] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][7] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][8] = 0;
	mTRANSFER.B_DEMAND_PSHOP_RECV( 0, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mTRANSFER.B_DEMAND_PSHOP_RECV( 3, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_PROCESS_QUEST_SEND
void W_PROCESS_QUEST_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage;
	int tIndex;
	int tXPost;
	int tYPost;
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tPage, &tPacket[5], 4 );
	CopyMemory( &tIndex, &tPacket[9], 4 );
	CopyMemory( &tXPost, &tPacket[13], 4 );
	CopyMemory( &tYPost, &tPacket[17], 4 );

	int index01;
	QUEST_INFO *tQUEST_INFO;

	if( mUSER[tUserIndex].mHealthState == 5 )
	{
		mTRANSFER.B_PROCESS_QUEST_RECV(1, tSort, tPage, tIndex, tXPost, tYPost );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}

	switch( tSort )
	{
	case 1 : //[ÀÓ¹«_¹ß±Þ]
		if( mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search( mUSER[tUserIndex].mAvatarInfo.aTribe, ( mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] + 1 ) );
		if( tQUEST_INFO == NULL )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch( tQUEST_INFO->qSort )
		{
		case 3 :
		case 6 :
			if( ( tPage < 0 ) || ( tPage > 1 ) || ( tIndex < 0 ) || ( tIndex > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tXPost < 0 ) || ( tXPost > 7 ) || ( tYPost < 0 ) || ( tYPost > 7 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( tPage == 1 )
			{
				if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] > 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tQUEST_INFO->qSolution[0];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tXPost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tYPost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0]++;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 1;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = tQUEST_INFO->qSort;
		if( tQUEST_INFO->qSort != 6 )
		{
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = tQUEST_INFO->qSolution[0];
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 1;
		}
		if( tQUEST_INFO->qSort != 6 )
		{
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = tQUEST_INFO->qSolution[0];
		}
		mTRANSFER.B_PROCESS_QUEST_RECV(0, tSort, tPage, tIndex, tXPost, tYPost );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 2 : //[ÀÓ¹«_¿Ï·á]
		if( mAVATAR_OBJECT[tUserIndex].ReturnQuestEndConditionState() != 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search( mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] );
		if( tQUEST_INFO == NULL )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( tPage != -1 )
		{
			if( ( tPage < 0 ) || ( tPage > 1 ) || ( tIndex < 0 ) || ( tIndex > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tXPost < 0 ) || ( tXPost > 7 ) || ( tYPost < 0 ) || ( tYPost > 7 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( tPage == 1 )
			{
				if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] > 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mGAMELOG.GL_610_QUEST_ITEM( tUserIndex, mAVATAR_OBJECT[tUserIndex].ReturnItemNumberForQuestReward(), mAVATAR_OBJECT[tUserIndex].ReturnItemQuantityForQuestReward(), 0, 0 );
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = mAVATAR_OBJECT[tUserIndex].ReturnItemNumberForQuestReward();
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tXPost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tYPost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = mAVATAR_OBJECT[tUserIndex].ReturnItemQuantityForQuestReward();
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		for( index01 = 0 ; index01 < 3 ; index01++ )
		{
			switch( tQUEST_INFO->qReward[index01][0] )
			{
			case 1 :
				break;
			case 2 :
				if( mUTIL.CheckOverMaximum( mUSER[tUserIndex].mAvatarInfo.aMoney, tQUEST_INFO->qReward[index01][1] ) )
				{
					break;
				}
				mGAMELOG.GL_611_QUEST_MONEY( tUserIndex, tQUEST_INFO->qReward[index01][1] );
				mUSER[tUserIndex].mAvatarInfo.aMoney += tQUEST_INFO->qReward[index01][1];
				break;
			case 3 :
				mGAMELOG.GL_612_QUEST_KILL_NUM( tUserIndex, tQUEST_INFO->qReward[index01][1] );
				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += tQUEST_INFO->qReward[index01][1];
				mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += tQUEST_INFO->qReward[index01][1];
				break;
			case 4 :
				mGAMELOG.GL_613_QUEST_EXP( tUserIndex, tQUEST_INFO->qReward[index01][1] );
				mUTIL.ProcessForExperience( tUserIndex, tQUEST_INFO->qReward[index01][1], 0, 0 );
				break;
			case 5 :
				/*mGAMELOG.GL_614_QUEST_TEACHER_POINT( tUserIndex, tQUEST_INFO->qReward[index01][1] );
				mUSER[tUserIndex].mAvatarInfo.aTeacherPoint += tQUEST_INFO->qReward[index01][1];*/
				break;
			case 6 :
				break;
			}
		}
		switch( mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] )
		{
		case 2 :
			mAVATAR_OBJECT[tUserIndex].DeleteQuestItem( tQUEST_INFO->qSolution[0] );
			break;
		case 3 :
			mAVATAR_OBJECT[tUserIndex].DeleteQuestItem( tQUEST_INFO->qSolution[0] );
			break;
		case 4 :
			mAVATAR_OBJECT[tUserIndex].DeleteQuestItem( tQUEST_INFO->qSolution[0] );
			break;
		case 6 :
			mAVATAR_OBJECT[tUserIndex].DeleteQuestItem( tQUEST_INFO->qSolution[1] );
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
		mTRANSFER.B_PROCESS_QUEST_RECV( 0, tSort, tPage, tIndex, tXPost, tYPost );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 3 : //[ÀÓ¹«¹°Ç°_¹ÞÀ½]
		switch( mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] )
		{
		case 3 :
			if( mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 2 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 4 :
			if( mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 2 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 6 :
			if( ( mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 2 ) && ( mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 4 ) )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default :
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search( mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] );
		if( tQUEST_INFO == NULL )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( ( tPage < 0 ) || ( tPage > 1 ) || ( tIndex < 0 ) || ( tIndex > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) || ( tXPost < 0 ) || ( tXPost > 7 ) || ( tYPost < 0 ) || ( tYPost > 7 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( tPage == 1 )
		{
			if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] > 0 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tQUEST_INFO->qSolution[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tXPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tYPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_PROCESS_QUEST_RECV( 0, tSort, tPage, tIndex, tXPost, tYPost );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 4 : //[ÀÓ¹«¹°Ç°_±³È¯]
		switch( mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] )
		{
		case 6 :
			if( mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 3 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default :
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search( mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] );
		if( tQUEST_INFO == NULL )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mAVATAR_OBJECT[tUserIndex].ChangeQuestItem( tQUEST_INFO->qSolution[0], tQUEST_INFO->qSolution[1] );
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 2;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = tQUEST_INFO->qSolution[1];
		mTRANSFER.B_PROCESS_QUEST_RECV( 0, tSort, tPage, tIndex, tXPost, tYPost );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 5 : //[ÀÓ¹«_Æ÷±â]
		if( ( mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() == 0 ) || ( mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() == 1 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search( mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] );
		if( tQUEST_INFO == NULL )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( tQUEST_INFO->qType != 2 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mAVATAR_OBJECT[tUserIndex].ReturnQuestEndConditionState() != 0 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
		mTRANSFER.B_PROCESS_QUEST_RECV( 0, tSort, tPage, tIndex, tXPost, tYPost );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	default : //[¿À·ù]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_CHANGE_TO_TRIBE4_SEND
void W_CHANGE_TO_TRIBE4_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	time_t tCountSeconds;
	struct tm *tPresentTime;

	time( &tCountSeconds );
	tPresentTime = localtime( &tCountSeconds );
	if( tPresentTime == NULL )
	{
		mTRANSFER.B_CHANGE_TO_TRIBE4_RECV( 2 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	
	//saturday, 12:00 ~ 24:00
	if(( ( tPresentTime->tm_wday != 6 ) || ( tPresentTime->tm_hour < 12 )) && 
			(( tPresentTime->tm_wday != 0 ) || ( tPresentTime->tm_hour > 0 ) || (tPresentTime->tm_min > 0)))
	{
		mTRANSFER.B_CHANGE_TO_TRIBE4_RECV( 2 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	int index01;
	int iCount = 0;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	switch( mUSER[tUserIndex].mAvatarInfo.aTribe )
	{
	case 0 :
		if( mSERVER_INFO.mServerNumber != 71 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 1 :
		if( mSERVER_INFO.mServerNumber != 72 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 2 :
		if( mSERVER_INFO.mServerNumber != 73 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}

	for(iCount = 0; iCount < MAX_TRIBE_VOTE_AVATAR_NUM; iCount++) {
		if(!::strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][iCount]
					, mUSER[tUserIndex].mAvatarInfo.aName)) {
			mTRANSFER.B_CHANGE_TO_TRIBE4_RECV( 1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
	}

	if( mUSER[tUserIndex].mAvatarInfo.aTribe == 3 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#if 0
	if( mGAME.ReturnTribePointWithAlliance( mUSER[tUserIndex].mAvatarInfo.aTribe ) < 100 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mGAME.CheckPossibleChangeToTribe4( mUSER[tUserIndex].mAvatarInfo.aTribe ) != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#endif
	if (100 > mGAME.mWorldInfo.mTribePoint[mUSER[tUserIndex].mAvatarInfo.aTribe]){
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mGAME.CheckPossibleChangeToTribe4_2( mUSER[tUserIndex].mAvatarInfo.aTribe ) != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aTeacher, "" ) != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aStudent, "" ) != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for( index01 = 0 ; index01 < MAX_FRIEND_NUM ; index01++ )
	{
		if( strcmp( mUSER[tUserIndex].mAvatarInfo.aFriend[index01], "" ) != 0 )
		{
			break;
		}
	}
	if( index01 < MAX_FRIEND_NUM )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mUSER[tUserIndex].mAvatarInfo.aTribe = 3;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aTribe = 3;
	mTRANSFER.B_CHANGE_TO_TRIBE4_RECV( 0 );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//--------------//
	//BROADCAST_INFO//
	//--------------//
	tBroadcastInfoSort = 51;
	CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 4 );
	CopyMemory( &tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
	mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
	//--------------//
	//--------------//
	//--------------//
}
//W_GENERAL_CHAT_SEND
void W_GENERAL_CHAT_SEND( int tUserIndex )
{
	//unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory( &tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	if( strcmp( tContent, "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	float tPostLocation[3];
	int tSpaceIndex[3];
	float tLocation[3];
	BYTE tAuthType = 0;

	if( mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2 )
	{
		return;
	}
    tPostLocation[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	tPostLocation[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	tPostLocation[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	tSpaceIndex[0] = (int) ( tPostLocation[0] / MAX_RADIUS_FOR_NETWORK );
	tSpaceIndex[1] = (int) ( tPostLocation[1] / MAX_RADIUS_FOR_NETWORK );
	tSpaceIndex[2] = (int) ( tPostLocation[2] / MAX_RADIUS_FOR_NETWORK );
	
	if (1 == mUSER[tUserIndex].mAuthInfo.AuthType){
		tAuthType = 1;
	}
	//LOG_TO_FILE_1("CHAT %s",&tContent[0]);
	mTRANSFER.B_GENERAL_CHAT_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0], tAuthType, &tContent[0] );

	char type[50];
	snprintf(type,50, "W_GENERAL_CHAT_SEND");
	mGAMELOG.CHAT_LOG_SEND( tUserIndex, NULL, &tContent[0], type);
		
	for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
	{
		if( !mAVATAR_OBJECT[index01].mCheckValidState )
		{
			continue;
		}
		if(1 != mUSER[tUserIndex].mAuthInfo.AuthType){
			if((1 != mUSER[index01].mAuthInfo.AuthType) || (1 != mAVATAR_OBJECT[index01].mChat)){
				if( ( mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) 
					&& ( mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) )
					&& ( mSERVER_INFO.mServerNumber != ZONE_PRISON ) )
				{
					continue;
				}
			}
		}
		else{
			if(1 != mAVATAR_OBJECT[tUserIndex].mChat){
				if( ( mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) 
					&& ( mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) ) 
					&& ( mSERVER_INFO.mServerNumber != ZONE_PRISON ) )
				{
					continue;
				}
			}
		}


		if((1 != mUSER[tUserIndex].mAuthInfo.AuthType) && (1 != mUSER[index01].mAuthInfo.AuthType)){
			if( ( mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) 
				&& ( mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) ) 
				&& ( mSERVER_INFO.mServerNumber != ZONE_PRISON ) )
			{
				continue;
			}
		}
#ifdef __GOD__
		if( ( mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) && ( mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) ) )
		{
			continue;
		}
#endif
		if( ( abs( mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - tSpaceIndex[0] ) > 1 ) || ( abs( mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - tSpaceIndex[1] ) > 1 ) || ( abs( mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - tSpaceIndex[2] ) > 1 ) )
		{
			continue;
		}
		tLocation[0] = mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0];
		tLocation[1] = mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1];
		tLocation[2] = mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2];
		if( ( ( tLocation[0] - tPostLocation[0] ) * ( tLocation[0] - tPostLocation[0] ) + ( tLocation[1] - tPostLocation[1] ) * ( tLocation[1] - tPostLocation[1] ) + ( tLocation[2] - tPostLocation[2] ) * ( tLocation[2] - tPostLocation[2] ) ) > ( MAX_RADIUS_FOR_NETWORK * MAX_RADIUS_FOR_NETWORK ) )
		{
			continue;
		}
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	}
}
//W_SECRET_CHAT_SEND
void W_SECRET_CHAT_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	CopyMemory( &tContent[0], &tPacket[( 1 + MAX_AVATAR_NAME_LENGTH )], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	if( strcmp( tContent, "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2 )
	{
		return;
	}
	if( ( strncmp( mUSER[tUserIndex].mAvatarInfo.aName, tAvatarName, MAX_AVATAR_NAME_LENGTH) == 0 ) 
			|| ( strcmp( tAvatarName, "" ) == 0 ) )
	{
		return;
	}
	mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND( &tAvatarName[0] );
	if( mPLAYUSER_COM.mRecv_ZoneNumber < 1 )
	{
		mTRANSFER.B_SECRET_CHAT_RECV( 1, 0, &tAvatarName[0], &tContent[0], 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false );
		return;
	}
	if(mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	{
		if( ( mUSER[tUserIndex].mAvatarInfo.aTribe != mPLAYUSER_COM.mRecv_Tribe ) && ( mUSER[tUserIndex].mAvatarInfo.aTribe != mGAME.ReturnAllianceTribe( mPLAYUSER_COM.mRecv_Tribe ) ) )
		{
			mTRANSFER.B_SECRET_CHAT_RECV( 2, 0, &tAvatarName[0], &tContent[0], 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false );
			return;
		}
	}
	mTRANSFER.B_SECRET_CHAT_RECV( 0, mPLAYUSER_COM.mRecv_ZoneNumber, &tAvatarName[0], &tContent[0], mUSER[tUserIndex].mAuthInfo.AuthType );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false );
	tSort = 103;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[MAX_AVATAR_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[( MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tContent[0], MAX_CHAT_CONTENT_LENGTH );
	CopyMemory( &tData[( MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH )], &mUSER[tUserIndex].mAuthInfo.AuthType, 1 );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );

	char type[50];
	snprintf(type, 50,"W_SECRET_CHAT_SEND");
	mGAMELOG.CHAT_LOG_SEND( tUserIndex, tAvatarName, &tContent[0], type);
}
//W_GENERAL_SHOUT_SEND
void W_GENERAL_SHOUT_SEND( int tUserIndex )
{
	//unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	BYTE tAuthType = 0;
	CopyMemory( &tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	if( strcmp( tContent, "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if( mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2 )
	{
		return;
	}
	if( ( mSERVER_INFO.mServerNumber != 37 ) && ( mSERVER_INFO.mServerNumber != 119 ) && ( mSERVER_INFO.mServerNumber != 124 ) &&
			( mSERVER_INFO.mServerNumber != 84 ))
	{
		return;
	}
	if(1 == mUSER[tUserIndex].mAuthInfo.AuthType)
		tAuthType = 1;

	mTRANSFER.B_GENERAL_SHOUT_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0], tAuthType, &tContent[0] );

	char type[50];
	snprintf(type, 50,"W_GENERAL_SHOUT_SEND");
	mGAMELOG.CHAT_LOG_SEND( tUserIndex, NULL, &tContent[0], type);
	mUTIL.Broadcast( FALSE, NULL, 0, false );
}
//W_GET_CASH_SIZE_SEND
void W_GET_CASH_SIZE_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if( !mEXTRA_COM.U_GET_CASH_SIZE_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0] ) )
	{
		mTRANSFER.B_GET_CASH_SIZE_RECV( 0, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mTRANSFER.B_GET_CASH_SIZE_RECV( mEXTRA_COM.mRecv_CashSize, mEXTRA_COM.mRecv_BonusCashSize );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_BUY_CASH_ITEM_SEND
void W_BUY_CASH_ITEM_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tCostInfoIndex;
	int tPage;
	int tIndex;
	int tValue[6];
	CopyMemory( &tCostInfoIndex, &tPacket[1], 4 );
	CopyMemory( &tPage, &tPacket[5], 4 );
	CopyMemory( &tIndex, &tPacket[9], 4 );
	CopyMemory( &tValue[0], &tPacket[13], 24 );

    // @ Cost Info Download @
    // Å¬¶óÀÌ¾ðÆ®°¡ °¡Áö°í ÀÖ´Â Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸ÀÇ ¹öÀü°ú
    // Zone ¼­¹ö°¡ °¡Áö°í ÀÖ´Â Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸ÀÇ ¹öÀüÀÌ ´Ù¸£¸é ½ÇÆÐ.
    int tVersion = 0;
    CopyMemory( &tVersion, &tPacket[37], 4 );
    if (tVersion != mEXTRA_COM.mCashItemInfoVersion)
    {
        mTRANSFER.B_BUY_CASH_ITEM_RECV( 3, 0, 0, tPage, tIndex, &tValue[0]);
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        mUSER[tUserIndex].mIsValidCashItemInfo = false;
        return;
    }
    if (mEXTRA_COM.mIsValidCashItemInfo == false) // COST_INFO Update Áß È¤Àº Update ¿À·ù·Î ÀÎÇÑ ÆÇ¸Å ÁßÁö.
    {
        mTRANSFER.B_BUY_CASH_ITEM_RECV( 4, 0, 0, tPage, tIndex, &tValue[0]);
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        return;
    } // @

	if( ( tPage < 0 ) || ( tPage > 1 ) || ( tIndex < 0 ) || ( tIndex > ( MAX_INVENTORY_SLOT_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if( tPage == 1 )
	{
		if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
    // @ Cost Info Download @
    //if( !mEXTRA_COM.U_BUY_CASH_ITEM_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0], tCostInfoIndex, tValue[0], tValue[3], &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aLevel1 ) )
    // @
    if( !mEXTRA_COM.U_BUY_CASH_ITEM_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0], tCostInfoIndex, tValue[0], tValue[3], &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aLevel1, tVersion ) )
	{
		mTRANSFER.B_BUY_CASH_ITEM_RECV( 2, 0, 0, tPage, tIndex, &tValue[0]);
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mEXTRA_COM.mRecv_Result != 0 )
	{
        // @ Cost Info Download @
        int result = 1;
        if (mEXTRA_COM.mRecv_Result == 2) // Ä³½¬ ¾ÆÀÌÅÛ ÆÇ¸Å ÁßÁö Áß.
        {
            result = 4;
        }
        else if (mEXTRA_COM.mRecv_Result == 3) // Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸ ¹öÀü ¿À·ù.
        {
            // ¹öÀü ¹ÌÀÏÄ¡ÀÎ °æ¿ì º¸Åë À§¿¡¼­ °Ë»çµÈ´Ù.
            // Center ¼­¹ö¿¡¼­ º¸³» ÁÖ´Â UPDATE_CASH_ITEM_INFO ÆÐÅ¶À» ¸ø ¹Þ¾Æ¼­
            // (ÀÏ½ÃÀûÀÎ Á¢¼Ó ²÷±è µî) ÇöÀç Á¸¼­¹ö°¡ °¡Áö°í ÀÖ´Â Á¤º¸¿¡ ¿À·ù°¡
            // ÀÖÀ» ¼ö ÀÖÀ¸¹Ç·Î ´Ù½Ã ¿äÃ»ÇÑ´Ù.
            mEXTRA_COM.U_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND();
            result = 3;
        }
        mTRANSFER.B_BUY_CASH_ITEM_RECV( result, 0, 0, tPage, tIndex, &tValue[0] );
        // @
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tValue[0] = tValue[0];
	tValue[1] = tValue[1];
	tValue[2] = tValue[2];
	tValue[3] = tValue[3];
	tValue[4] = 0;
	tValue[5] = mUTIL.ReturnItemRecognitionNumber( 0 );
	mGAMELOG.GL_604_BUY_CASH_ITEM( tUserIndex, tValue[0], tValue[3], tValue[4], tValue[5], mEXTRA_COM.mRecv_CostSize, mEXTRA_COM.mRecv_BonusCostSize );

    // ¼ö·® Ã¼Å©
    if (( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] == tValue[0]) && ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] == tValue[1]) && ( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] == tValue[2]))
    {
        ITEM_INFO *tITEM_INFO;
        tITEM_INFO = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] );
        if ( (tITEM_INFO != NULL) && (tITEM_INFO->iSort == 2) && (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] + tValue[3] <= 99))
        {
            tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] + tValue[3];
        }
    }

	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tValue[5];
	mTRANSFER.B_BUY_CASH_ITEM_RECV( 0, mEXTRA_COM.mRecv_CashSize, mEXTRA_COM.mRecv_BonusCashSize, tPage, tIndex, &tValue[0] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_DUEL_ASK_SEND
void W_DUEL_ASK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	if(124 == mSERVER_INFO.mServerNumber)
		return;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tSort;
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	CopyMemory( &tSort, &tPacket[( 1 + MAX_AVATAR_NAME_LENGTH )], 4 );

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0] != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mAVATAR_OBJECT[tUserIndex].CheckCommunityWork() )
	{
		mTRANSFER.B_DUEL_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_DUEL_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( tAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mTRANSFER.B_DUEL_ANSWER_RECV( 4 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mSERVER_INFO.mServerNumber != 37 ) && ( mSERVER_INFO.mServerNumber != 119 ) && ( mSERVER_INFO.mServerNumber != 124 ) )
	{
		if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe ) && ( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mGAME.ReturnAllianceTribe( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if( ( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork() ) )
	{
		mTRANSFER.B_DUEL_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_DUEL_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 1;
	strncpy( mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mAVATAR_OBJECT[tUserIndex].mDuelProcessSort = tSort;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 2;
	strncpy( mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessSort = tSort;
	mTRANSFER.B_DUEL_ASK_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0], tSort );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_DUEL_CANCEL_SEND
void W_DUEL_CANCEL_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mDuelProcessState != 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState != 2 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
	mTRANSFER.B_DUEL_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_DUEL_ANSWER_SEND
void W_DUEL_ANSWER_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tAnswer;
	CopyMemory( &tAnswer, &tPacket[1], 4 );

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mDuelProcessState != 2 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
		break;
	default :
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState != 1 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
		break;
	default :
		return;
	}
	mTRANSFER.B_DUEL_ANSWER_RECV( tAnswer );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_DUEL_START_SEND
void W_DUEL_START_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tAvatarDuelUniqueNumber;
	int tOtherAvatarIndex;

	tAvatarDuelUniqueNumber = mGAME.mAvatarDuelUniqueNumber;
	mGAME.mAvatarDuelUniqueNumber++;
	if( mAVATAR_OBJECT[tUserIndex].mDuelProcessState != 3 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0] = 1;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[1] = tAvatarDuelUniqueNumber;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[2] = 1;
	if( mAVATAR_OBJECT[tUserIndex].mDuelProcessSort == 1 )
	{
		mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion = FALSE;
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion = TRUE;
	}
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 4;
	mAVATAR_OBJECT[tUserIndex].mDuelProcessRemainTime = 180;
	mTRANSFER.B_DUEL_START_RECV( &mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tUserIndex].mDuelProcessRemainTime );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mTRANSFER.B_AVATAR_CHANGE_INFO_1( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[2] );
	mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false );
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState != 3 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0] = 1;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1] = tAvatarDuelUniqueNumber;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] = 2;
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessSort == 1 )
	{
		mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = FALSE;
	}
	else
	{
		mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = TRUE;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 4;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessRemainTime = 180;
	mTRANSFER.B_DUEL_START_RECV( &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessRemainTime );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mTRANSFER.B_AVATAR_CHANGE_INFO_1( tOtherAvatarIndex, mAVATAR_OBJECT[tOtherAvatarIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] );
    mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false );
}
//W_TRADE_ASK_SEND
void W_TRADE_ASK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	int tOtherAvatarIndex;
	if(1 == mUSER[tUserIndex].mAuthInfo.TradeFlag){
		mTRANSFER.B_TRADE_ANSWER_RECV( 6 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mAVATAR_OBJECT[tUserIndex].CheckCommunityWork() )
	{
		mTRANSFER.B_TRADE_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_TRADE_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( tAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mTRANSFER.B_TRADE_ANSWER_RECV( 4 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mSERVER_INFO.mServerNumber != 37 ) && ( mSERVER_INFO.mServerNumber != 119 ) && ( mSERVER_INFO.mServerNumber != 124 ) )
	{
		if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe ) && ( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mGAME.ReturnAllianceTribe( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if( ( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork() ) )
	{
		mTRANSFER.B_TRADE_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_TRADE_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if(1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag){
		mTRANSFER.B_TRADE_ANSWER_RECV( 7 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 1;
	strncpy( mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 2;
	strncpy( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mTRANSFER.B_TRADE_ASK_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aLevel1 );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TRADE_CANCEL_SEND
void W_TRADE_CANCEL_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 2 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
	mTRANSFER.B_TRADE_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TRADE_ANSWER_SEND
void W_TRADE_ANSWER_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tAnswer;
	CopyMemory( &tAnswer, &tPacket[1], 4 );

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 2 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		break;
	default :
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 1 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		break;
	default :
		return;
	}

	if(1 == mUSER[tUserIndex].mAuthInfo.TradeFlag){
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV( 6 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mTRANSFER.B_TRADE_ANSWER_RECV( 7 );
		mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	}
	else if(1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag){
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV( 7 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mTRANSFER.B_TRADE_ANSWER_RECV( 6 );
		mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	}
	else{
		mTRANSFER.B_TRADE_ANSWER_RECV( tAnswer );
		mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	}
}
//W_TRADE_START_SEND
void W_TRADE_START_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 3 )
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 3 )
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if(1 == mUSER[tUserIndex].mAuthInfo.TradeFlag){
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV( 6 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mTRANSFER.B_TRADE_ANSWER_RECV( 7 );
		mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag){
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV( 7 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mTRANSFER.B_TRADE_ANSWER_RECV( 6 );
		mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}

	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 4;
	mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu = 0;
	mTRANSFER.B_TRADE_START_RECV( mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney, mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 4;
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu = 0;
	mTRANSFER.B_TRADE_START_RECV( mUSER[tUserIndex].mAvatarInfo.aTradeMoney, mUSER[tUserIndex].mAvatarInfo.aTrade );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TRADE_MENU_SEND
void W_TRADE_MENU_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int index01;
	int tOtherAvatarIndex;
	int tTradeMoney;
	int tTrade[MAX_TRADE_SLOT_NUM][4];

	if( mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 4 )
	{
		return;
	}
	switch( mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu )
	{
	case 0 :
		tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex );
		if( tOtherAvatarIndex == -1 )
		{
			return;
		}
		if( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4 )
		{
			return;
		}
		if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
		{
			return;
		}
		if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
		{
			return;
		}
		if( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu == 2 )
		{
			return;
		}
		if(1 == mUSER[tUserIndex].mAuthInfo.TradeFlag){
			return;
		}
		else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag){
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu = 1;
		mTRANSFER.B_TRADE_MENU_RECV( 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mTRANSFER.B_TRADE_MENU_RECV( 1 );
		mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 1 :
		tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex );
		if( tOtherAvatarIndex == -1 )
		{
			return;
		}
		if( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4 )
		{
			return;
		}
		if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
		{
			return;
		}
		if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
		{
			return;
		}
		if( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu == 0 )
		{
			return;
		}
		if(1 == mUSER[tUserIndex].mAuthInfo.TradeFlag){
			return;
		}
		else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag){
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu = 2;
		mTRANSFER.B_TRADE_MENU_RECV( 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mTRANSFER.B_TRADE_MENU_RECV( 1 );
		mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		if( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu != 2 )
		{
			return;
		}
		tTradeMoney = mUSER[tUserIndex].mAvatarInfo.aTradeMoney;
		for( index01 = 0 ; index01 < MAX_TRADE_SLOT_NUM ; index01++ )
		{
			tTrade[index01][0] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][0];
			tTrade[index01][1] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][1];
			tTrade[index01][2] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][2];
			tTrade[index01][3] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][3];
		}
		if( mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney > 0 )
		{
			mGAMELOG.GL_616_TRADE_MONEY( tOtherAvatarIndex, tUserIndex, mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney );
		}
		mUSER[tUserIndex].mAvatarInfo.aTradeMoney = mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney;
		for( index01 = 0 ; index01 < MAX_TRADE_SLOT_NUM ; index01++ )
		{
			if( mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0] > 0 )
			{
				mGAMELOG.GL_615_TRADE_ITEM( tOtherAvatarIndex, tUserIndex, mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0], mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][1], mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][2], mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][3] );
			}
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][0] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0];
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][1] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][2] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][2];
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][3] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][3];
		}
		if( tTradeMoney > 0 )
		{
			mGAMELOG.GL_616_TRADE_MONEY( tUserIndex, tOtherAvatarIndex, tTradeMoney );
		}
		mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney = tTradeMoney;
		for( index01 = 0 ; index01 < MAX_TRADE_SLOT_NUM ; index01++ )
		{
			if( tTrade[index01][0] > 0 )
			{
				mGAMELOG.GL_615_TRADE_ITEM( tUserIndex, tOtherAvatarIndex, tTrade[index01][0], tTrade[index01][1], tTrade[index01][2], tTrade[index01][3] );
			}
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0] = tTrade[index01][0];
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][1] = tTrade[index01][1];
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][2] = tTrade[index01][2];
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][3] = tTrade[index01][3];
		}
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_END_RECV( 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_END_RECV( 0 );
		mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
}
//W_TRADE_END_SEND
void W_TRADE_END_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 4 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
	mTRANSFER.B_TRADE_END_RECV( 1 );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
	mTRANSFER.B_TRADE_END_RECV( 1 );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_FRIEND_ASK_SEND
void W_FRIEND_ASK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	if(124 == mSERVER_INFO.mServerNumber)
		return;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	int index01;
	int tOtherAvatarIndex;

	for( index01 = 0 ; index01 < MAX_FRIEND_NUM ; index01++ )
	{
		if( strcmp( mUSER[tUserIndex].mAvatarInfo.aFriend[index01], "" ) == 0 )
		{
			break;
		}
	}
	if( index01 == MAX_FRIEND_NUM )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for( index01 = 0 ; index01 < MAX_FRIEND_NUM ; index01++ )
	{
		if( strcmp( mUSER[tUserIndex].mAvatarInfo.aFriend[index01], tAvatarName ) == 0 )
		{
			break;
		}
	}
	if( index01 < MAX_FRIEND_NUM )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mAVATAR_OBJECT[tUserIndex].CheckCommunityWork() )
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( tAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV( 4 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork() ) )
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 1;
	strncpy( mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 2;
	strncpy( mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mTRANSFER.B_FRIEND_ASK_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0] );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_FRIEND_CANCEL_SEND
void W_FRIEND_CANCEL_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mFriendProcessState != 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState != 2 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
	mTRANSFER.B_FRIEND_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_FRIEND_ANSWER_SEND
void W_FRIEND_ANSWER_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tAnswer;
	CopyMemory( &tAnswer, &tPacket[1], 4 );

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mFriendProcessState != 2 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		break;
	default :
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState != 1 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
		break;
	default :
		return;
	}
	mTRANSFER.B_FRIEND_ANSWER_RECV( tAnswer );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_FRIEND_MAKE_SEND
void W_FRIEND_MAKE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tIndex;
	CopyMemory( &tIndex, &tPacket[1], 4 );
	if( ( tIndex < 0 ) || ( tIndex > ( MAX_FRIEND_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tOtherAvatarIndex;

	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "" ) != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mAVATAR_OBJECT[tUserIndex].mFriendProcessState != 3 )
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState != 3 )
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
	strncpy( mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], mUSER[tOtherAvatarIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH );
	mTRANSFER.B_FRIEND_MAKE_RECV( tIndex, &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
}
//W_FRIEND_FIND_SEND
void W_FRIEND_FIND_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tIndex;
	CopyMemory( &tIndex, &tPacket[1], 4 );
	if( ( tIndex < 0 ) || ( tIndex > ( MAX_FRIEND_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND( &mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex][0] );
	if( mUSER[tUserIndex].mAvatarInfo.aTribe != mPLAYUSER_COM.mRecv_Tribe )
	{
		mTRANSFER.B_FRIEND_FIND_RECV( tIndex, -1 );
	}
	else
	{
		mTRANSFER.B_FRIEND_FIND_RECV( tIndex, mPLAYUSER_COM.mRecv_ZoneNumber );
	}
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_FRIEND_DELETE_SEND
void W_FRIEND_DELETE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tIndex;
	CopyMemory( &tIndex, &tPacket[1], 4 );
	if( ( tIndex < 0 ) || ( tIndex > ( MAX_FRIEND_NUM - 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	strcpy( mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "" );
	mTRANSFER.B_FRIEND_DELETE_RECV( tIndex );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TEACHER_ASK_SEND
void W_TEACHER_ASK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	int tOtherAvatarIndex;

	if( ( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113 ) || ( strcmp( mUSER[tUserIndex].mAvatarInfo.aTeacher, "" ) != 0 ) || ( strcmp( mUSER[tUserIndex].mAvatarInfo.aStudent, "" ) != 0 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mAVATAR_OBJECT[tUserIndex].CheckCommunityWork() )
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( tAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV( 4 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe ) || ( mUSER[tOtherAvatarIndex].mAvatarInfo.aLevel1 > 112 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork() ) )
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( strcmp( mUSER[tOtherAvatarIndex].mAvatarInfo.aTeacher, "" ) != 0 )
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV( 6 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( strcmp( mUSER[tOtherAvatarIndex].mAvatarInfo.aStudent, "" ) != 0 )
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV( 7 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 1;
	strncpy( mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 2;
	strncpy( mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mTRANSFER.B_TEACHER_ASK_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0] );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TEACHER_CANCEL_SEND
void W_TEACHER_CANCEL_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mTeacherProcessState != 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState != 2 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
	mTRANSFER.B_TEACHER_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TEACHER_ANSWER_SEND
void W_TEACHER_ANSWER_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tAnswer;
	CopyMemory( &tAnswer, &tPacket[1], 4 );

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mTeacherProcessState != 2 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		break;
	default :
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState != 1 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
		break;
	default :
		return;
	}
	mTRANSFER.B_TEACHER_ANSWER_RECV( tAnswer );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TEACHER_START_SEND
void W_TEACHER_START_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mTeacherProcessState != 3 )
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState != 3 )
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
	strncpy( mUSER[tUserIndex].mAvatarInfo.aStudent, mUSER[tOtherAvatarIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH );
	mTRANSFER.B_TEACHER_START_RECV( 1, &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
	strncpy( mUSER[tOtherAvatarIndex].mAvatarInfo.aTeacher, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH );
	mTRANSFER.B_TEACHER_START_RECV( 2, &mUSER[tUserIndex].mAvatarInfo.aName[0] );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TEACHER_END_SEND
void W_TEACHER_END_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aTeacher, "" ) == 0 ) && ( strcmp( mUSER[tUserIndex].mAvatarInfo.aStudent, "" ) == 0 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	strcpy( mUSER[tUserIndex].mAvatarInfo.aTeacher, "" );
	strcpy( mUSER[tUserIndex].mAvatarInfo.aStudent, "" );
	mTRANSFER.B_TEACHER_END_RECV();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TEACHER_STATE_SEND
void W_TEACHER_STATE_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aTeacher, "" ) == 0 ) && ( strcmp( mUSER[tUserIndex].mAvatarInfo.aStudent, "" ) == 0 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aTeacher, "" ) != 0 )
	{
		tOtherAvatarIndex = mUTIL.SearchAvatar( mUSER[tUserIndex].mAvatarInfo.aTeacher, tUserIndex );
		if( tOtherAvatarIndex == -1 )
		{
			return;
		}
		if( strcmp( mUSER[tOtherAvatarIndex].mAvatarInfo.aStudent, mUSER[tUserIndex].mAvatarInfo.aName ) == 0 )
		{
			mTRANSFER.B_TEACHER_STATE_RECV( 0 );
		}
		else
		{
			mTRANSFER.B_TEACHER_STATE_RECV( 1 );
		}
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aStudent, "" ) != 0 )
	{
		tOtherAvatarIndex = mUTIL.SearchAvatar( mUSER[tUserIndex].mAvatarInfo.aStudent, tUserIndex );
		if( tOtherAvatarIndex == -1 )
		{
			return;
		}
		if( strcmp( mUSER[tOtherAvatarIndex].mAvatarInfo.aTeacher, mUSER[tUserIndex].mAvatarInfo.aName ) == 0 )
		{
			mTRANSFER.B_TEACHER_STATE_RECV( 0 );
		}
		else
		{
			mTRANSFER.B_TEACHER_STATE_RECV( 1 );
		}
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
}
//W_PARTY_ASK_SEND
void W_PARTY_ASK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	if(124 == mSERVER_INFO.mServerNumber)
		return;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	int tOtherAvatarIndex;

	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, "" ) != 0 )
	{
		if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName ) != 0 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if( mAVATAR_OBJECT[tUserIndex].CheckCommunityWork() )
	{
		mTRANSFER.B_PARTY_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_PARTY_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( tAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mTRANSFER.B_PARTY_ANSWER_RECV( 4 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( strcmp( mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName, "" ) != 0 )
	{
		mTRANSFER.B_PARTY_ANSWER_RECV( 6 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe ) && ( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mGAME.ReturnAllianceTribe( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#ifdef __GOD__
	if(abs((mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2)
				- (mUSER[tOtherAvatarIndex].mAvatarInfo.aLevel1 + mUSER[tOtherAvatarIndex].mAvatarInfo.aLevel2)) > 9)
#else
	if( abs( mUSER[tUserIndex].mAvatarInfo.aLevel1 - mUSER[tOtherAvatarIndex].mAvatarInfo.aLevel1 ) > 9 )
#endif
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork() ) )
	{
		mTRANSFER.B_PARTY_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_PARTY_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 1;
	strncpy( mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 2;
	strncpy( mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mTRANSFER.B_PARTY_ASK_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0] );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	LOG_TO_FILE_2("!party ask, %s, %s\n",  mAVATAR_OBJECT[tUserIndex].mDATA.aName,
			mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName);
}
//W_PARTY_CANCEL_SEND
void W_PARTY_CANCEL_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState != 2 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
	mTRANSFER.B_PARTY_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_PARTY_ANSWER_SEND
void W_PARTY_ANSWER_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tAnswer;
	CopyMemory( &tAnswer, &tPacket[1], 4 );

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 2 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
		break;
	default :
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState != 1 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
		break;
	default :
		return;
	}
	mTRANSFER.B_PARTY_ANSWER_RECV( tAnswer );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	LOG_TO_FILE_3("!party answer, %s, %s, %d\n",  mAVATAR_OBJECT[tUserIndex].mDATA.aName,
			mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, tAnswer);
}
//W_PARTY_MAKE_SEND
void W_PARTY_MAKE_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	if( mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 3 )
	{
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, "" ) != 0 )
	{
		return;
	}
	strncpy( mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH );
	strncpy( mAVATAR_OBJECT[tUserIndex].mDATA.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_PARTY_MAKE_RECV();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	LOG_TO_FILE_1("!party make, %s\n",  mAVATAR_OBJECT[tUserIndex].mDATA.aName);
}
//W_PARTY_JOIN_SEND
void W_PARTY_JOIN_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 3 )
	{
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, "" ) == 0 )
	{
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName ) != 0 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState != 3 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	strncpy( mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aPartyName, MAX_PARTY_NAME_LENGTH );
	strncpy( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aPartyName, mUSER[tUserIndex].mAvatarInfo.aPartyName, MAX_PARTY_NAME_LENGTH );
	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
	tSort = 104;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH );
	CopyMemory( &tData[MAX_PARTY_NAME_LENGTH], &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
	LOG_TO_FILE_2("!party join, %s, %s\n",  mAVATAR_OBJECT[tUserIndex].mDATA.aName,
			mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName);
}
//W_PARTY_CHAT_SEND
void W_PARTY_CHAT_SEND( int tUserIndex )
{
	//unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory( &tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	if( strcmp( tContent, "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2 )
	{
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, "" ) == 0 )
	{
		return;
	}
	tSort = 105;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH );
	CopyMemory( &tData[MAX_PARTY_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[( MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tContent[0], MAX_CHAT_CONTENT_LENGTH );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );


	char type[50];
	snprintf(type, 50,"W_PARTY_CHAT_SEND");
	mGAMELOG.CHAT_LOG_SEND( tUserIndex, NULL, &tContent[0], type);
}
//W_PARTY_LEAVE_SEND
void W_PARTY_LEAVE_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, "" ) == 0 )
	{
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName ) == 0 )
	{
		return;
	}
	tSort = 106;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH );
	CopyMemory( &tData[MAX_PARTY_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
	LOG_TO_FILE_1("!party leave, %s\n",  mAVATAR_OBJECT[tUserIndex].mDATA.aName);
}
//W_PARTY_EXILE_SEND
void W_PARTY_EXILE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, "" ) == 0 )
	{
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName ) != 0 )
	{
		return;
	}
	tSort = 107;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH );
	CopyMemory( &tData[MAX_PARTY_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
	LOG_TO_FILE_1("!party exile, %s\n",  mAVATAR_OBJECT[tUserIndex].mDATA.aName);
}
//W_PARTY_INFO_SEND
void W_PARTY_INFO_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tAvatarName01[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName02[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName03[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName04[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName05[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName01[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName01[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	CopyMemory( &tAvatarName02[0], &tPacket[( 1 + MAX_AVATAR_NAME_LENGTH )], MAX_AVATAR_NAME_LENGTH );
	tAvatarName02[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	CopyMemory( &tAvatarName03[0], &tPacket[( 1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], MAX_AVATAR_NAME_LENGTH );
	tAvatarName03[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	CopyMemory( &tAvatarName04[0], &tPacket[( 1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], MAX_AVATAR_NAME_LENGTH );
	tAvatarName04[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	CopyMemory( &tAvatarName05[0], &tPacket[( 1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], MAX_AVATAR_NAME_LENGTH );
	tAvatarName05[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, "" ) == 0 )
	{
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName ) != 0 )
	{
		return;
	}
	tSort = 108;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH );
	CopyMemory( &tData[MAX_PARTY_NAME_LENGTH], &tAvatarName01[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[( MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tAvatarName02[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[( MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tAvatarName03[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[( MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tAvatarName04[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[( MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tAvatarName05[0], MAX_AVATAR_NAME_LENGTH );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
	LOG_TO_FILE_1("!party info1, %s\n",  mAVATAR_OBJECT[tUserIndex].mDATA.aName);
	LOG_TO_FILE_4("!party info list, %s, %s, %s, %s",  tAvatarName01, tAvatarName02,
			tAvatarName03, tAvatarName04);
	LOG_TO_FILE_1(", %s\n",  tAvatarName05);
}
//W_PARTY_BREAK_SEND
void W_PARTY_BREAK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, "" ) == 0 )
	{
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName ) != 0 )
	{
		return;
	}
	tSort = 109;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH );
	CopyMemory( &tData[MAX_PARTY_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
	LOG_TO_FILE_1("party break %s\n",  mUSER[tUserIndex].mAvatarInfo.aName);
}
//W_GUILD_ASK_SEND
void W_GUILD_ASK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	if(124 == mSERVER_INFO.mServerNumber)
		return;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	int tOtherAvatarIndex;

	if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) && ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 1 ) ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mAVATAR_OBJECT[tUserIndex].CheckCommunityWork() )
	{
		mTRANSFER.B_GUILD_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_GUILD_ANSWER_RECV( 3 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( tAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		mTRANSFER.B_GUILD_ANSWER_RECV( 4 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( strcmp( mUSER[tOtherAvatarIndex].mAvatarInfo.aGuildName, "" ) != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( ( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork() ) )
	{
		mTRANSFER.B_GUILD_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11 ) || ( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12 ) )
	{
		mTRANSFER.B_GUILD_ANSWER_RECV( 5 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 1;
	strncpy( mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 2;
	strncpy( mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH );
	mTRANSFER.B_GUILD_ASK_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0] );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_GUILD_CANCEL_SEND
void W_GUILD_CANCEL_SEND( int tUserIndex )
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mGuildProcessState != 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState != 2 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
	mTRANSFER.B_GUILD_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_GUILD_ANSWER_SEND
void W_GUILD_ANSWER_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	int tAnswer;
	CopyMemory( &tAnswer, &tPacket[1], 4 );

	int tOtherAvatarIndex;

	if( mAVATAR_OBJECT[tUserIndex].mGuildProcessState != 2 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
		break;
	default :
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, tUserIndex );
	if( tOtherAvatarIndex == -1 )
	{
		return;
	}
	if( mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState != 1 )
	{
		return;
	}
	if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
	{
		return;
	}
	if( mUSER[tOtherAvatarIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	switch( tAnswer )
	{
	case 0 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 3;
		break;
	case 1 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
		break;
	case 2 :
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
		break;
	default :
		return;
	}
	mTRANSFER.B_GUILD_ANSWER_RECV( tAnswer );
	mUSER[tOtherAvatarIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_GUILD_WORK_SEND
void W_GUILD_WORK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_GUILD_WORK_SIZE];
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tData[0], &tPacket[5], MAX_GUILD_WORK_SIZE );

	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tOtherAvatarIndex;
	char tGuildName[MAX_GUILD_NAME_LENGTH];
	char tGuildNotice[4][MAX_GUILD_NOTICE_LENGTH];
	int tTotalMemberNum;
	int tCost;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tGuildRole;
	char tCallName[MAX_CALL_NAME_LENGTH];
	
	if(124 == mSERVER_INFO.mServerNumber){
		switch(tSort){
			case 2:
			case 5:
			case 9:
				break;
			default:
				return;
		}
	}

	switch( tSort )
	{
	case  1 : //[Ã¢¼³]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		if( ( strcmp( tGuildName, "" ) == 0 ) || ( !mUTIL.CheckNameString( tGuildName ) ) || ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) != 0 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 30 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mUSER[tUserIndex].mAvatarInfo.aMoney < 10000000 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &tGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( mEXTRA_COM.mRecv_Result, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		strncpy( mEXTRA_COM.mRecv_GuildInfo.gName, tGuildName, MAX_GUILD_NAME_LENGTH );
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 101;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &tGuildName[0], MAX_GUILD_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		mGAMELOG.GL_617_GUILD_MONEY( tUserIndex, 10000000, 1, mEXTRA_COM.mRecv_GuildInfo.gGrade);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 10000000;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2( 19, mUSER[tUserIndex].mAvatarInfo.aMoney ); 
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		strncpy( mUSER[tUserIndex].mAvatarInfo.aGuildName, tGuildName, MAX_GUILD_NAME_LENGTH );
		mUSER[tUserIndex].mAvatarInfo.aGuildRole = 0;
		strcpy( mUSER[tUserIndex].mAvatarInfo.aCallName, "" );
		strncpy( mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, tGuildName, MAX_GUILD_NAME_LENGTH );
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = 0;
		strcpy( mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, "" );
		return;
	case  2 : //[Á¤º¸]
		if( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  3 : //[°¡ÀÔ]
		if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) && ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mAVATAR_OBJECT[tUserIndex].mGuildProcessState != 3 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
		tOtherAvatarIndex = mUTIL.SearchAvatar( mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, tUserIndex );
		if( tOtherAvatarIndex == -1 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState != 3 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( strcmp( mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName ) != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( 2, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		tTotalMemberNum = 0;
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( mEXTRA_COM.mRecv_GuildInfo.gMemberName[index01], "" ) != 0 )
			{
				tTotalMemberNum++;
			}
		}
		if( tTotalMemberNum >= ( mEXTRA_COM.mRecv_GuildInfo.gGrade * 10 ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 2, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 102;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		strncpy( mUSER[tOtherAvatarIndex].mAvatarInfo.aGuildName, mUSER[tUserIndex].mAvatarInfo.aGuildName, MAX_GUILD_NAME_LENGTH );
		mUSER[tOtherAvatarIndex].mAvatarInfo.aGuildRole = 2;
		strcpy( mUSER[tOtherAvatarIndex].mAvatarInfo.aCallName, "" );
		strncpy( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aGuildName, mUSER[tUserIndex].mAvatarInfo.aGuildName, MAX_GUILD_NAME_LENGTH );
		mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aGuildRole = 2;
		strcpy( mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aCallName, "" );
		return;
	case  4 : //[Å»Åð]
		if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildRole == 0 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 103;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		strcpy( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" );
		mUSER[tUserIndex].mAvatarInfo.aGuildRole = 0;
		strcpy( mUSER[tUserIndex].mAvatarInfo.aCallName, "" );
		strcpy( mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, "" );
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = 0;
		strcpy( mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, "" );
		return;
	case  5 : //[¾Ë¸²]
		CopyMemory( tGuildNotice, &tData[0], ( 4 * MAX_GUILD_NOTICE_LENGTH ) );
		tGuildNotice[0][( MAX_GUILD_NOTICE_LENGTH - 1 )] = '\0';
		tGuildNotice[1][( MAX_GUILD_NOTICE_LENGTH - 1 )] = '\0';
		tGuildNotice[2][( MAX_GUILD_NOTICE_LENGTH - 1 )] = '\0';
		tGuildNotice[3][( MAX_GUILD_NOTICE_LENGTH - 1 )] = '\0';
		if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], tGuildNotice, ( 4 * MAX_GUILD_NOTICE_LENGTH ) );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 104;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		return;
	case  6 : //[ÇØ»ê]
		if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( 2, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		tTotalMemberNum = 0;
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( mEXTRA_COM.mRecv_GuildInfo.gMemberName[index01], "" ) != 0 )
			{
				tTotalMemberNum++;
			}
		}
		if( tTotalMemberNum != 1 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 2, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mGAMELOG.GL_617_GUILD_MONEY( tUserIndex, 0, 3, mEXTRA_COM.mRecv_GuildInfo.gGrade );
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 105;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		strcpy( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" );
		mUSER[tUserIndex].mAvatarInfo.aGuildRole = 0;
		strcpy( mUSER[tUserIndex].mAvatarInfo.aCallName, "" );
		strcpy( mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, "" );
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = 0;
		strcpy( mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, "" );
		return;
	case  7 : //[È®Àå]
		if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( 2, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		tTotalMemberNum = 0;
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( mEXTRA_COM.mRecv_GuildInfo.gMemberName[index01], "" ) != 0 )
			{
				tTotalMemberNum++;
			}
		}
		if( tTotalMemberNum < ( mEXTRA_COM.mRecv_GuildInfo.gGrade * 10 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch( mEXTRA_COM.mRecv_GuildInfo.gGrade )
		{
		case 1 :
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 50 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aMoney < 20000000 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 20000000;
			break;
		case 2 :
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 70 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aMoney < 30000000 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 30000000;
			break;
		case 3 :
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 90 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aMoney < 40000000 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 40000000;
			break;
		case 4 :
			if( mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aMoney < 50000000 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 50000000;
			break;
		default :
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 106;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		mGAMELOG.GL_617_GUILD_MONEY( tUserIndex, tCost, 2, mEXTRA_COM.mRecv_GuildInfo.gGrade );
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2( 19, mUSER[tUserIndex].mAvatarInfo.aMoney ); 
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  8 : //[Á¦¸í]
		CopyMemory( &tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		if( ( strcmp( tAvatarName, "" ) == 0 ) || ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 107;
		CopyMemory( &tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		return;
	case  9 : //[ÀÓ¸í]
		CopyMemory( &tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tGuildRole, &tData[MAX_AVATAR_NAME_LENGTH], 4 );
		if( ( strcmp( tAvatarName, "" ) == 0 ) || ( tGuildRole < 1 ) || ( tGuildRole > 2 ) || ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tData[( MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tGuildRole, 4 );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 108;
		CopyMemory( &tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tBroadcastInfoData[( MAX_AVATAR_NAME_LENGTH + MAX_GUILD_NAME_LENGTH )], &tGuildRole, 4 );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		return;
	case 10 : //[ÄªÈ£]
		CopyMemory( &tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tCallName[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_CALL_NAME_LENGTH );
		tCallName[( MAX_CALL_NAME_LENGTH - 1 )] = '\0';
		if( ( strcmp( tAvatarName, "" ) == 0 ) || ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tData[( MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tCallName[0], MAX_CALL_NAME_LENGTH );
		if( !mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND( tSort, &tData[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mEXTRA_COM.mRecv_Result != 0 )
		{
			mTRANSFER.B_GUILD_WORK_RECV( 1, tSort, &mEXTRA_COM.mRecv_GuildInfo );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 109;
		CopyMemory( &tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
		CopyMemory( &tBroadcastInfoData[( MAX_AVATAR_NAME_LENGTH + MAX_GUILD_NAME_LENGTH )], &tCallName[0], MAX_CALL_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		return;
	case 11 : //[¹®Àå]
		if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildMarkNum < 1 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aGuildMarkNum--;
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 12 : //[¹®ÆÄ±ê¹ß-ON]
		if( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aGuildMarkEffect = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildMarkEffect = 1;
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 13 : //[¹®ÆÄ±ê¹ß-OFF]
		if( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aGuildMarkEffect = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildMarkEffect = 0;
		mTRANSFER.B_GUILD_WORK_RECV( 0, tSort, &mEXTRA_COM.mRecv_GuildInfo );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	default : //[¿À·ù]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_GUILD_NOTICE_SEND
void W_GUILD_NOTICE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory( &tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	if( strcmp( tContent, "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2 )
	{
		return;
	}
	if( ( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0 ) )
	{
		return;
	}
	tSort = 111;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
	CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[( MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tContent[0], MAX_CHAT_CONTENT_LENGTH );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
}
//W_GUILD_CHAT_SEND
void W_GUILD_CHAT_SEND( int tUserIndex )
{
	//unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory( &tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	if( strcmp( tContent, "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2 )
	{
		return;
	}
	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 )
	{
		return;
	}
	tSort = 112;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH );
	CopyMemory( &tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[( MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], &tContent[0], MAX_CHAT_CONTENT_LENGTH );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );

	char type[50];
	snprintf(type, 50,"W_GUILD_CHAT_SEND");
	mGAMELOG.CHAT_LOG_SEND( tUserIndex, NULL, &tContent[0], type);
}
//W_GUILD_FIND_SEND
void W_GUILD_FIND_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory( &tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	if( strcmp( mUSER[tUserIndex].mAvatarInfo.aGuildName, "" ) == 0 )
	{
		return;
	}
	mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND( &tAvatarName[0] );
	mTRANSFER.B_GUILD_FIND_RECV( mPLAYUSER_COM.mRecv_ZoneNumber );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_TRIBE_WORK_SEND
void W_TRIBE_WORK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int iCount = 0;
	BYTE tData[MAX_TRIBE_WORK_SIZE];
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tData[0], &tPacket[5], MAX_TRIBE_WORK_SIZE );

	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tOtherUserIndex;
	int tTribeWeaponItemNumber;
    // @ Tribe Formation Skill @
    int tTribeSkillSort = 0;
    // @
#ifdef __GOD__
	int tKillOtherTribeNum;
	int tRandomNumber;
	int iIndex;
	ITEM_INFO *tITEM_INFO;
#endif

	switch( tSort )
	{
	case  1 : //[Ç÷¸ÆÅ¸Åë]
		if( mUSER[tUserIndex].mAvatarInfo.aLevel1 > 39 )
		//if( mUSER[tUserIndex].mAvatarInfo.aLevel1 > 145 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += ( mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4 );
		mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
		mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
		mUSER[tUserIndex].mAvatarInfo.aKi = 1;
		mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_TRIBE_WORK_RECV( 0, tSort, &tData[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  2 : //[ºÎ¼¼·ÂÀå_ÀÓ¸í]
		CopyMemory( &tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		if( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) != 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch( mUSER[tUserIndex].mAvatarInfo.aTribe )
		{
		case 0 :
			if( mSERVER_INFO.mServerNumber != 71 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1 :
			if( mSERVER_INFO.mServerNumber != 72 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2 :
			if( mSERVER_INFO.mServerNumber != 73 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3 :
			if( mSERVER_INFO.mServerNumber != 140 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if( strcmp( tAvatarName, "" ) == 0 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
#ifdef __GOD__
		for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
			{
				if( strcmp( mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], tAvatarName ) == 0 )
				{
					break;
				}
			}
			if( index01 < MAX_TRIBE_SUBMASTER_NUM )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
#endif
		for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
		{
			if( strcmp( mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], "" ) == 0 )
			{
				break;
			}
		}
		if( index01 == MAX_TRIBE_SUBMASTER_NUM )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tOtherUserIndex = mUTIL.SearchAvatar( &tAvatarName[0], tUserIndex );
		if( tOtherUserIndex == -1 )
		{
			mTRANSFER.B_TRIBE_WORK_RECV( 1, tSort, &tData[0] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mUSER[tOtherUserIndex].mMoveZoneResult == 1 )
		{
			mTRANSFER.B_TRIBE_WORK_RECV( 1, tSort, &tData[0] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mUSER[tOtherUserIndex].mAvatarInfo.aLevel1 < 113 )
		{
			mTRANSFER.B_TRIBE_WORK_RECV( 2, tSort, &tData[0] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( mUSER[tOtherUserIndex].mAvatarInfo.aKillOtherTribe < 1000 )
		{
			mTRANSFER.B_TRIBE_WORK_RECV( 3, tSort, &tData[0] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		/* SubMaster aName duplicate check */
		for(iCount = 0; iCount < MAX_TRIBE_SUBMASTER_NUM; iCount++) {
			if(!::strcmp(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][iCount], tAvatarName)) {
				mTRANSFER.B_TRIBE_WORK_RECV( 4, tSort, &tData[0] );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
		}
		/* SubMaster duplicate check */
		mTRANSFER.B_TRIBE_WORK_RECV( 0, tSort, &tData[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 60;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
		CopyMemory( &tBroadcastInfoData[4], &index01, 4 );
		CopyMemory( &tBroadcastInfoData[8], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		strncpy( mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], tAvatarName, MAX_AVATAR_NAME_LENGTH );
		return;
	case  3 : //[ºÎ¼¼·ÂÀå_Á¦¸í]
		CopyMemory( &tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		if( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) != 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch( mUSER[tUserIndex].mAvatarInfo.aTribe )
		{
		case 0 :
			if( mSERVER_INFO.mServerNumber != 71 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1 :
			if( mSERVER_INFO.mServerNumber != 72 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2 :
			if( mSERVER_INFO.mServerNumber != 73 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3 :
			if( mSERVER_INFO.mServerNumber != 140 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
		{
			if( strcmp( mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], tAvatarName ) == 0 )
			{
				break;
			}
		}
		if( index01 == MAX_TRIBE_SUBMASTER_NUM )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_TRIBE_WORK_RECV( 0, tSort, &tData[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 61;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
		CopyMemory( &tBroadcastInfoData[4], &index01, 4 );
		CopyMemory( &tBroadcastInfoData[8], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		strcpy( mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], "" );
		return;
	case  4 : //[¼¼·Â¹«±â_Á¦ÀÛ]
		if( ( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) != 1 ) && ( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) != 2 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch( mUSER[tUserIndex].mAvatarInfo.aTribe )
		{
		case 0 :
			if( mSERVER_INFO.mServerNumber != 1 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1 :
			if( mSERVER_INFO.mServerNumber != 6 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2 :
			if( mSERVER_INFO.mServerNumber != 11 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3 :
			if( mSERVER_INFO.mServerNumber != 140 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if( mUSER[tUserIndex].mAvatarInfo.aMoney < 100000000 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch( mUSER[tUserIndex].mAvatarInfo.aTribe )
		{
		case 0 :
			tTribeWeaponItemNumber = 1075;
			break;
		case 1 :
			tTribeWeaponItemNumber = 1076;
			break;
		case 2 :
			tTribeWeaponItemNumber = 1077;
			break;
		case 3 :
			tTribeWeaponItemNumber = 1078;
			break;
		}
		if( !mUTIL.ProcessForDropItem( 10, tTribeWeaponItemNumber, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], 0 ) )
		{
			mTRANSFER.B_TRIBE_WORK_RECV( 1, tSort, &tData[0] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mGAMELOG.GL_641_MAKE_TRIBE_WEAPON( tUserIndex, tTribeWeaponItemNumber, 0, 0, 0 );
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 100000000;
		mTRANSFER.B_TRIBE_WORK_RECV( 0, tSort, &tData[0] );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
    // @ Tribe Formation Skill @
    case  5 : //[¼¼·ÂÁø¹ý]
        CopyMemory( &tTribeSkillSort, &tData[0], 4 );
        if( ( tTribeSkillSort < 0 ) || ( tTribeSkillSort > 4 ) )
        {
            mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
            return;
        }
        if( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) != 1 )
        {
            mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
            return;
        }
        if( ( mGAME.mWorldInfo.mTribePoint[0] <= 100 ) || ( mGAME.mWorldInfo.mTribePoint[1] <= 100 ) || ( mGAME.mWorldInfo.mTribePoint[2] <= 100 ) || ( mGAME.mWorldInfo.mTribePoint[3] <= 100 ) )
        {
            mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
            return;
        }
        if( mGAME.ReturnSmallTribe() != mUSER[tUserIndex].mAvatarInfo.aTribe )
        {
            mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
            return;
        }
        if( mGAME.mWorldInfo.mTribeSymbolBattle != 1 )
        {
            mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
            return;
        }
        mTRANSFER.B_TRIBE_WORK_RECV( 0, tSort, &tData[0] );
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        //--------------//
        //BROADCAST_INFO//
        //--------------//
        tBroadcastInfoSort = 302;
        CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
        CopyMemory( &tBroadcastInfoData[4], &tTribeSkillSort, 4 );
        mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
        //--------------//
        //--------------//
        //--------------//
        return; // @
	default : //[¿À·ù]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_TRIBE_NOTICE_SEND
void W_TRIBE_NOTICE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory( &tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	if( strcmp( tContent, "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2 )
	{
		return;
	}
	if( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) != 1 )
	{
		return;
	}
	tSort = 113;
	CopyMemory( &tData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
	CopyMemory( &tData[MAX_AVATAR_NAME_LENGTH], &tContent[0], MAX_CHAT_CONTENT_LENGTH );
	CopyMemory( &tData[( MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH )], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
	mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
}
//W_TRIBE_CHAT_SEND
void W_TRIBE_CHAT_SEND( int tUserIndex )
{
	//unsigned int tRandom = 0;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		return;
	}
	if(10 >  mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory( &tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	if( strcmp( tContent, "" ) == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	BYTE tAuthType = 0;

	if( mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2 )
	{
		return;
	}
	if(1 == mUSER[tUserIndex].mAuthInfo.AuthType)
		tAuthType = 1;

	mTRANSFER.B_TRIBE_CHAT_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0], tAuthType, &tContent[0] );

	char type[50];
	snprintf(type, 50,"W_TRIBE_CHAT_SEND");
	mGAMELOG.CHAT_LOG_SEND( tUserIndex, NULL, &tContent[0], type);
	for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
	{
		if( !mAVATAR_OBJECT[index01].mCheckValidState )
		{
			continue;
		}
		if( ( mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) && ( mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe( mAVATAR_OBJECT[tUserIndex].mDATA.aTribe ) ) )
		{
			continue;
		}
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	}
}
//W_TRIBE_BANK_SEND
void W_TRIBE_BANK_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tValue;
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tValue, &tPacket[5], 4 );

	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tMoney;

	switch( tSort )
	{
	case 1 : //[Á¶È¸]
		if(mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			if( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) == 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		mPLAYUSER_COM.U_TRIBE_BANK_INFO_VIEW_SEND( mUSER[tUserIndex].mAvatarInfo.aTribe );
		mTRANSFER.B_TRIBE_BANK_RECV( mPLAYUSER_COM.mRecv_Result, 1, &mPLAYUSER_COM.mRecv_TribeBankInfo[0], 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 2 : //[ÀÎÃâ]
		if( ( tValue < 0 ) || ( tValue > ( MAX_TRIBE_BANK_SLOT_NUM - 1 ) ) || ( mGAME.ReturnTribeRole( &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe ) != 1 ) || ( mGAME.ReturnTribeSubMasterNum( mUSER[tUserIndex].mAvatarInfo.aTribe ) < 3 ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mPLAYUSER_COM.U_TRIBE_BANK_INFO_LOAD_SEND( mUSER[tUserIndex].mAvatarInfo.aTribe, tValue, mUSER[tUserIndex].mAvatarInfo.aMoney );
		switch( mPLAYUSER_COM.mRecv_Result )
		{
		case 0 :
			tMoney = mPLAYUSER_COM.mRecv_Money - mUSER[tUserIndex].mAvatarInfo.aMoney;
			mGAMELOG.GL_618_TRIBE_MONEY( tUserIndex, tMoney );
			mUSER[tUserIndex].mAvatarInfo.aMoney = mPLAYUSER_COM.mRecv_Money;
			mTRANSFER.B_TRIBE_BANK_RECV( 0, 2, &mPLAYUSER_COM.mRecv_TribeBankInfo[0], mPLAYUSER_COM.mRecv_Money );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 62;
			CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
			CopyMemory( &tBroadcastInfoData[4], &tMoney, 4 );
			mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
			//--------------//
			//--------------//
			//--------------//
			return;
		default :
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		return;
	default :
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_TRIBE_VOTE_SEND
void W_TRIBE_VOTE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tValue;
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tValue, &tPacket[5], 4 );

	int index01 = 0;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tLevelForTribeVote;
	int tPointForTribeVote;

	switch( tSort )
	{
	case 1 : //[µî·Ï]
		if( ( tValue < 0 ) || ( tValue > ( MAX_TRIBE_VOTE_AVATAR_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mGAME.mWorldInfo.mTribeVoteState[mUSER[tUserIndex].mAvatarInfo.aTribe] != 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mUSER[tUserIndex].mAvatarInfo.aLevel2 < 3 )
		{
			//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 1000 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for( index01 = 0 ; index01 < MAX_TRIBE_VOTE_AVATAR_NUM ; ++index01 )
		{
			if( strcmp( mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], mUSER[tUserIndex].mAvatarInfo.aName ) == 0 )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		for( index01 = 0 ; index01 < MAX_TRIBE_VOTE_AVATAR_NUM ; ++index01 ){
			if( strcmp( mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], "" ) != 0 )
				continue;
			tValue = index01;
			break;
		}
		if (MAX_TRIBE_VOTE_AVATAR_NUM == index01){
			tValue = 0;
			for( index01 = 1 ; index01 < MAX_TRIBE_VOTE_AVATAR_NUM; ++index01 ){
				if(mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] < 
						mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][index01]){
					continue;
				}
				tValue = index01;
			}
			if(mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe <= mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue]){
				mTRANSFER.B_TRIBE_VOTE_RECV( 1, tSort, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
		}

#if 0
		if( strcmp( mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], "" ) != 0 )
		{
			if( mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] >= mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe )
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
#endif
		mTRANSFER.B_TRIBE_VOTE_RECV( 0, tSort, tValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
#ifdef __GOD__
		tLevelForTribeVote = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2 - 112;
#else
		tLevelForTribeVote = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 112;
#endif
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 57;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
		CopyMemory( &tBroadcastInfoData[4], &tValue, 4 );
		CopyMemory( &tBroadcastInfoData[8], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tBroadcastInfoData[( 8 + MAX_AVATAR_NAME_LENGTH )], &tLevelForTribeVote, 4 );
		CopyMemory( &tBroadcastInfoData[( 12 + MAX_AVATAR_NAME_LENGTH )], &mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 4 );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		strncpy( mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH );
		mGAME.mTribeInfo.mTribeVoteLevel[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = tLevelForTribeVote;
		mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
		mGAME.mTribeInfo.mTribeVotePoint[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		return;
	case 2 : //[Ãë¼Ò]
		if( ( tValue < 0 ) || ( tValue > ( MAX_TRIBE_VOTE_AVATAR_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mGAME.mWorldInfo.mTribeVoteState[mUSER[tUserIndex].mAvatarInfo.aTribe] != 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( strcmp( mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], mUSER[tUserIndex].mAvatarInfo.aName ) != 0 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_TRIBE_VOTE_RECV( 0, tSort, tValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 58;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
		CopyMemory( &tBroadcastInfoData[4], &tValue, 4 );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		strcpy( mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], "" );
		mGAME.mTribeInfo.mTribeVoteLevel[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		mGAME.mTribeInfo.mTribeVotePoint[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		return;
	case 3 : //[ÅõÇ¥]
		if( ( tValue < 0 ) || ( tValue > ( MAX_TRIBE_VOTE_AVATAR_NUM - 1 ) ) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mGAME.mWorldInfo.mTribeVoteState[mUSER[tUserIndex].mAvatarInfo.aTribe] != 2 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mUSER[tUserIndex].mAvatarInfo.aLevel2 < 3 )
		{
			//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( strcmp( mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], "" ) == 0 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if( mUSER[tUserIndex].mAvatarInfo.aTribeVoteDate >= mUTIL.ReturnVoteDate() )
		{
			mTRANSFER.B_TRIBE_VOTE_RECV( 1, tSort, tValue );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aTribeVoteDate = mUTIL.ReturnNowDate();
		mTRANSFER.B_TRIBE_VOTE_RECV( 0, tSort, tValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
#ifdef __GOD__
		tPointForTribeVote = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2 * 3 - 112;
#else
		tPointForTribeVote = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 112;
#endif
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 59;
		CopyMemory( &tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4 );
		CopyMemory( &tBroadcastInfoData[4], &tValue, 4 );
		CopyMemory( &tBroadcastInfoData[8], &tPointForTribeVote, 4 );
		mCENTER_COM.U_DEMAND_BROADCAST_INFO( tBroadcastInfoSort, &tBroadcastInfoData[0] );
		//--------------//
		//--------------//
		//--------------//
		return;
	default :
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_CHECK_HACK_INFO
void W_CHECK_HACK_INFO( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tHackName[MAX_HACK_NAME_LENGTH];
	int tHackSize;
	CopyMemory( &tHackName[0], &tPacket[1], MAX_HACK_NAME_LENGTH );
	tHackName[( MAX_HACK_NAME_LENGTH - 1 )] = '\0';
	CopyMemory( &tHackSize, &tPacket[( 1 + MAX_HACK_NAME_LENGTH )], 4 );

	if( mHACKINFO.Check( tHackSize ) )
	{
		mPLAYUSER_COM.U_HACK_NAME_SEND( &mUSER[tUserIndex].uID[0], &tHackName[0], tHackSize );
	}
	mUSER[tUserIndex].mHackCheckTime = GetTickCount();
}
//W_CHECK_N_PROTECT_2
void W_CHECK_N_PROTECT_2( int tUserIndex )
{
	//---------//
	//N-PROTECT//
	//---------//
#ifdef __N_PROTECT__
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	GG_AUTH_DATA tValue;
	CopyMemory( &tValue, &tPacket[1], sizeof( GG_AUTH_DATA ) );

	if( !mUSER[tUserIndex].mCheckNPROTECT )
	{
		mGAMELOG.GL_642_N_PROTECT( tUserIndex, 102 );
		return;
	}
	CopyMemory( &mUSER[tUserIndex].mNPROTECT->m_AuthAnswer, &tValue, sizeof( GG_AUTH_DATA ) );
	if( mUSER[tUserIndex].mNPROTECT->CheckAuthAnswer() != 0 )
	{
		mGAMELOG.GL_642_N_PROTECT( tUserIndex, 103 );
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch( mUSER[tUserIndex].mNumberForNPROTECT )
	{
	case 1 :
		if( mUSER[tUserIndex].mNPROTECT->GetAuthQuery() != 0 )
		{
			mUSER[tUserIndex].mCheckNPROTECT = FALSE;
			mGAMELOG.GL_642_N_PROTECT( tUserIndex, 105 );
		}
		else
		{
			mUSER[tUserIndex].mCheckNPROTECT = TRUE;
			mUSER[tUserIndex].mNumberForNPROTECT = 2;
			mUSER[tUserIndex].mTickCountForNPROTECT = GetTickCount();
			mTRANSFER.B_CHECK_N_PROTECT_1( &mUSER[tUserIndex].mNPROTECT->m_AuthQuery );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
		return;
	case 2 :
		mUSER[tUserIndex].mCheckNPROTECT = FALSE;
		return;
	}
#endif
	//---------//
	//---------//
	//---------//
}

void W_CHECK_AUTH_KEY (int tUserIndex)
{
    if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }
    if( mUSER[tUserIndex].mMoveZoneResult == 1 )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }

    BYTE bResult = 0;
    CTOZ_CHECK_AUTH_KEY pack;
    char buffer[MAX_MOUSE_PASSWORD_LENGTH] = {0, };

    CopyMemory (&pack, mUSER[tUserIndex].mBUFFER_FOR_RECV, CTOZ_CHECK_AUTH_KEY_SIZE);
    snprintf (buffer, MAX_MOUSE_PASSWORD_LENGTH, "%04d", pack.m_wAuthKey);
    mPLAYUSER_COM.U_CHECK_AUTH_KEY (mUSER[tUserIndex].uID, buffer);
    bResult = static_cast<BYTE> (mPLAYUSER_COM.mRecv_Result);
    if( mPLAYUSER_COM.mRecv_Result != 0 ) {
        mGAMELOG.GL_644_CHECK_AUTH_KEY (tUserIndex);
        mUSER[tUserIndex].m_iTryCountForAuth++;
        bResult = static_cast<BYTE> (mUSER[tUserIndex].m_iTryCountForAuth);
    }

    mTRANSFER.B_CHECK_AUTH_KEY ( bResult );
    mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );

    if (mUSER[tUserIndex].m_iTryCountForAuth >= 3) {
        // 3¹ø ÀÌ»ó Æ²¸° À¯Àú´Â Ã¾·á½ÃÅ°µµ·ÃÇÕ´Ã´Ù.
        mUSER[tUserIndex].Quit ();
    }
}

void W_UPDATE_AUTH_KEY (int tUserIndex)
{
	//unsigned int tRandom = 0;
    if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }
    if( mUSER[tUserIndex].mMoveZoneResult == 1 )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }

    BYTE bResult = 0;
    CTOZ_UPDATE_AUTH_KEY pack;
    char buffer[2][MAX_MOUSE_PASSWORD_LENGTH] = {0, };

    CopyMemory (&pack, mUSER[tUserIndex].mBUFFER_FOR_RECV, CTOZ_UPDATE_AUTH_KEY_SIZE);
    snprintf (buffer[0], MAX_MOUSE_PASSWORD_LENGTH, "%04d", pack.m_wAuthKey[0]);
    snprintf (buffer[1], MAX_MOUSE_PASSWORD_LENGTH, "%04d", pack.m_wAuthKey[1]);
    mPLAYUSER_COM.U_UPDATE_AUTH_KEY (mUSER[tUserIndex].uID, buffer);
    bResult = static_cast<BYTE> (mPLAYUSER_COM.mRecv_Result);
    if( mPLAYUSER_COM.mRecv_Result != 0 )
        mGAMELOG.GL_644_CHECK_AUTH_KEY (tUserIndex);

    mTRANSFER.B_UPDATE_AUTH_KEY ( bResult );
    mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}

void W_ACK_INCOMING_UDP (int tUserIndex)
{
    if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }
    if( mUSER[tUserIndex].mMoveZoneResult == 1 )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }

    CTOZ_ACK_INCOMING_UDP pack;
    ::CopyMemory (&pack, mUSER[tUserIndex].mBUFFER_FOR_RECV, CTOZ_ACK_INCOMING_UDP_SIZE);
    g_BroadCastMgr.CheckArrivedAtClient (pack.m_szName);
}

void W_REQUEST_PRESENT (int tUserIndex)
{
    int iPage = 0, iInvenIndex = 0, iInvenSlot = 0;

    if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }
    if( mUSER[tUserIndex].mMoveZoneResult == 1 )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }

    if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 50 || 
        mUSER[tUserIndex].mAvatarInfo.aTeacherPoint < 200000) {
        mUSER[tUserIndex].Quit ();
        return ;
    }

    int iItemCounts = 0;
    ITEM_INFO* pItem = mITEM.GetPresentItemPtrByGoodwillAmbassador (iItemCounts);
    if (pItem != NULL) {
        if (mUTIL.FindEmptyInvenForItem (tUserIndex, pItem, iPage, iInvenIndex) == true) {
            iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);

            if (iInvenSlot != -1) {
                mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = pItem -> iIndex;
                mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
                mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
                mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = iItemCounts;
                mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
                mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;

                mUSER[tUserIndex].mAvatarInfo.aTeacherPoint -= 200000;

                mTRANSFER.B_REQUEST_PRESENT ( 0, iPage, iInvenSlot, iInvenIndex, pItem -> iIndex );
                mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
                return ;
            }
        } 

        // ... ... ...
        mTRANSFER.B_REQUEST_PRESENT ( 1, iPage, iInvenSlot, iInvenIndex, pItem -> iIndex );
        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        return ;
    }

    // .... .. . .. .. .. ......
    mTRANSFER.B_REQUEST_PRESENT( 2, iPage, iInvenSlot, iInvenIndex, 0 );
    mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}

void W_CHANGE_PLAYTIMETOTEACHERPOINT (int tUserIndex)
{
	return;
    if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }
    if( mUSER[tUserIndex].mMoveZoneResult == 1 )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }
    if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 50){
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
    int iTeacherPoints = mUSER[tUserIndex].mAvatarInfo.aPlayTime3 * 250;
    mUSER[tUserIndex].mAvatarInfo.aPlayTime3 = 0;
    mUSER[tUserIndex].mAvatarInfo.aTeacherPoint += iTeacherPoints;

    mTRANSFER.B_CHANGE_PLAYTIMETOTEACHERPOINT (0, iTeacherPoints);
    mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
}

void W_CHECK_EVENT_INFO(int tUserIndex)
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mTRANSFER.B_CHECK_EVENT_INFO();
    mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize, false);
}

void W_GET_RANK_INFO(int tUserIndex)
{
	//LOG_TO_FILE_1("tUserIndex : %d\n", tUserIndex);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[9];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState ) {
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mTRANSFER.B_GET_RANK_INFO(tPacket, tUserIndex);
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize, false);
}

void W_CHANGE_AUTO_INFO( int tUserIndex )
{
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__); // ÀÚµ¿¹°¾à ±â´É Á¦°Å·Î ÀÎÇØ ÇØ´ç ÆÐÅ¶À» ¸·½À´Ï´Ù. 2009.09.24
	return;

	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tValue01;
	int tValue02;
	CopyMemory( &tValue01, &tPacket[1], 4 );
	CopyMemory( &tValue02, &tPacket[5], 4 );

	if( ( tValue01 < 0 ) || ( tValue01 > 99 ) || ( tValue02 < 0 ) || ( tValue02 > 99 ) )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	//(100113 ÀÌ½ÂÇö) Á¸ ÀÌµ¿½Ã ÀÚµ¿¹°¾à ÃÊ±âÈ­ ¹ö±× ¼öÁ¤
	if ( mGAME.Check_Use_Auto_Day( tUserIndex ) > 0 )
	{
		mUSER[tUserIndex].mAvatarInfo.aAutoLifeRatio		= tValue01;
		mUSER[tUserIndex].mAvatarInfo.aAutoManaRatio		= tValue02;
	}
	else
	{
		mUSER[tUserIndex].mAvatarInfo.aAutoLifeRatio		= 0;
		mUSER[tUserIndex].mAvatarInfo.aAutoManaRatio		= 0;
	}
}

#ifdef __ANIMAL__
//W_ANIMAL_STATE_SEND
void W_ANIMAL_STATE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tValue01;
	int tValue02;
	CopyMemory( &tValue01, &tPacket[1], 4 );
	CopyMemory( &tValue02, &tPacket[5], 4 );

	switch( tValue01 )
	{
		case 1 : //[¿µ¼ö¼±ÅÃ]
			if( ( tValue02 < 0 ) || ( tValue02 > ( MAX_AVATAR_ANIMAL_NUM - 1 ) ) )
			{
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue02] == 0 )
			{
				return;
			}
			if( ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM ) && ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= ( MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1 ) ) )
			{
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aAnimalIndex = tValue02;
			mTRANSFER.B_ANIMAL_STATE_RECV( tValue01, tValue02 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case 2 : //[¼±ÅÃÇØÁ¦]
			if( ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM ) && ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= ( MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1 ) ) )
			{
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aAnimalIndex = -1;
			mTRANSFER.B_ANIMAL_STATE_RECV( tValue01, tValue02 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		case 3 : //[¿µ¼ö¼ÒÈ¯]
			if( ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 0 ) || ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex > ( MAX_AVATAR_ANIMAL_NUM - 1 ) ) )
			{
				return;
			}
			if( mUSER[tUserIndex].mAvatarInfo.aAnimalTime < 1 )
			{
				return;
			}
			if( mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1 )
			{
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aAnimalIndex += MAX_AVATAR_ANIMAL_NUM;
			mTRANSFER.B_ANIMAL_STATE_RECV( tValue01, tValue02 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = mUSER[tUserIndex].mAvatarInfo.aAnimal[( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - MAX_AVATAR_ANIMAL_NUM )];
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			if( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue )
			{
				mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
			}
			if( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue )
			{
				mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_1( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber, 0, 0 );
			mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1 );
			mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
			return;
		case 4 : //[¼ÒÈ¯ÇØÁ¦]
			if( ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < MAX_AVATAR_ANIMAL_NUM ) || ( mUSER[tUserIndex].mAvatarInfo.aAnimalIndex > ( MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1 ) ) )
			{
				return;
			}

			mUSER[tUserIndex].mAvatarInfo.aAnimalIndex -= MAX_AVATAR_ANIMAL_NUM;
			mTRANSFER.B_ANIMAL_STATE_RECV( tValue01, tValue02 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = 0;
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			if( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue )
			{
				mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
			}
			if( mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue )
			{
				mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_1( tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 12, 0, 0, 0 );
			mUTIL.Broadcast( TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1 );
			return;
		default :
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
	}
}
#endif


//W_MEDAL_EXCHANGE_SEND
void W_MEDAL_EXCHANGE_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if( mUSER[tUserIndex].mMoveZoneResult == 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tPage;
	int tIndex;
	int tValue;
	ITEM_INFO *tITEM_INFO;
	int tItem;
	int tItemCount;
	int tRandomValue;
	int iPage;
	int iInvenIndex;
	int iInvenSlot = -1;

	CopyMemory( &tPage, &tPacket[1], 4 );
	CopyMemory( &tIndex, &tPacket[5], 4 );
	CopyMemory( &tValue, &tPacket[9], 4 );
	
	if( tPage == 1 )
	{
		if( mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate() )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO = mITEM.Search( mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] );
	if( tITEM_INFO == NULL )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 99){
		mTRANSFER.B_MEDAL_EXCHANGE_RECV( 1, tPage, iInvenSlot, tIndex, tValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	tItemCount = 0;
	switch(tITEM_INFO->iIndex){
		case 1330:
			tRandomValue = rand_mir() % 1000;
			if(100 > tRandomValue){
				tItem = 1020;
			}
			else if(400 > tRandomValue){
				tItem = 1021;
			}
			else if(700 > tRandomValue){
				tItem = 1022;
			}
			else if(800 > tRandomValue){
				tItem = 1024;
			}
			else if(950 > tRandomValue){
				tItem = 1036;
			}
			else if(980 > tRandomValue){
				tItem = 1001;
				tItemCount = 99;
			}
			else if(990 > tRandomValue){
				tItem = 1002;
			}
			else{
				tItem = 1005;
			}
			break;
		case 1329:
			tRandomValue = rand_mir() % 1000;
			if(100 > tRandomValue){
				tItem = 1021;
			}
			else if(400 > tRandomValue){
				tItem = 1022;
			}
			else if(700 > tRandomValue){
				tItem = 1023;
			}
			else if(800 > tRandomValue){
				tItem = 1025;
			}
			else if(950 > tRandomValue){
				tItem = 1037;
			}
			else if(980 > tRandomValue){
				tItem = 1001;
				tItemCount = 99;
			}
			else if(990 > tRandomValue){
				tItem = 1003;
			}
			else{
				tItem = 1004;
			}
			break;
		case 1328:
			tRandomValue = rand_mir() % 1000;
			
			switch( mUSER[tUserIndex].mAvatarInfo.aPreviousTribe )
			{
			case 0 :
				
				if(125 > tRandomValue){
					tItem = 84481;
				}
				else if(250 > tRandomValue){
					tItem = 84505;
				}
				else if(375 > tRandomValue){
					tItem = 84529;
				}
				else if(500 > tRandomValue){
					tItem = 84553;
				}
				else if(625 > tRandomValue){
					tItem = 84577;
				}
				else if(750 > tRandomValue){
					tItem = 84601;
				}
				else if(875 > tRandomValue){
					tItem = 84625;
				}
				else{
					tItem = 84649;
				}
				
			break;
			case 1:
				if(125 > tRandomValue){
					tItem = 85481;
				}
				else if(250 > tRandomValue){
					tItem = 85505;
				}
				else if(375 > tRandomValue){
					tItem = 85529;
				}
				else if(500 > tRandomValue){
					tItem = 85553;
				}
				else if(625 > tRandomValue){
					tItem = 85577;
				}
				else if(750 > tRandomValue){
					tItem = 85601;
				}
				else if(875 > tRandomValue){
					tItem = 85625;
				}
				else{
					tItem = 85649;
				}
			break;
			case 2:
				if(125 > tRandomValue){
					tItem = 86481;
				}
				else if(250 > tRandomValue){
					tItem = 86505;
				}
				else if(375 > tRandomValue){
					tItem = 86529;
				}
				else if(500 > tRandomValue){
					tItem = 86553;
				}
				else if(625 > tRandomValue){
					tItem = 86577;
				}
				else if(750 > tRandomValue){
					tItem = 86601;
				}
				else if(875 > tRandomValue){
					tItem = 86625;
				}
				else{
					tItem = 86649;
				}
			break;
			}
			
			
			
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
	}
	if(tItem == 1001) {
		tITEM_INFO = mITEM.Search(1129);
	} else {
		tITEM_INFO = mITEM.Search(tItem);
	}
	if (tITEM_INFO == NULL) {
		mTRANSFER.B_MEDAL_EXCHANGE_RECV( 1, tPage, iInvenSlot, tIndex, tValue );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if (mUTIL.FindEmptyInvenForItem (tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true) {
		if(tItem == 1001 && tITEM_INFO->iIndex == 1129){
			tITEM_INFO = mITEM.Search(1001);
			if (tITEM_INFO == NULL) {
				mTRANSFER.B_MEDAL_EXCHANGE_RECV( 1, tPage, iInvenSlot, tIndex, tValue );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
		}
		iInvenSlot = mUTIL.GetEmptyInvenSlotIndex (tUserIndex, iPage);
		if (iInvenSlot != -1) {
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO -> iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
			
			

			if(tITEM_INFO -> iIndex == 84481 || 
			tITEM_INFO -> iIndex == 84505 ||  
			tITEM_INFO -> iIndex == 84529 ||  
			tITEM_INFO -> iIndex == 84553 ||  
			tITEM_INFO -> iIndex == 84577 ||   
			tITEM_INFO -> iIndex == 84601 || 
			tITEM_INFO -> iIndex == 84625 || 
			tITEM_INFO -> iIndex == 84649 || 
			tITEM_INFO -> iIndex == 85481 || 
			tITEM_INFO -> iIndex == 85505 ||  
			tITEM_INFO -> iIndex == 85529 ||  
			tITEM_INFO -> iIndex == 85553 ||  
			tITEM_INFO -> iIndex == 85577 ||   
			tITEM_INFO -> iIndex == 85601 || 
			tITEM_INFO -> iIndex == 85625 || 
			tITEM_INFO -> iIndex == 85649 ||
			tITEM_INFO -> iIndex == 86481 || 
			tITEM_INFO -> iIndex == 86505 ||  
			tITEM_INFO -> iIndex == 86529 ||   
			tITEM_INFO -> iIndex == 86553 ||  
			tITEM_INFO -> iIndex == 86577 ||   
			tITEM_INFO -> iIndex == 86601 || 
			tITEM_INFO -> iIndex == 86625 || 
			tITEM_INFO -> iIndex == 86649){
				
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
			}
			else{
				
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			}
			
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = tItemCount;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = mUTIL.ReturnItemRecognitionNumber( tITEM_INFO->iType );

			mTRANSFER.B_MEDAL_EXCHANGE_RECV( 0, iPage, iInvenSlot, iInvenIndex, tITEM_INFO->iIndex );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			
			
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

			return ;
		}
	} 
	mTRANSFER.B_MEDAL_EXCHANGE_RECV( 1, tPage, iInvenSlot, tIndex, tValue );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}

void W_CORRECT_ANSWER( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	// 2009.11.12 - Sphinx ´äº¯À» ÀÌ¿ëÇÑ ±â¿©µµ Hack ¼öÁ¤.
	// Sphinx Áú¹®À» ÇÏÁö ¾Ê¾Ò´Âµ¥ ÀÀ´äÀ» º¸³»´Â °æ¿ì.
	if (mUSER[tUserIndex].IsSend_Question() == FALSE)
	{
        mGAMELOG.GL_700_SPHINX_HACK(tUserIndex);
        // ÇØ´ç À¯Àú ºí·°.
		mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_1_SEND( 604, &mUSER[tUserIndex].uID[0] );
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
    }

	char temp_string[ 10 ];
	::ZeroMemory( temp_string, 10 );
	CopyMemory( &temp_string[ 0 ], &tPacket[ 1 ], 5 );
	/// Compare Logic
	if ( FALSE == strncmp( temp_string, mUSER[tUserIndex].Get_Sphinx_Question(), 5 ) )
	{
		mTRANSFER.B_CORRECT_ANSWER_RESULT( MyUser::RST_OK );
		mUSER[ tUserIndex ].Set_Send_Question( FALSE );
		mWORK.Sphinx_Requital( tUserIndex );
	}	
	else	
	{	
		if ( FALSE == mUSER[ tUserIndex ].IsWrong_CountOver() )
		{
			mUSER[ tUserIndex ].Set_Send_Question( FALSE );
			mTRANSFER.B_CORRECT_ANSWER_RESULT( MyUser::RST_WRONG_ANSWER_0 );
			mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

			mWORK.Sphinx_Question_Control( tUserIndex );
			return;
		}
		else
		{
			mTRANSFER.B_CORRECT_ANSWER_RESULT( MyUser::RST_WRONG_ANSWER_1 );
			mUSER[ tUserIndex ].Set_Send_Question( FALSE );
			mWORK.Sphinx_Punishment( tUserIndex );

			//mWORK.Write_Log( tUserIndex, mWORK.LOG_TYPE::PRISON_WRONG_VALUE );
		}
	}	
	mUSER[tUserIndex].Send (TRUE, (char*) mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
}

// @ Cost Info Download @
void W_GET_CASH_ITEM_INFO_SEND(int tUserIndex)
{
    char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
    if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }
    if( mUSER[tUserIndex].mMoveZoneResult == 1 )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }
    if( mUSER[tUserIndex].mIsValidCashItemInfo == true )
    {
        return;
    }

    mTRANSFER.B_GET_CASH_ITEM_INFO_RECV( 0, mEXTRA_COM.mCashItemInfoVersion, mEXTRA_COM.mCashItemInfo );
    mUSER[tUserIndex].Send(TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

    mUSER[tUserIndex].mIsValidCashItemInfo = true;
} // @

// # Defense Hack # {
//W_SPEED_HACK_SEND
void W_SPEED_HACK_SEND(int tUserIndex)
{
    char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[9];
    if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
    {
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }

    if(::strncmp(mAVATAR_OBJECT[tUserIndex].mDATA.aName, tPacket, MAX_AVATAR_NAME_LENGTH) == 0) {
        mGAMELOG.GL_660_AUTO_CHECK(tUserIndex);
        mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
        return;
    }
} // # }


/** 2009. 11. 18 : Àå½Ä ÇØ¹æ ½Ã½ºÅÛ (wolf) */
void W_TOGGLE_STOPWATCH (int tUserIndex)
{
	if( !mAVATAR_OBJECT[tUserIndex].mCheckValidState )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	CTOZ_TOGGLE_STOPWATCH pack;
	CopyMemory (&pack, mUSER[tUserIndex].mBUFFER_FOR_RECV, CTOZ_TOGGLE_STOPWATCH_TYPESIZE);

	switch (pack.m_bKind) 
	{
	case 0: // Àå½Ä ÇØ¹æ ½Ã½ºÅÛ (±ÝÀå¼­, ÀºÀå¼­) »ç¿ë ¿©ºÎ.
		mUSER[tUserIndex].mAvatarInfo.iUseOrnament = 0;
		if (pack.m_bUse == 1) 
		{
			// ±ÝÀå¼­ È¤Àº ÀºÀå¼­ ½Ã°£ÀÌ ÀÖ´ÂÁö È®ÀÎÇÑ´Ù.
			if (mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime > 0 || mUSER[tUserIndex].mAvatarInfo.iSilverOrnamentRemainsTime > 0) 
			{
				// ÀºÀå¼­ ÀÜ¿© ½Ã°£ÀÌ ÀÖ´Â °æ¿ì¿¡ »ç¿ëÇÏµµ·Ï ÇÑ´Ù.
				if (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 112) 
				{
					// 1°© ºÎÅÍ »ç¿ë°¡´É.
					mUSER[tUserIndex].mAvatarInfo.iUseOrnament = 1;
					mTRANSFER.B_TOGGLE_STOPWATCH (0, pack.m_bKind, 1);
				} 
				else 
				{ // ¼º ·¹º§ÀÎµ¥ ¿äÃ»ÇÑ °æ¿ì - ½ÇÆÐ.
					mTRANSFER.B_TOGGLE_STOPWATCH (1, pack.m_bKind, 0);
				}
			} 
			else 
			{ // »ç¿ë °¡´ÉÇÑ ½Ã°£ÀÌ ¾ø´Âµ¥, ¿äÃ»ÇÑ °æ¿ì - ½ÇÆÐ.
				mTRANSFER.B_TOGGLE_STOPWATCH (2, pack.m_bKind, 0);
			}
		} 
		else 
		{
			if (mUSER[tUserIndex].mAvatarInfo.iUseOrnament == 0) 
			{
				// »ç¿ëÁßÀÎ °æ¿ì¿¡¸¸ ²ô±â¸¦ Çã¿ëÇÑ´Ù.
				mTRANSFER.B_TOGGLE_STOPWATCH (0, pack.m_bKind, 0);
			} 
			else 
			{ // ²¨Á®ÀÖ´Â »óÅÂ¿¡¼­ ²ô±â ¿äÃ»Àº ½ÇÆÐ Ã³¸®ÇÑ´Ù.
				mTRANSFER.B_TOGGLE_STOPWATCH (1, pack.m_bKind, 0);
			}
		}
		break;
	default:
		// Á¤ÀÇµÇÁö ¾ÊÀº Á¾·ùÀÇ ÄÑ°í ²ô±â ¿É¼ÇÀº ¿¡·¯ Ã³¸®ÇÑ´Ù.
		mTRANSFER.B_TOGGLE_STOPWATCH (255, pack.m_bKind, 0);
		break;
	}

	mUSER[tUserIndex].Send (TRUE, reinterpret_cast<char*> (mTRANSFER.mOriginal), mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
}


/** 2009. 11. 18 : Àå½Ä ÇØ¹æ ½Ã½ºÅÛ (wolf) */
//-------------------------------------------------------------------------------------------------
