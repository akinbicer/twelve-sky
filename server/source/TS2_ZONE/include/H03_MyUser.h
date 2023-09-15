//-------------------------------------------------------------------------------------------------
//MY_USER_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_USER_H
#define MY_USER_H
#include "win2unix.h"
#include <pthread.h>
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_USER
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyUser
{

public :
    // # X-Trap # {
    char mXTrapSessionBuf[XTRAP_SESSION_BUF_SIZE];
    char mXTrapStep1_SendBuf[XTRAP_STEP_1_BUF_SIZE];
    unsigned long mXTrapTick;
    // # }

	int mEPFD;
	int *mCliFd;
	int mUserIndex;

	BOOL mCheckConnectState;
	BOOL mCheckValidState;

	DWORD mConnectTime;
	SOCKET mSocket;
	char mIP[16];

	char mPacketEncryptionValue[2];

	char *mBUFFER_FOR_SEND;
	int mTotalSendSize;
	char *mBUFFER_FOR_RECV;
	int mTotalRecvSize;

	//------------------------//
	//VARIABLE_FOR_THIS_SERVER//
	//------------------------//
	time_t mCheckTime;
	BOOL mCheckTempRegister;
	int mTempRegisterTribe;
	DWORD mRegisterTime;
	int mPlayUserIndex;
	char uID[MAX_USER_ID_LENGTH];
	int uUserSort;
	int uGoodFellow;
	int uLoginPlace;
	int uLoginPremium;
	int uLoginPremiumPCRoom;
	int uTraceState;
	char uBonus100Money;
    int uPremiumServerExpirationDate; // �����̾� ����(����) ����� ��ȿ ����(YYYYMMDD ������ ����) ����. // @_Premium_Server_@
	AVATAR_INFO mAvatarInfo;
	int mEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2];
	float mGeneralExperienceUpRatio;
	float mItemDropUpRatio;
	float mGeneralExperienceDownRatio;
	/** 2009. 11. 23 : ��Ű�� �����۰��� (wolf) */
	float mSelfPatExperienceUpRatio; // �����ġ ��·� ����
	/** 2009. 11. 23 : ��Ű�� �����۰��� (wolf) */
	int mSupportSkillTimeUpRatio;
	BOOL mCheckHealthState;
	int mHealthState;

	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
  DWORD mTickCountForDarkAttack;
  int iKindDarkAttack;
  /** 2009. 10. 26 : DarkAttack Potion add (wolf) */

	DWORD mTickCountFor01Second;
	DWORD mTickCountFor01SecondForProtect;
	DWORD mTickCountFor30Second;
	DWORD mTickCountFor01MinuteForHealth;
	DWORD mTickCountFor01Minute;

	DWORD mTickCountFor01Minute_2;
	DWORD mTickCountFor03Second;
  // # Defense Hack # {
  int mAutoCheckCount;
  DWORD mUniqueNumber;
  DWORD mAttackTickCount;
  unsigned int mSpeedTickCount;
  // # }
	int mCheckMaxAttackPacketNum;
	int mMaxAttackPacketNum;
	int mNowAttackPacketNum;
	int mAutoCheckState;
	int mAutoCheckAnswer;
	DWORD mAutoCheckTime;
	DWORD mHackCheckTime;
	int mMoveZoneResult;
	AUTH_INFO mAuthInfo;
#ifdef __LOCK__
	pthread_mutex_t m_user_lock;
	pthread_mutex_t m_user_quit_lock; // MyUser::Quit �Լ� ����ȭ ó����.
#endif

#ifdef __GOD__
	time_t mEffectCheckTime;
	int mAttackPacketSort;
#endif
	//------------------------//
	//------------------------//
	//------------------------//

	//---------//
	//N-PROTECT//
	//---------//
#ifdef __N_PROTECT__
	CCSAuth2 *mNPROTECT;
	BOOL mCheckNPROTECT;
	int mNumberForNPROTECT;
	DWORD mTickCountForNPROTECT;
#endif
	//---------//
	//---------//
	//---------//
	
	int mHeartCheckCount;
	time_t mHeartCheckTime;

    bool            m_bUDPActivated; /// UDP �ּ� Ȯ�� ����.
    SOCKADDR_IN     m_AddrFrom; ///< Address Info to broadcast by UDP.
	int             m_iTryCountForAuth;
#ifndef __ORG__
	bool            m_bUDPArrivedAtClient;
#endif

    MOVE_ITEM_INFO mMoveItemInfo; // �̵��� ��� ����.

	MyUser( void );

	BOOL Init( int tUserIndex, int tSendBufferSize, int tRecvBufferSize );
	void Free( void );

	void Send( BOOL tCheckValidBuffer, char *tBuffer, int tBufferSize, bool bUDPSend = false);
	//void Quit( void );
	void Quit(const char *tFileName = __FILE__, const char *tFuncName = __FUNCTION__ , int tLine = __LINE__);



	//@{ auto quize
	enum { TEMP_BUFF_SIZE=10, };
	enum { RST_OK, RST_WRONG_ANSWER_0, RST_WRONG_ANSWER_1, RST_TIME_OVER, };
	BOOL		m_bIsBonusRecv;
	BOOL		m_bIsSend_Question;			
	char		m_tSphinx_Question[ TEMP_BUFF_SIZE ];
	DWORD		m_dSend_Time;
	int			m_iWrong_Count;
	inline void Set_BonusRecv( BOOL bIsCheck )
	{
		m_bIsBonusRecv = bIsCheck;
	}
	inline BOOL Get_BonusRecv( void )
	{
		return m_bIsBonusRecv;
	}
	inline void Set_Send_Question( BOOL bisSend )
	{
		m_bIsSend_Question = bisSend;
	}
	inline BOOL IsSend_Question( void )
	{
		return m_bIsSend_Question;
	}
	inline void Set_Sphinx_Question( char const * tStr )
	{
		memcpy( m_tSphinx_Question, tStr, 5 );
	}
	inline char* Get_Sphinx_Question( void )
	{
		return m_tSphinx_Question;
	}
	inline void Set_Send_Question_Time( DWORD dTime )
	{
		m_dSend_Time = dTime;
	}
	BOOL IsSend_TimeOver( void );
	BOOL IsWrong_CountOver( void );
	//@}

    // @ Cost Info Download @
    bool mIsValidCashItemInfo;
    // @

	/** 2009. 11. 23 : ��Ű�� ������ ���� (wolf) */
	bool bUsePackItem;
	/** 2009. 11. 23 : ��Ű�� ������ ���� (wolf) */

    bool IsValidSkillNumber(int skillNumber);
    int GetMaxSkillGradeNum(int skillNumber);
};
//INSTANCE
extern MyUser *mUSER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
