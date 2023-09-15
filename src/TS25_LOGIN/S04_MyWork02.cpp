//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//INSTANCE
WORKER_FUNCTION W_FUNCTION[256];
//W_LOGIN_SEND
void W_LOGIN_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tID[MAX_USER_ID_LENGTH];
	char tPassword[MAX_USER_PASSWORD_LENGTH];
	int tVersion;
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tPassword[0], &tPacket[( 1 + MAX_USER_ID_LENGTH )], MAX_USER_PASSWORD_LENGTH);
	tPassword[(MAX_USER_PASSWORD_LENGTH - 1)] = '\0';
	CopyMemory(&tVersion, &tPacket[( 1 + MAX_USER_ID_LENGTH + MAX_USER_PASSWORD_LENGTH )], 4);
	memset(mUSER[tUserIndex].mAvatarInfo, 0, sizeof(AVATAR_INFO) * 3);

	int index01;
	int index02;
	int index03;
	int tResult;
	char first_login = '0';
	char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH];
	//__LogMgr()->Log("tID:%s   pw:%s    tVersion:%d  %d  %d",tID,tPassword,tVersion,MAX_USER_ID_LENGTH,MAX_USER_PASSWORD_LENGTH);
	if (mGAME.mMaxPlayerNum == 0)
	{
		mTRANSFER.B_LOGIN_RECV(1, &tID[0], 0, 0, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (1)] The server is not yet ready - Maximum User Number is 0.\n");
		return;
	}
	if (mGAME.CompareBlockIPInfo(mUSER[tUserIndex].mIPPart[0], mUSER[tUserIndex].mIPPart[1],
	                             mUSER[tUserIndex].mIPPart[2], mUSER[tUserIndex].mIPPart[3]))
	{
		mTRANSFER.B_LOGIN_RECV(9, &tID[0], 0, 0, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (2)] IP[%s] is blocked from connection attempt.\n", mUSER[tUserIndex].mIP);
		return;
	}
	if (mGAME.mPresentPlayerNum >= mGAME.mMaxPlayerNum)
	{
		mTRANSFER.B_LOGIN_RECV(3, &tID[0], 0, 0, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (3)] You cannot connect to exceed the maximum user number of connections.\n");
		return;
	}
	/*if( tVersion != (mSERVER_INFO.mServerVersion) )
	{
		mTRANSFER.B_LOGIN_RECV( 4, &tID[0], 0, 0, "0000" );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		for( index01 = 0 ; index01 < MAX_USER_AVATAR_NUM ; index01++ )
		{
			mTRANSFER.B_USER_AVATAR_INFO( &mUSER[tUserIndex].mAvatarInfo[index01] );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}*/
	/* Mir PCRoom check - start*/
	mUSER[tUserIndex].uLoginPremiumPCRoom = mDB.DB_PROCESS_14(mUSER[tUserIndex].mIP, tID);
	/* Mir PCRoom check - end  */

	mDB.DB_PROCESS_02(&mUSER[tUserIndex].mIP[0], &tID[0], &tPassword[0], &mUSER[tUserIndex].uID[0],
	                  &mUSER[tUserIndex].uCheckMOTP, &mUSER[tUserIndex].uMousePassword[0],
	                  &mUSER[tUserIndex].uSecretCard, &mUSER[tUserIndex].uUserSort, &mUSER[tUserIndex].uGoodFellow,
	                  &mUSER[tUserIndex].uLoginPlace, &mUSER[tUserIndex].uLoginPremium, &mUSER[tUserIndex].uTraceState,
	                  &mUSER[tUserIndex].uBonus100Money, &mUSER[tUserIndex].uPremiumServerExpirationDate,
	                  &mUSER[tUserIndex].uSaveMoney, &mUSER[tUserIndex].uSaveMoney2, mUSER[tUserIndex].uSaveItem,
	                  mUSER[tUserIndex].mAvatarInfo, &mUSER[tUserIndex].mAuthInfo, &tResult,
	                  &first_login); // &mUSER[tUserIndex].uPremiumServerExpirationDate �߰�. // @_Premium_Server_@
	if (tResult != 0)
	{
		mTRANSFER.B_LOGIN_RECV(tResult, &tID[0], 0, 0, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (%d)] Login failed by database.\n", tResult);
		return;
	}

	// # GM Enable Login IP # {
	/*if (mUSER[tUserIndex].mAuthInfo.AuthType != 0)
	{
	    if (!mGAME.mGMEnableLoginIPList.CompareIPInfo( mUSER[tUserIndex].mIPPart[0], mUSER[tUserIndex].mIPPart[1], mUSER[tUserIndex].mIPPart[2], mUSER[tUserIndex].mIPPart[3] ) )
	    {
	        mTRANSFER.B_LOGIN_RECV( 2, &tID[0], 0, 0, "0000" );
	        mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	        for( index01 = 0 ; index01 < MAX_USER_AVATAR_NUM ; index01++ )
	        {
	            mTRANSFER.B_USER_AVATAR_INFO( &mUSER[tUserIndex].mAvatarInfo[index01] );
	            mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	        }
			mTRANSFER.B_RCMD_WORLD_SEND();
			mUSER[tUserIndex].Send( TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	        __LogMgr()->Log ("![WARNING - (2)] GM Login IP[%s] is blocked from connection attempt.\n", mUSER[tUserIndex].mIP);
	        return;
	    }
	}*/
	// # }

	mPLAYUSER_COM.U_REGISTER_USER_FOR_LOGIN_1_SEND(&mUSER[tUserIndex].mIP[0], &mUSER[tUserIndex].uID[0],
	                                               mUSER[tUserIndex].uUserSort, mUSER[tUserIndex].uGoodFellow,
	                                               mUSER[tUserIndex].uLoginPlace, mUSER[tUserIndex].uLoginPremium,
	                                               mUSER[tUserIndex].uLoginPremiumPCRoom, mUSER[tUserIndex].uTraceState,
	                                               mUSER[tUserIndex].uBonus100Money,
	                                               mUSER[tUserIndex].uPremiumServerExpirationDate,
	                                               &mUSER[tUserIndex].mAuthInfo);
	// mUSER[tUserIndex].uPremiumServerExpirationDate �߰�. // @_Premium_Server_@

	switch (mPLAYUSER_COM.mRecv_Result)
	{
	case 0:
		break;
	case 1:
		mTRANSFER.B_LOGIN_RECV(8, &tID[0], 0, 0, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (8)] You cannot connect to exceed the maximum user number of connections.\n");
		return;
	case 2:
		mTRANSFER.B_LOGIN_RECV(5, &tID[0], 0, 0, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (5)] You cannot connect to exceed the maximum user number of connections.\n");
		return;
	case 3:
		mTRANSFER.B_LOGIN_RECV(5, &tID[0], 0, 0, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (5)] Login failed state change.\n", tResult);
		return;
	case 4:
		mTRANSFER.B_LOGIN_RECV(13, &tID[0], 0, 0, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (13)] Have the right to the same IP can not log on the premium.\n");
		return;
	default:
		mTRANSFER.B_LOGIN_RECV(5, &tID[0], 0, 0, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	mUSER[tUserIndex].mCheckValidState = TRUE;
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mPlayUserIndex = mPLAYUSER_COM.mRecv_PlayUserIndex;
	mUSER[tUserIndex].mSecondLoginTryNum = 0;
	mUSER[tUserIndex].mSecondLoginSort = 0;

	//if( mUSER[tUserIndex].uCheckMOTP == 0 )
	//{
	mUSER[tUserIndex].mSecondLoginSort = 1;
	//}


	mUSER[tUserIndex].mCheckDemandGiftIfo = FALSE;
	mUSER[tUserIndex].mMoveZoneResult = 0;
	if (strcmp(mUSER[tUserIndex].uMousePassword, "") == 0)
	{
		strcpy(tMousePassword, "");
	}
	else
	{
		strcpy(tMousePassword, "****");
	}

	//__LogMgr()->Log("first_login : %c\n", first_login);
	mTRANSFER.B_LOGIN_RECV(0, &mUSER[tUserIndex].uID[0], mUSER[tUserIndex].uUserSort,
	                       mUSER[tUserIndex].mSecondLoginSort, &tMousePassword[0], first_login);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
	{
		if (strcmp(&mUSER[tUserIndex].mAvatarInfo[index01].aName[0], "") == 0)
		{
			continue;
		}
		if (mUSER[tUserIndex].mAvatarInfo[index01].aExpandInventoryDate < mGAME.ReturnNowDate())
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aExpandInventoryDate = 0;
		}
		if (mUSER[tUserIndex].mAvatarInfo[index01].aExpandStoreDate < mGAME.ReturnNowDate())
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aExpandStoreDate = 0;
		}
		if (mUSER[tUserIndex].mAvatarInfo[index01].aAutoHunt7Day < mGAME.ReturnNowDate())
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aAutoHunt7Day = 0;
		}
		if (mUSER[tUserIndex].mAvatarInfo[index01].aAutoBuffScroll < mGAME.ReturnNowDate())
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aAutoBuffScroll = 0;
		}
		if (mUSER[tUserIndex].mAvatarInfo[index01].aPetInventoryDate < mGAME.ReturnNowDate())
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aPetInventoryDate = 0;
		}

		for (index02 = 0; index02 < MAX_EQUIP_SLOT_NUM; index02++)
		{
			if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][0]))
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][3] = 0;
			}
		}
		for (index02 = 0; index02 < 2; index02++)
		{
			for (index03 = 0; index03 < MAX_INVENTORY_SLOT_NUM; index03++)
			{
				if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][0]))
				{
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][0] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][1] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][2] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][3] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][4] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][5] = 0;
				}
			}
		}
		for (index02 = 0; index02 < MAX_TRADE_SLOT_NUM; index02++)
		{
			if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][0]))
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][3] = 0;
			}
		}
		for (index02 = 0; index02 < 2; index02++)
		{
			for (index03 = 0; index03 < MAX_STORE_ITEM_SLOT_NUM; index03++)
			{
				if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][0]))
				{
					mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][0] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][1] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][2] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][3] = 0;
				}
			}
		}
		for (index02 = 0; index02 < 3; index02++)
		{
			for (index03 = 0; index03 < MAX_HOT_KEY_NUM; index03++)
			{
				switch (mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2])
				{
				case 1:
					if ((mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] < 1) || (mUSER[tUserIndex].
						mAvatarInfo[index01].aHotKey[index02][index03][1] < 1))
					{
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					}
					break;
				case 2:
					if ((mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] < 1) || (mUSER[tUserIndex].
						mAvatarInfo[index01].aHotKey[index02][index03][1] != 0))
					{
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					}
					break;
				case 3:
					if ((mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] < 1) || (mUSER[tUserIndex].
						mAvatarInfo[index01].aHotKey[index02][index03][1] < 1))
					{
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					}
					if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0]))
					{
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					}
					break;
				default:
					mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					break;
				}
			}
		}
		if (mUSER[tUserIndex].mAvatarInfo[index01].aSearchAndBuyDate < mGAME.ReturnNowDate())
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aSearchAndBuyDate = 0;
		}
		for (index02 = 0; index02 < MAX_SAVE_ITEM_SLOT_NUM; index02++)
		{
			if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][0]))
			{
				mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][3] = 0;
			}
		}
		// @ __WEB_MALL__
		if (0 == index01)
		CopyMemory(mUSER[tUserIndex].uSaveItem, mUSER[tUserIndex].mAvatarInfo[0].uSaveItem,
		           ( MAX_SAVE_ITEM_SLOT_NUM * 4 * 4 ));
		// __WEB_MALL__ @
	}

#ifdef __WEB_MALL__
    int index04 = 0;
    int tList[MAX_SAVE_ITEM_SLOT_NUM][3];
    int tCount = 0;
    int tRemainSave = 0;
    GIFT_INFO tGiftInfo[MAX_SAVE_ITEM_SLOT_NUM];

    WEBMALL_INFO tWebMallInfo[MAX_SAVE_ITEM_SLOT_NUM];

    for(index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; ++index01){
        if( 1 > mUSER[tUserIndex].uSaveItem[index01][0])
            ++tRemainSave;
    }
    ::memset(tList, 0, ( MAX_SAVE_ITEM_SLOT_NUM * 4 * 3 ));
    ::memset(tWebMallInfo, 0, sizeof(WEBMALL_INFO) * MAX_SAVE_ITEM_SLOT_NUM);

    if(0 < tRemainSave){
        if(mDB.DB_PROCESS_18(tID, tRemainSave, &tList[0][0], tCount, tWebMallInfo)){
            if(0 != tCount){
                for(index01 = 0; index01 < tCount; ++index01){
                    for(index02 = 0; index02 < tList[index01][1]; ++index02){
                        tRemainSave -= tWebMallInfo[index01].mTotalGiftNum;
                        if (0 > tRemainSave)
                            break;
                        ++tList[index01][2];
                    }
                    if (0 > tRemainSave)
                        break;
                }

                index04 = 0;
                for(index01 = 0; index01 < tCount; ++index01){
                    if(0 >= tList[index01][2])
                        break;

                    if (mDB.DB_PROCESS_19(tID, tList[index01][0], tList[index01][2] , tWebMallInfo[index01].mWebMallSeq )){
                        for(index02 = 0; index02 < tList[index01][2]; ++index02){
                            for(index03 = 0; index03 < tWebMallInfo[index01].mTotalGiftNum; ++index03){
                                for (; index04 < MAX_SAVE_ITEM_SLOT_NUM; ++index04){
                                    if(0 < mUSER[tUserIndex].uSaveItem[index04][0])
                                        continue;
                                    mUSER[tUserIndex].uSaveItem[index04][0] = tWebMallInfo[index01].mGiftData[index03][0];
                                    mUSER[tUserIndex].uSaveItem[index04][1] = tWebMallInfo[index01].mGiftData[index03][1];
                                    mUSER[tUserIndex].uSaveItem[index04][2] = 0;
                                    mUSER[tUserIndex].uSaveItem[index04][3] = 0;
                                    ++index04;
                                    break;
                                }
                            }
                        }
                        //mGAMELOG.GL_505_WEB_MALL(tID, tList[index01]);
                        CopyMemory( &mUSER[tUserIndex].mAvatarInfo[0].uSaveItem[0][0], &mUSER[tUserIndex].uSaveItem[0][0], ( MAX_SAVE_ITEM_SLOT_NUM * 4 * 4 ) );
                        CopyMemory( &mUSER[tUserIndex].mAvatarInfo[1].uSaveItem[0][0], &mUSER[tUserIndex].uSaveItem[0][0], ( MAX_SAVE_ITEM_SLOT_NUM * 4 * 4 ) );
                        CopyMemory( &mUSER[tUserIndex].mAvatarInfo[2].uSaveItem[0][0], &mUSER[tUserIndex].uSaveItem[0][0], ( MAX_SAVE_ITEM_SLOT_NUM * 4 * 4 ) );
                    }
                }
            }
        }
    }
#endif
	// @ __WEB_MALL__
	mDB.DB_PROCESS_11(&mUSER[tUserIndex].uID[0], mUSER[tUserIndex].uSaveItem);
	// __WEB_MALL__ @

	for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
	{
		if (strcmp(&mUSER[tUserIndex].mAvatarInfo[index01].aName[0], "") == 0)
		{
			continue;
		}
		switch (mUSER[tUserIndex].mAvatarInfo[index01].aTribe)
		{
		case 0:
			if (mZONEMAININFO.ReturnZoneTribeInfo1(mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0]) != 0)
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0] = 1;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[1] = 5;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[3] = 4;
			}
			break;
		case 1:
			if (mZONEMAININFO.ReturnZoneTribeInfo1(mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0]) != 1)
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0] = 6;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[1] = -190;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[3] = 1270;
			}
			break;
		case 2:
			if (mZONEMAININFO.ReturnZoneTribeInfo1(mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0]) != 2)
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0] = 11;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[1] = 447;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[2] = 1;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[3] = 440;
			}
			break;
		case 3:
			if (mZONEMAININFO.ReturnZoneTribeInfo1(mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0]) != 3)
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0] = 140;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[1] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[3] = -6;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[4] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[4] = 1;
		}
		if (mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[5] < 0)
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[5] = 0;
		}
		if (mUSER[tUserIndex].uLoginPremiumPCRoom == 2)
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aZone126TypeTime = (60 * 60 * 24 * 7);
		}
	}

	for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
	{
		mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	mTRANSFER.B_RCMD_WORLD_SEND();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_CLIENT_OK_FOR_LOGIN_SEND
void W_CLIENT_OK_FOR_LOGIN_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
}

//W_CREATE_MOUSE_PASSWORD_SEND
void W_CREATE_MOUSE_PASSWORD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH];
	CopyMemory(&tMousePassword[0], &tPacket[1], MAX_MOUSE_PASSWORD_LENGTH);

	int index01;

	if (strlen(tMousePassword) != 4)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		if ((tMousePassword[index01] != '1') && (tMousePassword[index01] != '2') && (tMousePassword[index01] != '3') &&
			(tMousePassword[index01] != '4') && (tMousePassword[index01] != '5') && (tMousePassword[index01] != '6') &&
			(tMousePassword[index01] != '7') && (tMousePassword[index01] != '8') && (tMousePassword[index01] != '9') &&
			(tMousePassword[index01] != '0'))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (!mDB.DB_PROCESS_03(&mUSER[tUserIndex].uID[0], &tMousePassword[0]))
	{
		mTRANSFER.B_CREATE_MOUSE_PASSWORD_RECV(1, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	strcpy(mUSER[tUserIndex].uMousePassword, tMousePassword);
	mUSER[tUserIndex].mSecondLoginSort = 0;
	mTRANSFER.B_CREATE_MOUSE_PASSWORD_RECV(0, &mUSER[tUserIndex].uMousePassword[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_CHANGE_MOUSE_PASSWORD_SEND
void W_CHANGE_MOUSE_PASSWORD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH];
	char tChangeMousePassword[MAX_MOUSE_PASSWORD_LENGTH];
	CopyMemory(&tMousePassword[0], &tPacket[1], MAX_MOUSE_PASSWORD_LENGTH);
	CopyMemory(&tChangeMousePassword[0], &tPacket[( 1 + MAX_MOUSE_PASSWORD_LENGTH )], MAX_MOUSE_PASSWORD_LENGTH);

	int index01;

	if (strlen(tMousePassword) != 4)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		if ((tMousePassword[index01] != '1') && (tMousePassword[index01] != '2') && (tMousePassword[index01] != '3') &&
			(tMousePassword[index01] != '4') && (tMousePassword[index01] != '5') && (tMousePassword[index01] != '6') &&
			(tMousePassword[index01] != '7') && (tMousePassword[index01] != '8') && (tMousePassword[index01] != '9') &&
			(tMousePassword[index01] != '0'))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (strlen(tChangeMousePassword) != 4)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		if ((tChangeMousePassword[index01] != '1') && (tChangeMousePassword[index01] != '2') && (tChangeMousePassword[
			index01] != '3') && (tChangeMousePassword[index01] != '4') && (tChangeMousePassword[index01] != '5') && (
			tChangeMousePassword[index01] != '6') && (tChangeMousePassword[index01] != '7') && (tChangeMousePassword[
			index01] != '8') && (tChangeMousePassword[index01] != '9') && (tChangeMousePassword[index01] != '0'))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, tMousePassword) != 0)
	{
		//		//mGAMELOG.GL_502_MISMATCH_MOUSE_PASSWORD( &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].uMousePassword[0], &tMousePassword[0] );
		mTRANSFER.B_CHANGE_MOUSE_PASSWORD_RECV(1, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mSecondLoginTryNum++;
		if (mUSER[tUserIndex].mSecondLoginTryNum == 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			mPLAYUSER_COM.U_BLOCK_USER_FOR_LOGIN_1_SEND(503, &mUSER[tUserIndex].uID[0]);
			return;
		}
		return;
	}
	if (!mDB.DB_PROCESS_03(&mUSER[tUserIndex].uID[0], &tChangeMousePassword[0]))
	{
		mTRANSFER.B_CHANGE_MOUSE_PASSWORD_RECV(2, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	strcpy(mUSER[tUserIndex].uMousePassword, tChangeMousePassword);
	mUSER[tUserIndex].mSecondLoginSort = 0;
	mTRANSFER.B_CHANGE_MOUSE_PASSWORD_RECV(0, &mUSER[tUserIndex].uMousePassword[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_LOGIN_MOUSE_PASSWORD_SEND
void W_LOGIN_MOUSE_PASSWORD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tMousePasswordInput[MAX_MOUSE_PASSWORD_LENGTH];
	CopyMemory(&tMousePasswordInput[0], &tPacket[1], MAX_MOUSE_PASSWORD_LENGTH);

	int index01;

	if (strlen(tMousePasswordInput) != 4)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		if ((tMousePasswordInput[index01] != '1') && (tMousePasswordInput[index01] != '2') && (tMousePasswordInput[
			index01] != '3') && (tMousePasswordInput[index01] != '4') && (tMousePasswordInput[index01] != '5') && (
			tMousePasswordInput[index01] != '6') && (tMousePasswordInput[index01] != '7') && (tMousePasswordInput[
			index01] != '8') && (tMousePasswordInput[index01] != '9') && (tMousePasswordInput[index01] != '0'))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, tMousePasswordInput) != 0)
	{
		//mGAMELOG.GL_502_MISMATCH_MOUSE_PASSWORD( &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].uMousePassword[0], &tMousePasswordInput[0] );
		mTRANSFER.B_LOGIN_MOUSE_PASSWORD_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mSecondLoginTryNum++;
		if (mUSER[tUserIndex].mSecondLoginTryNum == 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			//mGAMELOG.GL_504_MOUSE_PASS_THREE_OUT(mUSER[tUserIndex].uID);
			//mPLAYUSER_COM.U_BLOCK_USER_FOR_LOGIN_1_SEND( 504, &mUSER[tUserIndex].uID[0] );
			return;
		}
		return;
	}
	mUSER[tUserIndex].mSecondLoginSort = 0;
	mTRANSFER.B_LOGIN_MOUSE_PASSWORD_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_LOGIN_SECRET_CARD_SEND
void W_LOGIN_SECRET_CARD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	//__LogMgr()->Log("ceshi %d",mUSER[tUserIndex].mSecondLoginSort);
	if (mUSER[tUserIndex].mSecondLoginSort != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tSecretCardInput01[3];
	char tSecretCardInput02[3];
	CopyMemory(&tSecretCardInput01[0], &tPacket[1], 3);
	CopyMemory(&tSecretCardInput02[0], &tPacket[4], 3);

	int index01;
	char tSecretCardInput03[5];
	char tSecretCardContent01[5];
	char tSecretCardContent02[5];
	char tSecretCardContent03[5];

	if (strlen(tSecretCardInput01) != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < 2; index01++)
	{
		if ((tSecretCardInput01[index01] != '1') && (tSecretCardInput01[index01] != '2') && (tSecretCardInput01[index01]
			!= '3') && (tSecretCardInput01[index01] != '4') && (tSecretCardInput01[index01] != '5') && (
			tSecretCardInput01[index01] != '6') && (tSecretCardInput01[index01] != '7') && (tSecretCardInput01[index01]
			!= '8') && (tSecretCardInput01[index01] != '9') && (tSecretCardInput01[index01] != '0'))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (strlen(tSecretCardInput02) != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < 2; index01++)
	{
		if ((tSecretCardInput02[index01] != '1') && (tSecretCardInput02[index01] != '2') && (tSecretCardInput02[index01]
			!= '3') && (tSecretCardInput02[index01] != '4') && (tSecretCardInput02[index01] != '5') && (
			tSecretCardInput02[index01] != '6') && (tSecretCardInput02[index01] != '7') && (tSecretCardInput02[index01]
			!= '8') && (tSecretCardInput02[index01] != '9') && (tSecretCardInput02[index01] != '0'))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tSecretCardInput03[0] = tSecretCardInput01[0];
	tSecretCardInput03[1] = tSecretCardInput01[1];
	tSecretCardInput03[2] = tSecretCardInput02[0];
	tSecretCardInput03[3] = tSecretCardInput02[1];
	tSecretCardInput03[4] = '\0';
	if (!mDB.DB_PROCESS_04(mUSER[tUserIndex].uSecretCard, mUSER[tUserIndex].mSecretCardIndex01,
	                       &tSecretCardContent01[0]))
	{
		mTRANSFER.B_LOGIN_SECRET_CARD_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (!mDB.DB_PROCESS_04(mUSER[tUserIndex].uSecretCard, mUSER[tUserIndex].mSecretCardIndex02,
	                       &tSecretCardContent02[0]))
	{
		mTRANSFER.B_LOGIN_SECRET_CARD_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tSecretCardContent03[0] = tSecretCardContent01[0];
	tSecretCardContent03[1] = tSecretCardContent01[1];
	tSecretCardContent03[2] = tSecretCardContent02[2];
	tSecretCardContent03[3] = tSecretCardContent02[3];
	tSecretCardContent03[4] = '\0';
	if (strcmp(tSecretCardContent03, tSecretCardInput03) != 0)
	{
		mTRANSFER.B_LOGIN_SECRET_CARD_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
#if 0
		mUSER[tUserIndex].mSecondLoginTryNum++;
		if( mUSER[tUserIndex].mSecondLoginTryNum == 3 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			mPLAYUSER_COM.U_BLOCK_USER_FOR_LOGIN_1_SEND( 505, &mUSER[tUserIndex].uID[0] );
			return;
		}
#endif
		return;
	}
	mUSER[tUserIndex].mSecondLoginSort = 0;
	mTRANSFER.B_LOGIN_SECRET_CARD_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_CREATE_AVATAR_SEND
void W_CREATE_AVATAR_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	//__LogMgr()->Log("Test %d  %d",mUSER[tUserIndex].mCheckValidState,mUSER[tUserIndex].mSecondLoginSort);
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tAvatarPost;
	AVATAR_INFO tAvatarInfo;
	CopyMemory(&tAvatarPost, &tPacket[1], 4);
	CopyMemory(&tAvatarInfo, &tPacket[5], SIZE_OF_AVATAR_INFO);
	mGAME.SafeAvatarInfoData(&tAvatarInfo);

	if ((tAvatarPost < 0) || (tAvatarPost > 2) || (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "") != 0) ||
		(strcmp(tAvatarInfo.aName, "") == 0) || (tAvatarInfo.aTribe < 0) || (tAvatarInfo.aTribe > 2) || (tAvatarInfo.
			aHeadType < 0) || (tAvatarInfo.aHeadType > 6) || (tAvatarInfo.aFaceType < 0) || (tAvatarInfo.aFaceType > 2))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	int index01;
	int index02;
	WORLD_INFO tWorldInfo;
	int tWeaponItemIndex;
	int tResult;

	if (!mDB.DB_PROCESS_12(&tWorldInfo))
	{
		mTRANSFER.B_CREATE_AVATAR_RECV(1, &tAvatarInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
#if 1
	switch (tAvatarInfo.aTribe)
	{
	case 0:
		if ((tWorldInfo.mTribePoint[0] >= 100) && (tWorldInfo.mTribePoint[0] > tWorldInfo.mTribePoint[3]))
		{
			if ((tWorldInfo.mTribePoint[0] > (tWorldInfo.mTribePoint[1] + tWorldInfo.mTribePoint[2])) && (tWorldInfo.
				mTribePoint[0] > (tWorldInfo.mTribePoint[1] + tWorldInfo.mTribePoint[3])) && (tWorldInfo.mTribePoint[0]
				> (tWorldInfo.mTribePoint[2] + tWorldInfo.mTribePoint[3])))
			{
				mTRANSFER.B_CREATE_AVATAR_RECV(3, &tAvatarInfo);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		break;
	case 1:
		if ((tWorldInfo.mTribePoint[1] >= 100) && (tWorldInfo.mTribePoint[1] > tWorldInfo.mTribePoint[3]))
		{
			if ((tWorldInfo.mTribePoint[1] > (tWorldInfo.mTribePoint[0] + tWorldInfo.mTribePoint[2])) && (tWorldInfo.
				mTribePoint[1] > (tWorldInfo.mTribePoint[0] + tWorldInfo.mTribePoint[3])) && (tWorldInfo.mTribePoint[1]
				> (tWorldInfo.mTribePoint[2] + tWorldInfo.mTribePoint[3])))
			{
				mTRANSFER.B_CREATE_AVATAR_RECV(3, &tAvatarInfo);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		break;
	case 2:
		if ((tWorldInfo.mTribePoint[2] >= 100) && (tWorldInfo.mTribePoint[2] > tWorldInfo.mTribePoint[3]))
		{
			if ((tWorldInfo.mTribePoint[2] > (tWorldInfo.mTribePoint[0] + tWorldInfo.mTribePoint[1])) && (tWorldInfo.
				mTribePoint[2] > (tWorldInfo.mTribePoint[0] + tWorldInfo.mTribePoint[3])) && (tWorldInfo.mTribePoint[2]
				> (tWorldInfo.mTribePoint[1] + tWorldInfo.mTribePoint[3])))
			{
				mTRANSFER.B_CREATE_AVATAR_RECV(3, &tAvatarInfo);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		break;
	}
#endif
	if (!mDB.DB_PROCESS_15(tAvatarInfo.aTribe))
	{
		mTRANSFER.B_CREATE_AVATAR_RECV(12, &tAvatarInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	tAvatarInfo.aVisibleState = 1;
	tAvatarInfo.aSpecialState = 0;
	tAvatarInfo.aPlayTime1 = 0;
	tAvatarInfo.aPlayTime2 = 0;
	tAvatarInfo.aKillOtherTribe = 0;
	tAvatarInfo.aPreviousTribe = tAvatarInfo.aTribe;
	tAvatarInfo.aLevel1 = 1;
	tAvatarInfo.aLevel2 = 0;
	tAvatarInfo.aGeneralExperience1 = 0;
	tAvatarInfo.aGeneralExperience2 = 0;
	tAvatarInfo.aVit = 1;
	tAvatarInfo.aStr = 1;
	tAvatarInfo.aInt = 1;
	tAvatarInfo.aDex = 1;
	tAvatarInfo.aEatLifePotion = 0;
	tAvatarInfo.aEatManaPotion = 0;
	tAvatarInfo.aStateBonusPoint = 0;
	tAvatarInfo.aSkillPoint = 0;
	tWeaponItemIndex = tAvatarInfo.aEquip[7][0];
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		tAvatarInfo.aEquip[index01][0] = 0;
		tAvatarInfo.aEquip[index01][1] = 0;
		tAvatarInfo.aEquip[index01][2] = 0;
		tAvatarInfo.aEquip[index01][3] = 0;
	}
	switch (tAvatarInfo.aTribe)
	{
	case 0:
		if ((tWeaponItemIndex != 5) && (tWeaponItemIndex != 6) && (tWeaponItemIndex != 7))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tAvatarInfo.aEquip[0][0] = 0; // Amulet
		tAvatarInfo.aEquip[0][2] = 0; // Amulet Enchant
		tAvatarInfo.aEquip[1][0] = 0; // Cape
		tAvatarInfo.aEquip[1][2] = 0; // Cape Enchant
		tAvatarInfo.aEquip[2][0] = 8; // Armor
		tAvatarInfo.aEquip[2][2] = 0; // Armor Enchant
		tAvatarInfo.aEquip[3][0] = 9; // Gloves
		tAvatarInfo.aEquip[3][2] = 0; // Gloves Enchant
		tAvatarInfo.aEquip[4][0] = 0; // Ring
		tAvatarInfo.aEquip[4][2] = 0; // Ring Enchant
		tAvatarInfo.aEquip[5][0] = 10; // Boots
		tAvatarInfo.aEquip[5][2] = 0; //Boots Enchant
		if (tWeaponItemIndex == 5) tAvatarInfo.aEquip[7][0] = 15135;
		if (tWeaponItemIndex == 6) tAvatarInfo.aEquip[7][0] = 15157;
		if (tWeaponItemIndex == 7) tAvatarInfo.aEquip[7][0] = 15179;
	//tAvatarInfo.aEquip[7][0] = tWeaponItemIndex; //Weapon
		tAvatarInfo.aEquip[7][2] = 0; //Weapon Enchant
		tAvatarInfo.aEquip[8][0] = 0; //Pet slot
		tAvatarInfo.aEquip[8][1] = 0; //Pet Activity	
		tAvatarInfo.aEquip[8][2] = 0; //Pet Exp - 320,000,000 = 100%
		break;
	case 1:
		if ((tWeaponItemIndex != 11) && (tWeaponItemIndex != 12) && (tWeaponItemIndex != 13))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tAvatarInfo.aEquip[0][0] = 0; // Amulet
		tAvatarInfo.aEquip[0][2] = 0; // Amulet Enchant
		tAvatarInfo.aEquip[1][0] = 0; // Cape
		tAvatarInfo.aEquip[1][2] = 0; // Cape Enchant
		tAvatarInfo.aEquip[2][0] = 14; // Armor
		tAvatarInfo.aEquip[2][2] = 0; // Armor Enchant
		tAvatarInfo.aEquip[3][0] = 15; // Gloves
		tAvatarInfo.aEquip[3][2] = 0; // Gloves Enchant
		tAvatarInfo.aEquip[4][0] = 0; // Ring
		tAvatarInfo.aEquip[4][2] = 0; // Ring Enchant
		tAvatarInfo.aEquip[5][0] = 16; // Boots
		tAvatarInfo.aEquip[5][2] = 0; // Boots Enchant
		if (tWeaponItemIndex == 11) tAvatarInfo.aEquip[7][0] = 11;
		if (tWeaponItemIndex == 12) tAvatarInfo.aEquip[7][0] = 12;
		if (tWeaponItemIndex == 13) tAvatarInfo.aEquip[7][0] = 13;
	//tAvatarInfo.aEquip[7][0] = tWeaponItemIndex; // Weapon
		tAvatarInfo.aEquip[7][2] = 0; // Weapon Enchant
		tAvatarInfo.aEquip[8][0] = 0; //Pet slot
		tAvatarInfo.aEquip[8][1] = 0; //Pet Activity
		tAvatarInfo.aEquip[8][2] = 0; //Pet Exp - 320,000,000 = 100%
		break;
	case 2:
		if ((tWeaponItemIndex != 17) && (tWeaponItemIndex != 18) && (tWeaponItemIndex != 19))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tAvatarInfo.aEquip[0][0] = 0; // Amulet
		tAvatarInfo.aEquip[0][2] = 0; // Amulet Enchant
		tAvatarInfo.aEquip[1][0] = 0; // Cape
		tAvatarInfo.aEquip[1][2] = 0; // Cape Enchant
		tAvatarInfo.aEquip[2][0] = 20; // Armor
		tAvatarInfo.aEquip[2][2] = 0; // Armor Enchant
		tAvatarInfo.aEquip[3][0] = 21; // Gloves
		tAvatarInfo.aEquip[3][2] = 0; // Gloves Enchant
		tAvatarInfo.aEquip[4][0] = 0; // Ring
		tAvatarInfo.aEquip[4][2] = 0; // Ring Enchant
		tAvatarInfo.aEquip[5][0] = 22; // Boots 
		tAvatarInfo.aEquip[5][2] = 0; // Boots Enchant
		if (tWeaponItemIndex == 17) tAvatarInfo.aEquip[7][0] = 17;
		if (tWeaponItemIndex == 18) tAvatarInfo.aEquip[7][0] = 18;
		if (tWeaponItemIndex == 19) tAvatarInfo.aEquip[7][0] = 19;
	//tAvatarInfo.aEquip[7][0] = tWeaponItemIndex; // Weapon
		tAvatarInfo.aEquip[7][2] = 0; // Weapon Enchant
		tAvatarInfo.aEquip[8][0] = 0; //Pet slot
		tAvatarInfo.aEquip[8][1] = 0; //Pet Activity
		tAvatarInfo.aEquip[8][2] = 0; //Pet Exp - 320,000,000 = 100%
		break;
	}
	if (mUSER[tUserIndex].uGoodFellow > 0)
	{
		tAvatarInfo.aEquip[1][0] = 1402;
		tAvatarInfo.aEquip[1][1] = 0;
		tAvatarInfo.aEquip[1][2] = 0;
		tAvatarInfo.aEquip[1][3] = 0;
	}
	tAvatarInfo.aExpandInventoryDate = mGAME.ReturnAddDate(mGAME.ReturnNowDate(), 7);
	tAvatarInfo.aMoney = 0;
	tAvatarInfo.aMoney2 = 0;
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			tAvatarInfo.aInventory[index01][index02][0] = 0;
			tAvatarInfo.aInventory[index01][index02][1] = 0;
			tAvatarInfo.aInventory[index01][index02][2] = 0;
			tAvatarInfo.aInventory[index01][index02][3] = 0;
			tAvatarInfo.aInventory[index01][index02][4] = 0;
			tAvatarInfo.aInventory[index01][index02][5] = 0;
		}
	}
	tAvatarInfo.aInventory[0][0][0] = 1026;
	tAvatarInfo.aInventory[0][0][1] = 0;
	tAvatarInfo.aInventory[0][0][2] = 0;
	tAvatarInfo.aInventory[0][0][3] = 12;
	tAvatarInfo.aInventory[0][0][4] = 0;
	tAvatarInfo.aInventory[0][0][5] = 0;
	tAvatarInfo.aTradeMoney = 0;
	tAvatarInfo.aTradeMoney2 = 0;
	for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
	{
		tAvatarInfo.aTrade[index01][0] = 0;
		tAvatarInfo.aTrade[index01][1] = 0;
		tAvatarInfo.aTrade[index01][2] = 0;
		tAvatarInfo.aTrade[index01][3] = 0;
	}
	tAvatarInfo.aExpandStoreDate = mGAME.ReturnAddDate(mGAME.ReturnNowDate(), 7);
	tAvatarInfo.aStoreMoney = 0;
	tAvatarInfo.aStoreMoney2 = 0;

	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_STORE_ITEM_SLOT_NUM; index02++)
		{
			tAvatarInfo.aStoreItem[index01][index02][0] = 0;
			tAvatarInfo.aStoreItem[index01][index02][1] = 0;
			tAvatarInfo.aStoreItem[index01][index02][2] = 0;
			tAvatarInfo.aStoreItem[index01][index02][3] = 0;
		}
	}
	for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
	{
		tAvatarInfo.aSkill[index01][0] = 0;
		tAvatarInfo.aSkill[index01][1] = 0;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
		{
			tAvatarInfo.aHotKey[index01][index02][0] = 0;
			tAvatarInfo.aHotKey[index01][index02][1] = 0;
			tAvatarInfo.aHotKey[index01][index02][2] = 0;
		}
	}
	switch (tAvatarInfo.aTribe)
	{
	case 0:
		tAvatarInfo.aSkill[0][0] = 1;
		tAvatarInfo.aSkill[0][1] = 1;
		tAvatarInfo.aHotKey[0][0][0] = 1;
		tAvatarInfo.aHotKey[0][0][1] = 1;
		tAvatarInfo.aHotKey[0][0][2] = 1;
		break;
	case 1:
		tAvatarInfo.aSkill[0][0] = 20;
		tAvatarInfo.aSkill[0][1] = 1;
		tAvatarInfo.aHotKey[0][0][0] = 20;
		tAvatarInfo.aHotKey[0][0][1] = 1;
		tAvatarInfo.aHotKey[0][0][2] = 1;
		break;
	case 2:
		tAvatarInfo.aSkill[0][0] = 39;
		tAvatarInfo.aSkill[0][1] = 1;
		tAvatarInfo.aHotKey[0][0][0] = 39;
		tAvatarInfo.aHotKey[0][0][1] = 1;
		tAvatarInfo.aHotKey[0][0][2] = 1;
		break;
	}
	tAvatarInfo.aHotKey[0][1][0] = 4;
	tAvatarInfo.aHotKey[0][1][1] = 99;
	tAvatarInfo.aHotKey[0][1][2] = 3;
	tAvatarInfo.aHotKey[0][2][0] = 4;
	tAvatarInfo.aHotKey[0][2][1] = 99;
	tAvatarInfo.aHotKey[0][2][2] = 3;
	tAvatarInfo.aHotKey[0][3][0] = 4;
	tAvatarInfo.aHotKey[0][3][1] = 99;
	tAvatarInfo.aHotKey[0][3][2] = 3;
	tAvatarInfo.aHotKey[0][4][0] = 28;
	tAvatarInfo.aHotKey[0][4][1] = 99;
	tAvatarInfo.aHotKey[0][4][2] = 3;
	tAvatarInfo.aHotKey[0][5][0] = 28;
	tAvatarInfo.aHotKey[0][5][1] = 99;
	tAvatarInfo.aHotKey[0][5][2] = 3;
	tAvatarInfo.aHotKey[0][6][0] = 28;
	tAvatarInfo.aHotKey[0][6][1] = 99;
	tAvatarInfo.aHotKey[0][6][2] = 3;
	tAvatarInfo.aQuestInfo[0] = 0;
	tAvatarInfo.aQuestInfo[1] = 0;
	tAvatarInfo.aQuestInfo[2] = 0;
	tAvatarInfo.aQuestInfo[3] = 0;
	tAvatarInfo.aQuestInfo[4] = 0;
	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		strcpy(tAvatarInfo.aFriend[index01], "");
	}
	strcpy(tAvatarInfo.aTeacher, "");
	strcpy(tAvatarInfo.aStudent, "");
	tAvatarInfo.aTeacherPoint = 0;
	strcpy(tAvatarInfo.aGuildName, "");
	tAvatarInfo.aGuildRole = 0;
	strcpy(tAvatarInfo.aCallName, "");
	tAvatarInfo.aGuildMarkNum = 0;
	tAvatarInfo.aGuildMarkEffect = 1;
	switch (tAvatarInfo.aTribe)
	{
	case 0:
		tAvatarInfo.aLogoutInfo[0] = 1;
		tAvatarInfo.aLogoutInfo[1] = 5;
		tAvatarInfo.aLogoutInfo[2] = 0;
		tAvatarInfo.aLogoutInfo[3] = 4;
		tAvatarInfo.aLogoutInfo[4] = 30;
		tAvatarInfo.aLogoutInfo[5] = 21;
		break;
	case 1:
		tAvatarInfo.aLogoutInfo[0] = 6;
		tAvatarInfo.aLogoutInfo[1] = -190;
		tAvatarInfo.aLogoutInfo[2] = 0;
		tAvatarInfo.aLogoutInfo[3] = 1270;
		tAvatarInfo.aLogoutInfo[4] = 30;
		tAvatarInfo.aLogoutInfo[5] = 21;
		break;
	case 2:
		tAvatarInfo.aLogoutInfo[0] = 11;
		tAvatarInfo.aLogoutInfo[1] = 447;
		tAvatarInfo.aLogoutInfo[2] = 1;
		tAvatarInfo.aLogoutInfo[3] = 440;
		tAvatarInfo.aLogoutInfo[4] = 30;
		tAvatarInfo.aLogoutInfo[5] = 21;
		break;
	}
	tAvatarInfo.aProtectForDeath = 0;
	tAvatarInfo.aProtectForDestroy = 0;
	tAvatarInfo.aDoubleExpTime1 = 0;
	tAvatarInfo.aDoubleExpTime2 = 0;
	tAvatarInfo.aDoubleKillNumTime = 0;
	tAvatarInfo.aDoubleKillExpTime = 0;
	tAvatarInfo.aNineTowerKeyNum = 0;
	tAvatarInfo.aZone101TypeTime = 0;
	tAvatarInfo.aZone125TypeTime = 0;
	tAvatarInfo.aZone126TypeTime = 0;
	tAvatarInfo.aKillMonsterNum = 0;
	tAvatarInfo.aSearchAndBuyDate = 0;
	tAvatarInfo.aLifePotionConvertNum = 0;
	//tAvatarInfo.aManaPotionConvertNum = 0;
	//tAvatarInfo.aTribeVoteDate = 0;
	tAvatarInfo.aEatStrengthPotion = 0;
	tAvatarInfo.aEatAgilityPotion = 0;
	tAvatarInfo.aPat_Exp_x2_Time = 0; // Pet Exp Boost Scroll
	//-------------------------------------------------------------------------------------------------
#ifdef __GOD__

	tAvatarInfo.aAutoLifeRatio = 0;
	tAvatarInfo.aAutoChiRatio = 0;

	for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
	{
		tAvatarInfo.aAnimal[index01] = 0;
	}
	tAvatarInfo.aAnimalIndex = -1;
	tAvatarInfo.aCostumeIndex = -1;
	tAvatarInfo.aAnimalTime = 0;
	tAvatarInfo.aUpgradeValue = 0;
	//tAvatarInfo.aKillOtherTribeEvent = 0;
	//tAvatarInfo.aTeacherPointEvent = 0;
	//tAvatarInfo.aPlayTimeEvent = 0;
	tAvatarInfo.aCPProtectionCharm = 0;
	tAvatarInfo.aEatElementAtkDefPotion = 0;
	tAvatarInfo.aExpPill = 0;
	tAvatarInfo.aDamageBoostScroll = 0;
	tAvatarInfo.aHealthBoostScroll = 0;
	tAvatarInfo.aCriticalBoostScroll = 0;
	tAvatarInfo.aMountAbsorbTime = 0;
	tAvatarInfo.aWingProtectionScroll = 0;
	tAvatarInfo.aPreventRefineBreak = 0;
	tAvatarInfo.aIslandOfBloodTime = 0;
	tAvatarInfo.aIslandOfSoul1Time = 0;
	tAvatarInfo.aIslandOfSoul2Time = 0;
	tAvatarInfo.aIslandOfSoul3Time = 0;
	tAvatarInfo.aIslandOfSoul4Time = 0;
	tAvatarInfo.aIslandOfSoul5Time = 0;
	tAvatarInfo.aIslandOfSoul6Time = 0;
	tAvatarInfo.iUseOrnament = 0;
	tAvatarInfo.iGoldOrnamentRemainsTime = 0;
	tAvatarInfo.iSilverOrnamentRemainsTime = 0;
	tAvatarInfo.aLifeOrDeath = 0;
	tAvatarInfo.aRankPoints = 0;
	tAvatarInfo.aRankAbility = 0;
	tAvatarInfo.aRebirth = 0;
	tAvatarInfo.aTitle = 0;
	tAvatarInfo.aAutoBuffScroll = 0;
	tAvatarInfo.aAutoHunt7Day = 99999999;
	tAvatarInfo.aAutoHunt5Hour = 0;
	tAvatarInfo.aDoubleBuffTime = 0;
	tAvatarInfo.aFactionNoticeScroll = 0;
	tAvatarInfo.aFactionReturnScroll = 0;
	tAvatarInfo.aPetInventoryDate = 0;
#endif
	//-------------------------------------------------------------------------------------------------
	//tAvatarInfo.aKillMonsterNum2 = 0;

	tAvatarInfo.uSaveMoney = mUSER[tUserIndex].uSaveMoney;
	tAvatarInfo.uSaveMoney2 = mUSER[tUserIndex].uSaveMoney2;

	for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
	{
		tAvatarInfo.uSaveItem[index01][0] = mUSER[tUserIndex].uSaveItem[index01][0];
		tAvatarInfo.uSaveItem[index01][1] = mUSER[tUserIndex].uSaveItem[index01][1];
		tAvatarInfo.uSaveItem[index01][2] = mUSER[tUserIndex].uSaveItem[index01][2];
		tAvatarInfo.uSaveItem[index01][3] = mUSER[tUserIndex].uSaveItem[index01][3];
	}
	for (index01 = 0; index01 < 5; index01++)
	{
		strcpy(tAvatarInfo.aPartyName[index01], "");
	}
	mDB.DB_PROCESS_05(tUserIndex, tAvatarPost, &tAvatarInfo, &tResult);
	if (tResult != 0)
	{
		mTRANSFER.B_CREATE_AVATAR_RECV(tResult, &tAvatarInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tUserIndex].uLoginPremiumPCRoom == 2)
	{
		tAvatarInfo.aZone126TypeTime = (60 * 60 * 24 * 7);
	}
	else
	{
		tAvatarInfo.aZone126TypeTime = 0;
	}
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo[tAvatarPost], &tAvatarInfo, SIZE_OF_AVATAR_INFO);
	mTRANSFER.B_CREATE_AVATAR_RECV(0, &tAvatarInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_DELETE_AVATAR_SEND
void W_DELETE_AVATAR_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tAvatarPost;
	CopyMemory(&tAvatarPost, &tPacket[1], 4);

	if ((tAvatarPost < 0) || (tAvatarPost > 2) || (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "") == 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	TRIBE_INFO tTribeInfo;

	if (!mDB.DB_PROCESS_13(&tTribeInfo))
	{
		__LogMgr()->Log("![WARNING - (1)] Database failed to delete character.\n");
		mTRANSFER.B_DELETE_AVATAR_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mGAME.ReturnTribeRole(&tTribeInfo, &mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0],
	                          mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aTribe) != 0)
	{
		__LogMgr()->Log("![WARNING - (2) Because the character can not delete the leader of group.\n");
		mTRANSFER.B_DELETE_AVATAR_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aGuildName, "") != 0)
	{
		__LogMgr()->Log("![WARNING - (3) You can not delete the character joined the guild.\n");
		mTRANSFER.B_DELETE_AVATAR_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	//if( mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLevel1 >= 40 )
	//{
	//	mTRANSFER.B_DELETE_AVATAR_RECV( 4 );
	//	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//	return;
	//}
	if (!mDB.DB_PROCESS_06(tUserIndex, tAvatarPost))
	{
		__LogMgr()->Log("![WARNING - (1) Database failed to delete character.\n");
		mTRANSFER.B_DELETE_AVATAR_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	strcpy(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "");
	mTRANSFER.B_DELETE_AVATAR_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_CHANGE_AVATAR_NAME_SEND
// 2009.12.16 : �輺��
// ����ȯ�� ó�� ����
void W_CHANGE_AVATAR_NAME_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tAvatarPost;
	char tChangeAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tPage;
	int tIndex;
	CopyMemory(&tAvatarPost, &tPacket[1], 4);
	CopyMemory(&tChangeAvatarName[0], &tPacket[5], MAX_AVATAR_NAME_LENGTH);
	tChangeAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tPage, &tPacket[( 5 + MAX_AVATAR_NAME_LENGTH )], 4);
	CopyMemory(&tIndex, &tPacket[( 9 + MAX_AVATAR_NAME_LENGTH )], 4);

	TRIBE_INFO tTribeInfo;
	int tResult;
	bool isChangeNameIntegration = false;

	// 2009.12.18  : �輺��
	// ���տ� ���� ����ȯ�� ��쿡 �Ʒ��� üũ ���� �ʴ´�.
	//if(!(tPage == -1 && tIndex == -1 && !mGAME.CheckNameString( mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName )))
	if (!(tPage == -1 && tIndex == -1))
	{
		if ((tAvatarPost < 0) || (tAvatarPost > 2)
			|| (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "") == 0)
			|| (strcmp(tChangeAvatarName, "") == 0)
			|| (strcmp(tChangeAvatarName, mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName) == 0)
			|| (tPage < 0)
			|| (tPage > 1)
			|| (tIndex < 0)
			|| (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		//�������� ���� ���
		if (mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][0] != 1133)
		{
			mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(8);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	else
	// ���� ���տ� ���� ���� ��ȯ�� ��� == �ƹ�Ÿ ���� Ư�����ڰ� ��� �� �ִ� ��� == tPage, tIndex �� -1�� ���.
	{
		if (mGAME.CheckNameString(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName) == FALSE)
		{
			isChangeNameIntegration = true;
		}
		else // ���� ���տ� ���� ���� ��ȯ�� �ƴѵ� -1, -1�� �����ٴ�...
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}

#ifndef __TK__
	//�߸��� ����
	if (!mGAME.CheckNameString(tChangeAvatarName))
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}
#endif


	// ��忡 ���ԵǾ� �ִ� ���
	if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aGuildName, "") != 0)
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}

	// �ý��� ó���� ���� (DB) - ������ �ĺ��ΰ�쵵 ����
	if (!mDB.DB_PROCESS_13(&tTribeInfo))
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(9);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	//������ Ȥ�� �μ������� ���
	if (mGAME.ReturnTribeRole(&tTribeInfo, &mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0],
	                          mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aTribe) != 0)
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	//�ؿ찡 �ִ� ���
	for (int i = 0; i < MAX_FRIEND_NUM; ++i)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aFriend[i], "") != 0)
		{
			mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(5);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}

	//������ �ִ� ���
	if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aTeacher, "") != 0)
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	//���ڰ� �ִ� ���
	if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aStudent, "") != 0)
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}


	//�̸����� - �̰� ���� �Ѵٴ� ���� ���� ������ �ִ� ���� �׿ܿ� ������ �߸��Ǿ��� ����̴�.
	// ���� �� ��� ���нÿ� ���� ������ �ִٰ� �Ǵ��Ѵ�.
	mDB.DB_PROCESS_07(&mUSER[tUserIndex].uID[0], tAvatarPost, &mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0],
	                  &tChangeAvatarName[0], &tResult);
	if (tResult != 0)
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	//	//mGAMELOG.GL_501_CHANGE_AVATAR_NAME( &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0], &tChangeAvatarName[0] );
	strcpy(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, tChangeAvatarName);
	if (isChangeNameIntegration == false)
	{
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][5] = 0;
		mDB.DB_PROCESS_08(&mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0],
		                  mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory);
	}
	mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_DEMAND_GIFT_SEND
void W_DEMAND_GIFT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tCardNumber[MAX_USER_CARD_NUMBER_LENGTH];
	CopyMemory(&tCardNumber[0], &tPacket[1], MAX_USER_CARD_NUMBER_LENGTH);
	tCardNumber[(MAX_USER_CARD_NUMBER_LENGTH - 1)] = '\0';

	char tID[MAX_USER_ID_LENGTH];

	// 	if( !mDB.DB_PROCESS_09( &tCardNumber[0], &tID[0], &mUSER[tUserIndex].mGiftInfo[0] ) )
	// 	{
	// 		mUSER[tUserIndex].mCheckDemandGiftIfo = FALSE;
	// 		mTRANSFER.B_DEMAND_GIFT_RECV( 1, &mUSER[tUserIndex].mGiftInfo[0] );
	// 		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	// 		return;
	// 	}
	// 	if( strcmp( mUSER[tUserIndex].uID, tID ) != 0 )
	// 	{
	// 		mUSER[tUserIndex].mCheckDemandGiftIfo = FALSE;
	// 		mTRANSFER.B_DEMAND_GIFT_RECV( 2, &mUSER[tUserIndex].mGiftInfo[0] );
	// 		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	// 		return;
	// 	}

	//    mGiftBankComm.U_CHECK_GIFTISSUESERIAL (tUserIndex, tCardNumber); 

	/*mUSER[tUserIndex].mCheckDemandGiftIfo = TRUE;
	strcpy( mUSER[tUserIndex].mCardNumber, tCardNumber );
	mTRANSFER.B_DEMAND_GIFT_RECV( 0, &mUSER[tUserIndex].mGiftInfo[0] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );*/
}

//W_WANT_GIFT_SEND
void W_WANT_GIFT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (!mUSER[tUserIndex].mCheckDemandGiftIfo)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tGiftInfoindex;
	CopyMemory(&tGiftInfoindex, &tPacket[1], 4);
	if ((tGiftInfoindex != 0) && (tGiftInfoindex != 2) && (tGiftInfoindex != 4) && (tGiftInfoindex != 6) && (
		tGiftInfoindex != 8))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	int index02;

	if (mUSER[tUserIndex].mGiftInfo[(tGiftInfoindex + 1)] < 1)
	{
		mTRANSFER.B_WANT_GIFT_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] < 1) || (mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] >
		MAX_GIFT_SORT_NUM))
	{
		mTRANSFER.B_WANT_GIFT_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	index02 = 0;
	for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
	{
		if (mUSER[tUserIndex].uSaveItem[index01][0] < 1)
		{
			index02++;
		}
	}
	if (index02 < mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)].mTotalGiftNum)
	{
		mTRANSFER.B_WANT_GIFT_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}


	for (index01 = 0; index01 < mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)].mTotalGiftNum;
	     index01++)
	{
		for (index02 = 0; index02 < MAX_SAVE_ITEM_SLOT_NUM; index02++)
		{
			if (mUSER[tUserIndex].uSaveItem[index02][0] > 0)
			{
				continue;
			}
#if 0
			__LogMgr()->Log_3("![%s] : %d %d\n", __FUNCTION__
					, mGAME.mGiftInfo[( mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1 )].mGiftData[index01][0]
					, mGAME.mGiftInfo[( mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1 )].mGiftData[index01][1]);
#endif
			mUSER[tUserIndex].uSaveItem[index02][0] = mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)]
				.mGiftData[index01][0];
			mUSER[tUserIndex].uSaveItem[index02][1] = mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)]
				.mGiftData[index01][1];
			mUSER[tUserIndex].uSaveItem[index02][2] = 0;
			mUSER[tUserIndex].uSaveItem[index02][3] = 0;
			break;
		}
	}
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo[0].uSaveItem[0][0], &mUSER[tUserIndex].uSaveItem[0][0],
	           ( MAX_SAVE_ITEM_SLOT_NUM * 4 * 4 ));
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo[1].uSaveItem[0][0], &mUSER[tUserIndex].uSaveItem[0][0],
	           ( MAX_SAVE_ITEM_SLOT_NUM * 4 * 4 ));
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo[2].uSaveItem[0][0], &mUSER[tUserIndex].uSaveItem[0][0],
	           ( MAX_SAVE_ITEM_SLOT_NUM * 4 * 4 ));
	mUSER[tUserIndex].mGiftInfo[(tGiftInfoindex + 1)]--;
	mDB.DB_PROCESS_10(&mUSER[tUserIndex].mCardNumber[0], &mUSER[tUserIndex].mGiftInfo[0]);
	mDB.DB_PROCESS_11(&mUSER[tUserIndex].uID[0], mUSER[tUserIndex].uSaveItem);
	mTRANSFER.B_WANT_GIFT_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//mGAMELOG.GL_503_GIFT( &mUSER[tUserIndex].uID[0], mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] );
}

//W_DEMAND_ZONE_SERVER_INFO_1
void W_DEMAND_ZONE_SERVER_INFO_1(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	//__LogMgr()->Log("ceshi %d  %d",mUSER[tUserIndex].mCheckValidState,mUSER[tUserIndex].mSecondLoginSort);
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		__LogMgr()->Log("!MOTP are not certified by the state can not ask the server information.\n");
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		__LogMgr()->Log("!Go to the status of the client not be able to request information on the server.\n");
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tAvatarPost;
	CopyMemory(&tAvatarPost, &tPacket[1], 4);

	if ((tAvatarPost < 0) || (tAvatarPost > 2) || (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "") == 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mCENTER_COM.U_GET_ZONE_SERVER_INFO_1(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLogoutInfo[0]);
	if (mCENTER_COM.mRecv_Result != 0)
	{
		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_1_RESULT(1, &mCENTER_COM.mRecv_IP[0], mCENTER_COM.mRecv_Port,
		                                             mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLogoutInfo[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("!Did not receive the information about zone(%d) server address [%s:%d].\n",
		                mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLogoutInfo[0],
		                mCENTER_COM.mRecv_IP, mCENTER_COM.mRecv_Port);
		return;
	}
	mPLAYUSER_COM.U_REGISTER_USER_FOR_LOGIN_3_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0],
	                                               &mUSER[tUserIndex].mAvatarInfo[tAvatarPost]);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		__LogMgr()->Log("!Failed to register a character on the playuser server(%d).\n", mPLAYUSER_COM.mRecv_Result);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mMoveZoneResult = 1;
	//__LogMgr()->Log("Enter Zone%s,%d",mCENTER_COM.mRecv_IP,mCENTER_COM.mRecv_Port);
	mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_1_RESULT(0, mCENTER_COM.mRecv_IP, mCENTER_COM.mRecv_Port,
	                                             mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLogoutInfo[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_FAIL_MOVE_ZONE_1_SEND
void W_FAIL_MOVE_ZONE_1_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	mUSER[tUserIndex].mMoveZoneResult = 0;
	mPLAYUSER_COM.U_REGISTER_USER_FOR_LOGIN_2_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0]);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
}

//W_RCMD_WORLD_SEND
void W_RCMD_WORLD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	mTRANSFER.B_RCMD_WORLD_SEND();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//-------------------------------------------------------------------------------------------------
