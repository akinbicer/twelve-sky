//-------------------------------------------------------------------------------------------------
//MY_GAME_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_GAME_H
#define MY_GAME_H
//-------------------------------------------------------------------------------------------------

//#include "zlib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAME
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_COST_INFO_NUM											1000

// @ Cost Info Download @
#define MAX_COST_INFO_CODE_LEN                                      51
#define MAX_COST_INFO_TYPE                                          5
// @

//DEFINE
class MyGame
{

private :
//-------------------------------------------------------------------------------------------------
// 2008.11.18 Kim SungSoo
// Intro : 	1. Modify win32 function to linux c++ 
//					2. Create that load file then return string
//-------------------------------------------------------------------------------------------------	
#ifdef __WIN32__
	BOOL GetOneValueFromFile( HANDLE hFile, int tBufferSize, char *tBuffer );
#else
    // @ Cost Info Download @
    //int GetOneValueFromFile(const char *pBuffer , int iParsorIndex);
    bool GetOneValueFromFile(const char *pBuffer , int iParsorIndex, int *tResult);
    // @
    bool GetOneValueFromFile(char *pValue , const char *pBuffer , int iParsorIndex);
#endif
//-------------------------------------------------------------------------------------------------	

public :

	DWORD mTickCount;

	int mTotalCostInfoNum;
    // @ Cost Info Download @
    // ���� ���� �߰�.
    int mCostInfoValue[MAX_COST_INFO_NUM][MAX_COST_INFO_TYPE]; //[0]::����,[1]::������,[2]::����,[3]::�Ǹſ���,[4]::��������(1���, 2����, 3���, 4��ȭ)

    bool mIsSellCashItem;
    int mCashItemInfoVersion;           // COST_INFO.TXT�� ����
    int mCashItemInfo[4][10][10][4];    // Ŭ���̾�Ʈ���� ����ϴ� ĳ�� ������ ���� ����

    int GetCostInfoVersion();
    bool LoadCostInfo(int *pTotalCostInfoNum, int *pVersion, int tCostInfoValue[MAX_COST_INFO_NUM][MAX_COST_INFO_TYPE], char tCostInfoCode[MAX_COST_INFO_NUM][MAX_COST_INFO_CODE_LEN]);
    bool MakeCashItemInfo(int tCashItemInfo[4][10][10][4], const int tCostInfoValue[MAX_COST_INFO_NUM][MAX_COST_INFO_TYPE], int totalCostInfoNum);
    // @
    char mCostInfoCode[MAX_COST_INFO_NUM][MAX_COST_INFO_CODE_LEN];

	MyGame( void );

	BOOL Init( void );
	void Free( void );

};
//INSTANCE
extern MyGame mGAME;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
