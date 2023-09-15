#include "MainApp.h"

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_WORK
//-------------------------------------------------------------------------------------------------
#define USER_SEND() {\
	if(type == 0) {\
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );\
	} else if(type == 1) {\
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C );\
	} else if(type == 2) {\
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal_R[0], mTRANSFER.mOriginalSize_R );\
	}\
}

void MyWork::ProcessForRelay(int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE], int type)
{
	int index01;
	int index02;
	char tContent[MAX_CHAT_CONTENT_LENGTH];
	//int tUserSort;
	BYTE tAuthType;
	int tTribe;
	int tFactionSort;
	int tPartyMoveZone = 1;
#ifdef __PARTY_BUG_FIX__
	party_check_t PartyCheck;
	::memset(&PartyCheck, 0, sizeof(party_check_t));
#endif
	char tPartyName[MAX_PARTY_NAME_LENGTH];
	char tGuildName[MAX_GUILD_NAME_LENGTH];
	char tAvatarName01[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName02[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName03[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName04[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName05[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName06[MAX_AVATAR_NAME_LENGTH];

	switch (tSort)
	{
	case 101: //[NOTICE]<-[TOOL]
		CopyMemory(&tContent[0], &tData[0], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tTribe, &tData[MAX_CHAT_CONTENT_LENGTH], 4);
		mTRANSFER.B_GENERAL_NOTICE_RECV(&tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (tTribe == 0)
			{
				USER_SEND();
			}
			else
			{
				if (mAVATAR_OBJECT[index01].mDATA.aTribe == (tTribe - 1))
				{
					USER_SEND();
				}
			}
		}
		return;
	case 102: //[NOTICE]<-[GM]
		CopyMemory(&tContent[0], &tData[0], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_GENERAL_NOTICE_RECV(&tContent[0], type);
		if (strcmp(tContent, "centershutdown") == 0)
		{
			mCENTER_COM.W_SHUTDOWN();
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			USER_SEND();
		}
		return;
	case 103: //[SECRET_CHAT]
		CopyMemory(&tAvatarName01[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName02[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName02[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[(MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tAuthType, &tData[(MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], 1);
		mTRANSFER.B_SECRET_CHAT_RECV(3, 0, &tAvatarName01[0], &tContent[0], tAuthType, type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName02) == 0)
			{
				USER_SEND();
				return;
			}
		}
		return;
	case 104: //[PARTY_JOIN]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_JOIN_RECV(tAvatarName01, type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				Logger("Valid state");
				continue;
			}
			if (strcmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName) == 0)
			{
				Logger("Send");
				USER_SEND();
			}
		}
		return;
	case 105: //[PARTY_CHAT]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[(MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_CHAT_RECV(&tAvatarName01[0], &tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName) == 0)
			{
				USER_SEND();
			}
		}
		return;
	case 106: //[PARTY_LEAVE]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_LEAVE_RECV(tAvatarName01, type);
		tPartyMoveZone = 1;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[0], tPartyName) == 0)
			{
				USER_SEND();
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName01) == 0)
			{
				strcpy(mUSER[index01].mAvatarInfo.aPartyName[0], "");
				strcpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, "");
			}
		}
#ifdef __PARTY_BUG_FIX__
		if (tPartyMoveZone) {
			::strncpy(PartyCheck.aName, tAvatarName01, MAX_AVATAR_NAME_LENGTH);
			PartyCheck.tSort = tSort;
			PartyCheck.RegDateTime = ::time(NULL);
			mGAME.map_party_check.insert(pair<string, party_check_t>(tPartyName, PartyCheck));
			//LOG_TO_FILE_4("----> insert : %d %s %s %lu\n", tSort, tPartyName, PartyCheck.aName, PartyCheck.RegDateTime);
		}
#endif
		return;
	case 107: //[PARTY_EXILE]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_EXILE_RECV(tAvatarName01, type);
		tPartyMoveZone = 1;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[0], tPartyName) == 0)
			{
				USER_SEND();
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName01) == 0)
			{
				strcpy(mUSER[index01].mAvatarInfo.aPartyName[0], "");
				strcpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, "");
			}
		}
#ifdef __PARTY_BUG_FIX__
		if (tPartyMoveZone) {
			::strncpy(PartyCheck.aName, tAvatarName01, MAX_AVATAR_NAME_LENGTH);
			PartyCheck.tSort = tSort;
			PartyCheck.RegDateTime = ::time(NULL);
			mGAME.map_party_check.insert(pair<string, party_check_t>(tPartyName, PartyCheck));
			//LOG_TO_FILE_4("----> insert : %d %s %s %lu\n", tSort, tPartyName, PartyCheck.aName, PartyCheck.RegDateTime);
		}
#endif
		return;
	case 108: //[PARTY_INFO]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName02[0], &tData[(MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_AVATAR_NAME_LENGTH);
		tAvatarName02[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName03[0], &tData[(MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)],
		           MAX_AVATAR_NAME_LENGTH);
		tAvatarName03[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName04[0],
		           &tData[(MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH +
			           MAX_AVATAR_NAME_LENGTH)], MAX_AVATAR_NAME_LENGTH);
		tAvatarName04[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName05[0],
		           &tData[(MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH +
			           MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_AVATAR_NAME_LENGTH);
		tAvatarName05[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_INFO_RECV(tAvatarName01, tAvatarName02, tAvatarName03, tAvatarName04, tAvatarName05, type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strncmp(mUSER[index01].mAvatarInfo.aPartyName[0], tPartyName, MAX_PARTY_NAME_LENGTH) == 0)
			{
				USER_SEND();
				if ((0 != strcmp(tAvatarName01, mUSER[index01].mAvatarInfo.aName)) &&
					(0 != strcmp(tAvatarName02, mUSER[index01].mAvatarInfo.aName)) &&
					(0 != strcmp(tAvatarName03, mUSER[index01].mAvatarInfo.aName)) &&
					(0 != strcmp(tAvatarName04, mUSER[index01].mAvatarInfo.aName)) &&
					(0 != strcmp(tAvatarName05, mUSER[index01].mAvatarInfo.aName)))
				{
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[0], "", MAX_PARTY_NAME_LENGTH);
					strncpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, "", MAX_PARTY_NAME_LENGTH);
				}
			}
		}
		return;

	case 109: //[PARTY_BREAK]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		strcpy(tAvatarName02, "");
		tPartyMoveZone = 1;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[0], tPartyName) == 0)
			{
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[0], mUSER[index01].mAvatarInfo.aName) == 0)
				{
					mTRANSFER.B_PARTY_BREAK_RECV(1, tAvatarName02, type);
					USER_SEND();
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[0], tAvatarName02, MAX_PARTY_NAME_LENGTH);
					strncpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, tAvatarName02, MAX_PARTY_NAME_LENGTH);
				}
				else
				{
					mTRANSFER.B_PARTY_BREAK_RECV(1, tAvatarName01, type);
					USER_SEND();
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[0], tAvatarName01, MAX_PARTY_NAME_LENGTH);
					strncpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, tAvatarName01, MAX_PARTY_NAME_LENGTH);
				}
			}
		}
#ifdef __PARTY_BUG_FIX__
		if (tPartyMoveZone) {
			::strncpy(PartyCheck.aName, tAvatarName01, MAX_AVATAR_NAME_LENGTH);
			PartyCheck.tSort = tSort;
			PartyCheck.RegDateTime = ::time(NULL);
			mGAME.map_party_check.insert(pair<string, party_check_t>(tPartyName, PartyCheck));
			//LOG_TO_FILE_4("----> insert : %d %s %s %lu\n", tSort, tPartyName, PartyCheck.aName, PartyCheck.RegDateTime);
		}
#endif
		return;

	case 110: //[GUILD_LOGIN]
		CopyMemory(&tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH);
		tGuildName[(MAX_GUILD_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_GUILD_LOGIN_INFO(&tAvatarName01[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aGuildName, tGuildName) == 0)
			{
				USER_SEND();
			}
		}
		return;
	case 111: //[GUILD_NOTICE]
		CopyMemory(&tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH);
		tGuildName[(MAX_GUILD_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_GUILD_NOTICE_RECV(&tAvatarName01[0], &tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aGuildName, tGuildName) == 0)
			{
				USER_SEND();
			}
		}
		return;
	case 112: //[GUILD_CHAT]
		CopyMemory(&tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH);
		tGuildName[(MAX_GUILD_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_GUILD_CHAT_RECV(&tAvatarName01[0], &tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aGuildName, tGuildName) == 0)
			{
				USER_SEND();
			}
		}
		return;
	case 113: //[TRIBE_NOTICE]
		CopyMemory(&tAvatarName01[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tTribe, &tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], 4);
		CopyMemory(&tFactionSort, &tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH) + 4], 4);
		mTRANSFER.B_TRIBE_NOTICE_RECV(tFactionSort, &tAvatarName01[0], &tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDATA.aTribe == tTribe)
			{
				USER_SEND();
			}
		}
		return;

	case 114: //[Faction_Notice]
		CopyMemory(&tAuthType, &tData[0], 4);
		CopyMemory(&tAvatarName01[0], &tData[4], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[4 + MAX_AVATAR_NAME_LENGTH], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tTribe, &tData[(4 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], 4);
		mTRANSFER.B_FACTION_NOTICE_RECV(&tAvatarName01[0], tAuthType, &tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDATA.aTribe == tTribe)
			{
				USER_SEND();
			}
		}
		return;


	case 115: // [NEW-PARTY]
		CopyMemory(&tPartyName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01, &tData[MAX_AVATAR_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName02, &tData[MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName02[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName03, &tData[MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH],
		           MAX_AVATAR_NAME_LENGTH);
		tAvatarName03[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName04,
		           &tData[MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH +
			           MAX_AVATAR_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName04[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName05,
		           &tData[MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH +
			           MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName05[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (strncmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName, MAX_AVATAR_NAME_LENGTH) == 0)
			{
				strncpy(mUSER[index01].mAvatarInfo.aPartyName[0], tAvatarName01, MAX_AVATAR_NAME_LENGTH);
				strncpy(mUSER[index01].mAvatarInfo.aPartyName[1], tAvatarName02, MAX_AVATAR_NAME_LENGTH);
				strncpy(mUSER[index01].mAvatarInfo.aPartyName[2], tAvatarName03, MAX_AVATAR_NAME_LENGTH);
				strncpy(mUSER[index01].mAvatarInfo.aPartyName[3], tAvatarName04, MAX_AVATAR_NAME_LENGTH);
				strncpy(mUSER[index01].mAvatarInfo.aPartyName[4], tAvatarName05, MAX_AVATAR_NAME_LENGTH);
				mTRANSFER.B_PARTY_MAKE_RECV(1, tAvatarName01, tAvatarName02, tAvatarName03, tAvatarName04,
				                            tAvatarName05);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		return;


	case 116: //[NEW-PARTY-EXILE]
		CopyMemory(&tPartyName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_EXILE_RECV(tAvatarName01, type);
		tPartyMoveZone = 1;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			/*if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				Logger("Work 2");
				continue;
			}*/
			if (strcmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName) == 0)
			{
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[1], tAvatarName01) == 0)
				{
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[1], mUSER[index01].mAvatarInfo.aPartyName[2],
					        MAX_AVATAR_NAME_LENGTH);
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[2], mUSER[index01].mAvatarInfo.aPartyName[3],
					        MAX_AVATAR_NAME_LENGTH);
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[3], mUSER[index01].mAvatarInfo.aPartyName[4],
					        MAX_AVATAR_NAME_LENGTH);
					memset(mUSER[index01].mAvatarInfo.aPartyName[4], 0, 13);
				}
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[2], tAvatarName01) == 0)
				{
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[2], mUSER[index01].mAvatarInfo.aPartyName[3],
					        MAX_AVATAR_NAME_LENGTH);
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[3], mUSER[index01].mAvatarInfo.aPartyName[4],
					        MAX_AVATAR_NAME_LENGTH);
					memset(mUSER[index01].mAvatarInfo.aPartyName[4], 0, 13);
				}
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[3], tAvatarName01) == 0)
				{
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[3], mUSER[index01].mAvatarInfo.aPartyName[4],
					        MAX_AVATAR_NAME_LENGTH);
					memset(mUSER[index01].mAvatarInfo.aPartyName[4], 0, 13);
				}
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[4], tAvatarName01) == 0)
				{
					memset(mUSER[index01].mAvatarInfo.aPartyName[4], 0, 13);
				}
				USER_SEND();
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName01) == 0)
			{
				memset(mUSER[index01].mAvatarInfo.aPartyName, 0, 65);
				strcpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, "");
			}
		}
		return;

	case 117: //[NEW-PARTY-BREAK]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		strcpy(tAvatarName02, "");
		tPartyMoveZone = 1;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[0], tPartyName) == 0)
			{
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[0], tPartyName) == 0)
				{
					mTRANSFER.B_PARTY_BREAK_RECV(1, tAvatarName02, type);
					USER_SEND();
					memset(mUSER[index01].mAvatarInfo.aPartyName, 0, 65);
					memset(mAVATAR_OBJECT[index01].mDATA.aPartyName, 0, 13);
				}
			}
		}
		return;

	case 118: //[NEW-PARTY-LEAVE]
		CopyMemory(&tPartyName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_LEAVE_RECV(tAvatarName01, type);
		tPartyMoveZone = 1;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			/*if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				Logger("Work 2");
				continue;
			}*/
			if (strcmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName) == 0)
			{
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[1], tAvatarName01) == 0)
				{
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[1], mUSER[index01].mAvatarInfo.aPartyName[2],
					        MAX_AVATAR_NAME_LENGTH);
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[2], mUSER[index01].mAvatarInfo.aPartyName[3],
					        MAX_AVATAR_NAME_LENGTH);
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[3], mUSER[index01].mAvatarInfo.aPartyName[4],
					        MAX_AVATAR_NAME_LENGTH);
					memset(mUSER[index01].mAvatarInfo.aPartyName[4], 0, 13);
				}
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[2], tAvatarName01) == 0)
				{
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[2], mUSER[index01].mAvatarInfo.aPartyName[3],
					        MAX_AVATAR_NAME_LENGTH);
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[3], mUSER[index01].mAvatarInfo.aPartyName[4],
					        MAX_AVATAR_NAME_LENGTH);
					memset(mUSER[index01].mAvatarInfo.aPartyName[4], 0, 13);
				}
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[3], tAvatarName01) == 0)
				{
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[3], mUSER[index01].mAvatarInfo.aPartyName[4],
					        MAX_AVATAR_NAME_LENGTH);
					memset(mUSER[index01].mAvatarInfo.aPartyName[4], 0, 13);
				}
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[4], tAvatarName01) == 0)
				{
					memset(mUSER[index01].mAvatarInfo.aPartyName[4], 0, 13);
				}
				USER_SEND();
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName01) == 0)
			{
				memset(mUSER[index01].mAvatarInfo.aPartyName, 0, 65);
				strcpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, "");
			}
		}
	}
}

//PROCESS_FOR_DATA
void MyWork::ProcessForData(int tUserIndex, int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE])
{
	int tResult;
	int tPage1;
	int tIndex1;
	int tQuantity1;
	int tPage2;
	int tIndex2;
	int tXPost2;
	int tYPost2;
	int nIndex;
	int sIndex;
	int tSkillIndex;
	int tSkillSort;
	int tSkillGrade;
	int tHotKeyPage;
	int tHotKeyIndex;
	int tStatSort;
	int tMoney;
	int tValue;
	float tCoord[3];
	int tChangeTribeSort;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	BYTE tGMData[MAX_TRIBE_WORK_SIZE];
	int tOtherUserIndex;
	int tGod;
	int tChat;
	int tLevel;
	char tContent[MAX_CHAT_CONTENT_LENGTH];
	int index01;
#ifdef __GOD__
	int iMaxLevel = 157;
	int tTribe = -1;
	int tZoneNumber = -1;
	int tLevel2 = 0;
	int tGeneralExperience1 = 0;
	int tGeneralExperience2 = 0;
#else
	int iMaxLevel = ((mSERVER_INFO.m_iDeploymentStage > 0) ? MAX_LIMIT_LEVEL_NUM : 112);
#endif
	char tChangeAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tTargetIndex = -1;
	int tRes;
	int tMove;
	int tCount = 0;
	bool tCheck = false;
	int tAvatarDuelUniqueNumber = 0;
	float tDuelCenter[3];
	float tDuelCenter2[3];

	tDuelCenter[0] = 0.0f;
	tDuelCenter[1] = 0.0f;
	tDuelCenter[2] = 0.0f;
	tDuelCenter2[0] = 0.0f;
	tDuelCenter2[1] = 0.0f;
	tDuelCenter2[2] = 0.0f;

	switch (tSort)
	{
	case 201: //[WORLD]->[INVENTORY]
		if (1 == mUSER[tUserIndex].mAuthInfo.GItemFlag)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForGetItem(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		if (!tResult)
		{
			mTRANSFER.B_ITEM_ACTION_RECV(tPage1, mITEM_OBJECT[tPage1].mUniqueNumber, &mITEM_OBJECT[tPage1].mDATA, 3);
			mUTIL.Broadcast(TRUE, &mITEM_OBJECT[tPage1].mDATA.iLocation[0], UNIT_SCALE_RADIUS1, false);
			mITEM_OBJECT[tPage1].mCheckValidState = FALSE;
			//-----------//
			//.._...//
			//-----------//
			if (mUSER[tUserIndex].mHealthState == 5)
			{
				return;
			}
			//-----------//
			//-----------//
			//-----------//
			//-----//
			//QUEST//
			//-----//
			if ((mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] == 2) && (mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] ==
				mITEM_OBJECT[tPage1].mDATA.iIndex) && (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() == 2))
			{
				mTRANSFER.B_PROCESS_QUEST_RECV(0, 7, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			//-----//
			//-----//
			//-----//
		}
		return;

	case 202: //[NPC]->[SKILL]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);


			return;
		}
		CopyMemory(&nIndex, &tData[0], 4);
		CopyMemory(&sIndex, &tData[4], 4);
		if (!ProcessForLearnSkill1(tUserIndex, nIndex, sIndex, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 203: //[SKILL]->[UP]
		CopyMemory(&tSkillIndex, &tData[0], 4);
		if (!ProcessForSkillUpgrade(tUserIndex, tSkillIndex, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 204: //[SKILL,EMOTICON]->[HOTKEY]
		CopyMemory(&tSkillSort, &tData[0], 4);
		CopyMemory(&tSkillIndex, &tData[4], 4);
		CopyMemory(&tSkillGrade, &tData[8], 4);
		CopyMemory(&tHotKeyPage, &tData[12], 4);
		CopyMemory(&tHotKeyIndex, &tData[16], 4);
		if (!ProcessForSkillToHotKey(tUserIndex, tSkillSort, tSkillIndex, tSkillGrade, tHotKeyPage, tHotKeyIndex,
		                             &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 205: //[HOTKEY(SKILL,EMOTICON)]->[NO]
		CopyMemory(&tHotKeyPage, &tData[0], 4);
		CopyMemory(&tHotKeyIndex, &tData[4], 4);
		if (!ProcessForHotKeyToNo(tUserIndex, tHotKeyPage, tHotKeyIndex, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 206: //[STAT+]
		CopyMemory(&tStatSort, &tData[0], 4);
		if (!ProcessForStatPlus(tUserIndex, tStatSort, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 207: //[MONEY]->[NO]
		CopyMemory(&tMoney, &tData[0], 4);
		if ((tMoney < 0) || (tMoney > 100000000) || (mUSER[tUserIndex].mAvatarInfo.aMoney < tMoney))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tMoney;
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 208: //[INVENTORY]->[INVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                    &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 209: //[INVENTORY]->[WORLD]
		//if (1 == mUSER[tUserIndex].mAuthInfo.DItemFlag) {
		//	mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
		//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//	return;
		//}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToWorld(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 210: //[INVENTORY]->[EQUIP]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToEquip(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 211: //[INVENTORY]->[HOTKEY]
	case 253:
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToHotKey(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                 &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 254: //[Inventory]->[PetInventory]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToPetInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                       tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 255: //[PetInventory]->[Inventory]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForPetInventoryToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                       tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 256: //[PetInventory]->[PetInventory]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForPetInventoryToPetInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                          tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 212: //[INVENTORY]->[NPC-SHOP]
	case 252:
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 4))
		{
			// # Defense Hack # {
			//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			//mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 11, 0);
			// #
			return;
		}
		if (1 == mUSER[tUserIndex].mAuthInfo.ShopFlag)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToNPCShop(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                  &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 213: //[EQUIP]->[INVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForEquipToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 214: //[HOTKEY]->[INVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForHotKeyToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                 &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 215: //[NPC-SHOP]->[INVENTORY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 4))
		{
			// # Defense Hack # {
			//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			//mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 10, 0);
			// #
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForNPCShopToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                  &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 216: //[HOTKEY]->[HOTKEY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForHotKeyToHotKey(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                              &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 217: //[INVENTORY_MONEY]->[WORLD]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoneyToWorld(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                     &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 218: //[INVENTORY]->[TRADE]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToTrade(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 219: //[TRADE]->[INVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForTradeToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 220: //[TRADE]->[TRADE]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForTradeToTrade(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                            &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 221: //[INVENTORY_MONEY]->[TRADE_MONEY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoneyToTradeMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                          tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 222: //[TRADE_MONEY]->[INVENTORY_MONEY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForTradeMoneyToInventoryMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                          tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 223: //[INVENTORY]->[STORE]
	case 250:
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToStore(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 224: //[STORE]->[INVENTORY]
	case 248:
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForStoreToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                                &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 240: //[aMoney2]->[aTradeMoney2]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoney2ToTradeMoney2(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                            tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 241: //[aMoney2]->[aStoreMoney2]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoney2ToStoreMoney2(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                            tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 242: //[aMoney2]->[uSaveMoney2]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoney2ToSaveMoney2(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                           tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 243: //[TradeMoney2]->[aMoney2]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForTradeMoney2ToInventoryMoney2(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                            tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 244: //[aStoreMoney2]->[aMoney2]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForStoreMoney2ToInventoryMoney2(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                            tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 245: //[uSaveMoney2]->[aMoney2]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForSaveMoney2ToInventoryMoney2(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                           tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 246: //[MONEY01]->[MONEY02]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoneyToInventoryMoney2(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2,
		                                               tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 247: //[MONEY2]->[MONEY1]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoney2ToInventoryMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2,
		                                               tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 225: //[STORE]->[STORE]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForStoreToStore(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                            &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 226: //[INVENTORY_MONEY]->[STORE_MONEY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoneyToStoreMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                          tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 227: //[STORE_MONEY]->[INVENTORY_MONEY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForStoreMoneyToInventoryMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                          tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 228: //[INVENTORY]->[SAVE]
	case 251:
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToSave(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                               &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 229: //[SAVE]->[INVENTORY]
	case 249:
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForSaveToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2,
		                               &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 230: //[SAVE]->[SAVE]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForSaveToSave(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 231: //[INVENTORY_MONEY]->[SAVE_MONEY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoneyToSaveMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                         tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 232: //[SAVE_MONEY]->[INVENTORY_MONEY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForSaveMoneyToInventoryMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2,
		                                         tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 233: //[TRIBE_4_NPC]->[SKILL]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 37))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&nIndex, &tData[0], 4);
		CopyMemory(&sIndex, &tData[4], 4);
		if (!ProcessForLearnSkill2(tUserIndex, nIndex, sIndex, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 236: //[CP -> Item]
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 30)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (!mUTIL.ProcessForChange(tUserIndex))
		{
			mTRANSFER.B_PROCESS_DATA_RECV(2, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 30;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 30;
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;


	//------------//
	//[GM]-COMMAND//
	//------------//

	case 501: //[GM]-HIDE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.HideFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		GameLogger(3, "<GM_HIDE>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName,
		           mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aVisibleState = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aVisibleState = 0;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(9, mUSER[tUserIndex].mAvatarInfo.aVisibleState);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 502: //[GM]-SHOW
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.ShowFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		GameLogger(3, "<GM_SHOW>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName,
		           mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aVisibleState = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aVisibleState = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(9, mUSER[tUserIndex].mAvatarInfo.aVisibleState);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 503: //[GM]-EXP
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.ExpFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		GameLogger(3, "<GM_EXP>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName,
		           mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		if ((tValue < 1) || (tValue > 100000000))
		{
			return;
		}
	//mGAMELOG.GL_656_GM_EXP(tUserIndex, tValue);
		mUTIL.ProcessForExperience(tUserIndex, tValue, 0, 0);
		return;
	case 504: //[GM]-MONEY
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MoneyFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		GameLogger(3, "<GM_MONEY>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName,
		           mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		if ((tValue < 1) || (tValue > MAX_NUMBER_SIZE))
		{
			return;
		}
		if (!mUTIL.ProcessForDropItem(4, 1, tValue, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], "",
		                              0))
		{
			return;
		}
	//mGAMELOG.GL_601_GM_CREATE_MONEY(tUserIndex, tValue);
		return;
	case 505: //[GM]-ITEM
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.ItemFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		GameLogger(3, "<GM_CREATE_ITEM>(%s),(%s),(Item: %d),[[%d]]", mUSER[tUserIndex].uID,
		           mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		if ((tValue < 2) || (tValue > 99999))
		{
			return;
		}
		if (!mUTIL.ProcessForDropItem(4, tValue, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], "",
		                              0))
		{
			return;
		}
	//mGAMELOG.GL_602_GM_CREATE_ITEM(tUserIndex, tValue, 0, 0, 0);
		return;
	case 506: //[GM]-MONCALL
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MonCallFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		GameLogger(3, "<GM_MONCALL>(%s),(%s),(Monster ID: %d),[[%d]]", mUSER[tUserIndex].uID,
		           mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		CopyMemory(&tCount, &tData[4], 4);
	/*if (tCount <= 0) {
		Logger("4");
		mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}*/
		if (100 < tCount)
		{
			tCount = 100;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
	//mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//for (index01 = 0; index01 < tCount; ++index01) {
		mSUMMON.SummonMonsterForSpecial(tValue, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], FALSE);
	//}
	//mGAMELOG.GL_628_GM_MONCALL(tUserIndex, tValue);
		return;
	case 507: //[GM]-MOVE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MoveFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tCoord[0], &tData[0], 12);
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] = tCoord[0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1] = tCoord[1];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2] = tCoord[2];
		mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
		return;
	case 508: //[GM]-DIE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.DieFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		if ((tValue < 0) || (tValue > (MAX_MONSTER_OBJECT_NUM - 1)))
		{
			return;
		}
		if (!mMONSTER_OBJECT[tValue].mCheckValidState)
		{
			return;
		}
	//mGAMELOG.GL_657_GM_DIE(tUserIndex, tValue);
		mMONSTER_OBJECT[tValue].mCheckValidState = FALSE;
		mMONSTER_OBJECT[tValue].mInvalidTimeForSummon = GetTickCount64();
		GameLogger(3, "<GM_DIE>(%s),(%s),(Monster ID: %d),[[%d]]", mUSER[tUserIndex].uID,
		           mUSER[tUserIndex].mAvatarInfo.aName, mMONSTER_OBJECT[tValue].mDATA.mIndex,
		           mSERVER_INFO.mServerNumber);
		return;
	case 509: //[GM]-MAX
		if (mUSER[tUserIndex].uUserSort < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		GameLogger(3, "<GM_MAX>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName,
		           mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aVit = 100000;
		mUSER[tUserIndex].mAvatarInfo.aStr = 100000;
		mUSER[tUserIndex].mAvatarInfo.aInt = 100000;
		mUSER[tUserIndex].mAvatarInfo.aDex = 100000;
		mUSER[tUserIndex].mAvatarInfo.aSkillPoint = 100000;
		mUSER[tUserIndex].mAvatarInfo.aUpgradeValue = 96;
		mUSER[tUserIndex].mAvatarInfo.aLevel1 = 145;
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 = MAX_NUMBER_SIZE;
		mUSER[tUserIndex].mAvatarInfo.aLevel2 = 12;
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	case 510: //[GM]-TRIBE
		if (mUSER[tUserIndex].uUserSort < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tChangeTribeSort, &tData[0], 4);
		switch (tChangeTribeSort)
		{
		case 1:
			if (mUSER[tUserIndex].mAvatarInfo.aTribe == 3)
			{
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aTribe = 3;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		case 2:
			if (mUSER[tUserIndex].mAvatarInfo.aTribe != 3)
			{
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aTribe = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		return;
	case 511: //[GM]-EQUIP
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.EquipFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		GameLogger(3, "<GM_EQUIP>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName,
		           mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aSpecialState = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aSpecialState = 1;
		return;
	case 512: //[GM]-UNEQUIP
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.UnequipFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		GameLogger(3, "<GM_UNEQUIP>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName,
		           mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aSpecialState = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aSpecialState = 0;
		return;
	case 513: //[GM]-FIND
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.FindFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND(&tAvatarName[0]);
		CopyMemory(&tGMData[0], &mPLAYUSER_COM.mRecv_ZoneNumber, 4);
		mTRANSFER.B_GM_COMMAND_INFO(1, &tGMData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 514: //[GM]-CALL
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.CallFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[
			0];
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[
			1];
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[
			2];
	//mGAMELOG.GL_655_GM_CALL(tUserIndex, tOtherUserIndex);
		CopyMemory(&tGMData[0], &mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[0], 12);
		mTRANSFER.B_GM_COMMAND_INFO(2, &tGMData[0]);
		mUSER[tOtherUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 515: //[GM]-MOVE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MoveFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] = mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[
			0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1] = mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[
			1];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2] = mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[
			2];
		CopyMemory(&tGMData[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 12);
		mTRANSFER.B_GM_COMMAND_INFO(2, &tGMData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 516: //[GM]-NCHAT
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.NchatFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
	//mGAMELOG.GL_629_GM_NCHAT(tUserIndex, tOtherUserIndex);
		mUSER[tOtherUserIndex].mAvatarInfo.aSpecialState = 2;
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aSpecialState = 2;
		return;
	case 517: //[GM]-YCHAT
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.YchatFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
	//mGAMELOG.GL_630_GM_YCHAT(tUserIndex, tOtherUserIndex);
		mUSER[tOtherUserIndex].mAvatarInfo.aSpecialState = 0;
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aSpecialState = 0;
		return;
	case 518: //[GM]-KICK
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.KickFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
	//mGAMELOG.GL_631_GM_KICK(tUserIndex, tOtherUserIndex);
		mUSER[tOtherUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	case 519: //[GM]-BLOCK
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.BlockFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
	//mGAMELOG.GL_632_GM_BLOCK(tUserIndex, tOtherUserIndex);
		mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_1_SEND(603, &mUSER[tOtherUserIndex].uID[0]);
		mUSER[tOtherUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	case 520: //GOD
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.GodFlag == 0)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tGod, &tData[0], 4);
		mAVATAR_OBJECT[tUserIndex].mGod = tGod;
	//mGAMELOG.GL_648_GM_GOD(tUserIndex, tGod);
		return;
	//case 521: //CHAT
	//	//if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	//	//{
	//	//	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	//	//
	//	//	return;
	//	//}
	//	//if (mUSER[tUserIndex].mAuthInfo.ChatFlag == 0) {
	//	//	mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
	//	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//	//	return;
	//	//}
	//	mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//	CopyMemory(&tChat, &tData[0], 4);
	//	mAVATAR_OBJECT[tUserIndex].mChat = tChat;
	//	//mGAMELOG.GL_649_GM_CHAT( tUserIndex );
	//	return;
	case 522: //UMOVE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(tAvatarName, &tData[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tMove, &tData[MAX_AVATAR_NAME_LENGTH], 4);
		if (0 > tMove)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (0 != strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName))
			{
				continue;
			}
			tTargetIndex = index01;
			break;
		}
		if (-1 == tTargetIndex)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		if (mAVATAR_OBJECT[tTargetIndex].CheckCommunityWork())
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tResult = 0;
		CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH + 4], &tResult, 4);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		tResult = 1;
		CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH + 4], &tResult, 4);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tTargetIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//mGAMELOG.GL_650_GM_UMOVE(tUserIndex, tTargetIndex, tMove);
		return;
	case 521: //LEVEL
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tLevel, &tData[0], 4);
		if ((tLevel > iMaxLevel) || (tLevel < 1))
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
#ifdef __GOD__
		if (tLevel > 145)
		{
			tLevel2 = tLevel - 145;
			tLevel = 145;
			tGeneralExperience1 = MAX_NUMBER_SIZE;
			tGeneralExperience2 = 0;
		}
		else
		{
			tLevel2 = 0;
			tGeneralExperience1 = mLEVEL.ReturnLevelFactor1(tLevel);
			tGeneralExperience2 = 0;
		}
#endif
		GameLogger(3, "<GM_LEVEL>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName,
		           mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//mGAMELOG.GL_651_GM_LEVEL(tUserIndex, tLevel);
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 = mLEVEL.ReturnLevelFactor1(tLevel);
		mUSER[tUserIndex].mAvatarInfo.aLevel1 = tLevel;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 = tLevel;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
#ifdef __GOD__
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = tGeneralExperience2;
		mUSER[tUserIndex].mAvatarInfo.aLevel2 = tLevel2;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = tLevel2;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11,
		                                 mUSER[tUserIndex].mAvatarInfo.aLevel2,
		                                 mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
#endif

		return;
	case 524: //ZNOTICE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//mGAMELOG.GL_652_GM_ZNOTICE( tUserIndex );
		CopyMemory(&tContent[0], &tData[0], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_GENERAL_NOTICE_RECV(&tContent[0], 0);
	//mTRANSFER.B_TRIBE_CHAT_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0] );
	//mCHATLOG.SendToLogServer( mUSER[tUserIndex].mAvatarInfo.aTribe, 6, mUSER[tUserIndex].mAvatarInfo.aName, "", tContent );
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;
	case 525: //RES
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(tAvatarName, &tData[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tRes, &tData[MAX_AVATAR_NAME_LENGTH], 4);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (0 != strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName))
			{
				continue;
			}
			tTargetIndex = index01;
			break;
		}
		if (-1 == tTargetIndex)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		switch (tRes)
		{
		case 0:
			mUSER[tTargetIndex].mAuthInfo.TradeFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.ShopFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.PShopFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.GItemFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.DItemFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.AttackFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.UZonemoveFlag = 0;
			break;
		case 1:
			mUSER[tTargetIndex].mAuthInfo.TradeFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.ShopFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.PShopFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.GItemFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.DItemFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.AttackFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.UZonemoveFlag = 1;
			break;
		case 2:
			tResult = 2;
			CopyMemory(&tData[0], &tResult, 4);
			snprintf((char*)&tData[4], MAX_BROADCAST_DATA_SIZE, "%d%d%d%d%d%d%d",
			         mUSER[tTargetIndex].mAuthInfo.TradeFlag, mUSER[tTargetIndex].mAuthInfo.ShopFlag,
			         mUSER[tTargetIndex].mAuthInfo.PShopFlag,
			         mUSER[tTargetIndex].mAuthInfo.GItemFlag, mUSER[tTargetIndex].mAuthInfo.DItemFlag,
			         mUSER[tTargetIndex].mAuthInfo.AttackFlag,
			         mUSER[tTargetIndex].mAuthInfo.UZonemoveFlag);
			break;
		case 11:
			mUSER[tTargetIndex].mAuthInfo.TradeFlag = 1;
			break;
		case 12:
			mUSER[tTargetIndex].mAuthInfo.ShopFlag = 1;
			break;
		case 13:
			mUSER[tTargetIndex].mAuthInfo.PShopFlag = 1;
			break;
		case 14:
			mUSER[tTargetIndex].mAuthInfo.GItemFlag = 1;
			break;
		case 15:
			mUSER[tTargetIndex].mAuthInfo.DItemFlag = 1;
			break;
		case 16:
			mUSER[tTargetIndex].mAuthInfo.AttackFlag = 1;
			break;
		case 17:
			mUSER[tTargetIndex].mAuthInfo.UZonemoveFlag = 1;
			break;
		default:
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//mGAMELOG.GL_653_GM_RES(tUserIndex, tTargetIndex, tRes);
		return;
	case 526: //RENAME
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tChangeAvatarName[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tChangeAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (0 != strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName))
			{
				continue;
			}
			tTargetIndex = index01;
			break;
		}
		if (-1 == tTargetIndex)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mPLAYUSER_COM.U_CHANGE_AVATAR_NAME_FOR_ZONE_SEND(mUSER[tTargetIndex].mPlayUserIndex, tChangeAvatarName);

		if (0 != mPLAYUSER_COM.mRecv_Result)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tData[0], &tTargetIndex, 4);
		CopyMemory(&tData[4], &mAVATAR_OBJECT[tTargetIndex].mUniqueNumber, 4);
		CopyMemory(&tData[8], tChangeAvatarName, MAX_AVATAR_NAME_LENGTH);

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
	//mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tTargetIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);

		CopyMemory(mUSER[tTargetIndex].mAvatarInfo.aName, tChangeAvatarName, MAX_AVATAR_NAME_LENGTH);
		CopyMemory(mAVATAR_OBJECT[tTargetIndex].mDATA.aName, tChangeAvatarName, MAX_AVATAR_NAME_LENGTH);
	}
}
