//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "H01_MainApplication.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_WORK
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyWork mWORK;
//CREATE
MyWork::MyWork( void )
{
}
//INIT
BOOL MyWork::Init( void )
{
	int index01;

	for( index01 = 0 ; index01 < 256 ; index01++ )
	{
		W_FUNCTION[index01].PROC = NULL;
	}
	//---------------//
	//LOGIN->PLAYUSER//
	//---------------//
	//W_LOGIN_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_LOGIN_FOR_PLAYUSER_SEND] = S_LOGIN_FOR_PLAYUSER_SEND;
	W_FUNCTION[P_LOGIN_FOR_PLAYUSER_SEND].PROC = W_LOGIN_FOR_PLAYUSER_SEND;
	//W_LOGIN_OK_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_LOGIN_OK_FOR_PLAYUSER_SEND] = S_LOGIN_OK_FOR_PLAYUSER_SEND;
	W_FUNCTION[P_LOGIN_OK_FOR_PLAYUSER_SEND].PROC = W_LOGIN_OK_FOR_PLAYUSER_SEND;
	//W_REGISTER_USER_FOR_LOGIN_1_SEND
	mWorkerPacketSize[P_REGISTER_USER_FOR_LOGIN_1_SEND] = S_REGISTER_USER_FOR_LOGIN_1_SEND;
	W_FUNCTION[P_REGISTER_USER_FOR_LOGIN_1_SEND].PROC = W_REGISTER_USER_FOR_LOGIN_1_SEND;
	//W_REGISTER_USER_FOR_LOGIN_2_SEND
	mWorkerPacketSize[P_REGISTER_USER_FOR_LOGIN_2_SEND] = S_REGISTER_USER_FOR_LOGIN_2_SEND;
	W_FUNCTION[P_REGISTER_USER_FOR_LOGIN_2_SEND].PROC = W_REGISTER_USER_FOR_LOGIN_2_SEND;
	//W_REGISTER_USER_FOR_LOGIN_3_SEND
	mWorkerPacketSize[P_REGISTER_USER_FOR_LOGIN_3_SEND] = S_REGISTER_USER_FOR_LOGIN_3_SEND;
	W_FUNCTION[P_REGISTER_USER_FOR_LOGIN_3_SEND].PROC = W_REGISTER_USER_FOR_LOGIN_3_SEND;
	//W_UNREGISTER_USER_FOR_LOGIN_SEND
	mWorkerPacketSize[P_UNREGISTER_USER_FOR_LOGIN_SEND] = S_UNREGISTER_USER_FOR_LOGIN_SEND;
	W_FUNCTION[P_UNREGISTER_USER_FOR_LOGIN_SEND].PROC = W_UNREGISTER_USER_FOR_LOGIN_SEND;
	//W_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND
	mWorkerPacketSize[P_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND] = S_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND;
	W_FUNCTION[P_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND].PROC = W_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND;
	//W_BLOCK_USER_FOR_LOGIN_1_SEND
	mWorkerPacketSize[P_BLOCK_USER_FOR_LOGIN_1_SEND] = S_BLOCK_USER_FOR_LOGIN_1_SEND;
	W_FUNCTION[P_BLOCK_USER_FOR_LOGIN_1_SEND].PROC = W_BLOCK_USER_FOR_LOGIN_1_SEND;
	//W_BLOCK_USER_FOR_LOGIN_2_SEND
	mWorkerPacketSize[P_BLOCK_USER_FOR_LOGIN_2_SEND] = S_BLOCK_USER_FOR_LOGIN_2_SEND;
	W_FUNCTION[P_BLOCK_USER_FOR_LOGIN_2_SEND].PROC = W_BLOCK_USER_FOR_LOGIN_2_SEND;
	//--------------//
	//ZONE->PLAYUSER//
	//--------------//
	//W_ZONE_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_ZONE_FOR_PLAYUSER_SEND] = S_ZONE_FOR_PLAYUSER_SEND;
	W_FUNCTION[P_ZONE_FOR_PLAYUSER_SEND].PROC = W_ZONE_FOR_PLAYUSER_SEND;
	//W_ZONE_OK_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_ZONE_OK_FOR_PLAYUSER_SEND] = S_ZONE_OK_FOR_PLAYUSER_SEND;
	W_FUNCTION[P_ZONE_OK_FOR_PLAYUSER_SEND].PROC = W_ZONE_OK_FOR_PLAYUSER_SEND;
	//W_REGISTER_USER_FOR_ZONE_0_SEND
	mWorkerPacketSize[P_REGISTER_USER_FOR_ZONE_0_SEND] = S_REGISTER_USER_FOR_ZONE_0_SEND;
	W_FUNCTION[P_REGISTER_USER_FOR_ZONE_0_SEND].PROC = W_REGISTER_USER_FOR_ZONE_0_SEND;
	//W_REGISTER_USER_FOR_ZONE_1_SEND
	mWorkerPacketSize[P_REGISTER_USER_FOR_ZONE_1_SEND] = S_REGISTER_USER_FOR_ZONE_1_SEND;
	W_FUNCTION[P_REGISTER_USER_FOR_ZONE_1_SEND].PROC = W_REGISTER_USER_FOR_ZONE_1_SEND;
	//W_REGISTER_USER_FOR_ZONE_2_SEND
	mWorkerPacketSize[P_REGISTER_USER_FOR_ZONE_2_SEND] = S_REGISTER_USER_FOR_ZONE_2_SEND;
	W_FUNCTION[P_REGISTER_USER_FOR_ZONE_2_SEND].PROC = W_REGISTER_USER_FOR_ZONE_2_SEND;
	//W_REGISTER_USER_FOR_ZONE_3_SEND
	mWorkerPacketSize[P_REGISTER_USER_FOR_ZONE_3_SEND] = S_REGISTER_USER_FOR_ZONE_3_SEND;
	W_FUNCTION[P_REGISTER_USER_FOR_ZONE_3_SEND].PROC = W_REGISTER_USER_FOR_ZONE_3_SEND;
	//W_UNREGISTER_USER_FOR_ZONE_SEND
	mWorkerPacketSize[P_UNREGISTER_USER_FOR_ZONE_SEND] = S_UNREGISTER_USER_FOR_ZONE_SEND;
	W_FUNCTION[P_UNREGISTER_USER_FOR_ZONE_SEND].PROC = W_UNREGISTER_USER_FOR_ZONE_SEND;
	//W_FIND_AVATAR_FOR_ZONE_SEND
	mWorkerPacketSize[P_FIND_AVATAR_FOR_ZONE_SEND] = S_FIND_AVATAR_FOR_ZONE_SEND;
	W_FUNCTION[P_FIND_AVATAR_FOR_ZONE_SEND].PROC = W_FIND_AVATAR_FOR_ZONE_SEND;
	//W_TRIBE_BANK_INFO_SAVE_SEND
	mWorkerPacketSize[P_TRIBE_BANK_INFO_SAVE_SEND] = S_TRIBE_BANK_INFO_SAVE_SEND;
	W_FUNCTION[P_TRIBE_BANK_INFO_SAVE_SEND].PROC = W_TRIBE_BANK_INFO_SAVE_SEND;
	//W_TRIBE_BANK_INFO_VIEW_SEND
	mWorkerPacketSize[P_TRIBE_BANK_INFO_VIEW_SEND] = S_TRIBE_BANK_INFO_VIEW_SEND;
	W_FUNCTION[P_TRIBE_BANK_INFO_VIEW_SEND].PROC = W_TRIBE_BANK_INFO_VIEW_SEND;
	//W_TRIBE_BANK_INFO_LOAD_SEND
	mWorkerPacketSize[P_TRIBE_BANK_INFO_LOAD_SEND] = S_TRIBE_BANK_INFO_LOAD_SEND;
	W_FUNCTION[P_TRIBE_BANK_INFO_LOAD_SEND].PROC = W_TRIBE_BANK_INFO_LOAD_SEND;
	//W_HACK_NAME_SEND
	mWorkerPacketSize[P_HACK_NAME_SEND] = S_HACK_NAME_SEND;
	W_FUNCTION[P_HACK_NAME_SEND].PROC = W_HACK_NAME_SEND;
	//night_kutu
	//W_BLOCK_USER_FOR_ZONE_1_SEND
	mWorkerPacketSize[P_BLOCK_USER_FOR_ZONE_1_SEND] = S_BLOCK_USER_FOR_ZONE_1_SEND;
	W_FUNCTION[P_BLOCK_USER_FOR_ZONE_1_SEND].PROC = W_BLOCK_USER_FOR_ZONE_1_SEND;


	mWorkerPacketSize[P_USER_ZONE_SEND_CASH] = S_USER_ZONE_SEND_CASH;
	W_FUNCTION[P_USER_ZONE_SEND_CASH].PROC = W_USER_ZONE_SEND_CASH;
	//W_BLOCK_USER_FOR_ZONE_2_SEND
	mWorkerPacketSize[P_BLOCK_USER_FOR_ZONE_2_SEND] = S_BLOCK_USER_FOR_ZONE_2_SEND;
	W_FUNCTION[P_BLOCK_USER_FOR_ZONE_2_SEND].PROC = W_BLOCK_USER_FOR_ZONE_2_SEND;
	//W_ADD_AUTO_USER_LIST_SEND
	mWorkerPacketSize[P_ADD_AUTO_USER_LIST_SEND] = S_ADD_AUTO_USER_LIST_SEND;
	W_FUNCTION[P_ADD_AUTO_USER_LIST_SEND].PROC = W_ADD_AUTO_USER_LIST_SEND;
	//W_CHECK_KILL_OTHER_TRIBE_SEND
	mWorkerPacketSize[P_CHECK_KILL_OTHER_TRIBE_SEND] = S_CHECK_KILL_OTHER_TRIBE_SEND;
	W_FUNCTION[P_CHECK_KILL_OTHER_TRIBE_SEND].PROC = W_CHECK_KILL_OTHER_TRIBE_SEND;
	//W_EVENT_INFO_SEND
	mWorkerPacketSize[P_EVENT_INFO_SEND] = S_EVENT_INFO_SEND;
	W_FUNCTION[P_EVENT_INFO_SEND].PROC = W_EVENT_INFO_SEND;

	mWorkerPacketSize[ZTOP_CHECK_AUTH_KEY_TYPE] = ZTOP_CHECK_AUTH_KEY_SIZE;
	W_FUNCTION[ZTOP_CHECK_AUTH_KEY_TYPE].PROC = W_CHECK_AUTH_KEY;

	mWorkerPacketSize[ZTOP_UPDATE_AUTH_KEY_TYPE] = ZTOP_UPDATE_AUTH_KEY_SIZE;
	W_FUNCTION[ZTOP_UPDATE_AUTH_KEY_TYPE].PROC = W_UPDATE_AUTH_KEY;
	//W_CHANGE_AVATAR_NAME_FOR_ZONE_SEND
	mWorkerPacketSize[P_CHANGE_AVATAR_NAME_FOR_ZONE_SEND] = S_CHANGE_AVATAR_NAME_FOR_ZONE_SEND;
	W_FUNCTION[P_CHANGE_AVATAR_NAME_FOR_ZONE_SEND].PROC = W_CHANGE_AVATAR_NAME_FOR_ZONE_SEND;
	//W_BONUS_100_MONEY_FOR_ZONE_SEND
	mWorkerPacketSize[P_BONUS_100_MONEY_FOR_ZONE_SEND] = S_BONUS_100_MONEY_FOR_ZONE_SEND;
	W_FUNCTION[P_BONUS_100_MONEY_FOR_ZONE_SEND].PROC = W_BONUS_100_MONEY_FOR_ZONE_SEND;
#ifdef __EVENT_KILL__
	//W_EVENT_FOR_ZONE_SEND
	mWorkerPacketSize[P_EVENT_FOR_ZONE_SEND] = S_EVENT_FOR_ZONE_SEND;
	W_FUNCTION[P_EVENT_FOR_ZONE_SEND].PROC = W_EVENT_FOR_ZONE_SEND;
#elif __EVENT_GOLD_PHONE__
	//W_EVENT_FOR_ZONE_SEND
	mWorkerPacketSize[P_EVENT_FOR_ZONE_SEND] = S_EVENT_FOR_ZONE_SEND;
	W_FUNCTION[P_EVENT_FOR_ZONE_SEND].PROC = W_EVENT_FOR_ZONE_SEND;
#endif
    //W_SET_MOVE_ITEM_FOR_ZONE_SEND
    mWorkerPacketSize[P_SET_MOVE_ITEM_FOR_ZONE_SEND] = S_SET_MOVE_ITEM_FOR_ZONE_SEND;
    W_FUNCTION[P_SET_MOVE_ITEM_FOR_ZONE_SEND].PROC = W_SET_MOVE_ITEM_FOR_ZONE_SEND;

	//--------------//
	//TOOL->PLAYUSER//
	//--------------//
	//W_TOOL_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_TOOL_FOR_PLAYUSER_SEND] = S_TOOL_FOR_PLAYUSER_SEND;
	W_FUNCTION[P_TOOL_FOR_PLAYUSER_SEND].PROC = W_TOOL_FOR_PLAYUSER_SEND;
	//W_TOOL_OK_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_TOOL_OK_FOR_PLAYUSER_SEND] = S_TOOL_OK_FOR_PLAYUSER_SEND;
	W_FUNCTION[P_TOOL_OK_FOR_PLAYUSER_SEND].PROC = W_TOOL_OK_FOR_PLAYUSER_SEND;
	//W_CHANGE_LOGIN_USER_NUM_SEND
	mWorkerPacketSize[P_CHANGE_LOGIN_USER_NUM_SEND] = S_CHANGE_LOGIN_USER_NUM_SEND;
	W_FUNCTION[P_CHANGE_LOGIN_USER_NUM_SEND].PROC = W_CHANGE_LOGIN_USER_NUM_SEND;
	//W_CHECK_ZONE_FOR_TOOL_SEND
	mWorkerPacketSize[P_CHECK_ZONE_FOR_TOOL_SEND] = S_CHECK_ZONE_FOR_TOOL_SEND;
	W_FUNCTION[P_CHECK_ZONE_FOR_TOOL_SEND].PROC = W_CHECK_ZONE_FOR_TOOL_SEND;
	//W_GET_PRESENT_USER_NUM_FOR_TOOL_SEND
	mWorkerPacketSize[P_GET_PRESENT_USER_NUM_FOR_TOOL_SEND] = S_GET_PRESENT_USER_NUM_FOR_TOOL_SEND;
	W_FUNCTION[P_GET_PRESENT_USER_NUM_FOR_TOOL_SEND].PROC = W_GET_PRESENT_USER_NUM_FOR_TOOL_SEND;
	//W_FIND_AVATAR_FOR_TOOL_SEND
	mWorkerPacketSize[P_FIND_AVATAR_FOR_TOOL_SEND] = S_FIND_AVATAR_FOR_TOOL_SEND;
	W_FUNCTION[P_FIND_AVATAR_FOR_TOOL_SEND].PROC = W_FIND_AVATAR_FOR_TOOL_SEND;
	//W_FIND_USER_FOR_TOOL_SEND
	mWorkerPacketSize[P_FIND_USER_FOR_TOOL_SEND] = S_FIND_USER_FOR_TOOL_SEND;
	W_FUNCTION[P_FIND_USER_FOR_TOOL_SEND].PROC = W_FIND_USER_FOR_TOOL_SEND;
	//W_BLOCK_USER_FOR_TOOL_1_SEND
	mWorkerPacketSize[P_BLOCK_USER_FOR_TOOL_1_SEND] = S_BLOCK_USER_FOR_TOOL_1_SEND;
	W_FUNCTION[P_BLOCK_USER_FOR_TOOL_1_SEND].PROC = W_BLOCK_USER_FOR_TOOL_1_SEND;
	//W_BLOCK_USER_FOR_TOOL_2_SEND
	mWorkerPacketSize[P_BLOCK_USER_FOR_TOOL_2_SEND] = S_BLOCK_USER_FOR_TOOL_2_SEND;
	W_FUNCTION[P_BLOCK_USER_FOR_TOOL_2_SEND].PROC = W_BLOCK_USER_FOR_TOOL_2_SEND;
	//W_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND
	mWorkerPacketSize[P_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND] = S_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND;
	W_FUNCTION[P_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND].PROC = W_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND;
	//----------------------//
	//[POLICE] -> [PLAYUSER]//
	//----------------------//
	//W_POLICE_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_POLICE_FOR_PLAYUSER_SEND] = S_POLICE_FOR_PLAYUSER_SEND;
	W_FUNCTION[P_POLICE_FOR_PLAYUSER_SEND].PROC = W_POLICE_FOR_PLAYUSER_SEND;
	//W_POLICE_OK_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_POLICE_OK_FOR_PLAYUSER_SEND] = S_POLICE_OK_FOR_PLAYUSER_SEND;
	W_FUNCTION[P_POLICE_OK_FOR_PLAYUSER_SEND].PROC = W_POLICE_OK_FOR_PLAYUSER_SEND;
	return TRUE;
}
//FREE
void MyWork::Free( void )
{
}
//-------------------------------------------------------------------------------------------------
