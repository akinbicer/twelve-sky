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
#define MAX_USER_NUM												4096
#define MAX_SEND_BUFFER_SIZE										100000
#define MAX_RECV_BUFFER_SIZE										10000

#include "win2unix.h"

//DEFINE
class MyServer
{

private :

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

public :

	MyServer( void );

	BOOL Init( int *tResult );
	void Free( void );
	int	PROCESS_FOR_NETWORK (SOCKET* from, UINT status, void* pArgs);
	void PROCESS_FOR_TIMER( void );
};
//INSTANCE
extern MyServer mSERVER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
