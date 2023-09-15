//-------------------------------------------------------------------------------------------------
//MY_USER_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_USER_H
#define MY_USER_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_USER
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyUser
{
public :
	BOOL mCheckConnectState;

	DWORD mUsedTime;
	SOCKET mSocket;
	int mEPFD;
	char mIP[16];

	char* mBUFFER_FOR_SEND;
	int mTotalSendSize;
	char* mBUFFER_FOR_RECV;
	int mTotalRecvSize;

	//------------------------//
	//VARIABLE_FOR_THIS_SERVER//
	//------------------------//
	int mCheckServerType;
	int mZoneServerNumber;
	int mZoneServerPort;
	//------------------------//
	//------------------------//
	//------------------------//

	MyUser(void);

	BOOL Init(int tSendBufferSize, int tRecvBufferSize);
	void Free(void);

	void Send(BOOL tCheckValidBuffer, char* tBuffer, int tBufferSize);
	void Quit(int tSort = 2002);
};

//INSTANCE
extern MyUser* mUSER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
