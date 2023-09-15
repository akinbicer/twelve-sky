//-------------------------------------------------------------------------------------------------
//MY_SERVER_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_SERVER_H
#define MY_SERVER_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_SERVER
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_USER_NUM												MAX_ZONE_NUMBER_NUM
#define MAX_SEND_BUFFER_SIZE										100000
#define MAX_RECV_BUFFER_SIZE										100000
//DEFINE
#include "win2unix.h"

class MyServer
{

private :

#ifdef __WIN32__
	WSADATA mWsaData;
#endif
	int *m_epfd;
	SOCKET mSocket;
	struct sockaddr_in mAddress;

public :

	MyServer( void );

	BOOL Init( int *tResult );
	void Free( void );

	//void PROCESS_FOR_NETWORK( HWND hWnd, WPARAM wPrm, LPARAM lPrm );
	int PROCESS_FOR_NETWORK(SOCKET *cli_fd, UINT fd_status, void *arg);

	void PROCESS_FOR_TIMER( void );

	//void WRITE_FOR_ERROR( char *tErrorData );

};
//INSTANCE
extern MyServer mSERVER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
