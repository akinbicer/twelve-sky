﻿//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "MainApp.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_PLAYUSER_COM
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyPlayUserCom mPLAYUSER_COM;
//CREATE
MyPlayUserCom::MyPlayUserCom(void)
{
}

//CONNECT
BOOL MyPlayUserCom::Connect(void)
{
	if (mCheckConnectState)
	{
		return TRUE;
	}

	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tOKRecvCheck;
	char tOKDataCheck;

	WSAData wsaData;
	int err = 0;
	WORD wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0)
	{
		return FALSE;
	}

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket < 0)
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(mIP);
	mAddress.sin_port = htons(mPort);
	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(mSocket);
		Sleep(1);
		return FALSE;
	}

	tConnectRecvCheck = recv(mSocket, &tConnectDataCheck, 1, 0);
	if (tConnectRecvCheck != 1)
	{
		closesocket(mSocket);
		return FALSE;
	}
	tSendData[0] = P_ZONE_FOR_PLAYUSER_SEND;
	CopyMemory(&tSendData[1], &mZoneNumber, 4);
	tSendDataSize = S_ZONE_FOR_PLAYUSER_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &tSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 < 0)
		{
			if (errno == EINTR)
				continue;
			closesocket(mSocket);
			return FALSE;
		}
		if (tSendValue03 == 0)
		{
			closesocket(mSocket);
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	tOKRecvCheck = recv(mSocket, &tOKDataCheck, 1, 0);
	if (tOKRecvCheck != 1)
	{
		closesocket(mSocket);
		return FALSE;
	}
	mCheckConnectState = TRUE;

	return TRUE;
}

//SEND
BOOL MyPlayUserCom::Send(void)
{
	int nResult = 0;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;

	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &mSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 < 0)
		{
			if (errno == EINTR)
				continue;

			Close();
			return FALSE;
		}
		if (tSendValue03 == 0)
		{
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}

	return TRUE;
}

//RECV
BOOL MyPlayUserCom::Recv(void)
{
	int nCount = 0;
	int nResult = 0;
	int ret_val = 0;
	int tRecvValue01;
	int tRecvValue02;
	int chk_flag = 0;
	int chk_result = 0;

	if (mRecvDataSize > 0)
	{
		tRecvValue01 = 0;
		while (TRUE)
		{
			tRecvValue02 = recv(mSocket, &mRecvData[tRecvValue01], mRecvDataSize - tRecvValue01, 0);
			if (tRecvValue02 < 0)
			{
				if (errno == EINTR)
					continue;
				Close();
				return FALSE;
			}
			if (tRecvValue02 == 0)
			{
				Close();
				return FALSE;
			}
			tRecvValue01 += tRecvValue02;
			if (tRecvValue01 == mRecvDataSize)
			{
				break;
			}
		}
	}

	return TRUE;
}

//CLOSE
void MyPlayUserCom::Close(void)
{
	if (!mCheckConnectState)
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket(mSocket);
}

//INIT
BOOL MyPlayUserCom::Init(int tZoneNumber, char tIP[16], int tPort)
{
	mCheckConnectState = FALSE;
	if (tZoneNumber < 1)
	{
		return FALSE;
	}
	mZoneNumber = tZoneNumber;
	strcpy(mIP, tIP);
	mPort = tPort;
	pthread_mutex_init(&m_lock, nullptr);

	if (!Connect())
	{
		return FALSE;
	}

	return TRUE;
}

//FREE
void MyPlayUserCom::Free(void)
{
	Close();
	pthread_mutex_destroy(&m_lock);
}

//PROCESS_FOR_NETWORK
BOOL MyPlayUserCom::ProcessForNetwork(void)
{
	if (!Connect())
	{
		return FALSE;
	}
	if (!Send())
	{
		return FALSE;
	}
	if (!Recv())
	{
		return FALSE;
	}

	return TRUE;
}

//U_ZONE_OK_FOR_PLAYUSER_SEND
void MyPlayUserCom::U_ZONE_OK_FOR_PLAYUSER_SEND(void)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_ZONE_OK_FOR_PLAYUSER_SEND;
		mSendDataSize = S_ZONE_OK_FOR_PLAYUSER_SEND;
		mRecvDataSize = 0;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//U_REGISTER_USER_FOR_ZONE_0_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_ZONE_0_SEND(char tID[MAX_USER_ID_LENGTH])
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_REGISTER_USER_FOR_ZONE_0_SEND;
		CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
		mSendDataSize = S_REGISTER_USER_FOR_ZONE_0_SEND;
		mRecvDataSize = S_REGISTER_USER_FOR_ZONE_0_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_PlayUserIndex, &mRecvData[5], 4);
	pthread_mutex_unlock(&m_lock);
}

//U_REGISTER_USER_FOR_ZONE_1_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_ZONE_1_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH],
                                                    char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tLogoutInfo[6])
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_REGISTER_USER_FOR_ZONE_1_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tLogoutInfo[0], 24);
		mSendDataSize = S_REGISTER_USER_FOR_ZONE_1_SEND;
		mRecvDataSize = S_REGISTER_USER_FOR_ZONE_1_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_UserSort, &mRecvData[5], 4);
	CopyMemory(&mRecv_AvatarInfo, &mRecvData[34], SIZE_OF_AVATAR_INFO);
	CopyMemory(mRecv_EffectValue, &mRecvData[(34 + SIZE_OF_AVATAR_INFO)], (MAX_AVATAR_EFFECT_SORT_NUM * 8));
	CopyMemory(&mRecv_CheckFirstZone, &mRecvData[(34 + SIZE_OF_AVATAR_INFO + MAX_AVATAR_EFFECT_SORT_NUM * 8)], 4);
	CopyMemory(&mRecv_AuthInfo, &mRecvData[(38 + SIZE_OF_AVATAR_INFO + (MAX_AVATAR_EFFECT_SORT_NUM * 8))],
	           sizeof(AUTH_INFO));
	CopyMemory(&mRecv_MoveItemInfo,
	           &mRecvData[(38 + SIZE_OF_AVATAR_INFO + (MAX_AVATAR_EFFECT_SORT_NUM * 8) + sizeof(AUTH_INFO))],
	           sizeof(MOVE_ITEM_INFO));
	pthread_mutex_unlock(&m_lock);
}

//U_REGISTER_USER_FOR_ZONE_2_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_ZONE_2_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH],
                                                    AVATAR_INFO* tAvatarInfo,
                                                    int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2],
                                                    AUTH_INFO* tAuthInfo)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_REGISTER_USER_FOR_ZONE_2_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], tAvatarInfo, SIZE_OF_AVATAR_INFO);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + SIZE_OF_AVATAR_INFO)], tEffectValue,
		           (MAX_AVATAR_EFFECT_SORT_NUM * 8));
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + SIZE_OF_AVATAR_INFO + (MAX_AVATAR_EFFECT_SORT_NUM * 8))],
		           tAuthInfo, sizeof(AUTH_INFO));
		mSendDataSize = S_REGISTER_USER_FOR_ZONE_2_SEND;
		mRecvDataSize = S_REGISTER_USER_FOR_ZONE_2_RECV;
		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	pthread_mutex_unlock(&m_lock);
}

//U_REGISTER_USER_FOR_ZONE_3_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_ZONE_3_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH],
                                                    AVATAR_INFO* tAvatarInfo,
                                                    int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2],
                                                    AUTH_INFO* tAuthInfo)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_REGISTER_USER_FOR_ZONE_3_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], tAvatarInfo, SIZE_OF_AVATAR_INFO);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + SIZE_OF_AVATAR_INFO)], tEffectValue,
		           (MAX_AVATAR_EFFECT_SORT_NUM * 8));
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + SIZE_OF_AVATAR_INFO + (MAX_AVATAR_EFFECT_SORT_NUM * 8))],
		           tAuthInfo, sizeof(AUTH_INFO));
		mSendDataSize = S_REGISTER_USER_FOR_ZONE_3_SEND;
		mRecvDataSize = S_REGISTER_USER_FOR_ZONE_3_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	pthread_mutex_unlock(&m_lock);
}

//U_UNREGISTER_USER_FOR_ZONE_SEND
void MyPlayUserCom::U_UNREGISTER_USER_FOR_ZONE_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH],
                                                    AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_UNREGISTER_USER_FOR_ZONE_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], tAvatarInfo, SIZE_OF_AVATAR_INFO);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + SIZE_OF_AVATAR_INFO)], tAuthInfo, sizeof(AUTH_INFO));
		mSendDataSize = S_UNREGISTER_USER_FOR_ZONE_SEND;
		mRecvDataSize = S_UNREGISTER_USER_FOR_ZONE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//U_FIND_AVATAR_FOR_ZONE_SEND
void MyPlayUserCom::U_FIND_AVATAR_FOR_ZONE_SEND(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_FIND_AVATAR_FOR_ZONE_SEND;
		CopyMemory(&mSendData[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mSendDataSize = S_FIND_AVATAR_FOR_ZONE_SEND;
		mRecvDataSize = S_FIND_AVATAR_FOR_ZONE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_ZoneNumber, &mRecvData[1], 4);
	CopyMemory(&mRecv_Tribe, &mRecvData[5], 4);
	pthread_mutex_unlock(&m_lock);
}

//U_TRIBE_BANK_INFO_SAVE_SEND
void MyPlayUserCom::U_TRIBE_BANK_INFO_SAVE_SEND(int tMoney[4])
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_TRIBE_BANK_INFO_SAVE_SEND;
		CopyMemory(&mSendData[1], &tMoney[0], 16);
		mSendDataSize = S_TRIBE_BANK_INFO_SAVE_SEND;
		mRecvDataSize = S_TRIBE_BANK_INFO_SAVE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//U_TRIBE_BANK_INFO_VIEW_SEND
void MyPlayUserCom::U_TRIBE_BANK_INFO_VIEW_SEND(int tTribe)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_TRIBE_BANK_INFO_VIEW_SEND;
		CopyMemory(&mSendData[1], &tTribe, 4);
		mSendDataSize = S_TRIBE_BANK_INFO_VIEW_SEND;
		mRecvDataSize = S_TRIBE_BANK_INFO_VIEW_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_TribeBankInfo[0], &mRecvData[5], (MAX_TRIBE_BANK_SLOT_NUM * 4));
	pthread_mutex_unlock(&m_lock);
}

//U_TRIBE_BANK_INFO_LOAD_SEND
void MyPlayUserCom::U_TRIBE_BANK_INFO_LOAD_SEND(int tTribe, int tTribeBankInfoIndex, int tInventoryMoney)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_TRIBE_BANK_INFO_LOAD_SEND;
		CopyMemory(&mSendData[1], &tTribe, 4);
		CopyMemory(&mSendData[5], &tTribeBankInfoIndex, 4);
		CopyMemory(&mSendData[9], &tInventoryMoney, 4);
		mSendDataSize = S_TRIBE_BANK_INFO_LOAD_SEND;
		mRecvDataSize = S_TRIBE_BANK_INFO_LOAD_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_Money, &mRecvData[5], 4);
	pthread_mutex_unlock(&m_lock);
}

//U_HACK_NAME_SEND
void MyPlayUserCom::U_HACK_NAME_SEND(char tID[MAX_USER_ID_LENGTH], char tHackName[MAX_HACK_NAME_LENGTH], int tHackSize)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_HACK_NAME_SEND;
		CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(1 + MAX_USER_ID_LENGTH)], &tHackName[0], MAX_HACK_NAME_LENGTH);
		CopyMemory(&mSendData[(1 + MAX_USER_ID_LENGTH + MAX_HACK_NAME_LENGTH)], &tHackSize, 4);
		mSendDataSize = S_HACK_NAME_SEND;
		mRecvDataSize = S_HACK_NAME_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	pthread_mutex_unlock(&m_lock);
}

//U_BLOCK_USER_FOR_ZONE_1_SEND
void MyPlayUserCom::U_BLOCK_USER_FOR_ZONE_1_SEND(int tSort, char tID[MAX_USER_ID_LENGTH])
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_BLOCK_USER_FOR_ZONE_1_SEND;
		CopyMemory(&mSendData[1], &tSort, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		mSendDataSize = S_BLOCK_USER_FOR_ZONE_1_SEND;
		mRecvDataSize = S_BLOCK_USER_FOR_ZONE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//U_BLOCK_USER_FOR_ZONE_2_SEND
void MyPlayUserCom::U_BLOCK_USER_FOR_ZONE_2_SEND(int tSort, char tID[MAX_USER_ID_LENGTH])
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_BLOCK_USER_FOR_ZONE_2_SEND;
		CopyMemory(&mSendData[1], &tSort, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		mSendDataSize = S_BLOCK_USER_FOR_ZONE_2_SEND;
		mRecvDataSize = S_BLOCK_USER_FOR_ZONE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//U_ADD_AUTO_USER_LIST_SEND
void MyPlayUserCom::U_ADD_AUTO_USER_LIST_SEND(char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH],
                                              int tWorldNumber, int tZoneNumber)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_ADD_AUTO_USER_LIST_SEND;
		CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(1 + MAX_USER_ID_LENGTH)], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mSendData[(1 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tWorldNumber, 4);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tZoneNumber, 4);
		mSendDataSize = S_ADD_AUTO_USER_LIST_SEND;
		mRecvDataSize = S_ADD_AUTO_USER_LIST_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	pthread_mutex_unlock(&m_lock);
}

//U_CHECK_KILL_OTHER_TRIBE_SEND
void MyPlayUserCom::U_CHECK_KILL_OTHER_TRIBE_SEND(char tAvatarName1[MAX_AVATAR_NAME_LENGTH],
                                                  char tAvatarName2[MAX_AVATAR_NAME_LENGTH])
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_CHECK_KILL_OTHER_TRIBE_SEND;
		CopyMemory(&mSendData[1], &tAvatarName1[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mSendData[(1 + MAX_AVATAR_NAME_LENGTH)], &tAvatarName2[0], MAX_AVATAR_NAME_LENGTH);
		mSendDataSize = S_CHECK_KILL_OTHER_TRIBE_SEND;
		mRecvDataSize = S_CHECK_KILL_OTHER_TRIBE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	pthread_mutex_unlock(&m_lock);
}

//U_EVENT_INFO_SEND
void MyPlayUserCom::U_EVENT_INFO_SEND(char tID[MAX_USER_ID_LENGTH], int tSort)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_EVENT_INFO_SEND;
		CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(1 + MAX_USER_ID_LENGTH)], &tSort, 4);
		mSendDataSize = S_EVENT_INFO_SEND;
		mRecvDataSize = S_EVENT_INFO_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

void MyPlayUserCom::U_CHECK_AUTH_KEY(char szID[MAX_USER_ID_LENGTH], char szAuthKey[MAX_MOUSE_PASSWORD_LENGTH])
{
	pthread_mutex_lock(&m_lock);
	while (true)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		ZTOP_CHECK_AUTH_KEY pack1;
		::CopyMemory(pack1.m_szUserID, szID, sizeof(pack1.m_szUserID));
		::CopyMemory(pack1.m_szAuthKey, szAuthKey, sizeof(pack1.m_szAuthKey));
		::CopyMemory(mSendData, &pack1, ZTOP_CHECK_AUTH_KEY_SIZE);
		mSendDataSize = ZTOP_CHECK_AUTH_KEY_SIZE;
		mRecvDataSize = PTOZ_CHECK_AUTH_KEY_SIZE;

		if (ProcessForNetwork() == TRUE)
			break;
	}

	PTOZ_CHECK_AUTH_KEY pack2;
	::CopyMemory(&pack2, mRecvData, PTOZ_CHECK_AUTH_KEY_SIZE);
	mRecv_Result = static_cast<int>(pack2.m_bResult);
	pthread_mutex_unlock(&m_lock);
}

void MyPlayUserCom::U_UPDATE_AUTH_KEY(char szID[MAX_USER_ID_LENGTH], char szAuthKey[3][MAX_MOUSE_PASSWORD_LENGTH])
{
	pthread_mutex_lock(&m_lock);
	while (true)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		ZTOP_UPDATE_AUTH_KEY pack1;
		::CopyMemory(pack1.m_szUserID, szID, sizeof(pack1.m_szUserID));
		::CopyMemory(pack1.m_szAuthKey, szAuthKey, sizeof(pack1.m_szAuthKey));
		::CopyMemory(mSendData, &pack1, ZTOP_UPDATE_AUTH_KEY_SIZE);
		mSendDataSize = ZTOP_UPDATE_AUTH_KEY_SIZE;
		mRecvDataSize = PTOZ_UPDATE_AUTH_KEY_SIZE;

		if (ProcessForNetwork() == TRUE)
			break;
	}

	PTOZ_UPDATE_AUTH_KEY pack2;
	::CopyMemory(&pack2, mRecvData, PTOZ_UPDATE_AUTH_KEY_SIZE);
	mRecv_Result = static_cast<int>(pack2.m_bResult);
	pthread_mutex_unlock(&m_lock);
}

void MyPlayUserCom::U_CHANGE_AVATAR_NAME_FOR_ZONE_SEND(int tPlayUserIndex, char* tChangeAvatarName)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_CHANGE_AVATAR_NAME_FOR_ZONE_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], tChangeAvatarName, MAX_AVATAR_NAME_LENGTH);
		mSendDataSize = S_CHANGE_AVATAR_NAME_FOR_ZONE_SEND;
		mRecvDataSize = S_CHANGE_AVATAR_NAME_FOR_ZONE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	pthread_mutex_unlock(&m_lock);
}

void MyPlayUserCom::U_BONUS_100_MONEY_FOR_ZONE_SEND(int tPlayUserIndex)
{
#if 0
	mSendData[0] = P_BONUS_100_MONEY_FOR_ZONE_SEND;
	CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
	mSendDataSize = S_BONUS_100_MONEY_FOR_ZONE_SEND;
	mRecvDataSize = S_BONUS_100_MONEY_FOR_ZONE_RECV;
	while (TRUE)
	{
		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
#endif
}

void MyPlayUserCom::U_SET_MOVE_ITEM_FOR_ZONE_SEND(int tPlayUserIndex, MOVE_ITEM_INFO* tMoveItemInfo)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_SET_MOVE_ITEM_FOR_ZONE_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], tMoveItemInfo, sizeof(MOVE_ITEM_INFO));

		mSendDataSize = S_SET_MOVE_ITEM_FOR_ZONE_SEND;
		mRecvDataSize = 0;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//U_EVENT_FOR_ZONE_SEND
void MyPlayUserCom::U_EVENT_FOR_ZONE_SEND(int tPlayUserIndex, int tKillNum)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_EVENT_FOR_ZONE_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tKillNum, 4);

		mSendDataSize = S_EVENT_FOR_ZONE_SEND;
		mRecvDataSize = 0;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//void MyPlayUserCom::U_EVENT_FOR_ZONE_SEND_PHONE(int tPlayUserIndex)
//{
//	pthread_mutex_lock(&m_lock);
//	while (TRUE)
//	{
//		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
//		mSendData[0] = P_EVENT_FOR_ZONE_SEND_PHONE;
//		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
//
//		mSendDataSize = S_EVENT_FOR_ZONE_SEND_PHONE;
//		mRecvDataSize = 0;
//
//		if (ProcessForNetwork())
//		{
//			break;
//		}
//	}
//	pthread_mutex_unlock(&m_lock);
//}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//INSTANCE
MyCenterCom mCENTER_COM;
//CREATE
MyCenterCom::MyCenterCom(void)
{
	// @ Cost Info Download @
	mIsUpdateCashItemInfo = false;
	// @
}

//CONNECT
BOOL MyCenterCom::Connect(void)
{
	if (*mCheckConnectState)
	{
		return TRUE;
	}

	int n_read = 0;
	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tRecvDataSize;
	int tRecvValue01;
	int tRecvValue02;
	int chk_first = 1;
	mGAME.mRankInfo = nullptr;
	mGAME.mRankInfoSize = 0;

	WSAData wsaData;
	int err = 0;
	WORD wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return FALSE;
	}
	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket < 0)
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(mIP);
	mAddress.sin_port = htons(mPort);

	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		Close();
		return FALSE;
	}

	tConnectRecvCheck = recv(mSocket, &tConnectDataCheck, 1, 0);
	if (tConnectRecvCheck != 1)
	{
		Close();
		return FALSE;
	}

	mRecvDataSize = 0;
	memset(mRecvData, 0, MAX_RECV_DATA_SIZE);

	tSendData[0] = P_ZONE_FOR_CENTER_SEND;
	CopyMemory(&tSendData[1], &mZoneNumber, 4);
	CopyMemory(&tSendData[5], &mZonePort, 4);
	tSendDataSize = S_ZONE_FOR_CENTER_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &tSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 < 0)
		{
			if (errno == EINTR)
				continue;
			Close();
			return FALSE;
		}
		if (tSendValue03 == 0)
		{
			Close();
			return FALSE;
		}

		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	tRecvDataSize = S_ZONE_FOR_CENTER_RECV + S_TOTAL_ZONE_CONNECTION_INFO + S_WORLD_INFO;
	tRecvValue01 = 0;
	while (TRUE)
	{
		tRecvValue02 = recv(mSocket, &mRecvData[tRecvValue01], tRecvDataSize, 0);
		if (tRecvValue02 < 0)
		{
			if (errno == EINTR)
				continue;
			Close();
			return FALSE;
		}
		if (tRecvValue02 == 0)
		{
			Close();
			return FALSE;
		}
		tRecvValue01 += tRecvValue02;
		if (tRecvValue01 >= tRecvDataSize)
		{
			break;
		}
	}
	CopyMemory(&mGAME.mZoneConnectionInfo, &mRecvData[2], sizeof(ZONE_CONNECTION_INFO));
	CopyMemory(&mGAME.mWorldInfo, &mRecvData[(3 + sizeof(ZONE_CONNECTION_INFO))], SIZE_OF_WORLD_INFO);
	CopyMemory(&mGAME.mTribeInfo, &mRecvData[(3 + sizeof(ZONE_CONNECTION_INFO) + SIZE_OF_WORLD_INFO)],
	           SIZE_OF_TRIBE_INFO);

	memmove(mRecvData, &mRecvData[tRecvDataSize], (tRecvValue01 - tRecvDataSize));
	mRecvDataSize = tRecvValue01 - tRecvDataSize;

#if 0
	/* Get Total Rank Info Start */
	tSendData[0] = P_GET_TOTAL_RANK_INFO_SEND;
	tSendDataSize = S_GET_TOTAL_RANK_INFO_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		SVR_TRACE();
		tSendValue03 = send(mSocket, &tSendData[tSendValue02], tSendValue01, 0);
		SVR_TRACE();
		if (tSendValue03 < 0)
		{
			if (errno == EINTR)
				continue;
			Close();
			//closesocket( mSocket );
			return FALSE;
		}
		else if (tSendValue03 == 0)
		{
			Close();
			//closesocket( mSocket );
			return FALSE;
		}

		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	tRecvDataSize = 13;
	tRecvValue01 = 0;
	tRecvValue02 = 0;
	while (TRUE)
	{
		SVR_TRACE();
		tRecvValue02 = recv(mSocket, &mRecvData[tRecvValue01], tRecvDataSize, 0);
		SVR_TRACE();
		LOG_TO_FILE_4("---> %d %d %d %s\n", tRecvValue02, tRecvDataSize, tRecvValue01, strerror(errno));
		if (tRecvValue02 < 0)
		{
			if (errno == EINTR)
				continue;
			Close();
			//closesocket( mSocket );
			return FALSE;
		}
		else if (tRecvValue02 == 0)
		{
			Close();
			//closesocket( mSocket );
			return FALSE;
		}
		tRecvValue01 += tRecvValue02;
		//LOG_TO_FILE_2("total recv_size : %d %d\n", tRecvValue01, (tRecvDataSize + 13));
		if ((tRecvValue01 == tRecvDataSize) && chk_first)
		{
			chk_first = 0;
			::memcpy(&tRecvDataSize, mRecvData + 1, 4);
			if (tRecvDataSize == 0)
				break;
		}
		else if (tRecvValue01 == (tRecvDataSize + 13))
		{
			::memcpy(&mGAME.mRankInfo, mRecvData, tRecvValue01);
			break;
		}
	}

	if (!mGAME.mRankInfo)
		::free(mGAME.mRankInfo);

	mGAME.mRankInfoSize = tRecvValue01 - 1;
	mGAME.mRankInfo = (char*)malloc(tRecvValue01 - 1);
	::memcpy(mGAME.mRankInfo, mRecvData + 1, (tRecvValue01 - 1));
#endif
	/* Get Total Rank Info End */

	memmove(mRecvData, &mRecvData[0], tRecvValue01);
	mRecvDataSize = 0;
	*mCheckConnectState = TRUE;

	fd_set read_fds;

	while (true)
	{
		struct timeval tv = {5, 0};
		FD_ZERO(&read_fds);
		FD_SET(mSocket, &read_fds);

		if (!(*mCheckConnectState))
		{
			//LOG_TO_FILE_1("Center connect closed(%d)\n", *mCheckConnectState);
			Close();
			return FALSE;
		}
		//LOG_TO_FILE_2("!CHECK center select : %d %d \n", mSocket, mCheckConnectState);
		//if(select(mSocket + 1, &read_fds, NULL, NULL, &tv) < 0) {
		*mCheckSocketState = 1;
		if (chk_first == 1 && mSERVER.mRankCheck)
		{
			W_RANK_TOTAL_SEND();
			chk_first = 0;
		}
		if (select(mSocket + 1, &read_fds, nullptr, nullptr, nullptr) < 0)
		{
			if (errno == EINTR)
			{
				continue;
			}
			//LOG_TO_FILE_4("![%s] : %s(%d)-%d(!!!!)\n", __FUNCTION__, strerror(errno), errno, mSocket);
			FD_CLR(mSocket, &read_fds);
			Close();
			*mCheckSocketState = 0;
			return FALSE;
		}

		if (FD_ISSET(mSocket, &read_fds))
		{
			*mCheckSocketState = 0;
			n_read = WindowProc(nullptr, WM_NETWORK_MESSAGE_2, reinterpret_cast<WPARAM>(&mSocket), FD_READ);
			if (n_read == 0)
			{
				FD_CLR(mSocket, &read_fds);
				Close();
				return FALSE;
			}
			*mCheckSocketState = 1;
			*mCheckConnectState = TRUE;
		}
	}

	return TRUE;
}

//SEND
BOOL MyCenterCom::Send(void)
{
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &mSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 < 0)
		{
			if (errno != EINTR)
			{
				Close();
				return FALSE;
			}
			continue;
		}
		if (tSendValue03 == 0)
		{
			Close();
			return FALSE;
		}

		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	return TRUE;
}

//CLOSE
void MyCenterCom::Close(void)
{
	if (!(*mCheckConnectState))
	{
		return;
	}
	*mCheckConnectState = FALSE;
	closesocket(mSocket);
}

void* MyCenterCom::Start(void* arg)
{
	auto mThd = reinterpret_cast<MyCenterCom*>(arg);

	while (true)
	{
		if (!(*mThd->mCheckConnectState))
		{
			if (!mThd->Connect())
			{
				Sleep(500000);
			}
		}
	}
}

void MyCenterCom::connect_thread(void)
{
	if (!(*mCheckConnectState))
	{
		if (pthread_create(&m_handle, nullptr, Start, this) != 0)
		{
			//LOG_TO_FILE_2("![%s] : %s\n", __FUNCTION__, strerror(errno));
			return;
		}
		pthread_detach(m_handle);
	}
}

//INIT
BOOL MyCenterCom::Init(int tZoneNumber, int tZonePort, char tIP[16], int tPort)
{
	mCheckSocketState = static_cast<BOOL*>(malloc(sizeof(bool)));
	mCheckConnectState = static_cast<BOOL*>(malloc(sizeof(bool)));
	*mCheckConnectState = FALSE;
	if (tZoneNumber < 1)
	{
		free(mCheckSocketState);
		free(mCheckConnectState);
		return FALSE;
	}
	mZoneNumber = tZoneNumber;
	mZonePort = tZonePort;
	strcpy(mIP, tIP);
	mPort = tPort;
	*mCheckSocketState = 0;
	pthread_mutex_init(&m_lock, nullptr); //³õÊ¼»¯
	//pthread_mutex_init(&m_lock, NULL);

	connect_thread();

	return TRUE;
}

//FREE
void MyCenterCom::Free(void)
{
	Close();
	pthread_mutex_destroy(&m_lock);
	//pthread_mutex_destroy(&m_lock);
}

//PROCESS_FOR_NETWORK
int MyCenterCom::PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
{
	int tRecvSize;
	BYTE tProtocol;
	int tTotalPacketSize;

	switch (WSAGETSELECTEVENT(lPrm))
	{
	case FD_READ:
	AGAIN:
		tRecvSize = recv(mSocket, &mRecvData[mRecvDataSize], (MAX_RECV_DATA_SIZE - mRecvDataSize), 0);
		if (tRecvSize < 0)
		{
			if (errno == EINTR)
				goto AGAIN;
			Close();
			return 0;
		}
		if (tRecvSize == 0)
		{
			Close();
			return 0;
		}

		mRecvDataSize += tRecvSize;
		while (TRUE)
		{
			if (mRecvDataSize < 1)
			{
				return tRecvSize;
			}
			tProtocol = static_cast<BYTE>(mRecvData[0]);
			switch (tProtocol)
			{
			case P_WORLD_INFO:
				tTotalPacketSize = S_WORLD_INFO;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_WORLD_INFO();
				break;
			case P_ZONE_CONNECTION_INFO:
				tTotalPacketSize = S_ZONE_CONNECTION_INFO;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_ZONE_CONNECTION_INFO();
				break;
			case P_BROADCAST_INFO:
				tTotalPacketSize = S_BROADCAST_INFO;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_BROADCAST_INFO();
				break;
			case P_START:
				tTotalPacketSize = S_START;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_START();
				break;
			case P_NOTICE:
				tTotalPacketSize = S_NOTICE;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_NOTICE();
				break;
			case P_SET_EVENT:
				tTotalPacketSize = S_SET_EVENT;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_SET_EVENT();
				break;
			case P_SHUTDOWN:
				tTotalPacketSize = S_SHUTDOWN;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_SHUTDOWN();
				break;
			case P_TRIBE_CHAT:
				tTotalPacketSize = S_TRIBE_CHAT;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_TRIBE_CHAT();
				break;
			case P_SECRET_CHAT:
				tTotalPacketSize = S_SECRET_CHAT;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_SECRET_CHAT();
				break;
			case P_POLICE_INFO:
				tTotalPacketSize = S_POLICE_INFO;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_POLICE_INFO();
				break;
			case P_SET_GM_ORDER:
				tTotalPacketSize = S_SET_GM_ORDER;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_SET_GM_ORDER();
				break;
			case P_SERCH_AVATAR:
				tTotalPacketSize = S_SERCH_AVATAR;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_SERCH_AVATAR();
				break;
			case P_SET_GM_ORDER_MOVE_AVATAR:
				tTotalPacketSize = S_SET_GM_ORDER_MOVE_AVATAR;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_SET_GM_ORDER_MOVE_AVATAR();
				break;
			case GTOZ_BAN_PLAYER_TYPE:
				tTotalPacketSize = GTOZ_BAN_PLAYER_SIZE;
				if (mRecvDataSize < tTotalPacketSize)
					return tRecvSize;
				W_BAN_PLAYER();
				break;
			case P_CHECK_EVENT:
				tTotalPacketSize = S_CHECK_EVENT;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_CHECK_EVENT();
				break;
			case P_TOTAL_RANK_INFO_RECV:
				if (mRecvDataSize > 5)
				{
					memcpy(&tTotalPacketSize, &mRecvData[1], 4);
					tTotalPacketSize += 13;
				}
				else if ((mRecvDataSize < 5))
				{
					goto AGAIN;
				}
				if (mRecvDataSize < tTotalPacketSize)
				{
					goto AGAIN;
				}
				W_RANK_TOTAL_INFO_SEND(tTotalPacketSize);
				break;
			case P_RANK_INFO_RECV:
				tTotalPacketSize = S_RANK_INFO_RECV;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_RANK_INFO_SEND();
				break;
			// # X-Trap # {
			case P_XTRAP_MAP_FILE_CHANGE_FOR_ZONE:
				tTotalPacketSize = S_XTRAP_MAP_FILE_CHANGE_FOR_ZONE;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_XTRAP_MAP_FILE_CHANGE_FOR_ZONE();
				break;

			case P_UPDATE_CASH_ITEM_INFO_FOR_ZONE:
				tTotalPacketSize = S_UPDATE_CASH_ITEM_INFO_FOR_ZONE;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_UPDATE_CASH_ITEM_INFO_FOR_ZONE();
				break;
			default:
				Close();
				return 0;
			}
			if (*mCheckConnectState)
			{
				memmove(mRecvData, mRecvData + tTotalPacketSize, (mRecvDataSize - tTotalPacketSize));
				mRecvDataSize -= tTotalPacketSize;
			}
		}
		return tRecvSize;
	case FD_CLOSE:
		Close();
		return 0;
	}
	return 0;
}

//W_WORLD_INFO
void MyCenterCom::W_WORLD_INFO(void)
{
	char* tPacket = &mRecvData[0];

	CopyMemory(&mGAME.mWorldInfo, &tPacket[1], SIZE_OF_WORLD_INFO);
	CopyMemory(&mGAME.mTribeInfo, &tPacket[(1 + SIZE_OF_WORLD_INFO)], SIZE_OF_TRIBE_INFO);

	mTRANSFER.B_BROADCAST_WORLD_INFO2(&mGAME.mWorldInfo, &mGAME.mTribeInfo);
	mUTIL.Broadcast(FALSE, nullptr, 0, false, 2);
}

//W_ZONE_CONNECTION_INFO
void MyCenterCom::W_ZONE_CONNECTION_INFO(void)
{
	char* tPacket = &mRecvData[0];

	int tZoneNumber;
	char tIP[16];
	int tPort;
	CopyMemory(&tZoneNumber, &tPacket[1], 4);
	CopyMemory(&tIP[0], &tPacket[5], 16);
	CopyMemory(&tPort, &tPacket[21], 4);

	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
		return;
	}
	strcpy(mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)], tIP);
	mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)] = tPort;
}

//W_BROADCAST_INFO
void MyCenterCom::W_BROADCAST_INFO(void)
{
	char* tPacket = &mRecvData[0];

	int tInfoSort;
	BYTE tInfoData[MAX_BROADCAST_INFO_SIZE];
	CopyMemory(&tInfoSort, &tPacket[1], 4);
	CopyMemory(&tInfoData[0], &tPacket[5], MAX_BROADCAST_INFO_SIZE);

	mGAME.ProcessForBroadcastInfo(tInfoSort, &tInfoData[0]);
}

//W_STRAT
void MyCenterCom::W_START(void)
{
	char* tPacket = &mRecvData[0];
	mGAME.mCheckActiveBattleLogic = TRUE;
}

//W_NOTICE
void MyCenterCom::W_NOTICE(void)
{
	char* tPacket = &mRecvData[0];

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	int tTribe;
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tTribe, &tPacket[(1 + MAX_CHAT_CONTENT_LENGTH)], 4);

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	tSort = 101;
	CopyMemory(&tData[0], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tData[MAX_CHAT_CONTENT_LENGTH], &tTribe, 4);
	mWORK.ProcessForRelay(tSort, &tData[0], 1);
}

//W_SET_EVENT
void MyCenterCom::W_SET_EVENT(void)
{
	char* tPacket = &mRecvData[0];

	int tEventSort;
	int tEventValue;
	CopyMemory(&tEventSort, &tPacket[1], 4);
	CopyMemory(&tEventValue, &tPacket[5], 4);

	switch (tEventSort)
	{
	case 1:
		if ((tEventValue < 10) || (tEventValue > 100))
		{
			return;
		}
		mGAME.mGeneralExperienceUpRatio = static_cast<float>(tEventValue) * 0.1f;
		return;
	case 2:
		if ((tEventValue < 10) || (tEventValue > 100))
		{
			return;
		}
		mGAME.mItemDropUpRatio = static_cast<float>(tEventValue) * 0.1f;
		return;
	case 3:
		/*	if ((tEventValue < 10) || (tEventValue > 100))
			{
				return;
			}
			mGAME.mItemDropUpRatioForMyoung = (float)tEventValue * 0.1f;	*/
		return;
	case 4:
		if ((tEventValue < 0) || (tEventValue > 10))
		{
			return;
		}
		mGAME.mKillOtherTribeAddValue = tEventValue;
		return;
	//(081118 ....) CSTOOL .. .. ..
	case 5: //... ..
		if ((tEventValue < 1) || (tEventValue > 2))
		{
			return;
		}
		mGAME.mTeacherPointUpRatio = tEventValue;
		return;
	case 6: //.. ... ..
		if ((tEventValue < 10) || (tEventValue > 100))
		{
			return;
		}
		mGAME.mPatExperienceUpRatio = static_cast<float>(tEventValue) * 0.1f;
		return;
	case 7: //.. ... ..
		if ((tEventValue < 10) || (tEventValue > 100))
		{
			return;
		}
		mGAME.mBonusGainGeneralExperienceUpRatio = static_cast<float>(tEventValue) * 0.1f;
		return;
	case 8: //.. ... ..
		if ((tEventValue < 0) || (tEventValue > 2))
		{
			return;
		}
		mGAME.mGeneralExperienceDownRatio = tEventValue;
		return;
	case 9:
		if ((tEventValue < 1) || (tEventValue > 3))
		{
			return;
		}
		mGAME.mKillOtherTribeExperienceUpRatio = tEventValue;
		return;
	case 10: //AutoUser ¸ó½ºÅÍ Ä«¿îÅÍ Á¶Á¤
		if ((tEventValue < 1) || (tEventValue > 100000))
		{
			return;
		}
		mGAME.mAutoUserMonsterCount = tEventValue;
	}
}

//W_SHUTDOWN
void MyCenterCom::W_SHUTDOWN(void)
{
	char* tPacket = &mRecvData[0];

	int index01;

	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
	}
	//	::kill(0, SIGKILL);
}

//W_TRIBE_CHAT
void MyCenterCom::W_TRIBE_CHAT(void)
{
	char* tPacket = &mRecvData[0];

	int tZoneNumber;
	int tTribe;
	char tAvatarName01[25];
	char tAvatarName02[25];
	char tContent[101];
	CopyMemory(&tZoneNumber, &tPacket[1], 4);
	CopyMemory(&tTribe, &tPacket[5], 4);
	CopyMemory(&tAvatarName01[0], &tPacket[9], 13);
	CopyMemory(&tAvatarName02[0], &tPacket[22], 13);
	CopyMemory(&tContent[0], &tPacket[35], 51);

	int index01;

	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aTribe != tTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.
			ReturnAllianceTribe(tTribe)))
		{
			continue;
		}
		mTRANSFER.B_TRIBE_CHAT_RECV2(&tAvatarName01[0], &tContent[0]);
		mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C);
	}
}

//W_SECRET_CHAT
void MyCenterCom::W_SECRET_CHAT(void)
{
	char* tPacket = &mRecvData[0];

	int tZoneNumber;
	int tTribe;
	char tAvatarName01[25];
	char tAvatarName02[25];
	char tContent[101];
	CopyMemory(&tZoneNumber, &tPacket[1], 4);
	CopyMemory(&tTribe, &tPacket[5], 4);
	CopyMemory(&tAvatarName01[0], &tPacket[9], 13);
	CopyMemory(&tAvatarName02[0], &tPacket[22], 13);
	CopyMemory(&tContent[0], &tPacket[35], 51);

	int index01;

	mTRANSFER.B_SECRET_CHAT_RECV(3, 0, &tAvatarName01[0], &tContent[0], 1, 1);
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mUSER[index01].mCheckValidState)
		{
			continue;
		}
		if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName02) == 0)
		{
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C);
			return;
		}
	}
}

//W_POLICE_INFO
void MyCenterCom::W_POLICE_INFO(void)
{
	char* tPacket = &mRecvData[0];

	char tID[33];
	int tLoginTime;
	int tLogoutTime;
	CopyMemory(&tID[0], &tPacket[1], 33);
	CopyMemory(&tLoginTime, &tPacket[34], 4);
	CopyMemory(&tLogoutTime, &tPacket[38], 4);

	int index01;

	//-----------//
	//.._...//
	//-----------//
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mUSER[index01].mCheckValidState)
		{
			continue;
		}
		if (strcmp(mUSER[index01].uID, tID) == 0)
		{
			mUSER[index01].uLoginPremium = tLogoutTime;
			mUSER[index01].mAvatarInfo.aPlayTime2 = tLoginTime;
			if (mUSER[index01].mAvatarInfo.aPlayTime2 < 1)
			{
				mUSER[index01].mAvatarInfo.aPlayTime2 = 1;
			}
			if (mUSER[index01].mAvatarInfo.aPlayTime2 > 300)
			{
				mUSER[index01].mAvatarInfo.aPlayTime2 = 300;
			}
			//mUSER[index01].mCheckHealthState = TRUE;
			//mUSER[index01].mHealthState = mUTIL.ReturnHealthState(mUSER[index01].mAvatarInfo.aPlayTime2);
			return;
		}
	}
}

//W_SET_GM_ORDER
void MyCenterCom::W_SET_GM_ORDER(void)
{
	char* tPacket = &mRecvData[0];

	int tEventSort;
	int tMoveZoneNumber;
	char tAvatarName01[13];
	CopyMemory(&tEventSort, &tPacket[1], 4);
	CopyMemory(&tMoveZoneNumber, &tPacket[5], 4);
	CopyMemory(&tAvatarName01, &tPacket[9], 13);

	int tOtherUserIndex;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];

	switch (tEventSort)
	{
	case 0: //[GM]-KICK
		CopyMemory(&tAvatarName[0], &tAvatarName01[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = SearchAvatarforGM(&tAvatarName[0]);
		if (tOtherUserIndex == -1)
		{
			return;
		}
	//mGAMELOG.GL_631_GM_KICK( -1, tOtherUserIndex );
		mUSER[tOtherUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		break;
	case 1: //[GM]-YCHAT
		CopyMemory(&tAvatarName[0], &tAvatarName01[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = SearchAvatarforGM(&tAvatarName[0]);
		if (tOtherUserIndex == -1)
		{
			return;
		}
	//mGAMELOG.GL_630_GM_YCHAT( -1, tOtherUserIndex );
		mUSER[tOtherUserIndex].mAvatarInfo.aSpecialState = 0;
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aSpecialState = 0;
		break;
	case 2: //[GM]-NCHAT
		CopyMemory(&tAvatarName[0], &tAvatarName01[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = SearchAvatarforGM(&tAvatarName[0]);
		if (tOtherUserIndex == -1)
		{
			return;
		}
	//mGAMELOG.GL_629_GM_NCHAT( -1, tOtherUserIndex );
		mUSER[tOtherUserIndex].mAvatarInfo.aSpecialState = 2;
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aSpecialState = 2;
		break;
#if 0
	case 3:			//[GM]-AVATAR MOVEZONE
		CopyMemory(&tAvatarName[0], &tAvatarName01[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = SearchAvatarforGM(&tAvatarName[0]);
		if (tOtherUserIndex == -1)
		{
			return;
		}
		MoveZone(tOtherUserIndex, tMoveZoneNumber);

		break;
#endif
	}
}

void MyCenterCom::W_SET_GM_ORDER_MOVE_AVATAR(void)
{
	int tPosX;
	int tPosY;
	int tPosZ;
	char tAvatarName01[13];
	char* tPacket = &mRecvData[0];
	BYTE tGMData[MAX_TRIBE_WORK_SIZE];
	CopyMemory(&tAvatarName01, &tPacket[1], 13);
	CopyMemory(&tPosX, &tPacket[14], 4);
	CopyMemory(&tPosY, &tPacket[18], 4);
	CopyMemory(&tPosZ, &tPacket[22], 4);

	int tOtherUserIndex;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tAvatarName01[0], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	tOtherUserIndex = SearchAvatarforGM(&tAvatarName[0]);
	if (tOtherUserIndex == -1)
	{
		return;
	}
	//[GM]-AVATAR MOVE
	mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[0] = static_cast<float>(tPosX);
	mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[1] = static_cast<float>(tPosY);
	mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[2] = static_cast<float>(tPosZ);

	CopyMemory(&tGMData[0], &mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[0], 12);
	mTRANSFER.B_GM_COMMAND_INFO2(2, &tGMData[0]);
	mUSER[tOtherUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C);
}

void MyCenterCom::W_SERCH_AVATAR(void)
{
	char* tPacket = &mRecvData[0];

	char tAvatarName01[13];
	int tUserIndex;
	int tGmindex;

	CopyMemory(&tAvatarName01, &tPacket[1], 13);
	CopyMemory(&tUserIndex, &tPacket[14], 4);
	CopyMemory(&tGmindex, &tPacket[18], 4);

	int tOtherUserIndex;

	if (SearchAvatarforGM(tAvatarName01) == -1)
	{
		tOtherUserIndex = 0;
	}
	else
	{
		tOtherUserIndex = 1;
	}

	pthread_mutex_lock(&m_lock);
	mSendData[0] = P_SERCH_AVATAR_SEND;
	CopyMemory(&mSendData[1], &mZoneNumber, 4);
	CopyMemory(&mSendData[5], &tOtherUserIndex, 4);
	CopyMemory(&mSendData[9], &tUserIndex, 4);
	CopyMemory(&mSendData[13], &tGmindex, 4);
	mSendDataSize = S_SERCH_AVATAR_SEND;

	while (TRUE)
	{
		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

void MyCenterCom::W_RANK_TOTAL_SEND(void)
{
	pthread_mutex_lock(&m_lock);
	mSendData[0] = P_GET_TOTAL_RANK_INFO_SEND;
	mSendDataSize = S_GET_TOTAL_RANK_INFO_SEND;

	while (true)
	{
		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

void MyCenterCom::W_RANK_TOTAL_INFO_SEND(int TotalSize)
{
	if (mGAME.mRankInfo)
		free(mGAME.mRankInfo);

	mGAME.mRankInfoSize = TotalSize - 1;
	mGAME.mRankInfo = static_cast<char*>(malloc(TotalSize - 1));
	memcpy(mGAME.mRankInfo, mRecvData + 1, (TotalSize - 1));
}

//W_RANK_INFO_SEND(zone -> end user)
void MyCenterCom::W_RANK_INFO_SEND(void)
{
#if 0
	int tUserIndex = 0;
	mTRANSFER.mOriginal_C[0] = P_ZTOP_RANK_INFO_SEND;
	::memcpy(&tUserIndex, &mRecvData[1 + sizeof(rank_info_t)], 4);

	if (mGAME.mRankInfoSize > 0) {
		::memcpy(&mTRANSFER.mOriginal_C[1], &mRecvData[1], sizeof(rank_info_t));
		::memcpy(&mTRANSFER.mOriginal_C[1 + sizeof(rank_info_t)]
			, mGAME.mRankInfo, mGAME.mRankInfoSize);
		mTRANSFER.mOriginalSize_C = 1 + sizeof(rank_info_t) + mGAME.mRankInfoSize;
	}
	else {
		::memset(&mTRANSFER.mOriginal_C[1], 0, sizeof(rank_info_t));
		::memset(&mTRANSFER.mOriginal_C[1 + sizeof(rank_info_t)], 0, 4);
		::memset(&mTRANSFER.mOriginal_C[1 + sizeof(rank_info_t) + 4], 0, 4);
		::memset(&mTRANSFER.mOriginal_C[1 + sizeof(rank_info_t) + 8], 0, 4);
		mTRANSFER.mOriginalSize_C = 1 + sizeof(rank_info_t) + 12;
	}

	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C);
#endif
}

// # X-Trap # {
// W_XTRAP_MAP_FILE_CHANGE_FOR_ZONE
// ¸Ê ÆÄÀÏÀ» ±³Ã¼ÇÕ´Ï´Ù.
void MyCenterCom::W_XTRAP_MAP_FILE_CHANGE_FOR_ZONE(void)
{
	//	mXTRAP.XTrapMapFileChange();
} // # }

// @ Cost Info Download @
void MyCenterCom::W_UPDATE_CASH_ITEM_INFO_FOR_CENTER(int tResult)
{
	pthread_mutex_lock(&m_lock);
	mSendData[0] = P_UPDATE_CASH_ITEM_INFO_FOR_CENTER;
	CopyMemory(&mSendData[1], &tResult, 4);
	mSendDataSize = S_UPDATE_CASH_ITEM_INFO_FOR_CENTER;

	while (true)
	{
		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

void MyCenterCom::W_UPDATE_CASH_ITEM_INFO_FOR_ZONE()
{
	char* tPacket = &mRecvData[0];

	SetUpdateCashItemInfo(true);
} // @

//PROCESS_FOR_SEND
BOOL MyCenterCom::ProcessForSend(void)
{
	if (!(*mCheckConnectState))
	{
		Close();
		Sleep(1);
		return FALSE;
	}

	if (!Send())
	{
		Close();
		Sleep(1);
		return FALSE;
	}

	return TRUE;
}

//U_ZONE_OK_FOR_CENTER_SEND
void MyCenterCom::U_ZONE_OK_FOR_CENTER_SEND(void)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		mSendData[0] = P_ZONE_OK_FOR_CENTER_SEND;
		mSendDataSize = S_ZONE_OK_FOR_CENTER_SEND;

		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//U_DEMAND_BROADCAST_INFO
void MyCenterCom::U_DEMAND_BROADCAST_INFO(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE])
{
	pthread_mutex_lock(&m_lock);
	mSendData[0] = P_DEMAND_BROADCAST_INFO;
	CopyMemory(&mSendData[1], &tInfoSort, 4);
	CopyMemory(&mSendData[5], &tInfoData[0], MAX_BROADCAST_INFO_SIZE);
	mSendDataSize = S_DEMAND_BROADCAST_INFO;

	while (TRUE)
	{
		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//SEARCH_AVATAR
int MyCenterCom::SearchAvatarforGM(const char* tAvatarName)
{
	int index01;

	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (strcmp(mAVATAR_OBJECT[index01].mDATA.aName, tAvatarName) == 0)
		{
			break;
		}
	}
	if (index01 < mSERVER.mMAX_USER_NUM)
	{
		return index01;
	}
	return -1;
}

void MyCenterCom::W_BAN_PLAYER(void)
{
	GTOZ_BAN_PLAYER pack;
	::CopyMemory(&pack, mRecvData, GTOZ_BAN_PLAYER_SIZE);

	for (int i = 0; i < mSERVER.mMAX_USER_NUM; i++)
	{
		if (mUSER[i].mCheckValidState == TRUE)
		{
			if (strncmp(mUSER[i].uID, pack.m_szID, MAX_USER_ID_LENGTH - 1) == 0)
			{
				mUSER[i].Quit();
				break;
			}
		}
	}
}

//W_CHECK_EVENT
void MyCenterCom::W_CHECK_EVENT(void)
{
	char* tPacket = &mRecvData[0];
	float num;

	int tEventSort;
	int tUserIndex;
	int tGmIndex;
	int tEventValue;
	CopyMemory(&tEventSort, &tPacket[1], 4);
	CopyMemory(&tUserIndex, &tPacket[5], 4);
	CopyMemory(&tGmIndex, &tPacket[9], 4);


	switch (tEventSort)
	{
	case 1:
		num = (mGAME.mGeneralExperienceUpRatio * 10.0f);
		tEventValue = static_cast<int>(num);
		break;
	case 2:
		num = (mGAME.mItemDropUpRatio * 10.0f);
		tEventValue = static_cast<int>(num);
		break;
	case 3:
		/*	num = (mGAME.mItemDropUpRatioForMyoung * 10.0f);
			tEventValue = (int)num;		*/
		break;
	case 4:
		tEventValue = mGAME.mKillOtherTribeAddValue;
		break;
	case 5:
		tEventValue = mGAME.mTeacherPointUpRatio;
		break;
	case 6:
		num = (mGAME.mPatExperienceUpRatio * 10.0f);
		tEventValue = static_cast<int>(num);
		break;
	case 7:
		num = (mGAME.mBonusGainGeneralExperienceUpRatio * 10.0f);
		tEventValue = static_cast<int>(num);
		break;
	case 8:
		tEventValue = mGAME.mGeneralExperienceDownRatio;
		break;
	case 9:
		tEventValue = mGAME.mKillOtherTribeExperienceUpRatio;
		break;
	case 10:
		tEventValue = mGAME.mAutoUserMonsterCount;
		break;
	}

	pthread_mutex_lock(&m_lock);
	mSendData[0] = P_CHECK_EVENT_SEND;
	CopyMemory(&mSendData[1], &tEventSort, 4);
	CopyMemory(&mSendData[5], &tEventValue, 4);
	CopyMemory(&mSendData[9], &tUserIndex, 4);
	CopyMemory(&mSendData[13], &tGmIndex, 4);
	mSendDataSize = S_CHECK_EVENT_SEND;

	while (TRUE)
	{
		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

void MyCenterCom::W_CENTER_GET_RANK_INFO(const char* aName, int tUserIndex)
{
	pthread_mutex_lock(&m_lock);
	mSendData[0] = P_GET_RANK_INFO_SEND;
	memcpy(mSendData + 1, aName, MAX_AVATAR_NAME_LENGTH);
	memcpy(mSendData + 14, &tUserIndex, 4);
	mSendDataSize = S_GET_RANK_INFO_SEND;

	while (TRUE)
	{
		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

void MyCenterCom::W_ZONE_OTHER_CONNECTION_INFO(int tZoneNumber)
{
	pthread_mutex_lock(&m_lock);
	mSendData[0] = P_ZONE_CONNECTION_INFO_SEND;
	mSendDataSize = S_ZONE_CONNECTION_INFO_SEND;
	memcpy(mSendData + 1, &tZoneNumber, 4);

	while (true)
	{
		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

// @ Cost Info Download @
bool MyCenterCom::IsUpdateCashItemInfo()
{
	bool isUpdate = false;

	pthread_mutex_lock(&m_lock);
	if (mIsUpdateCashItemInfo)
	{
		isUpdate = true;
	}
	pthread_mutex_unlock(&m_lock);

	return isUpdate;
}

void MyCenterCom::SetUpdateCashItemInfo(bool isUpdate)
{
	pthread_mutex_lock(&m_lock);
	mIsUpdateCashItemInfo = isUpdate;
	pthread_mutex_unlock(&m_lock);
} // @
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_EXTRA_COM
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyExtraCom mEXTRA_COM;
//CREATE
MyExtraCom::MyExtraCom(void)
{
	// @ Cost Info Download @
	mIsValidCashItemInfo = false;
	mCashItemInfoVersion = 0;
	// @
}

//CONNECT
BOOL MyExtraCom::Connect(void)
{
	if (mCheckConnectState)
	{
		return TRUE;
	}

	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tOKRecvCheck;
	char tOKDataCheck;

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket < 0) //== INVALID_SOCKET )
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(mIP);
	mAddress.sin_port = htons(mPort);
	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) //== SOCKET_ERROR )
	{
		closesocket(mSocket);
		Sleep(1);
		return FALSE;
	}

	tConnectRecvCheck = recv(mSocket, &tConnectDataCheck, 1, 0);
	if (tConnectRecvCheck != 1)
	{
		closesocket(mSocket);
		return FALSE;
	}
	tSendData[0] = P_ZONE_FOR_EXTRA_SEND;
	CopyMemory(&tSendData[1], &mZoneNumber, 4);
	tSendDataSize = S_ZONE_FOR_EXTRA_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &tSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 < 0) //== SOCKET_ERROR )
		{
			if (errno == EINTR)
				continue;
			closesocket(mSocket);
			return FALSE;
		}
		if (tSendValue03 == 0)
		{
			closesocket(mSocket);
			return FALSE;
		}

		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	int tRecvValue01 = 0;
	int tRecvValue02 = 0;
	char tRecvData[S_ZONE_FOR_EXTRA_RECV] = {0};
	constexpr int RECV_DATA_SIZE = S_ZONE_FOR_EXTRA_RECV;
	while (TRUE)
	{
		tRecvValue02 = recv(mSocket, &tRecvData[tRecvValue01], RECV_DATA_SIZE - tRecvValue01, 0);
		if (tRecvValue02 < 0)
		{
			if (errno == EINTR)
				continue;
			closesocket(mSocket);
			return FALSE;
		}
		if (tRecvValue02 == 0)
		{
			closesocket(mSocket);
			return FALSE;
		}
		tRecvValue01 += tRecvValue02;
		if (tRecvValue01 == RECV_DATA_SIZE)
		{
			break;
		}
	}
	CopyMemory(&mCashItemInfoVersion, &tRecvData[1], 4);
	CopyMemory(mCashItemInfo, &tRecvData[5], 8960);
	mIsValidCashItemInfo = true;
	// @

	mCheckConnectState = TRUE;

	return TRUE;
}

//SEND
BOOL MyExtraCom::Send(void)
{
	int nResult = 0;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &mSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 < 0) //== SOCKET_ERROR )
		{
			if (errno == EINTR)
				continue;
			Close();
			return FALSE;
		}
		if (tSendValue03 == 0)
		{
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	return TRUE;
}

//RECV
BOOL MyExtraCom::Recv(void)
{
	int nCount = 0;
	int nResult = 0;
	int tRecvValue01;
	int tRecvValue02;

	if (mRecvDataSize > 0)
	{
		tRecvValue01 = 0;
		while (TRUE)
		{
			tRecvValue02 = recv(mSocket, &mRecvData[tRecvValue01], mRecvDataSize - tRecvValue01, 0);
			if (tRecvValue02 < 0)
			{
				if (errno == EINTR)
					continue;
				Close();
				return FALSE;
			}
			if (tRecvValue02 == 0)
			{
				Close();
				return FALSE;
			}
			tRecvValue01 += tRecvValue02;
			if (tRecvValue01 == mRecvDataSize)
			{
				break;
			}
		}
	}

	return TRUE;
}

//CLOSE
void MyExtraCom::Close(void)
{
	if (!mCheckConnectState)
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket(mSocket);
}

//INIT
BOOL MyExtraCom::Init(int tZoneNumber, char tIP[16], int tPort)
{
	mCheckConnectState = FALSE;
	if (tZoneNumber < 1)
	{
		return FALSE;
	}
	mZoneNumber = tZoneNumber;
	strcpy(mIP, tIP);
	mPort = tPort;

	if (!Connect())
	{
		return FALSE;
	}

	return TRUE;
}

//FREE
void MyExtraCom::Free(void)
{
	Close();
}

//PROCESS_FOR_NETWORK
BOOL MyExtraCom::ProcessForNetwork(void)
{
	if (!Connect())
	{
		return FALSE;
	}
	if (!Send())
	{
		return FALSE;
	}
	if (!Recv())
	{
		return FALSE;
	}

	return TRUE;
}

//U_ZONE_OK_FOR_EXTRA_SEND
BOOL MyExtraCom::U_ZONE_OK_FOR_EXTRA_SEND(void)
{
	mSendData[0] = P_ZONE_OK_FOR_EXTRA_SEND;
	mSendDataSize = S_ZONE_OK_FOR_EXTRA_SEND;
	mRecvDataSize = 0;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	return TRUE;
}

//U_GUILD_WORK_FOR_EXTRA_SEND
BOOL MyExtraCom::U_GUILD_WORK_FOR_EXTRA_SEND(int tSort, BYTE tData[MAX_GUILD_WORK_SIZE])
{
	mSendData[0] = P_GUILD_WORK_FOR_EXTRA_SEND;
	CopyMemory(&mSendData[1], &tSort, 4);
	CopyMemory(&mSendData[5], &tData[0], MAX_GUILD_WORK_SIZE);
	mSendDataSize = S_GUILD_WORK_FOR_EXTRA_SEND;
	mRecvDataSize = S_GUILD_WORK_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_GuildInfo, &mRecvData[5], sizeof(GUILD_INFO));
	return TRUE;
}

//U_GET_CASH_SIZE_FOR_EXTRA_SEND
BOOL MyExtraCom::U_GET_CASH_SIZE_FOR_EXTRA_SEND(char tID[MAX_USER_ID_LENGTH])
{
	mSendData[0] = P_GET_CASH_SIZE_FOR_EXTRA_SEND;
	CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
	mSendDataSize = S_GET_CASH_SIZE_FOR_EXTRA_SEND;
	mRecvDataSize = S_GET_CASH_SIZE_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	CopyMemory(&mRecv_CashSize, &mRecvData[1], 4);
	CopyMemory(&mRecv_BonusCashSize, &mRecvData[5], 4);
	return TRUE;
}

// @ Cost Info Download @
// tVersion Ãß°¡.
//U_BUY_CASH_ITEM_FOR_EXTRA_SEND
//BOOL MyExtraCom::U_BUY_CASH_ITEM_FOR_EXTRA_SEND( char tID[MAX_USER_ID_LENGTH], int tCostInfoIndex, int iIndex, int iQuantity, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe, int tLevel )
// @
BOOL MyExtraCom::U_BUY_CASH_ITEM_FOR_EXTRA_SEND(char tID[MAX_USER_ID_LENGTH], int tCostInfoIndex, int iIndex,
                                                int iQuantity, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe,
                                                int tLevel, int tVersion)
{
	int svr_num = 1;
	//g_env.svr_num
	mSendData[0] = P_BUY_CASH_ITEM_FOR_EXTRA_SEND;
	CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
	CopyMemory(&mSendData[(1 + MAX_USER_ID_LENGTH)], &tCostInfoIndex, 4);
	CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], &iIndex, 4);
	CopyMemory(&mSendData[(9 + MAX_USER_ID_LENGTH)], &iQuantity, 4);
	CopyMemory(&mSendData[(13 + MAX_USER_ID_LENGTH)], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mSendData[(13 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tTribe, 4);
	CopyMemory(&mSendData[(17 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tLevel, 4);
	CopyMemory(&mSendData[(17 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH + 4)], &svr_num, 4);

	// @ Cost Info Download @
	CopyMemory(&mSendData[(17 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH + 4 + 4)], &tVersion, 4);
	// @
	mSendDataSize = S_BUY_CASH_ITEM_FOR_EXTRA_SEND;
	mRecvDataSize = S_BUY_CASH_ITEM_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_CashSize, &mRecvData[5], 4);
	CopyMemory(&mRecv_BonusCashSize, &mRecvData[9], 4);
	CopyMemory(&mRecv_CostSize, &mRecvData[13], 4);
	CopyMemory(&mRecv_BonusCostSize, &mRecvData[17], 4);
	return TRUE;
}

// @ Cost Info Download @
BOOL MyExtraCom::U_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND()
{
	mSendData[0] = P_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	mSendDataSize = S_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	mRecvDataSize = S_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}

	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	if (mRecv_Result == 0) // ¾÷µ¥ÀÌÆ® ÇÊ¿ä.
	{
		mIsValidCashItemInfo = false;
		return TRUE;
	}
	if (mRecv_Result == 1) // ¾÷µ¥ÀÌÆ® ºÒÇÊ¿ä.
	{
		return FALSE;
	}
	// ¾÷µ¥ÀÌÆ®¸¦ ÇØ¾ß ÇÏ³ª COST_INFO ÀÇ ¹öÀüÀÌ Æ²¸°(ÇöÀç ¹öÀü + 1ÀÌ ¾Æ´Ñ) °æ¿ì.
	mIsValidCashItemInfo = false;
	return FALSE;
}

BOOL MyExtraCom::U_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND()
{
	mSendData[0] = P_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	CopyMemory(&mSendData[1], &mSERVER_INFO.mServerNumber, 4);
	mSendDataSize = S_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	mRecvDataSize = S_GET_CASH_ITEM_INFO_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	if (mRecv_Result == 0)
	{
		CopyMemory(&mCashItemInfoVersion, &mRecvData[5], 4);
		CopyMemory(mCashItemInfo, &mRecvData[9], 8960);
		mIsValidCashItemInfo = true;
		return TRUE;
	}
	return FALSE;
} // @

// 2009.12.16 ÅÍÅ°¿¡¼­¸¸ »ç¿ëÇÕ´Ï´Ù.
// ÆÐÅ°Áö ¾ÆÀÌÅÛ(1418 ~ 1423) »ç¿ë ½Ã º¸³Ê½º Ä³½¬ Áö±Þ ¿äÃ» ÇÔ¼ö.
BOOL MyExtraCom::U_USE_PACKAGE_ITEM_FOR_EXTRA_SEND(char tID[MAX_USER_ID_LENGTH], int iIndex,
                                                   char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	mSendData[0] = P_USE_PACKAGE_ITEM_FOR_EXTRA_SEND;
	CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
	CopyMemory(&mSendData[(1 + MAX_USER_ID_LENGTH)], &iIndex, 4);
	CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], &mSERVER_INFO.mServerNumber, 4);

	mSendDataSize = S_USE_PACKAGE_ITEM_FOR_EXTRA_SEND;
	mRecvDataSize = S_USE_PACKAGE_ITEM_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);

	return TRUE;
}

//-------------------------------------------------------------------------------------------------

//INSTANCE
MyRelayCom mRELAY_COM;
//CREATE
MyRelayCom::MyRelayCom(void)
{
}

//CONNECT
BOOL MyRelayCom::Connect(void)
{
	if (*mCheckConnectState)
	{
		return TRUE;
	}

	int n_read = 0;
	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tRecvDataSize;
	int tRecvValue01;
	int tRecvValue02;

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket < 0) // INVALID_SOCKET )
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(mIP);
	mAddress.sin_port = htons(mPort);

	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) //== SOCKET_ERROR )
	{
		Close();
		return FALSE;
	}

	tConnectRecvCheck = recv(mSocket, &tConnectDataCheck, 1, 0);
	if (tConnectRecvCheck != 1)
	{
		Close();
		return FALSE;
	}

	mRecvDataSize = 0;
	memset(mRecvData, 0, MAX_RECV_DATA_SIZE);

	tSendData[0] = P_ZONE_FOR_RELAY_SEND;
	CopyMemory(&tSendData[1], &mZoneNumber, 4);
	tSendDataSize = S_ZONE_FOR_RELAY_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &tSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 < 0) //== SOCKET_ERROR )
		{
			if (errno == EINTR)
				continue;
			Close();
			return FALSE;
		}
		if (tSendValue03 == 0)
		{
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	tRecvDataSize = S_ZONE_FOR_RELAY_RECV;
	tRecvValue01 = 0;
	while (TRUE)
	{
		tRecvValue02 = recv(mSocket, &mRecvData[tRecvValue01], tRecvDataSize, 0);
		if (tRecvValue02 < 0)
		{
			if (errno == EINTR)
				continue;
			Close();
			return FALSE;
		}
		if (tRecvValue02 == 0)
		{
			Close();
			return FALSE;
		}
		tRecvValue01 += tRecvValue02;
		if (tRecvValue01 >= tRecvDataSize)
		{
			break;
		}
	}
	memmove(mRecvData, mRecvData + tRecvDataSize, (tRecvValue01 - tRecvDataSize));
	mRecvDataSize = tRecvValue01 - tRecvDataSize;
	*mCheckConnectState = TRUE;

	fd_set read_fds;

	while (true)
	{
		struct timeval tv = {5, 0};
		FD_ZERO(&read_fds);
		FD_SET(mSocket, &read_fds);

		if (!(*mCheckConnectState))
		{
			//LOG_TO_FILE_1("Relay connect closed(%d)\n", *mCheckConnectState);
			Close();
			return FALSE;
		}
		//LOG_TO_FILE_2("!CHECK relay  select : %d %d\n", mSocket, mCheckConnectState);
		//if(select(mSocket + 1, &read_fds, NULL, NULL, &tv) < 0) {
		*mCheckSocketState = 1;
		if (select(mSocket + 1, &read_fds, nullptr, nullptr, nullptr) < 0)
		{
			if (errno == EINTR)
			{
				continue;
			}
			//LOG_TO_FILE_4("![%s] : %s(%d)-%d(!!!!)\n", __FUNCTION__, strerror(errno), errno, mSocket);
			FD_CLR(mSocket, &read_fds);
			Close();
			*mCheckSocketState = 0;
			return FALSE;
		}

		if (FD_ISSET(mSocket, &read_fds))
		{
			*mCheckSocketState = 0;
			n_read = WindowProc(nullptr, WM_NETWORK_MESSAGE_3, reinterpret_cast<WPARAM>(&mSocket), FD_READ);
			if (n_read == 0)
			{
				FD_CLR(mSocket, &read_fds);
				Close();
				return FALSE;
			}
			*mCheckSocketState = 1;
			*mCheckConnectState = TRUE;
		}
	}
	return TRUE;
}

//SEND
BOOL MyRelayCom::Send(void)
{
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &mSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 < 0) //== SOCKET_ERROR )
		{
			if (errno == EINTR)
				continue;
			Close();
			return FALSE;
		}
		if (tSendValue03 == 0)
		{
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	return TRUE;
}

//CLOSE
void MyRelayCom::Close(void)
{
	if (!(*mCheckConnectState))
	{
		return;
	}
	*mCheckConnectState = FALSE;
	closesocket(mSocket);
}

void* MyRelayCom::Start(void* arg)
{
	auto mThd = reinterpret_cast<MyRelayCom*>(arg);

	while (true)
	{
		if (!(*mThd->mCheckConnectState))
		{
			if (!mThd->Connect())
			{
				//LOG_TO_FILE_2("![%s] : %s\n", __FUNCTION__, "Relay server connect failed");
				//LOG_TO_FILE_2("![%s] : Relay Server died(%d)\n", __FUNCTION__, __LINE__);
				Sleep(500000);
			}
		}
	}
}

void MyRelayCom::connect_thread(void)
{
	if (!(*mCheckConnectState))
	{
		if (pthread_create(&m_handle, nullptr, Start, this) != 0)
		{
			//LOG_TO_FILE_2("![%s] : %s\n", __FUNCTION__, strerror(errno));
			return;
		}
		pthread_detach(m_handle);
	}

	// 	if(!(*mCheckConnectState)) 
	// 	{
	// 		if(pthread_create(&m_handle, 0, MyRelayCom::Start, this) != 0) {
	// 			//LOG_TO_FILE_2("![%s] : %s\n", __FUNCTION__, strerror(errno));
	// 			return;
	// 		}
	// 		pthread_detach(m_handle);
	// 	}
}

//INIT
BOOL MyRelayCom::Init(int tZoneNumber, char tIP[16], int tPort)
{
	mCheckSocketState = static_cast<BOOL*>(malloc(sizeof(bool)));
	mCheckConnectState = static_cast<BOOL*>(malloc(sizeof(bool)));
	*mCheckConnectState = FALSE;
	if (tZoneNumber < 1)
	{
		free(mCheckSocketState);
		free(mCheckConnectState);
		return FALSE;
	}
	mZoneNumber = tZoneNumber;
	strcpy(mIP, tIP);
	mPort = tPort;
	*mCheckSocketState = 0;
	pthread_mutex_init(&m_lock, nullptr); //³õÊ¼»¯
	connect_thread();

	return TRUE;
}

//FREE
void MyRelayCom::Free(void)
{
	Close();
	pthread_mutex_destroy(&m_lock);
}

//PROCESS_FOR_NETWORK
int MyRelayCom::PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
{
	int tRecvSize;
	BYTE tProtocol;
	int tTotalPacketSize;

	switch (WSAGETSELECTEVENT(lPrm)) // WSAGETSELECTEVENT( lPrm ) )
	{
	case FD_READ:
	AGAIN:
		tRecvSize = recv(mSocket, &mRecvData[mRecvDataSize], (MAX_RECV_DATA_SIZE - mRecvDataSize), 0);
		if (tRecvSize < 0)
		{
			if (errno == EINTR)
				goto AGAIN;
			Close();
			return 0;
		}
		if (tRecvSize == 0)
		{
			Close();
			return 0;
		}

		mRecvDataSize += tRecvSize;
		while (TRUE)
		{
			if (mRecvDataSize < 1)
			{
				return tRecvSize;
			}
			tProtocol = static_cast<BYTE>(mRecvData[0]);
			switch (tProtocol)
			{
			case P_BROADCAST_DATA:
				tTotalPacketSize = S_BROADCAST_DATA;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_BROADCAST_DATA();
				break;
			default:
				Close();
				return 0;
			}
			if (*mCheckConnectState)
			{
				memmove(mRecvData, mRecvData + tTotalPacketSize, (mRecvDataSize - tTotalPacketSize));
				mRecvDataSize -= tTotalPacketSize;
			}
		}
		return tRecvSize;
	case FD_CLOSE:
		Close();
		return 0;
	}
	return 0;
}

//W_BROADCAST_DATA
void MyRelayCom::W_BROADCAST_DATA(void)
{
	char* tPacket = &mRecvData[0];

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tData[0], &tPacket[5], MAX_BROADCAST_DATA_SIZE);

	mWORK.ProcessForRelay(tSort, &tData[0], 2);
}

//PROCESS_FOR_SEND
BOOL MyRelayCom::ProcessForSend(void)
{
	if (!(*mCheckConnectState))
	{
		Close();
		Sleep(1);
		return FALSE;
	}

	if (!Send())
	{
		Close();
		Sleep(1);
		return FALSE;
	}

	return TRUE;
}

//U_ZONE_OK_FOR_RELAY_SEND
void MyRelayCom::U_ZONE_OK_FOR_RELAY_SEND(void)
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		mSendData[0] = P_ZONE_OK_FOR_RELAY_SEND;
		mSendDataSize = S_ZONE_OK_FOR_RELAY_SEND;

		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//U_DEMAND_BROADCAST_DATA
void MyRelayCom::U_DEMAND_BROADCAST_DATA(int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE])
{
	pthread_mutex_lock(&m_lock);
	while (TRUE)
	{
		mSendData[0] = P_DEMAND_BROADCAST_DATA;
		CopyMemory(&mSendData[1], &tSort, 4);
		CopyMemory(&mSendData[5], &tData[0], MAX_BROADCAST_DATA_SIZE);
		mSendDataSize = S_DEMAND_BROADCAST_DATA;

		if (ProcessForSend())
		{
			break;
		}
	}
	pthread_mutex_unlock(&m_lock);
}

//-------------------------------------------------------------------------------------------------
