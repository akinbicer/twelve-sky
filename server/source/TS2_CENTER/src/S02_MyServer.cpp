//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "H01_MainApplication.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_SERVER
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyServer mSERVER;
//CREATE
MyServer::MyServer( void )
{
}
//INIT
BOOL MyServer::Init( int *tResult )
{
	int index01;

	srand( (unsigned int) time( NULL ) );
#ifdef __WIN32__ 
	if( !SetTimer( hMainWindow, 1, 10000, NULL ) )
	{
		*tResult = 1;
		return FALSE;
	}
#endif
	if( !mDB.Init() )
	{
		*tResult = 2;
		return FALSE;
	}
#ifdef __WIN32__
	ZeroMemory( &mWsaData, sizeof( WSADATA ) );
	if( WSAStartup( MAKEWORD( 2, 2 ), &mWsaData ) != 0 )
	{
		*tResult = 3;
		return FALSE;
	}
	mSocket = socket( AF_INET, SOCK_STREAM, 0 );
	if( mSocket == INVALID_SOCKET )
	{
		*tResult = 4;
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = htonl( INADDR_ANY );
	mAddress.sin_port = htons( mSERVER_INFO.mServerPort );
	if( bind( mSocket, (LPSOCKADDR) &mAddress, sizeof( mAddress ) ) == SOCKET_ERROR )
	{
		*tResult = 5;
		return FALSE;
	}
	if( listen( mSocket, SOMAXCONN ) == SOCKET_ERROR )
	{
		*tResult = 6;
		return FALSE;
	}
	if( WSAAsyncSelect( mSocket, hMainWindow, WM_NETWORK_MESSAGE_1, FD_ACCEPT ) == SOCKET_ERROR )
	{
		*tResult = 7;
		return FALSE;
	}
#endif
	LOG_TO_FILE_1("![%s] : Main server start\n", __FUNCTION__);
	if( !mGAMELOG.Init( mSERVER_INFO.mUpperServer_1_IP, mSERVER_INFO.mUpperServer_1_Port ) )
	{
		*tResult = 8;
		return FALSE;
	}
	LOG_TO_FILE_1("! : Center Max User = %d \n", MAX_USER_NUM);
	LOG_TO_FILE_1("![%s] : Gamelog server start\n", __FUNCTION__);
#ifdef __WIN32__
	mUSER = (MyUser *) GlobalAlloc( GMEM_FIXED, ( MAX_USER_NUM * sizeof( MyUser ) ) );
#else
	mUSER = (MyUser *) calloc (1, (MAX_USER_NUM * sizeof (MyUser)));
#endif
	if( mUSER == NULL )
	{
		*tResult = 9;
		return FALSE;
	}
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		mUSER[index01].mBUFFER_FOR_SEND = NULL;
		mUSER[index01].mBUFFER_FOR_RECV = NULL;
	}	
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( !mUSER[index01].Init( MAX_SEND_BUFFER_SIZE, MAX_RECV_BUFFER_SIZE ) )
		{
			*tResult = 10;
			return FALSE;
		}
	}
	if( !mWORK.Init() )
	{
		*tResult = 11;
		return FALSE;
	}
	LOG_TO_FILE_1("![%s] : Work start\n", __FUNCTION__);
	if( !mTRANSFER.Init() )
	{
		*tResult = 12;
		return FALSE;
	}
	LOG_TO_FILE_1("![%s] : Transfer start\n", __FUNCTION__);
	if( !mGAME.Init() )
	{
		*tResult = 13;
		return FALSE;
	}
	LOG_TO_FILE_1("![%s] : Rank Info Get start\n", __FUNCTION__);
	if(!mDB.DB_PROCESS_12(1)) {
		*tResult = 14;
		return FALSE;
	}
	LOG_TO_FILE_1("![%s] : Game start\n", __FUNCTION__);
	return TRUE;
}
//FREE
void MyServer::Free( void )
{
	int index01;

	mGAME.Free();
	mTRANSFER.Free();
	mWORK.Free();
	if( mUSER )
	{
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			mUSER[index01].Quit( 0 );
		}
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			mUSER[index01].Free();
		}
#ifdef __WIN32__
		GlobalFree( mUSER );
#else
		free (mUSER);
#endif
		mUSER = NULL;
	}
	mGAMELOG.Free();
	closesocket( mSocket );
	//WSACleanup();
	mDB.Free();
	//KillTimer( hMainWindow, 1 );
}
//PROCESS_FOR_NETWORK
int MyServer::PROCESS_FOR_NETWORK(SOCKET *cli_fd, UINT fd_status, void *arg = NULL)
{
	int index01;
	int tAddressLength;
	SOCKET tSocket;
	SOCKADDR_IN	tAddress;
	int tempUserIndex;
	int tRecvSizeFromUser;
	BYTE tProtocol;

	tSocket = *cli_fd;
	switch( fd_status )
	{
		case FD_READ :
			for( tempUserIndex = 0 ; tempUserIndex < MAX_USER_NUM ; tempUserIndex++ )
			{
				if( !mUSER[tempUserIndex].mCheckConnectState )
				{
					continue;
				}
				if( mUSER[tempUserIndex].mSocket == tSocket )
				{
					break;
				}
			}
			if( tempUserIndex == MAX_USER_NUM )
			{
				// 2009.10.26 : 김성수
				// 제거 내용 :mUSER[tempUserIndex].Quit (10001);
				return -1;
			}

			//AGAIN:
			while(1) {
			        tRecvSizeFromUser = recv (tSocket, &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mUSER[tempUserIndex].mTotalRecvSize], ( MAX_RECV_BUFFER_SIZE - mUSER[tempUserIndex].mTotalRecvSize), 0);
			        //LOG_TO_FILE_2 ("![%d] read size : %d\n", tSocket, tRecvSizeFromUser);
			        if (tRecvSizeFromUser < 0)
			        {
				        if(errno == EINTR)
						continue;
						//goto AGAIN;
				        if (errno != EAGAIN && errno != EWOULDBLOCK)
				        {
					        //LOG_TO_FILE_1 ("!recv size is -1, error[%s]\n", strerror (errno));
						mUSER[tempUserIndex].Quit (10002);
					        return 0;
				        }
				        return -1;
			        } else if (0 == tRecvSizeFromUser) {
				        //LOG_TO_FILE_3 ("!Error - [%d], Zone[%d], Recv errno[%s]\n", tSocket, mUSER[tempUserIndex].mZoneServerNumber, strerror (errno));
				        mUSER[tempUserIndex].Quit (1001);
				        return 0;
			        }
			        mUSER[tempUserIndex].mTotalRecvSize += tRecvSizeFromUser;
				        break;
			}

			while (TRUE)
			{
				if (mUSER[tempUserIndex].mTotalRecvSize < 1)
				{
					mUSER[tempUserIndex].Quit (10003);
					return 0;
				}
				tProtocol = (BYTE) mUSER[tempUserIndex].mBUFFER_FOR_RECV[0];
				//LOG_TO_FILE_1("=============> tProtocol : %d\n", tProtocol);
				if( W_FUNCTION[tProtocol].PROC == NULL )
				{
					//LOG_TO_FILE_2 ("!Zone[%d], not permit protocol[%d]\n", mUSER[tempUserIndex].mZoneServerNumber, (int) tProtocol);
					mUSER[tempUserIndex].Quit( 1002 );
					return 0;
				}
					//LOG_TO_FILE_4 ("![%d], Zone[%d], totalrecv[%d], packetsize[%d]\n", tSocket, mUSER[tempUserIndex].mCheckConnectState, mUSER[tempUserIndex].mTotalRecvSize, mWORK.mWorkerPacketSize[tProtocol]); 
				if( mUSER[tempUserIndex].mTotalRecvSize < mWORK.mWorkerPacketSize[tProtocol] )
				{
					return -1;
					//goto AGAIN;
					//continue;
				}
				W_FUNCTION[tProtocol].PROC( tempUserIndex );
					//LOG_TO_FILE_4 ("![%d], Zone[%d], totalrecv[%d], packetsize[%d]\n", tSocket, mUSER[tempUserIndex].mCheckConnectState, mUSER[tempUserIndex].mTotalRecvSize, mWORK.mWorkerPacketSize[tProtocol]); 
				if( mUSER[tempUserIndex].mCheckConnectState )
				{
					MoveMemory( &mUSER[tempUserIndex].mBUFFER_FOR_RECV[0], &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mWORK.mWorkerPacketSize[tProtocol]], ( mUSER[tempUserIndex].mTotalRecvSize - mWORK.mWorkerPacketSize[tProtocol] ) );
					mUSER[tempUserIndex].mTotalRecvSize -= mWORK.mWorkerPacketSize[tProtocol];
				}
				if (0 == mUSER[tempUserIndex].mTotalRecvSize)
				{
					break;
				}
			}
			return tRecvSizeFromUser;
		case FD_WRITE :
			for( tempUserIndex = 0 ; tempUserIndex < MAX_USER_NUM ; tempUserIndex++ )
			{
				if( !mUSER[tempUserIndex].mCheckConnectState )
				{
					continue;
				}
				if( mUSER[tempUserIndex].mSocket == tSocket )
				{
					break;
				}
			}
			if( tempUserIndex == MAX_USER_NUM )
			{
				return -1;
			}
			mUSER[tempUserIndex].Send( FALSE, NULL, 0 );
			return 0;
		case FD_ACCEPT :
#ifdef __WIN32__
			tAddressLength = sizeof( tAddress );
			tSocket = accept( mSocket, (LPSOCKADDR) &tAddress, &tAddressLength );
			if( tSocket == INVALID_SOCKET )
			{
				return;
			}
#endif
			for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
			{
				if( !mUSER[index01].mCheckConnectState )
				{
					break;
				}
			}
			if( index01 == MAX_USER_NUM )
			{
				//LOG_TO_FILE ("!Current user counts is max\n");
				closesocket( tSocket );
				return 0;
			}
#ifdef __WIN32__
			if( WSAAsyncSelect( tSocket, hWnd, WM_NETWORK_MESSAGE_1, ( FD_READ | FD_WRITE | FD_CLOSE ) ) == SOCKET_ERROR )
			{
				closesocket( tSocket );
				return;
			}
#endif
			mUSER[index01].mCheckConnectState = TRUE;
			mUSER[index01].mUsedTime = GetTickCount();
			mUSER[index01].mSocket = tSocket;
#if 0
			sprintf( mUSER[index01].mIP, "%d.%d.%d.%d", tAddress.sin_addr.S_un.S_un_b.s_b1, tAddress.sin_addr.S_un.S_un_b.s_b2, tAddress.sin_addr.S_un.S_un_b.s_b3, tAddress.sin_addr.S_un.S_un_b.s_b4 );
#endif
			mUSER[index01].mEPFD = *(((arg_t *)arg)->epfd);
			sprintf (mUSER[index01].mIP, "%s", inet_ntoa(((struct in_addr)((arg_t *)arg)->cli_addr->sin_addr))); 
			mUSER[index01].mTotalSendSize = 0;
			mUSER[index01].mTotalRecvSize = 0;
			mUSER[index01].mCheckServerType = 0;
			mTRANSFER.B_CONNECT_OK();
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return 1;
		case FD_CLOSE :
			for( tempUserIndex = 0 ; tempUserIndex < MAX_USER_NUM ; tempUserIndex++ )
			{
				if( !mUSER[tempUserIndex].mCheckConnectState )
				{
					continue;
				}
				if( mUSER[tempUserIndex].mSocket == tSocket )
				{
					break;
				}
			}
			if( tempUserIndex == MAX_USER_NUM )
			{
				return 0;
			}
			//LOG_TO_FILE_3 ("![%d], Zone[%d], Type[%d], FD_CLOSE\n", tSocket, mUSER[tempUserIndex].mZoneServerNumber, mUSER[tempUserIndex].mCheckServerType);
			mUSER[tempUserIndex].Quit( 0 );
			return 0;
	}
}
//PROCESS_FOR_TIMER
void MyServer::PROCESS_FOR_TIMER( void )
{
	int index01;
	DWORD tPresentTime;

	tPresentTime = GetTickCount();
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( !mUSER[index01].mCheckConnectState )
		{
			continue;
		}
		//LOG_TO_FILE_3 ("!********************* %d %d %d\n", index01, tPresentTime, mUSER[index01].mUsedTime);
		//if( ( tPresentTime - mUSER[index01].mUsedTime ) > 300000 )
		if( ( tPresentTime - mUSER[index01].mUsedTime ) > 1800000 )
		{
			//LOG_TO_FILE_3 ("![%d], Zone[%d], long time no action (%d)\n", mUSER[index01].mSocket, mUSER[index01].mZoneServerNumber, (tPresentTime - mUSER[index01].mUsedTime));
			//LOG_TO_FILE_3("![%s] : %u %u\n", __FUNCTION__, tPresentTime, mUSER[index01].mUsedTime);
			mUSER[index01].Quit( 1003 );
		}
	}
	mGAME.mTickCount++;
	if( ( mGAME.mTickCount % 180 ) == 0 )
	{
		mDB.DB_PROCESS_02( &mGAME.mWorldInfo );
		mTRANSFER.B_WORLD_INFO( &mGAME.mWorldInfo, &mGAME.mTribeInfo );
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			if( mUSER[index01].mCheckServerType == 2 )
			{
				mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			}
		}
	}
}
#ifdef __WIN32__
//WRITE_FOR_ERROR
void MyServer::WRITE_FOR_ERROR( char *tErrorData )
{
	char tempString01[10000];
	char tempString02[10000];
	time_t tCountSeconds;
	struct tm *tPresentTime;
	HANDLE hFile;
	DWORD nWriteByte;

	time( &tCountSeconds );
	tPresentTime = localtime( &tCountSeconds );
	if( tPresentTime == NULL )
	{
		return;
	}
	strcpy( tempString01, "LOG\\ERROR_" );
	itoa( ( tPresentTime->tm_year + 1900 ), tempString02, 10 );
	strcat( tempString01, tempString02 );
	strcat( tempString01, "-" );
	if( tPresentTime->tm_mon < 9 )
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mon + 1 + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa( ( tPresentTime->tm_mon + 1 ), tempString02, 10 );
	}
	strcat( tempString01, tempString02 );
	strcat( tempString01, "-" );
	if( tPresentTime->tm_mday < 10 )
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mday + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa( tPresentTime->tm_mday, tempString02, 10 );
	}
	strcat( tempString01, tempString02 );
	strcat( tempString01, ".TXT" );
	sprintf( tempString02, "[%d:%d:%d] %s\r\n", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tErrorData );
	hFile = CreateFile(	tempString01, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return;
	}
	if( SetFilePointer( hFile, 0, 0, FILE_END ) == 0xFFFFFFFF )
	{
		CloseHandle( hFile );
		return;
	}
	if( !WriteFile( hFile, tempString02, strlen( tempString02 ), &nWriteByte, NULL ) )
	{
		CloseHandle( hFile );
		return;
	}
	if( nWriteByte != strlen( tempString02 ) )
	{
		CloseHandle( hFile );
		return;
	}
	if( !CloseHandle( hFile ) )
	{
		return;
	}
}
#endif
//-------------------------------------------------------------------------------------------------
