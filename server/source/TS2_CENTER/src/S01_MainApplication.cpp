//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "H01_MainApplication.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CALLBACK_FUNCTION
//-------------------------------------------------------------------------------------------------
//LRESULT CALLBACK WinMainProcedure( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm );
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//APPLICATION_FUNCTION
//-------------------------------------------------------------------------------------------------
#if 0
BOOL ReadServerInfo( void );
BOOL GetOneValueFromFile( HANDLE hFile, char *tBuffer, int tBufferSize );
BOOL ApplicationInit( void );
void ApplicationFree( void );
void BugTrapInit( void );
#endif
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//GLOBAL_VARIABLES
//-------------------------------------------------------------------------------------------------
#if 0
HWND hMainWindow;
SERVER_INFO mSERVER_INFO;
#endif
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WIN_MAIN
//-------------------------------------------------------------------------------------------------
#if 0
int WINAPI WinMain( HINSTANCE hThis, HINSTANCE hPrev, LPSTR lArgs, int nMode )
{
	BugTrapInit();
	if( !ReadServerInfo() )
	{
		MessageBox( NULL, "[Error::ReadServerInfo()]", "SERVER", ( MB_OK | MB_SYSTEMMODAL ) );
		return FALSE;
	}

	WNDCLASSEX wCls;
	MSG nMss;

	wCls.cbSize	= sizeof( WNDCLASSEX );
	wCls.style = CS_HREDRAW | CS_VREDRAW;
	wCls.lpfnWndProc = WinMainProcedure;
	wCls.cbClsExtra = 0;
	wCls.cbWndExtra = 0;
	wCls.hInstance = hThis;
	wCls.hIcon = LoadIcon( hThis, MAKEINTRESOURCE(IDI_SERVER) );
	wCls.hCursor = LoadCursor( NULL, IDC_ARROW );
	wCls.hbrBackground = (HBRUSH) GetStockObject( BLACK_BRUSH );
	wCls.lpszMenuName = NULL;
	wCls.lpszClassName = mSERVER_INFO.mServerName;
	wCls.hIconSm = NULL;
	if( !RegisterClassEx( &wCls ) )
	{
		MessageBox( NULL, "[Error::RegisterClassEx()]", mSERVER_INFO.mServerName, ( MB_OK | MB_SYSTEMMODAL ) );
		return FALSE;
	}
	hMainWindow = CreateWindowEx( NULL, mSERVER_INFO.mServerName, mSERVER_INFO.mServerName, ( WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE ), ( GetSystemMetrics( SM_CXSCREEN ) / 2 - ( MAIN_WINDOW_SIZE_X / 2 ) ), ( GetSystemMetrics( SM_CYSCREEN ) / 2 - ( MAIN_WINDOW_SIZE_Y / 2 ) ), MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y, HWND_DESKTOP, NULL, hThis, NULL );
	if( !hMainWindow )
	{
		MessageBox( NULL, "[Error::CreateWindow()]", mSERVER_INFO.mServerName, ( MB_OK | MB_SYSTEMMODAL ) );
		return FALSE;
	}
	ShowWindow( hMainWindow, SW_MINIMIZE );
	UpdateWindow( hMainWindow );
	if( !ApplicationInit() )
	{
		ApplicationFree();
#ifdef __WIN32__
		MessageBox( NULL, "[Error::ApplicationInit()]", mSERVER_INFO.mServerName, ( MB_OK | MB_SYSTEMMODAL ) );
#else
		LOG_TO_FILE_1("[Error::ApplicationInit()]");
#endif
		return FALSE;
	}
	while( GetMessage( &nMss, NULL, 0, 0 ) )
	{
		TranslateMessage( &nMss );
		DispatchMessage( &nMss );
	}
	ApplicationFree();
	return nMss.wParam;
}
#endif
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CALLBACK_FUNCTION
//-------------------------------------------------------------------------------------------------
//WIN_MAIN_PROCEDURE
int ProcessResponse (UINT nMss, SOCKET *cli_fd, UINT fd_status, void *arg)
{
	int n_result = 0;
	
	switch (nMss)
	{
	case WM_NETWORK_MESSAGE_1 :
		n_result = mSERVER.PROCESS_FOR_NETWORK( cli_fd, fd_status, arg);
		break;	
#if 0
	case WM_TIMER :
		mSERVER.PROCESS_FOR_TIMER();
		return 0;
	case WM_DESTROY :
		PostQuitMessage( 0 );
		return 0;
#endif
	}
	return n_result;
}

#if 0
LRESULT CALLBACK WinMainProcedure( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm )
{
	switch( nMss )
	{
	case WM_NETWORK_MESSAGE_1 :
		mSERVER.PROCESS_FOR_NETWORK( hWnd, wPrm, lPrm );
		return 0;
	case WM_TIMER :
		mSERVER.PROCESS_FOR_TIMER();
		return 0;
	case WM_DESTROY :
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd,	nMss, wPrm,	lPrm );
}
#endif
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//APPLICATION_FUNCTION
//-------------------------------------------------------------------------------------------------
//READ_SERVER_INFO
#if 0
BOOL ReadServerInfo( void )
{
	HANDLE hFile;
	char tempString01[100];

	hFile = CreateFile( "CONFIG\\SERVER_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mServerName, tempString01 );
	if( strcmp( mSERVER_INFO.mServerName, "" ) == 0 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mServerPort = atoi( tempString01 );
	if( ( mSERVER_INFO.mServerPort < 10000 ) || ( mSERVER_INFO.mServerPort > 99999 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mWorldNumber = atoi( tempString01 );
	if( ( mSERVER_INFO.mWorldNumber < 1 ) || ( mSERVER_INFO.mWorldNumber > 999 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mUpperServer_1_IP, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mUpperServer_1_Port = atoi( tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_IP, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mDB_1_PORT = atoi( tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_ID, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_PASSWORD, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table01, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table02, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table03, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table04, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table05, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table06, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table07, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table08, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table09, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table10, tempString01 );
	if( !CloseHandle( hFile ) )
	{
		return FALSE;
	}
	return TRUE;
}
//GET_ONE_VALUE_FROM_FILE
BOOL GetOneValueFromFile( HANDLE hFile, char *tBuffer, int tBufferSize )
{
	int index01;
	DWORD nReadByte;
	BOOL tCheckSaveState;
	char tData;

	index01 = 0;
	tCheckSaveState = FALSE;
	while( TRUE )
	{
		if( !ReadFile( hFile, &tData, 1, &nReadByte, NULL ) )
		{
			return FALSE;
		}
		if( nReadByte != 1 )
		{
			return FALSE;
		}
		if( !tCheckSaveState )
		{
			if( tData == '[' )
			{
				tCheckSaveState = TRUE;
			}
		}
		else
		{
			if( tData == ']' )
			{
				tBuffer[index01] = '\0';
				break;
			}
			else
			{
				if( index01 < ( tBufferSize - 1 ) )
				{
					tBuffer[index01] = tData;
					index01++;
				}
				else
				{
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}
//APPLICATION_INIT
BOOL ApplicationInit( void )
{
	char tempString01[1000];
	int tResult;

	if( !mSERVER.Init( &tResult ) )
	{
		sprintf( tempString01, "[Error::mSERVER.Init()]-(%d)", tResult );
#ifdef __WIN32__
		MessageBox( NULL, tempString01, mSERVER_INFO.mServerName, ( MB_OK | MB_SYSTEMMODAL ) );
#else
		LOG_TO_FILE_1(tempString01);
#endif
		return FALSE;
	}
	return TRUE;
}
//APPLICATION_FREE
void ApplicationFree( void )
{
	mSERVER.Free();
}
//BUG_TRAP_INIT
void BugTrapInit( void )
{
	BT_InstallSehFilter();
	BT_SetFlags( BTF_DETAILEDMODE );
	BT_SetAppName( "TS2_CENTER" );
}
#endif
//-------------------------------------------------------------------------------------------------
