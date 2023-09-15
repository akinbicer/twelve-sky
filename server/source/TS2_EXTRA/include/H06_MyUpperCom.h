//-------------------------------------------------------------------------------------------------
// 2008.11.18 Kim SungSoo
// Intro : 1.define to convert that win32 variable type to c++ type
//-------------------------------------------------------------------------------------------------
#include "win2unix.h"
#include <pthread.h>
#include <poll.h>
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//MY_UPPER_COM_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_UPPER_COM_H
#define MY_UPPER_COM_H
//-------------------------------------------------------------------------------------------------

#pragma pack (push, 1)
// ��Ű�� ������ ��� �� ���ʽ� ĳ�� ��û ��Ŷ ����ü.
typedef struct _BILL_PACK_USE_REQ
{
	WORD wPacketType;   // ����������(10:���Ӽ��������û, 20:�ܾ���ȸ��û, 30:���ݿ�û, 40:��Ű�� ������ ��� ��û.
	WORD wPacketSize;   // ��������
	DWORD dwSeqNo;      // ��Ŷ �Ϸù�ȣ

	DWORD dwIPAddr;     // IP Addr.
	char szUserID[51];  // ����� ID
	char szItemKey[51]; // ���ӳ��� ������ ���� key(������ ��ȣ).
} BILL_PACK_USE_REQ;

typedef struct _BILL_PACK_USE_REP
{
	WORD wPacketType;   // ����������(11:���Ӽ�����������, 21:�ܾ���ȸ����, 31:��������, 41:��Ű�� ������ ��� ����.
	WORD wPacketSize;   // ��������
	DWORD dwSeqNo;      // ��Ŷ �Ϸù�ȣ

	BYTE bResult;       // ���� �ڵ�
	DWORD dwRemainGC;   // Game Cash �ܾ�
} BILL_PACK_USE_REP;
#pragma pack (pop)

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_FOR_CCashCom
//-------------------------------------------------------------------------------------------------
//CLASS
class CCashCom
{

private :

	BOOL mCheckConnectState;

	char mIP[16];
	int mPort;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	BOOL Connect( void );
	void Close( void );

public :

	BOOL Init( void );
	void Free( void );

	int GetCash( char *tID );
	int ChangeCash( char *tID, int tCostInfoIndex, char *tSellNo );

    int UsePackageItem( char *tID, int iIndex );

};
//INSTANCE
extern CCashCom mCASH_COM;
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAMELOG
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyGameLog
{

private :

	BOOL mCheckConnectState;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	int mLogSort;
	char mGameLogData[MAX_GAMELOG_LENGTH];
	char mSendBuffer[( MAX_GAMELOG_LENGTH * 2 )];

	BOOL CheckValidState( char tID[MAX_USER_ID_LENGTH] );

public :

	MyGameLog( void );

	BOOL Init( char tIP[16], int tPort );
	void Free( void );

	void SendToLogServer( void );
	void SendToLogServerForDB( void );

	void GL_000_ITEM_LOG( char uID[MAX_USER_ID_LENGTH], int uWorld, int uItemNumber, int uPostMoney01, int uPostMoney02, int uCostMoney01, int uCostMoney02, char aName[MAX_AVATAR_NAME_LENGTH], int aTribe, int  aLevel, int uZoneNumber);

};
//INSTANCE
extern MyGameLog mGAMELOG;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
