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
	//W_TEMP_REGISTER_SEND
	mWorkerPacketSize[P_TEMP_REGISTER_SEND] = S_TEMP_REGISTER_SEND;
	W_FUNCTION[P_TEMP_REGISTER_SEND].PROC = W_TEMP_REGISTER_SEND;
	//W_REGISTER_AVATAR_SEND
	mWorkerPacketSize[P_REGISTER_AVATAR_SEND] = S_REGISTER_AVATAR_SEND;
	W_FUNCTION[P_REGISTER_AVATAR_SEND].PROC = W_REGISTER_AVATAR_SEND;
	//W_CLIENT_OK_FOR_ZONE_SEND
	mWorkerPacketSize[P_CLIENT_OK_FOR_ZONE_SEND] = S_CLIENT_OK_FOR_ZONE_SEND;
	W_FUNCTION[P_CLIENT_OK_FOR_ZONE_SEND].PROC = W_CLIENT_OK_FOR_ZONE_SEND;
	//W_AUTO_CHECK_ASK_RECV
	mWorkerPacketSize[P_AUTO_CHECK_ASK_RECV] = S_AUTO_CHECK_ASK_RECV;
	W_FUNCTION[P_AUTO_CHECK_ASK_RECV].PROC = W_AUTO_CHECK_ASK_RECV;
	//W_AVATAR_ACTION_SEND
	mWorkerPacketSize[P_AVATAR_ACTION_SEND] = S_AVATAR_ACTION_SEND;
	W_FUNCTION[P_AVATAR_ACTION_SEND].PROC = W_AVATAR_ACTION_SEND;
	//W_UPDATE_AVATAR_ACTION
	mWorkerPacketSize[P_UPDATE_AVATAR_ACTION] = S_UPDATE_AVATAR_ACTION;
	W_FUNCTION[P_UPDATE_AVATAR_ACTION].PROC = W_UPDATE_AVATAR_ACTION;
	//W_GENERAL_NOTICE_SEND
	mWorkerPacketSize[P_GENERAL_NOTICE_SEND] = S_GENERAL_NOTICE_SEND;
	W_FUNCTION[P_GENERAL_NOTICE_SEND].PROC = W_GENERAL_NOTICE_SEND;
	//W_PROCESS_ATTACK_SEND
	mWorkerPacketSize[P_PROCESS_ATTACK_SEND] = S_PROCESS_ATTACK_SEND;
	W_FUNCTION[P_PROCESS_ATTACK_SEND].PROC = W_PROCESS_ATTACK_SEND;
	//W_PROCESS_DATA_SEND
	mWorkerPacketSize[P_PROCESS_DATA_SEND] = S_PROCESS_DATA_SEND;
	W_FUNCTION[P_PROCESS_DATA_SEND].PROC = W_PROCESS_DATA_SEND;
	//W_DEMAND_ZONE_SERVER_INFO_2
	mWorkerPacketSize[P_DEMAND_ZONE_SERVER_INFO_2] = S_DEMAND_ZONE_SERVER_INFO_2;
	W_FUNCTION[P_DEMAND_ZONE_SERVER_INFO_2].PROC = W_DEMAND_ZONE_SERVER_INFO_2;
	//W_FAIL_MOVE_ZONE_2_SEND
	mWorkerPacketSize[P_FAIL_MOVE_ZONE_2_SEND] = S_FAIL_MOVE_ZONE_2_SEND;
	W_FUNCTION[P_FAIL_MOVE_ZONE_2_SEND].PROC = W_FAIL_MOVE_ZONE_2_SEND;
	//W_USE_HOTKEY_ITEM_SEND
	mWorkerPacketSize[P_USE_HOTKEY_ITEM_SEND] = S_USE_HOTKEY_ITEM_SEND;
	W_FUNCTION[P_USE_HOTKEY_ITEM_SEND].PROC = W_USE_HOTKEY_ITEM_SEND;
	//W_USE_INVENTORY_ITEM_SEND
	mWorkerPacketSize[P_USE_INVENTORY_ITEM_SEND] = S_USE_INVENTORY_ITEM_SEND;
	W_FUNCTION[P_USE_INVENTORY_ITEM_SEND].PROC = W_USE_INVENTORY_ITEM_SEND;
	//W_IMPROVE_ITEM_SEND
	mWorkerPacketSize[P_IMPROVE_ITEM_SEND] = S_IMPROVE_ITEM_SEND;
	W_FUNCTION[P_IMPROVE_ITEM_SEND].PROC = W_IMPROVE_ITEM_SEND;
	//W_ADD_ITEM_SEND
	mWorkerPacketSize[P_ADD_ITEM_SEND] = S_ADD_ITEM_SEND;
	W_FUNCTION[P_ADD_ITEM_SEND].PROC = W_ADD_ITEM_SEND;
	//W_EXCHANGE_ITEM_SEND
	mWorkerPacketSize[P_EXCHANGE_ITEM_SEND] = S_EXCHANGE_ITEM_SEND;
	W_FUNCTION[P_EXCHANGE_ITEM_SEND].PROC = W_EXCHANGE_ITEM_SEND;
	//W_HIGH_ITEM_SEND
	mWorkerPacketSize[P_HIGH_ITEM_SEND] = S_HIGH_ITEM_SEND;
	W_FUNCTION[P_HIGH_ITEM_SEND].PROC = W_HIGH_ITEM_SEND;
	//W_LOW_ITEM_SEND
	mWorkerPacketSize[P_LOW_ITEM_SEND] = S_LOW_ITEM_SEND;
	W_FUNCTION[P_LOW_ITEM_SEND].PROC = W_LOW_ITEM_SEND;
	//W_MAKE_ITEM_SEND
	mWorkerPacketSize[P_MAKE_ITEM_SEND] = S_MAKE_ITEM_SEND;
	W_FUNCTION[P_MAKE_ITEM_SEND].PROC = W_MAKE_ITEM_SEND;
	//W_MAKE_SKILL_SEND
	mWorkerPacketSize[P_MAKE_SKILL_SEND] = S_MAKE_SKILL_SEND;
	W_FUNCTION[P_MAKE_SKILL_SEND].PROC = W_MAKE_SKILL_SEND;
	//W_START_PSHOP_SEND
	mWorkerPacketSize[P_START_PSHOP_SEND] = S_START_PSHOP_SEND;
	W_FUNCTION[P_START_PSHOP_SEND].PROC = W_START_PSHOP_SEND;
	//W_END_PSHOP_SEND
	mWorkerPacketSize[P_END_PSHOP_SEND] = S_END_PSHOP_SEND;
	W_FUNCTION[P_END_PSHOP_SEND].PROC = W_END_PSHOP_SEND;
	//W_DEMAND_PSHOP_SEND
	mWorkerPacketSize[P_DEMAND_PSHOP_SEND] = S_DEMAND_PSHOP_SEND;
	W_FUNCTION[P_DEMAND_PSHOP_SEND].PROC = W_DEMAND_PSHOP_SEND;
	//W_PSHOP_ITEM_INFO_SEND
	mWorkerPacketSize[P_PSHOP_ITEM_INFO_SEND] = S_PSHOP_ITEM_INFO_SEND;
	W_FUNCTION[P_PSHOP_ITEM_INFO_SEND].PROC = W_PSHOP_ITEM_INFO_SEND;
	//W_BUY_PSHOP_SEND
	mWorkerPacketSize[P_BUY_PSHOP_SEND] = S_BUY_PSHOP_SEND;
	W_FUNCTION[P_BUY_PSHOP_SEND].PROC = W_BUY_PSHOP_SEND;
	//W_PROCESS_QUEST_SEND
	mWorkerPacketSize[P_PROCESS_QUEST_SEND] = S_PROCESS_QUEST_SEND;
	W_FUNCTION[P_PROCESS_QUEST_SEND].PROC = W_PROCESS_QUEST_SEND;
	//W_CHANGE_TO_TRIBE4_SEND
	mWorkerPacketSize[P_CHANGE_TO_TRIBE4_SEND] = S_CHANGE_TO_TRIBE4_SEND;
	W_FUNCTION[P_CHANGE_TO_TRIBE4_SEND].PROC = W_CHANGE_TO_TRIBE4_SEND;
	//W_GENERAL_CHAT_SEND
	mWorkerPacketSize[P_GENERAL_CHAT_SEND] = S_GENERAL_CHAT_SEND;
	W_FUNCTION[P_GENERAL_CHAT_SEND].PROC = W_GENERAL_CHAT_SEND;
	//W_SECRET_CHAT_SEND
	mWorkerPacketSize[P_SECRET_CHAT_SEND] = S_SECRET_CHAT_SEND;
	W_FUNCTION[P_SECRET_CHAT_SEND].PROC = W_SECRET_CHAT_SEND;
	//W_GENERAL_SHOUT_SEND
	mWorkerPacketSize[P_GENERAL_SHOUT_SEND] = S_GENERAL_SHOUT_SEND;
	W_FUNCTION[P_GENERAL_SHOUT_SEND].PROC = W_GENERAL_SHOUT_SEND;
	//W_GET_CASH_SIZE_SEND
	mWorkerPacketSize[P_GET_CASH_SIZE_SEND] = S_GET_CASH_SIZE_SEND;
	W_FUNCTION[P_GET_CASH_SIZE_SEND].PROC = W_GET_CASH_SIZE_SEND;
	//W_BUY_CASH_ITEM_SEND
	mWorkerPacketSize[P_BUY_CASH_ITEM_SEND] = S_BUY_CASH_ITEM_SEND;
	W_FUNCTION[P_BUY_CASH_ITEM_SEND].PROC = W_BUY_CASH_ITEM_SEND;
	//W_DUEL_ASK_SEND
	mWorkerPacketSize[P_DUEL_ASK_SEND] = S_DUEL_ASK_SEND;
	W_FUNCTION[P_DUEL_ASK_SEND].PROC = W_DUEL_ASK_SEND;
	//W_DUEL_CANCEL_SEND
	mWorkerPacketSize[P_DUEL_CANCEL_SEND] = S_DUEL_CANCEL_SEND;
	W_FUNCTION[P_DUEL_CANCEL_SEND].PROC = W_DUEL_CANCEL_SEND;
	//W_DUEL_ANSWER_SEND
	mWorkerPacketSize[P_DUEL_ANSWER_SEND] = S_DUEL_ANSWER_SEND;
	W_FUNCTION[P_DUEL_ANSWER_SEND].PROC = W_DUEL_ANSWER_SEND;
	//W_DUEL_START_SEND
	mWorkerPacketSize[P_DUEL_START_SEND] = S_DUEL_START_SEND;
	W_FUNCTION[P_DUEL_START_SEND].PROC = W_DUEL_START_SEND;
	//W_TRADE_ASK_SEND
	mWorkerPacketSize[P_TRADE_ASK_SEND] = S_TRADE_ASK_SEND;
	W_FUNCTION[P_TRADE_ASK_SEND].PROC = W_TRADE_ASK_SEND;
	//W_TRADE_CANCEL_SEND
	mWorkerPacketSize[P_TRADE_CANCEL_SEND] = S_TRADE_CANCEL_SEND;
	W_FUNCTION[P_TRADE_CANCEL_SEND].PROC = W_TRADE_CANCEL_SEND;
	//W_TRADE_ANSWER_SEND
	mWorkerPacketSize[P_TRADE_ANSWER_SEND] = S_TRADE_ANSWER_SEND;
	W_FUNCTION[P_TRADE_ANSWER_SEND].PROC = W_TRADE_ANSWER_SEND;
	//W_TRADE_START_SEND
	mWorkerPacketSize[P_TRADE_START_SEND] = S_TRADE_START_SEND;
	W_FUNCTION[P_TRADE_START_SEND].PROC = W_TRADE_START_SEND;
	//W_TRADE_MENU_SEND
	mWorkerPacketSize[P_TRADE_MENU_SEND] = S_TRADE_MENU_SEND;
	W_FUNCTION[P_TRADE_MENU_SEND].PROC = W_TRADE_MENU_SEND;
	//W_TRADE_END_SEND
	mWorkerPacketSize[P_TRADE_END_SEND] = S_TRADE_END_SEND;
	W_FUNCTION[P_TRADE_END_SEND].PROC = W_TRADE_END_SEND;
	//W_FRIEND_ASK_SEND
	mWorkerPacketSize[P_FRIEND_ASK_SEND] = S_FRIEND_ASK_SEND;
	W_FUNCTION[P_FRIEND_ASK_SEND].PROC = W_FRIEND_ASK_SEND;
	//W_FRIEND_CANCEL_SEND
	mWorkerPacketSize[P_FRIEND_CANCEL_SEND] = S_FRIEND_CANCEL_SEND;
	W_FUNCTION[P_FRIEND_CANCEL_SEND].PROC = W_FRIEND_CANCEL_SEND;
	//W_FRIEND_ANSWER_SEND
	mWorkerPacketSize[P_FRIEND_ANSWER_SEND] = S_FRIEND_ANSWER_SEND;
	W_FUNCTION[P_FRIEND_ANSWER_SEND].PROC = W_FRIEND_ANSWER_SEND;
	//W_FRIEND_MAKE_SEND
	mWorkerPacketSize[P_FRIEND_MAKE_SEND] = S_FRIEND_MAKE_SEND;
	W_FUNCTION[P_FRIEND_MAKE_SEND].PROC = W_FRIEND_MAKE_SEND;
	//W_FRIEND_FIND_SEND
	mWorkerPacketSize[P_FRIEND_FIND_SEND] = S_FRIEND_FIND_SEND;
	W_FUNCTION[P_FRIEND_FIND_SEND].PROC = W_FRIEND_FIND_SEND;
	//W_FRIEND_DELETE_SEND
	mWorkerPacketSize[P_FRIEND_DELETE_SEND] = S_FRIEND_DELETE_SEND;
	W_FUNCTION[P_FRIEND_DELETE_SEND].PROC = W_FRIEND_DELETE_SEND;
	//W_TEACHER_ASK_SEND
	mWorkerPacketSize[P_TEACHER_ASK_SEND] = S_TEACHER_ASK_SEND;
	W_FUNCTION[P_TEACHER_ASK_SEND].PROC = W_TEACHER_ASK_SEND;
	//W_TEACHER_CANCEL_SEND
	mWorkerPacketSize[P_TEACHER_CANCEL_SEND] = S_TEACHER_CANCEL_SEND;
	W_FUNCTION[P_TEACHER_CANCEL_SEND].PROC = W_TEACHER_CANCEL_SEND;
	//W_TEACHER_ANSWER_SEND
	mWorkerPacketSize[P_TEACHER_ANSWER_SEND] = S_TEACHER_ANSWER_SEND;
	W_FUNCTION[P_TEACHER_ANSWER_SEND].PROC = W_TEACHER_ANSWER_SEND;
	//W_TEACHER_START_SEND
	mWorkerPacketSize[P_TEACHER_START_SEND] = S_TEACHER_START_SEND;
	W_FUNCTION[P_TEACHER_START_SEND].PROC = W_TEACHER_START_SEND;
	//W_TEACHER_END_SEND
	mWorkerPacketSize[P_TEACHER_END_SEND] = S_TEACHER_END_SEND;
	W_FUNCTION[P_TEACHER_END_SEND].PROC = W_TEACHER_END_SEND;
	//W_TEACHER_STATE_SEND
	mWorkerPacketSize[P_TEACHER_STATE_SEND] = S_TEACHER_STATE_SEND;
	W_FUNCTION[P_TEACHER_STATE_SEND].PROC = W_TEACHER_STATE_SEND;
	//W_PARTY_ASK_SEND
	mWorkerPacketSize[P_PARTY_ASK_SEND] = S_PARTY_ASK_SEND;
	W_FUNCTION[P_PARTY_ASK_SEND].PROC = W_PARTY_ASK_SEND;
	//W_PARTY_CANCEL_SEND
	mWorkerPacketSize[P_PARTY_CANCEL_SEND] = S_PARTY_CANCEL_SEND;
	W_FUNCTION[P_PARTY_CANCEL_SEND].PROC = W_PARTY_CANCEL_SEND;
    //W_PARTY_ANSWER_SEND
	mWorkerPacketSize[P_PARTY_ANSWER_SEND] = S_PARTY_ANSWER_SEND;
	W_FUNCTION[P_PARTY_ANSWER_SEND].PROC = W_PARTY_ANSWER_SEND;
	//W_PARTY_MAKE_SEND
	mWorkerPacketSize[P_PARTY_MAKE_SEND] = S_PARTY_MAKE_SEND;
	W_FUNCTION[P_PARTY_MAKE_SEND].PROC = W_PARTY_MAKE_SEND;
	//W_PARTY_JOIN_SEND
	mWorkerPacketSize[P_PARTY_JOIN_SEND] = S_PARTY_JOIN_SEND;
	W_FUNCTION[P_PARTY_JOIN_SEND].PROC = W_PARTY_JOIN_SEND;
	//W_PARTY_CHAT_SEND
	mWorkerPacketSize[P_PARTY_CHAT_SEND] = S_PARTY_CHAT_SEND;
	W_FUNCTION[P_PARTY_CHAT_SEND].PROC = W_PARTY_CHAT_SEND;
	//W_PARTY_LEAVE_SEND
	mWorkerPacketSize[P_PARTY_LEAVE_SEND] = S_PARTY_LEAVE_SEND;
	W_FUNCTION[P_PARTY_LEAVE_SEND].PROC = W_PARTY_LEAVE_SEND;
	//W_PARTY_EXILE_SEND
	mWorkerPacketSize[P_PARTY_EXILE_SEND] = S_PARTY_EXILE_SEND;
	W_FUNCTION[P_PARTY_EXILE_SEND].PROC = W_PARTY_EXILE_SEND;
	//W_PARTY_OUT_INFO_SEND
	/*
	mWorkerPacketSize[P_PARTY_OUT_INFO_SEND] = S_PARTY_OUT_INFO_SEND;
	W_FUNCTION[P_PARTY_OUT_INFO_SEND].PROC = W_PARTY_OUT_INFO_SEND;
	*/
	//W_PARTY_INFO_SEND
	mWorkerPacketSize[P_PARTY_INFO_SEND] = S_PARTY_INFO_SEND;
	W_FUNCTION[P_PARTY_INFO_SEND].PROC = W_PARTY_INFO_SEND;
	//W_PARTY_BREAK_SEND
	mWorkerPacketSize[P_PARTY_BREAK_SEND] = S_PARTY_BREAK_SEND;
	W_FUNCTION[P_PARTY_BREAK_SEND].PROC = W_PARTY_BREAK_SEND;
	//W_GUILD_ASK_SEND
	mWorkerPacketSize[P_GUILD_ASK_SEND] = S_GUILD_ASK_SEND;
	W_FUNCTION[P_GUILD_ASK_SEND].PROC = W_GUILD_ASK_SEND;
	//W_GUILD_CANCEL_SEND
	mWorkerPacketSize[P_GUILD_CANCEL_SEND] = S_GUILD_CANCEL_SEND;
	W_FUNCTION[P_GUILD_CANCEL_SEND].PROC = W_GUILD_CANCEL_SEND;
	//W_GUILD_ANSWER_SEND
	mWorkerPacketSize[P_GUILD_ANSWER_SEND] = S_GUILD_ANSWER_SEND;
	W_FUNCTION[P_GUILD_ANSWER_SEND].PROC = W_GUILD_ANSWER_SEND;
	//W_GUILD_WORK_SEND
	mWorkerPacketSize[P_GUILD_WORK_SEND] = S_GUILD_WORK_SEND;
	W_FUNCTION[P_GUILD_WORK_SEND].PROC = W_GUILD_WORK_SEND;
	//W_GUILD_NOTICE_SEND
	mWorkerPacketSize[P_GUILD_NOTICE_SEND] = S_GUILD_NOTICE_SEND;
	W_FUNCTION[P_GUILD_NOTICE_SEND].PROC = W_GUILD_NOTICE_SEND;
	//W_GUILD_CHAT_SEND
	mWorkerPacketSize[P_GUILD_CHAT_SEND] = S_GUILD_CHAT_SEND;
	W_FUNCTION[P_GUILD_CHAT_SEND].PROC = W_GUILD_CHAT_SEND;
	//W_GUILD_FIND_SEND
	mWorkerPacketSize[P_GUILD_FIND_SEND] = S_GUILD_FIND_SEND;
	W_FUNCTION[P_GUILD_FIND_SEND].PROC = W_GUILD_FIND_SEND;
	//W_TRIBE_WORK_SEND
	mWorkerPacketSize[P_TRIBE_WORK_SEND] = S_TRIBE_WORK_SEND;
	W_FUNCTION[P_TRIBE_WORK_SEND].PROC = W_TRIBE_WORK_SEND;
	//W_TRIBE_NOTICE_SEND
	mWorkerPacketSize[P_TRIBE_NOTICE_SEND] = S_TRIBE_NOTICE_SEND;
	W_FUNCTION[P_TRIBE_NOTICE_SEND].PROC = W_TRIBE_NOTICE_SEND;
	//W_TRIBE_CHAT_SEND
	mWorkerPacketSize[P_TRIBE_CHAT_SEND] = S_TRIBE_CHAT_SEND;
	W_FUNCTION[P_TRIBE_CHAT_SEND].PROC = W_TRIBE_CHAT_SEND;
	//W_TRIBE_BANK_SEND
	mWorkerPacketSize[P_TRIBE_BANK_SEND] = S_TRIBE_BANK_SEND;
	W_FUNCTION[P_TRIBE_BANK_SEND].PROC = W_TRIBE_BANK_SEND;
	//W_TRIBE_VOTE_SEND
	mWorkerPacketSize[P_TRIBE_VOTE_SEND] = S_TRIBE_VOTE_SEND;
	W_FUNCTION[P_TRIBE_VOTE_SEND].PROC = W_TRIBE_VOTE_SEND;
	//W_CHECK_HACK_INFO
	mWorkerPacketSize[P_CHECK_HACK_INFO] = S_CHECK_HACK_INFO;
	W_FUNCTION[P_CHECK_HACK_INFO].PROC = W_CHECK_HACK_INFO;
	//W_CHECK_N_PROTECT_2
#ifdef __N_PROTECT__
	mWorkerPacketSize[P_CHECK_N_PROTECT_2] = S_CHECK_N_PROTECT_2;
	W_FUNCTION[P_CHECK_N_PROTECT_2].PROC = W_CHECK_N_PROTECT_2;
#endif
	mWorkerPacketSize[CTOZ_CHECK_AUTH_KEY_TYPE] = CTOZ_CHECK_AUTH_KEY_SIZE;
	W_FUNCTION[CTOZ_CHECK_AUTH_KEY_TYPE].PROC = W_CHECK_AUTH_KEY;

	mWorkerPacketSize[CTOZ_UPDATE_AUTH_KEY_TYPE] = CTOZ_UPDATE_AUTH_KEY_SIZE;
	W_FUNCTION[CTOZ_UPDATE_AUTH_KEY_TYPE].PROC = W_UPDATE_AUTH_KEY;

	mWorkerPacketSize[CTOZ_ACK_INCOMING_UDP_TYPE] = CTOZ_ACK_INCOMING_UDP_SIZE;
	W_FUNCTION[CTOZ_ACK_INCOMING_UDP_TYPE].PROC = W_ACK_INCOMING_UDP;

	mWorkerPacketSize[CTOZ_REQUEST_PRESENT_TYPE] = CTOZ_REQUEST_PRESENT_SIZE;
	W_FUNCTION[CTOZ_REQUEST_PRESENT_TYPE].PROC = W_REQUEST_PRESENT;

	mWorkerPacketSize[CTOZ_CHANGE_PLAYTIMETOTEACHERPOINT_TYPE] = CTOZ_CHANGE_PLAYTIMETOTEACHERPOINT_SIZE;
	W_FUNCTION[CTOZ_CHANGE_PLAYTIMETOTEACHERPOINT_TYPE].PROC = W_CHANGE_PLAYTIMETOTEACHERPOINT;

	/* Mir added 08.12.12 */
	mWorkerPacketSize[P_CHECK_EVENT_INFO_RECV] = S_CHECK_EVENT_INFO_RECV;
	W_FUNCTION[P_CHECK_EVENT_INFO_RECV].PROC = W_CHECK_EVENT_INFO;
	/* end */
	mWorkerPacketSize[P_PTOZ_GET_RANK_INFO] = S_PTOZ_GET_RANK_INFO;
	W_FUNCTION[P_PTOZ_GET_RANK_INFO].PROC = W_GET_RANK_INFO;

	mWorkerPacketSize[P_CHANGE_AUTO_INFO] = S_CHANGE_AUTO_INFO;
	W_FUNCTION[P_CHANGE_AUTO_INFO].PROC = W_CHANGE_AUTO_INFO;

#ifdef __ANIMAL__
	//W_ANIMAL_STATE_SEND
	mWorkerPacketSize[P_ANIMAL_STATE_SEND] = S_ANIMAL_STATE_SEND;
	W_FUNCTION[P_ANIMAL_STATE_SEND].PROC = W_ANIMAL_STATE_SEND;
#endif
	//W_MEDAL_EXCHANGE_SEND
	mWorkerPacketSize[P_MEDAL_EXCHANGE_SEND] = S_MEDAL_EXCHANGE_SEND;
	W_FUNCTION[P_MEDAL_EXCHANGE_SEND].PROC = W_MEDAL_EXCHANGE_SEND;


	//@{ auto quiz
	mWorkerPacketSize[ P_CORRECT_ANSWER ] = S_CORRECT_ANSWER;	
	W_FUNCTION[ P_CORRECT_ANSWER ].PROC = W_CORRECT_ANSWER;
	//@}

    // @ Cost Info Download @
    //W_GET_CASH_ITEM_INFO_SEND
    mWorkerPacketSize[P_GET_CASH_ITEM_INFO_SEND] = S_GET_CASH_ITEM_INFO_SEND;
    W_FUNCTION[P_GET_CASH_ITEM_INFO_SEND].PROC = W_GET_CASH_ITEM_INFO_SEND;
    // @

    // # Defense Hack # {
    mWorkerPacketSize[P_SPEED_HACK_SEND] = S_SPEED_HACK_SEND;
    W_FUNCTION[P_SPEED_HACK_SEND].PROC = W_SPEED_HACK_SEND;
    // # }

	/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
	mWorkerPacketSize[CTOZ_TOGGLE_STOPWATCH_TYPE] = CTOZ_TOGGLE_STOPWATCH_TYPESIZE;
	W_FUNCTION[CTOZ_TOGGLE_STOPWATCH_TYPE].PROC = W_TOGGLE_STOPWATCH;
	/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */

	return TRUE;
}
//FREE
void MyWork::Free( void )
{
}
//-------------------------------------------------------------------------------------------------
