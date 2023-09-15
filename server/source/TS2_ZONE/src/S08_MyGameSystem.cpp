//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "H01_MainApplication.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_LEVELSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
LEVELSYSTEM mLEVEL;
//CREATE
LEVELSYSTEM::LEVELSYSTEM( void )
{
	int index01;

	for( index01 = 0 ; index01 < MAX_LIMIT_LEVEL_NUM ; index01++ )
	{
		mGainExpInfoForKillOtherTribe[index01] = 0.0f;
	}
	mGainExpInfoForKillOtherTribe[  0] =  40.0f;
	mGainExpInfoForKillOtherTribe[  1] =  40.0f;
	mGainExpInfoForKillOtherTribe[  2] =  40.0f;
	mGainExpInfoForKillOtherTribe[  3] =  40.0f;
	mGainExpInfoForKillOtherTribe[  4] =  40.0f;
	mGainExpInfoForKillOtherTribe[  5] =  40.0f;
	mGainExpInfoForKillOtherTribe[  6] =  40.0f;
	mGainExpInfoForKillOtherTribe[  7] =  40.0f;
	mGainExpInfoForKillOtherTribe[  8] =  40.0f;
	mGainExpInfoForKillOtherTribe[  9] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 10] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 11] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 12] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 13] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 14] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 15] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 16] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 17] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 18] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 19] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 20] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 21] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 22] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 23] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 24] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 25] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 26] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 27] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 28] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 29] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 30] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 31] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 32] =  40.0f;
	mGainExpInfoForKillOtherTribe[ 33] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 34] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 35] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 36] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 37] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 38] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 39] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 40] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 41] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 42] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 43] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 44] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 45] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 46] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 47] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 48] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 49] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 50] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 51] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 52] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 53] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 54] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 55] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 56] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 57] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 58] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 59] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 60] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 61] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 62] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 63] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 64] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 65] =  50.0f;
	mGainExpInfoForKillOtherTribe[ 66] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 67] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 68] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 69] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 70] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 71] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 72] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 73] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 74] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 75] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 76] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 77] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 78] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 79] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 80] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 81] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 82] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 83] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 84] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 85] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 86] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 87] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 88] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 89] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 90] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 91] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 92] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 93] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 94] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 95] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 96] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 97] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 98] =  60.0f;
	mGainExpInfoForKillOtherTribe[ 99] =  66.0f;
	mGainExpInfoForKillOtherTribe[100] =  66.0f;
	mGainExpInfoForKillOtherTribe[101] =  66.0f;
	mGainExpInfoForKillOtherTribe[102] =  66.0f;
	mGainExpInfoForKillOtherTribe[103] =  72.0f;
	mGainExpInfoForKillOtherTribe[104] =  72.0f;
	mGainExpInfoForKillOtherTribe[105] =  72.0f;
	mGainExpInfoForKillOtherTribe[106] =  78.0f;
	mGainExpInfoForKillOtherTribe[107] =  78.0f;
	mGainExpInfoForKillOtherTribe[108] =  78.0f;
	mGainExpInfoForKillOtherTribe[109] =  84.0f;
	mGainExpInfoForKillOtherTribe[110] =  84.0f;
	mGainExpInfoForKillOtherTribe[111] =  84.0f;
	mGainExpInfoForKillOtherTribe[112] =  90.0f;
	mGainExpInfoForKillOtherTribe[113] =  90.0f;
	mGainExpInfoForKillOtherTribe[114] =  90.0f;
	mGainExpInfoForKillOtherTribe[115] =  90.0f;
	mGainExpInfoForKillOtherTribe[116] =  90.0f;
	mGainExpInfoForKillOtherTribe[117] =  90.0f;
	mGainExpInfoForKillOtherTribe[118] =  90.0f;
	mGainExpInfoForKillOtherTribe[119] =  90.0f;
	mGainExpInfoForKillOtherTribe[120] =  90.0f;
	mGainExpInfoForKillOtherTribe[121] =  90.0f;
	mGainExpInfoForKillOtherTribe[122] =  90.0f;
	mGainExpInfoForKillOtherTribe[123] = 100.0f;
	mGainExpInfoForKillOtherTribe[124] = 100.0f;
	mGainExpInfoForKillOtherTribe[125] = 100.0f;
	mGainExpInfoForKillOtherTribe[126] = 100.0f;
	mGainExpInfoForKillOtherTribe[127] = 100.0f;
	mGainExpInfoForKillOtherTribe[128] = 100.0f;
	mGainExpInfoForKillOtherTribe[129] = 100.0f;
	mGainExpInfoForKillOtherTribe[130] = 100.0f;
	mGainExpInfoForKillOtherTribe[131] = 100.0f;
	mGainExpInfoForKillOtherTribe[132] = 100.0f;
	mGainExpInfoForKillOtherTribe[133] = 100.0f;
	mGainExpInfoForKillOtherTribe[134] = 110.0f;
	mGainExpInfoForKillOtherTribe[135] = 110.0f;
	mGainExpInfoForKillOtherTribe[136] = 110.0f;
	mGainExpInfoForKillOtherTribe[137] = 110.0f;
	mGainExpInfoForKillOtherTribe[138] = 110.0f;
	mGainExpInfoForKillOtherTribe[139] = 110.0f;
	mGainExpInfoForKillOtherTribe[140] = 110.0f;
	mGainExpInfoForKillOtherTribe[141] = 110.0f;
	mGainExpInfoForKillOtherTribe[142] = 110.0f;
	mGainExpInfoForKillOtherTribe[143] = 110.0f;
	mGainExpInfoForKillOtherTribe[144] = 110.0f;
#ifdef __GOD__
	mGainExpInfoForKillOtherTribe[145] = 330.0f;
	mGainExpInfoForKillOtherTribe[146] = 330.0f;
	mGainExpInfoForKillOtherTribe[147] = 330.0f;
	mGainExpInfoForKillOtherTribe[148] = 330.0f;
	mGainExpInfoForKillOtherTribe[149] = 360.0f;
	mGainExpInfoForKillOtherTribe[150] = 360.0f;
	mGainExpInfoForKillOtherTribe[151] = 360.0f;
	mGainExpInfoForKillOtherTribe[152] = 360.0f;
	mGainExpInfoForKillOtherTribe[153] = 390.0f;
	mGainExpInfoForKillOtherTribe[154] = 390.0f;
	mGainExpInfoForKillOtherTribe[155] = 390.0f;
	mGainExpInfoForKillOtherTribe[156] = 390.0f;
	mRangeForHigh[ 0] =  962105896;
	mRangeForHigh[ 1] = 1000590131;
	mRangeForHigh[ 2] = 1040613736;
	mRangeForHigh[ 3] = 1082238285;
	mRangeForHigh[ 4] = 1125527816;
	mRangeForHigh[ 5] = 1170548928;
	mRangeForHigh[ 6] = 1217370885;
	mRangeForHigh[ 7] = 1266065720;
	mRangeForHigh[ 8] = 1316708348;
	mRangeForHigh[ 9] = 1369376681;
	mRangeForHigh[10] = 1424151748;
	mRangeForHigh[11] = 1481117817;
#endif
}
//CHECK_VALID_ELEMENT
BOOL LEVELSYSTEM::CheckValidElement( int tArrayIndex )
{
	if( ( mDATA[tArrayIndex].lIndex < 1 ) || ( mDATA[tArrayIndex].lIndex > MAX_LIMIT_LEVEL_NUM ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( mDATA[tArrayIndex].lIndex != ( tArrayIndex + 1 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].lRangeInfo[0] < 0 ) || ( mDATA[tArrayIndex].lRangeInfo[0] > MAX_NUMBER_SIZE ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].lRangeInfo[1] < 1 ) || ( mDATA[tArrayIndex].lRangeInfo[1] > MAX_NUMBER_SIZE ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( mDATA[tArrayIndex].lRangeInfo[0] >= mDATA[tArrayIndex].lRangeInfo[1] )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( tArrayIndex < 144 )
	{
		if( mDATA[tArrayIndex].lRangeInfo[1] != ( mDATA[( tArrayIndex + 1 )].lRangeInfo[0] - 1 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].lRangeInfo[2] < 0 ) || ( mDATA[tArrayIndex].lRangeInfo[2] > 100 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].lAttackPower < 0 ) || ( mDATA[tArrayIndex].lAttackPower > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].lDefensePower < 0 ) || ( mDATA[tArrayIndex].lDefensePower > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].lAttackSuccess < 0 ) || ( mDATA[tArrayIndex].lAttackSuccess > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].lAttackBlock < 0 ) || ( mDATA[tArrayIndex].lAttackBlock > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].lElementAttack < 0 ) || ( mDATA[tArrayIndex].lElementAttack > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].lLife < 0 ) || ( mDATA[tArrayIndex].lLife > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].lMana < 0 ) || ( mDATA[tArrayIndex].lMana > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	return TRUE;
}
//INIT
BOOL LEVELSYSTEM::Init( char *tFileName )
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE *tOriginal;
	DWORD tCompressSize;
	BYTE *tCompress;
	int tDataNum;

	Free();
#ifdef __WIN32__
	HANDLE hFile;
	hFile = CreateFile( tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}
	if( !ReadFile( hFile, &tOriginalSize, 4, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != 4 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	tOriginal = (BYTE *) GlobalAlloc( GMEM_FIXED, tOriginalSize );
	if( tOriginal == NULL )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !ReadFile( hFile, &tCompressSize, 4, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != 4 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	tCompress = (BYTE *) GlobalAlloc( GMEM_FIXED, tCompressSize );
	if( tCompress == NULL )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !ReadFile( hFile, tCompress, tCompressSize, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != tCompressSize )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !CloseHandle( hFile ) )
	{
		return FALSE;
	}
	if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	{
		return FALSE;
	}
	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	if( tDataNum != MAX_LIMIT_LEVEL_NUM )
	{
		return FALSE;
	}
	CopyMemory( &mDATA[0], &tOriginal[4], ( tDataNum * sizeof( LEVEL_INFO ) ) );
	GlobalFree( tCompress );
	GlobalFree( tOriginal );
#else
	FILE *r_fp = NULL;

	if(!(r_fp = fopen(tFileName, "r"))) {
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if((nReadByte = fread(&tOriginalSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	tOriginal = (BYTE *) calloc(1, tOriginalSize );
	if( tOriginal == NULL )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if((nReadByte = fread(&tCompressSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	tCompress = (BYTE *)calloc(1, tCompressSize );

	if( tCompress == NULL )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if((nReadByte = fread(tCompress, 1, tCompressSize, r_fp)) < 0) {
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if( nReadByte != tCompressSize )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	fclose(r_fp);

	if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	
	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	if( tDataNum != MAX_LIMIT_LEVEL_NUM )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	CopyMemory( &mDATA[0], &tOriginal[4], ( tDataNum * sizeof( LEVEL_INFO ) ) );
	free( tCompress );
	free( tOriginal );
#endif
	for( index01 = 0 ; index01 < tDataNum ; index01++ )
	{
		if( !CheckValidElement( index01 ) )
		{
			LOG_TO_FILE_2("! [%s] %d" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//FREE
void LEVELSYSTEM::Free( void )
{
}
//RETURN_LEVEL
int LEVELSYSTEM::ReturnLevel( int tGeneralExperience )
{
	int index01;

	if( tGeneralExperience < mDATA[0].lRangeInfo[0] )
	{
		return 1;
	}
	for( index01 = 0 ; index01 < ( MAX_LIMIT_LEVEL_NUM - 1 ) ; index01++ )
	{
		if( ( tGeneralExperience >= mDATA[index01].lRangeInfo[0] ) && ( tGeneralExperience <= mDATA[index01].lRangeInfo[1] ) )
		{
			return ( index01 + 1 );
		}
	}
	return MAX_LIMIT_LEVEL_NUM;
}
//RETURN_LEVEL_FACTOR_1
int LEVELSYSTEM::ReturnLevelFactor1( int tLevel )
{
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
	{
		return 0;
	}
	return mDATA[( tLevel - 1 )].lRangeInfo[0];
}
//RETURN_LEVEL_FACTOR_2
int LEVELSYSTEM::ReturnLevelFactor2( int tLevel )
{
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
	{
		return 0;
	}
	return mDATA[( tLevel - 1 )].lRangeInfo[1];
}
//RETURN_LEVEL_FACTOR_3
int LEVELSYSTEM::ReturnLevelFactor3( int tLevel )
{
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
	{
		return 0;
	}
#if 0
	for(int i = 0; i < 145; i++) {
		LOG_TO_FILE_2("===> %d %d\n", i, mDATA[( i )].lRangeInfo[2]);
	}
#endif
	return mDATA[( tLevel - 1 )].lRangeInfo[2];
}
//RETURN_LEVEL_FACTOR_ATTACK_POWER
int LEVELSYSTEM::ReturnLevelFactorAttackPower( int tLevel )
{
#ifdef __GOD__
	if( ( tLevel < 1 ) || ( tLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) )
#else
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if(tLevel > MAX_LIMIT_LEVEL_NUM )
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[( tLevel - 1 )].lAttackPower;
}
//RETURN_LEVEL_FACTOR_DEFENSE_POWER
int LEVELSYSTEM::ReturnLevelFactorDefensePower( int tLevel )
{
#ifdef __GOD__
	if( ( tLevel < 1 ) || ( tLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) )
#else
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if(tLevel > MAX_LIMIT_LEVEL_NUM )
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[( tLevel - 1 )].lDefensePower;
}
//RETURN_LEVEL_FACTOR_ATTACK_SUCCESS
int LEVELSYSTEM::ReturnLevelFactorAttackSuccess( int tLevel )
{
#ifdef __GOD__
	if( ( tLevel < 1 ) || ( tLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) )
#else
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if(tLevel > MAX_LIMIT_LEVEL_NUM )
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[( tLevel - 1 )].lAttackSuccess;
}
//RETURN_LEVEL_FACTOR_ATTACK_BLOCK
int LEVELSYSTEM::ReturnLevelFactorAttackBlock( int tLevel )
{
#ifdef __GOD__
	if( ( tLevel < 1 ) || ( tLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) )
#else
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if(tLevel > MAX_LIMIT_LEVEL_NUM )
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[( tLevel - 1 )].lAttackBlock;
}
//RETURN_LEVEL_FACTOR_ELEMENT_ATTACK
int LEVELSYSTEM::ReturnLevelFactorElementAttack( int tLevel )
{
#ifdef __GOD__
	if( ( tLevel < 1 ) || ( tLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) )
#else
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if(tLevel > MAX_LIMIT_LEVEL_NUM )
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[( tLevel - 1 )].lElementAttack;
}
//RETURN_LEVEL_FACTOR_LIFE
int LEVELSYSTEM::ReturnLevelFactorLife( int tLevel )
{
#ifdef __GOD__
	if( ( tLevel < 1 ) || ( tLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) )
#else
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if(tLevel > MAX_LIMIT_LEVEL_NUM )
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[( tLevel - 1 )].lLife;
}
//RETURN_LEVEL_FACTOR_MANA
int LEVELSYSTEM::ReturnLevelFactorMana( int tLevel )
{
#ifdef __GOD__
	if( ( tLevel < 1 ) || ( tLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) )
#else
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_LEVEL_NUM ) )
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if(tLevel > MAX_LIMIT_LEVEL_NUM )
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[( tLevel - 1 )].lMana;
}

#ifdef __GOD__
//RETURN_HIGH_EXP_VALUE
int LEVELSYSTEM::ReturnHighExpValue( int tLevel )
{
	if( ( tLevel < 1 ) || ( tLevel > MAX_LIMIT_HIGH_LEVEL_NUM ) )
	{
		return 0;
	}
	return mRangeForHigh[( tLevel - 1 )];
}
#endif

//RETURN_GAIN_EXP_FOR_KILL_OTHER_TRIBE
int LEVELSYSTEM::ReturnGainExpForKillOtherTribe( int tAttackLevel, int tDefenseLevel )
{
#ifdef __GOD__
	if( ( tAttackLevel < 1 ) || ( tAttackLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) || ( tDefenseLevel < 1 ) || ( tDefenseLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) || ( ( tAttackLevel - tDefenseLevel ) > 9 ) )
#else
	if( ( tAttackLevel < 1 ) || ( tAttackLevel > MAX_LIMIT_LEVEL_NUM ) || ( tDefenseLevel < 1 ) || ( tDefenseLevel > MAX_LIMIT_LEVEL_NUM ) || ( ( tAttackLevel - tDefenseLevel ) > 9 ) )
#endif
	{
		return 0;
	}
	if( tAttackLevel < tDefenseLevel )
	{
		return (int) ( mGainExpInfoForKillOtherTribe[( tDefenseLevel - 1 )] + ( mGainExpInfoForKillOtherTribe[( tDefenseLevel - 1 )] * ( (float) ( tDefenseLevel - tAttackLevel ) * 0.1f ) ) );
	}
	else
	{
		return (int) ( mGainExpInfoForKillOtherTribe[( tDefenseLevel - 1 )] - ( mGainExpInfoForKillOtherTribe[( tDefenseLevel - 1 )] * ( (float) ( tAttackLevel - tDefenseLevel ) * 0.1f ) ) );
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_ITEMSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
ITEMSYSTEM mITEM;
//CREATE
ITEMSYSTEM::ITEMSYSTEM( void )
{
	int index01;
	int index02;
	int index03;

	mDataNum = 0;
	mDATA = NULL;
	for( index01 = 0 ; index01 < MAX_LIMIT_LEVEL_NUM ; index01++ )
	{
		for( index02 = 0 ; index02 < 4 ; index02++ )
		{
			for( index03 = 0 ; index03 < 22 ; index03++ )
			{
				mPartNum[index01][index02][index03] = 0;
				mPART[index01][index02][index03] = NULL;
			}
		}
	}
	//mSharedMemMap = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL ITEMSYSTEM::CheckValidElement( int tArrayIndex )
{
	int index01;
	int index02;

	if( mDATA[tArrayIndex].iIndex == 0 )
	{
		return TRUE;
	}
	if( ( mDATA[tArrayIndex].iIndex < 1 ) || ( mDATA[tArrayIndex].iIndex > 99999 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( mDATA[tArrayIndex].iIndex != ( tArrayIndex + 1 ) )
	{
		LOG_TO_FILE_2("! [%s] %d " , __FUNCTION__ , __LINE__);
		LOG_TO_FILE_2("!iIndex = %d , tArrayIndex = %d \n" ,  mDATA[tArrayIndex].iIndex , tArrayIndex);
		return FALSE;
	}
	for( index01 = 0 ; index01 < 25 ; index01++ )
	{
		if( mDATA[tArrayIndex].iName[index01] == '\0' )
		{
			break;
		}
	}
	if( index01 == 25 )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	for( index01 = 0 ; index01 < 3 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].iDescription[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].iType < 1 ) || ( mDATA[tArrayIndex].iType > 4 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iSort < 1 ) || ( mDATA[tArrayIndex].iSort > 22 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iDataNumber2D < 1 ) || ( mDATA[tArrayIndex].iDataNumber2D > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iDataNumber3D < 0 ) || ( mDATA[tArrayIndex].iDataNumber3D > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iAddDataNumber3D < 0 ) || ( mDATA[tArrayIndex].iAddDataNumber3D > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iLevel < 1 ) || ( mDATA[tArrayIndex].iLevel > MAX_LIMIT_LEVEL_NUM ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	if( ( mDATA[tArrayIndex].iMartialLevel < 0 ) || ( mDATA[tArrayIndex].iMartialLevel > 12 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
#endif
	if( ( mDATA[tArrayIndex].iEquipInfo[0] < 1 ) || ( mDATA[tArrayIndex].iEquipInfo[0] > 4 ) )
	{
		LOG_TO_FILE_2("! [%s] %d" , __FUNCTION__ , __LINE__);
		LOG_TO_FILE_1("iEquipInfo[0] =  %d\n" ,mDATA[tArrayIndex].iEquipInfo[0]);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iEquipInfo[1] < 1 ) || ( mDATA[tArrayIndex].iEquipInfo[1] > 14 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iBuyCost < 1 ) || ( mDATA[tArrayIndex].iBuyCost > MAX_NUMBER_SIZE ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iSellCost < 0 ) || ( mDATA[tArrayIndex].iSellCost > MAX_NUMBER_SIZE ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iLevelLimit < 1 ) || ( mDATA[tArrayIndex].iLevelLimit > MAX_LIMIT_LEVEL_NUM ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	if( ( mDATA[tArrayIndex].iMartialLevelLimit < 0 ) || ( mDATA[tArrayIndex].iMartialLevelLimit > 12 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
#endif
	if( ( mDATA[tArrayIndex].iCheckMonsterDrop < 1 ) || ( mDATA[tArrayIndex].iCheckMonsterDrop > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckNPCSell < 1 ) || ( mDATA[tArrayIndex].iCheckNPCSell > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckNPCShop < 1 ) || ( mDATA[tArrayIndex].iCheckNPCShop > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckAvatarDrop < 1 ) || ( mDATA[tArrayIndex].iCheckAvatarDrop > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckAvatarTrade < 1 ) || ( mDATA[tArrayIndex].iCheckAvatarTrade > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckAvatarShop < 1 ) || ( mDATA[tArrayIndex].iCheckAvatarShop > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckImprove < 1 ) || ( mDATA[tArrayIndex].iCheckImprove > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckHighImprove < 1 ) || ( mDATA[tArrayIndex].iCheckHighImprove > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckHighItem < 1 ) || ( mDATA[tArrayIndex].iCheckHighItem > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckLowItem < 1 ) || ( mDATA[tArrayIndex].iCheckLowItem > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCheckExchange < 1 ) || ( mDATA[tArrayIndex].iCheckExchange > 2 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iStrength < 0 ) || ( mDATA[tArrayIndex].iStrength > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iWisdom < 0 ) || ( mDATA[tArrayIndex].iWisdom > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iVitality < 0 ) || ( mDATA[tArrayIndex].iVitality > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iKi < 0 ) || ( mDATA[tArrayIndex].iKi > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iLuck < 0 ) || ( mDATA[tArrayIndex].iLuck > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iAttackPower < 0 ) || ( mDATA[tArrayIndex].iAttackPower > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iDefensePower < 0 ) || ( mDATA[tArrayIndex].iDefensePower > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iAttackSucess < 0 ) || ( mDATA[tArrayIndex].iAttackSucess > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iAttackBlock < 0 ) || ( mDATA[tArrayIndex].iAttackBlock > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iElementAttackPower < 0 ) || ( mDATA[tArrayIndex].iElementAttackPower > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iElementDefensePower < 0 ) || ( mDATA[tArrayIndex].iElementDefensePower > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCritical < 0 ) || ( mDATA[tArrayIndex].iCritical > 100 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
    // Potion Type add 11 -> 13
    /** 2009. 10. 26 : DarkAttack Potion add (wolf) */
	if( ( mDATA[tArrayIndex].iPotionType[0] < 0 ) || ( mDATA[tArrayIndex].iPotionType[0] > 13 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iPotionType[1] < 0 ) || ( mDATA[tArrayIndex].iPotionType[1] > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( mDATA[tArrayIndex].iPotionType[0] == 9 )
	{
		if( ( mDATA[tArrayIndex].iPotionType[1] < 1 ) || ( mDATA[tArrayIndex].iPotionType[1] > 3 ) )
		{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].iGainSkillNumber < 0 ) || ( mDATA[tArrayIndex].iGainSkillNumber > 300 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iLastAttackBonusInfo[0] < 0 ) || ( mDATA[tArrayIndex].iLastAttackBonusInfo[0] > 100 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iLastAttackBonusInfo[1] < 0 ) || ( mDATA[tArrayIndex].iLastAttackBonusInfo[1] > 1000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCapeInfo[0] < 0 ) || ( mDATA[tArrayIndex].iCapeInfo[0] > 100 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCapeInfo[1] < 0 ) || ( mDATA[tArrayIndex].iCapeInfo[1] > 100 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].iCapeInfo[2] < 0 ) || ( mDATA[tArrayIndex].iCapeInfo[2] > 100 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	for( index01 = 0 ; index01 < 8 ; index01++ )
#else
	for( index01 = 0 ; index01 < 5 ; index01++ )
#endif
	{
		if( ( mDATA[tArrayIndex].iBonusSkillInfo[index01][0] < 0 ) || ( mDATA[tArrayIndex].iBonusSkillInfo[index01][0] > 300 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].iBonusSkillInfo[index01][1] < 0 ) || ( mDATA[tArrayIndex].iBonusSkillInfo[index01][1] > 100 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL ITEMSYSTEM::Init( char *tFileName )
{
	int index01;
	int index02;
	int index03;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE *tOriginal;
	DWORD tCompressSize;
	BYTE *tCompress;
	int tDataNum;
	ITEM_INFO *tDATA;
	int tLevel;
	int tType;
	int tSort;
	BOOL tCheckFirstCreate;

	Free();

	FILE *r_fp = NULL;
	if(!(r_fp = fopen(tFileName, "r"))) {
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if((nReadByte = fread(&tOriginalSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	tOriginal = (BYTE *)calloc(1, tOriginalSize );
	if( tOriginal == NULL )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if((nReadByte = fread(&tCompressSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	tCompress = (BYTE *) calloc(1, tCompressSize );
	if( tCompress == NULL )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if((nReadByte = fread(tCompress, 1, tCompressSize, r_fp)) < 0) {
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	if( nReadByte != tCompressSize )
	{
		fclose(r_fp);
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	fclose(r_fp);

	if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	mSharedMemSize += 4;
	if( tDataNum != 99999 )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	tDATA = (ITEM_INFO *) calloc(1, ( tDataNum * sizeof( ITEM_INFO ) ) );
	if( tDATA == NULL )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	CopyMemory( &tDATA[0], &tOriginal[4], ( tDataNum * sizeof( ITEM_INFO ) ) );
	mSharedMemSize += ( tDataNum * sizeof( ITEM_INFO ) );
	free( tCompress );
	free( tOriginal );
	mDataNum = tDataNum;
	mDATA = tDATA;
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( !CheckValidElement( index01 ) )
		{
			LOG_TO_FILE_3("! [%s] %d , index = %d \n" , __FUNCTION__ , __LINE__ , index01);
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( mDATA[index01].iIndex == 0 )
		{
			continue;
		}
		tLevel = mDATA[index01].iLevel - 1;
		tType = mDATA[index01].iType - 1;
		tSort = mDATA[index01].iSort - 1;
		mPartNum[tLevel][tType][tSort]++;
	}
	for( index01 = 0 ; index01 < MAX_LIMIT_LEVEL_NUM ; index01++ )
	{
		for( index02 = 0 ; index02 < 4 ; index02++ )
		{
			for( index03 = 0 ; index03 < 22 ; index03++ )
			{
				mSharedMemSize += 4;
				if( mPartNum[index01][index02][index03] < 1 )
				{
					continue;
				}
				mSharedMemSize += ( mPartNum[index01][index02][index03] * 4 );
				mPART[index01][index02][index03] = (int *) calloc( 1, ( mPartNum[index01][index02][index03] * 4 ) );
				if( mPART[index01][index02][index03] == NULL )
				{
					LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
					return FALSE;
				}
				mPartNum[index01][index02][index03] = 0;
			}
		}
	}
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( mDATA[index01].iIndex == 0 )
		{
			continue;
		}
		tLevel = mDATA[index01].iLevel - 1;
		tType = mDATA[index01].iType - 1;
		tSort = mDATA[index01].iSort - 1;
		mPART[tLevel][tType][tSort][mPartNum[tLevel][tType][tSort]] = index01;
		mPartNum[tLevel][tType][tSort]++;
	}

	mSharedMemMap = shmget((key_t)KEY_SHM_ITEM, mSharedMemSize, 0600 | IPC_CREAT);
	//mSharedMemMap = shmget((key_t)KEY_SHM_ITEM, mSharedMemSize, 0600 | IPC_CREAT | IPC_EXCL);
	if(mSharedMemMap < 0) {
		if(errno != EEXIST) {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		} else {
			mSharedMemMap = shmget((key_t)KEY_SHM_ITEM, mSharedMemSize, 0);
			if(mSharedMemMap < 0)
				LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
				return FALSE;
		}
		tCheckFirstCreate = FALSE;
	} else {
		/*
		mSharedMemMap = shmget((key_t)KEY_SHM_ITEM, mSharedMemSize, 0);
		if(mSharedMemMap < 0) 
			return FALSE;
		*/
		tCheckFirstCreate = TRUE;
	}

	mSharedPostMem = (BYTE *)shmat(mSharedMemMap, (char *)0, 0);
	if( mSharedPostMem == NULL ) {
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}

	mSharedMemSizeForCheck = 0;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4 );
	}
	CopyMemory( &mSharedItemData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4 );
	mSharedMemSizeForCheck += 4;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], mDATA, ( mDataNum * sizeof( ITEM_INFO ) ) );
	}
	mSharedItemData.mDATA = (ITEM_INFO *) &mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += ( mDataNum * sizeof( ITEM_INFO ) );
	for( index01 = 0 ; index01 < MAX_LIMIT_LEVEL_NUM ; index01++ )
	{
		for( index02 = 0 ; index02 < 4 ; index02++ )
		{
			for( index03 = 0 ; index03 < 22 ; index03++ )
			{
				if( tCheckFirstCreate )
				{
					CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], &mPartNum[index01][index02][index03], 4 );
				}
				CopyMemory( &mSharedItemData.mPartNum[index01][index02][index03], &mSharedPostMem[mSharedMemSizeForCheck], 4 );
				mSharedMemSizeForCheck += 4;
			}
		}
	}
	for( index01 = 0 ; index01 < MAX_LIMIT_LEVEL_NUM ; index01++ )
	{
		for( index02 = 0 ; index02 < 4 ; index02++ )
		{
			for( index03 = 0 ; index03 < 22 ; index03++ )
			{
				if( mPartNum[index01][index02][index03] < 1 )
				{
					continue;
				}
				if( tCheckFirstCreate )
				{
					CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], mPART[index01][index02][index03], ( mPartNum[index01][index02][index03] * 4 ) );
				}
				mSharedItemData.mPART[index01][index02][index03] = (int *) &mSharedPostMem[mSharedMemSizeForCheck];
				mSharedMemSizeForCheck += ( mPartNum[index01][index02][index03] * 4 );
			}
		}
	}
	if( mSharedMemSize != mSharedMemSizeForCheck )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	mDataNum = 0;
	if( mDATA )
	{
		free( mDATA );
		mDATA = NULL;
	}
	for( index01 = 0 ; index01 < MAX_LIMIT_LEVEL_NUM ; index01++ )
	{
		for( index02 = 0 ; index02 < 4 ; index02++ )
		{
			for( index03 = 0 ; index03 < 22 ; index03++ )
			{
				mPartNum[index01][index02][index03] = 0;
				if( mPART[index01][index02][index03] )
				{
					free( mPART[index01][index02][index03] );
					mPART[index01][index02][index03] = NULL;
				}
			}
		}
	}

	return TRUE;
}
//FREE
void ITEMSYSTEM::Free( void )
{
	int index01;
	int index02;
	int index03;

	mDataNum = 0;
	if( mDATA )
	{
#ifdef __WIN32__
		GlobalFree( mDATA );
#else
		free( mDATA );
#endif
		mDATA = NULL;
	}
	for( index01 = 0 ; index01 < MAX_LIMIT_LEVEL_NUM ; index01++ )
	{
		for( index02 = 0 ; index02 < 4 ; index02++ )
		{
			for( index03 = 0 ; index03 < 22 ; index03++ )
			{
				mPartNum[index01][index02][index03] = 0;
				if( mPART[index01][index02][index03] )
				{
#ifdef __WIN32__
					GlobalFree( mPART[index01][index02][index03] );
#else
					free( mPART[index01][index02][index03] );
#endif
					mPART[index01][index02][index03] = NULL;
				}
			}
		}
	}
	if( mSharedPostMem != NULL )
	{
#ifdef __WIN32__
		UnmapViewOfFile( mSharedPostMem );
#else 
		shmdt(mSharedPostMem);
#endif
		mSharedPostMem = NULL;
	}
	if( mSharedMemMap != 0 )
	{
#ifdef __WIN32__
		CloseHandle( mSharedMemMap );
		mSharedMemMap = NULL;
#else 
		shmctl(mSharedMemMap, IPC_RMID, 0);
		mSharedMemMap = 0;
#endif
	}
}
//SEARCH
ITEM_INFO * ITEMSYSTEM::Search( int iIndex )
{
	if( ( iIndex < 1 ) || ( iIndex > mSharedItemData.mDataNum ) )
	{
		return NULL;
	}
	if( mSharedItemData.mDATA[( iIndex - 1 )].iIndex == 0 )
	{
		return NULL;
	}
	return &mSharedItemData.mDATA[( iIndex - 1 )];
}
//RETURN
ITEM_INFO * ITEMSYSTEM::Return( int iLevel, int iType, int iSort )
{
#ifdef __GOD__
	if( ( iLevel < 1 ) || ( iLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) || ( iType < 1 ) || ( iType > 5 ) || ( iSort < 1 ) || ( iSort > 22 ) )
#else
	if( ( iLevel < 1 ) || ( iLevel > MAX_LIMIT_LEVEL_NUM ) || ( iType < 1 ) || ( iType > 5 ) || ( iSort < 1 ) || ( iSort > 22 ) )
#endif
	{
		return NULL;
	}
#ifdef __GOD__
	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];

	if( iLevel <= MAX_LIMIT_LEVEL_NUM )
	{
#endif
		if( mSharedItemData.mPartNum[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )] < 1 )
		{
			return NULL;
		}
#ifdef __GOD__
		if( iLevel < MAX_LIMIT_LEVEL_NUM )
		{
			return &mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )][( rand() % mSharedItemData.mPartNum[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )] )]];
		}
		tTotalSearchItemNum = 0;
		for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )] ; index01++ )
		{
			if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )][index01]].iMartialLevel == 0 )
			{
				if( tTotalSearchItemNum < 1000 )
				{
					tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )][index01];
					tTotalSearchItemNum++;
				}
			}
		}
		if( tTotalSearchItemNum == 0 )
		{
			return NULL;
		}
		return &mSharedItemData.mDATA[tSearchItemIndex[( rand() % tTotalSearchItemNum )]];
	}
	if( mSharedItemData.mPartNum[( MAX_LIMIT_LEVEL_NUM - 1 )][( iType - 1 )][( iSort - 1 )] < 1 )
	{
		return NULL;
	}
	tTotalSearchItemNum = 0;
	for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( MAX_LIMIT_LEVEL_NUM - 1 )][( iType - 1 )][( iSort - 1 )] ; index01++ )
	{
		if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( iType - 1 )][( iSort - 1 )][index01]].iMartialLevel == ( iLevel - MAX_LIMIT_LEVEL_NUM ) )
		{
			if( tTotalSearchItemNum < 1000 )
			{
				tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( iType - 1 )][( iSort - 1 )][index01];
				tTotalSearchItemNum++;
			}
		}
	}
	if( tTotalSearchItemNum == 0 )
	{
		return NULL;
	}
#endif
	unsigned int tRandom = 0;
	tRandom = rand_mir();
#ifdef __GOD__
	return &mSharedItemData.mDATA[tSearchItemIndex[( tRandom % tTotalSearchItemNum )]];
#else
	return &mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )][( tRandom % mSharedItemData.mPartNum[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )] )]];
#endif
}
//RETURN
ITEM_INFO * ITEMSYSTEM::Return( int iLevel, int iType, int iSort, ITEM_INFO *tITEM_INFO )
{
#ifdef __GOD__
	if( ( iLevel < 1 ) || ( iLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) || ( iType < 1 ) || ( iType > 4 ) || ( iSort < 1 ) || ( iSort > 22 ) || ( tITEM_INFO == NULL ) )
#else
	if( ( iLevel < 1 ) || ( iLevel > MAX_LIMIT_LEVEL_NUM ) || ( iType < 1 ) || ( iType > 4 ) || ( iSort < 1 ) || ( iSort > 22 ) || ( tITEM_INFO == NULL ) )
#endif
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];
	unsigned int tRandom = 0;

#ifdef __GOD__
	if( iLevel <= MAX_LIMIT_LEVEL_NUM )
	{
		tTotalSearchItemNum = 0;
		for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )] ; index01++ )
		{
			if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0] )
			{
				if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )][index01]].iMartialLevel == 0 )
				{
					if( tTotalSearchItemNum < 1000 )
					{
						tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )][index01];
						tTotalSearchItemNum++;
					}
				}
			}
		}
		if( tTotalSearchItemNum == 0 )
		{
			return NULL;
		}
		return &mSharedItemData.mDATA[tSearchItemIndex[( rand() % tTotalSearchItemNum )]];
	}
	tTotalSearchItemNum = 0;
	for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( MAX_LIMIT_LEVEL_NUM - 1 )][( iType - 1 )][( iSort - 1 )] ; index01++ )
	{
		if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( iType - 1 )][( iSort - 1 )][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0] )
		{
			if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( iType - 1 )][( iSort - 1 )][index01]].iMartialLevel == ( iLevel - MAX_LIMIT_LEVEL_NUM ) )
			{
				if( tTotalSearchItemNum < 1000 )
				{
					tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( iType - 1 )][( iSort - 1 )][index01];
					tTotalSearchItemNum++;
				}
			}
		}
	}
#else
	tTotalSearchItemNum = 0;
	for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )] ; index01++ )
	{
		if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0] )
		{
			if( tTotalSearchItemNum < 1000 )
			{
				tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( iLevel - 1 )][( iType - 1 )][( iSort - 1 )][index01];
				tTotalSearchItemNum++;
			}
		}
	}
#endif
	if( tTotalSearchItemNum == 0 )
	{
		return NULL;
	}
	tRandom = rand_mir();
	return &mSharedItemData.mDATA[tSearchItemIndex[( tRandom % tTotalSearchItemNum )]];
}

#ifdef __GOD__
//RETURN_1
ITEM_INFO * ITEMSYSTEM::Return_1( int iLevel, ITEM_INFO *tITEM_INFO )
{
	if( ( iLevel < 1 ) || ( iLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) || ( tITEM_INFO == NULL ) )
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];
	unsigned int tRandom = 0;

	if( iLevel <= MAX_LIMIT_LEVEL_NUM )
	{
		tTotalSearchItemNum = 0;
		for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )] ; index01++ )
		{
			if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0] )
			{
				if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iMartialLevel == 0 )
				{
					if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0] )
					{
						if( tTotalSearchItemNum < 1000 )
						{
							tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01];
							tTotalSearchItemNum++;
						}
					}
					else
					{
						if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iBonusSkillInfo[1][0] == tITEM_INFO->iBonusSkillInfo[0][0] )
						{
							if( tTotalSearchItemNum < 1000 )
							{
								tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01];
								tTotalSearchItemNum++;
							}
						}
					}
				}
			}
		}
		if( tTotalSearchItemNum == 0 )
		{
			return NULL;
		}
		tRandom = rand_mir();
		return &mSharedItemData.mDATA[tSearchItemIndex[( tRandom % tTotalSearchItemNum )]];
	}

	tTotalSearchItemNum = 0;
	for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )] ; index01++ )
	{
		if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0] )
		{
			if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iMartialLevel == ( iLevel - MAX_LIMIT_LEVEL_NUM ) )
			{
				if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0] )
				{
					if( tTotalSearchItemNum < 1000 )
					{
						tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01];
						tTotalSearchItemNum++;
					}
				}
				else
				{
					if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iBonusSkillInfo[1][0] == tITEM_INFO->iBonusSkillInfo[0][0] )
					{
						if( tTotalSearchItemNum < 1000 )
						{
							tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01];
							tTotalSearchItemNum++;
						}
					}
				}
			}
		}
	}
	if( tTotalSearchItemNum == 0 )
	{
		return NULL;
	}
	tRandom = rand_mir();
	return &mSharedItemData.mDATA[tSearchItemIndex[( tRandom % tTotalSearchItemNum )]];
}
#endif

#ifdef __GOD__
//RETURN_2
ITEM_INFO * ITEMSYSTEM::Return_2( int iLevel, ITEM_INFO *tITEM_INFO )
{
	if( ( iLevel < 1 ) || ( iLevel > ( MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ) ) || ( tITEM_INFO == NULL ) )
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	unsigned int tRandom = 0;
	int tSearchItemIndex[1000];

	if( iLevel <= MAX_LIMIT_LEVEL_NUM )
	{
		tTotalSearchItemNum = 0;
		for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )] ; index01++ )
		{
			if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0] )
			{
				if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iMartialLevel == 0 )
				{
					if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0] )
					{
						if( tTotalSearchItemNum < 1000 )
						{
							tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01];
							tTotalSearchItemNum++;
						}
					}
				}
			}
		}
		if( tTotalSearchItemNum == 0 )
		{
			return NULL;
		}
		tRandom = rand_mir();
		return &mSharedItemData.mDATA[tSearchItemIndex[( tRandom % tTotalSearchItemNum )]];
	}

	tTotalSearchItemNum = 0;
	for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )] ; index01++ )
	{
		if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0] )
		{
			if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iMartialLevel == ( iLevel - MAX_LIMIT_LEVEL_NUM ) )
			{
				if( mSharedItemData.mDATA[mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0] )
				{
					if( tTotalSearchItemNum < 1000 )
					{
						tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( MAX_LIMIT_LEVEL_NUM - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01];
						tTotalSearchItemNum++;
					}
				}
			}
		}
	}
	if( tTotalSearchItemNum == 0 )
	{
		return NULL;
	}
	tRandom = rand_mir();
	return &mSharedItemData.mDATA[tSearchItemIndex[( tRandom % tTotalSearchItemNum )]];	
}
#else
//RETURN
ITEM_INFO * ITEMSYSTEM::Return( int iLevel, ITEM_INFO *tITEM_INFO )
{
	if( ( iLevel < 1 ) || ( iLevel > MAX_LIMIT_LEVEL_NUM ) || ( tITEM_INFO == NULL ) )
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];
	unsigned int tRandom = 0;

	tTotalSearchItemNum = 0;
	for( index01 = 0 ; index01 < mSharedItemData.mPartNum[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )] ; index01++ )
	{
		if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0] )
		{
			if( mSharedItemData.mDATA[mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0] )
			{
				if( tTotalSearchItemNum < 1000 )
				{
					tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[( iLevel - 1 )][( tITEM_INFO->iType - 1 )][( tITEM_INFO->iSort - 1 )][index01];
					tTotalSearchItemNum++;
				}
			}
		}
	}
	if( tTotalSearchItemNum == 0 )
	{
		return NULL;
	}
	tRandom = rand_mir();
	return &mSharedItemData.mDATA[tSearchItemIndex[( tRandom % tTotalSearchItemNum )]];
}
#endif
ITEM_INFO* ITEMSYSTEM::ReturnRareItem (int iTribe, int iLevel)
{
    int iSortNum = 0;
    int iSort[9] = {0, };
	unsigned int tRandom = 0;
    ITEM_INFO* pItemInfoPtr = NULL;

    iSort[0] = 7;   // ....
    iSort[1] = 9;   // ...
    iSort[2] = 10;  // ...
    iSort[3] = 11;  // ...
    iSort[4] = 12;  // ...

    switch (iTribe) {
        case 0: // ...
            iSort[5] = 13;  // ..
            iSort[6] = 14;  // ..
            iSort[7] = 15;  // ...
            break;
        case 1: // ...
            iSort[5] = 16;  // ...
            iSort[6] = 17;  // ...
            iSort[7] = 18;  // ...
            break;
        case 2: // ...
            iSort[5] = 19;  // ...
            iSort[6] = 20;  // ...
            iSort[7] = 21;  // ....
            break;
        default: // .. ...
            return NULL;
    }

	tRandom = rand_mir();
    iSortNum = iSort[tRandom % 8];

    while (true) {
        pItemInfoPtr = Return (iLevel, 3, iSortNum);
        if (pItemInfoPtr != NULL) {
            if ((pItemInfoPtr -> iEquipInfo[0] == 1) || ((pItemInfoPtr -> iEquipInfo[0] - 2) == iTribe)) 
                break;

            pItemInfoPtr = NULL;
        }
    }

    return pItemInfoPtr;
}

ITEM_INFO* ITEMSYSTEM::ReturnRareItem (int iTribe, int iType, int iLevel)
{
    int iSortNum = 0;
    int iSort[9] = {0, };
	unsigned int tRandom = 0;
    ITEM_INFO* pItemInfoPtr = NULL;

    iSort[0] = 7;   // ....
    iSort[1] = 9;   // ...
    iSort[2] = 10;  // ...
    iSort[3] = 11;  // ...
    iSort[4] = 12;  // ...

    switch (iTribe) {
        case 0: // ...
            iSort[5] = 13;  // ..
            iSort[6] = 14;  // ..
            iSort[7] = 15;  // ...
            break;
        case 1: // ...
            iSort[5] = 16;  // ...
            iSort[6] = 17;  // ...
            iSort[7] = 18;  // ...
            break;
        case 2: // ...
            iSort[5] = 19;  // ...
            iSort[6] = 20;  // ...
            iSort[7] = 21;  // ....
            break;
        default: // .. ...
            return NULL;
    }

	tRandom = rand_mir();
    iSortNum = iSort[tRandom % 8];

    while (true) {
        pItemInfoPtr = Return (iLevel, iType, iSortNum);
        if (pItemInfoPtr != NULL) {
            if ((pItemInfoPtr -> iEquipInfo[0] == 1) || ((pItemInfoPtr -> iEquipInfo[0] - 2) == iTribe)) 
                break;

            pItemInfoPtr = NULL;
        }
    }

    return pItemInfoPtr;
}

ITEM_INFO* ITEMSYSTEM::GetResultItemPtrByGigabyteItem (void)
{
    int iRandom = 0, iResultItemIndex = 0;
    iRandom = rand_mir() % 1000;
    if (iRandom < 450) // 45.00%
        iResultItemIndex = 3;
    else if (iRandom < 700) // 25.00%
        iResultItemIndex = 4;
    else if (iRandom < 800) // 10.00%
        iResultItemIndex = 27;
    else if (iRandom < 860) // 6.00%
        iResultItemIndex = 28;
    else if (iRandom < 900) // 4.00%
        iResultItemIndex = 23;
    else if (iRandom < 930) // 3.00%
        iResultItemIndex = 29;
    else if (iRandom < 955) // 2.50%
        iResultItemIndex = 24;
    else if (iRandom < 975) // 2.00%
        iResultItemIndex = 30;
    else if (iRandom < 990) // 1.50%
        iResultItemIndex = 32;
    else 
        iResultItemIndex = 33;

    return Search (iResultItemIndex);
}

ITEM_INFO* ITEMSYSTEM::GetMoneyBy1WonLuckyBag (void)
{
    int iRandom = 0;
	int tItemIndex = 0;
    iRandom = rand_mir() % 10000;
    if (iRandom < 3000) {
		tItemIndex = 1308;
	}
	else if (iRandom < 3350){
		tItemIndex = 1310;
	}
	else if (iRandom < 5350){
		tItemIndex = 1019;
	}
	else if (iRandom < 6350){
		tItemIndex = 1045;
	}
	else if (iRandom < 8150){
		tItemIndex = 1020;
	}
	else if (iRandom < 8950){
		tItemIndex = 1036;
	}
	else if (iRandom < 9950){
		tItemIndex = 1021;
	}
	else if (iRandom < 9999){
		tItemIndex = 1035;
	}
	else{
		tItemIndex = 1103;
	}
    return Search (tItemIndex); // ....
}

ITEM_INFO* ITEMSYSTEM::GetPresentItemPtrByGoodwillAmbassador (int& iCounts)
{
	 return NULL;
    int iRandom = 0;

    iCounts = 0;
    iRandom = rand_mir() % 1000;

	if (iRandom < 400) {
		return Search (1036);     // ... (.).
	} else if (iRandom < 700) {
		return Search (1037);     // ... (.)
	} else if (iRandom < 900) {
		return Search (1022);   // ... (9%)
	} else if (iRandom < 990) {
#ifdef __TK__
		return Search (1023);   // 1. ....
#else
		return Search (1047);   // 1. ....
#endif
	} else {
		return Search (1108);   // . ...
	}
    return NULL;
}

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_SKILLSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
SKILLSYSTEM mSKILL;
//CREATE
SKILLSYSTEM::SKILLSYSTEM( void )
{
	mDataNum = 0;
	mDATA = NULL;
}
//CHECK_VALID_ELEMENT
BOOL SKILLSYSTEM::CheckValidElement( int tArrayIndex )
{
	int index01;
	int index02;

	if( mDATA[tArrayIndex].sIndex == 0 )
	{
		return TRUE;
	}
	if( ( mDATA[tArrayIndex].sIndex < 1 ) || ( mDATA[tArrayIndex].sIndex > 300 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( mDATA[tArrayIndex].sIndex != ( tArrayIndex + 1 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	for( index01 = 0 ; index01 < 25 ; index01++ )
	{
		if( mDATA[tArrayIndex].sName[index01] == '\0' )
		{
			break;
		}
	}
	if( index01 == 25 )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	for( index01 = 0 ; index01 < 10 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].sDescription[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].sType < 1 ) || ( mDATA[tArrayIndex].sType > 4 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].sAttackType < 1 ) || ( mDATA[tArrayIndex].sAttackType > 5 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].sDataNumber2D < 1 ) || ( mDATA[tArrayIndex].sDataNumber2D > 10000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].sTribeInfo[0] < 1 ) || ( mDATA[tArrayIndex].sTribeInfo[0] > 4 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].sTribeInfo[1] < 1 ) || ( mDATA[tArrayIndex].sTribeInfo[1] > 10 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].sLearnSkillPoint < 1 ) || ( mDATA[tArrayIndex].sLearnSkillPoint > 1000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].sMaxUpgradePoint < 1 ) || ( mDATA[tArrayIndex].sMaxUpgradePoint > 1000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].sTotalHitNumber < 0 ) || ( mDATA[tArrayIndex].sTotalHitNumber > 10 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].sValidRadius < 0 ) || ( mDATA[tArrayIndex].sValidRadius > 1000 ) )
	{
		LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	for( index01 = 0 ; index01 < 2 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sManaUse < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sManaUse > 10000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[0] < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[0] > 10000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[1] < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[1] > 10000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sStunAttack < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sStunAttack > 100 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sStunDefense < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sStunDefense > 100 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sFastRunSpeed < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sFastRunSpeed > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[0] < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[0] > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[1] < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[1] > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[2] < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[2] > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sRunTime < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sRunTime > 10000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sChargingDamageUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sChargingDamageUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackPowerUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackPowerUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sDefensePowerUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sDefensePowerUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackSuccessUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackSuccessUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackBlockUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackBlockUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sElementAttackUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sElementAttackUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sElementDefenseUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sElementDefenseUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackSpeedUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sAttackSpeedUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sRunSpeedUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sRunSpeedUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sShieldLifeUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sShieldLifeUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sLuckUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sLuckUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sCriticalUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sCriticalUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sReturnSuccessUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sReturnSuccessUp > 10000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sStunDefenseUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sStunDefenseUp > 1000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].sGradeInfo[index01].sDestroySuccessUp < 0 ) || ( mDATA[tArrayIndex].sGradeInfo[index01].sDestroySuccessUp > 10000 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL SKILLSYSTEM::Init( char *tFileName )
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE *tOriginal;
	DWORD tCompressSize;
	BYTE *tCompress;
	int tDataNum;
	SKILL_INFO *tDATA;

	Free();
	 FILE *r_fp = NULL;
	 if(!(r_fp = fopen(tFileName, "r"))) {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 return FALSE;
	 }

	 if((nReadByte = fread(&tOriginalSize, 1, 4, r_fp)) < 0) {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 fclose(r_fp);
		 return FALSE;
	 }

	 if( nReadByte != 4 )
	 {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 fclose(r_fp);
		 return FALSE;
	 }

	 tOriginal = (BYTE *)calloc(1, tOriginalSize );
	 if( tOriginal == NULL )
	 {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 fclose(r_fp);
		 return FALSE;
	 }

	 if((nReadByte = fread(&tCompressSize, 1, 4, r_fp)) < 0) {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 fclose(r_fp);
		 return FALSE;
	 }

	 if( nReadByte != 4 )
	 {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 fclose(r_fp);
		 return FALSE;
	 }

	 tCompress = (BYTE *) calloc(1, tCompressSize );

	 if( tCompress == NULL )
	 {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 fclose(r_fp);
		 return FALSE;
	 }

	 if((nReadByte = fread(tCompress, 1, tCompressSize, r_fp)) < 0) {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 fclose(r_fp);
		 return FALSE;
	 }

	 if( nReadByte != tCompressSize )
	 {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 fclose(r_fp);
		 return FALSE;
	 }
		 fclose(r_fp);

	 if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	 {
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		 return FALSE;
	 }

	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	if( tDataNum != 300 )
	{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	tDATA = (SKILL_INFO *)calloc(1, ( tDataNum * sizeof( SKILL_INFO ) ) );
	if( tDATA == NULL )
	{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
		return FALSE;
	}
	CopyMemory( &tDATA[0], &tOriginal[4], ( tDataNum * sizeof( SKILL_INFO ) ) );
	free( tCompress );
	free( tOriginal );

	mDataNum = tDataNum;
	mDATA = tDATA;
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( !CheckValidElement( index01 ) )
		{
			LOG_TO_FILE_2("! [%s] %d\n" , __FUNCTION__ , __LINE__);
			return FALSE;
		}
	}	
	return TRUE;
}
//FREE
void SKILLSYSTEM::Free( void )
{
	mDataNum = 0;
	if( mDATA )
	{
		free( mDATA );
		mDATA = NULL;
	}
}
//SEARCH
SKILL_INFO * SKILLSYSTEM::Search( int sIndex )
{
	if( ( sIndex < 1 ) || ( sIndex > mDataNum ) )
	{
		return NULL;
	}
	if( mDATA[( sIndex - 1 )].sIndex == 0 )
	{
		return NULL;
	}
	return &mDATA[( sIndex - 1 )];
}
//RETURN_ATTACK_TYPE
int SKILLSYSTEM::ReturnAttackType( int sIndex )
{
	SKILL_INFO *tSKILL_INFO;

	tSKILL_INFO = Search( sIndex );
	if( tSKILL_INFO == NULL )
	{
		return 0;
	}
	return tSKILL_INFO->sAttackType;
}
//RETURN_TOTAL_HIT_NUMBER
int SKILLSYSTEM::ReturnTotalHitNumber( int sIndex )
{
	SKILL_INFO *tSKILL_INFO;

	tSKILL_INFO = Search( sIndex );
	if( tSKILL_INFO == NULL )
	{
		return 0;
	}
	return tSKILL_INFO->sTotalHitNumber;
}
//RETURN_SKILL_VALUE
float SKILLSYSTEM::ReturnSkillValue( int sIndex, int sPoint, int sFactor )
{
	SKILL_INFO *tSKILL_INFO;
	int tMinValue;
	int tMaxValue;
	float tValue;

	tSKILL_INFO = Search( sIndex );
	if( tSKILL_INFO == NULL )
	{
		return 0.0f;
	}
	if( sPoint < 1 )
	{
		return 0.0f;
	}
	switch( sFactor )
	{
	case  1 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sManaUse;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sManaUse;
		break;
	case  2 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRecoverInfo[0];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRecoverInfo[0];
		break;
	case  3 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRecoverInfo[1];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRecoverInfo[1];
		break;
	case  4 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sStunAttack;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sStunAttack;
		break;
	case  5 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sStunDefense;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sStunDefense;
		break;
	case  6 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sFastRunSpeed;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sFastRunSpeed;
		break;
	case  7 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackInfo[0];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackInfo[0];
		break;
	case  8 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackInfo[1];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackInfo[1];
		break;
	case  9 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackInfo[2];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackInfo[2];
		break;
	case 10 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRunTime;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRunTime;
		break;
	case 11 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sChargingDamageUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sChargingDamageUp;
		break;
	case 12 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackPowerUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackPowerUp;
		break;
	case 13 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sDefensePowerUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sDefensePowerUp;
		break;
	case 14 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackSuccessUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackSuccessUp;
		break;
	case 15 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackBlockUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackBlockUp;
		break;
	case 16 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sElementAttackUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sElementAttackUp;
		break;
	case 17 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sElementDefenseUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sElementDefenseUp;
		break;
	case 18 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackSpeedUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackSpeedUp;
		break;
	case 19 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRunSpeedUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRunSpeedUp;
		break;
	case 20 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sShieldLifeUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sShieldLifeUp;
		break;
	case 21 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sLuckUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sLuckUp;
		break;
	case 22 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sCriticalUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sCriticalUp;
		break;
	case 23 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sReturnSuccessUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sReturnSuccessUp;
		break;
	case 24 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sStunDefenseUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sStunDefenseUp;
		break;
	case 25 :
		tMinValue = tSKILL_INFO->sGradeInfo[0].sDestroySuccessUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sDestroySuccessUp;
		break;
	default :
		return 0.0f;
	}
	tValue = (float) tMinValue + (float) ( ( tMaxValue - tMinValue ) * sPoint ) / (float) tSKILL_INFO->sMaxUpgradePoint;
	if( tValue <= 0.0f )
	{
		return 0.0f;
	}
	if( tValue < 1.0f )
	{
		return 1.0f;
	}
	return tValue;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MONSTERSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
MONSTERSYSTEM mMONSTER;
//CREATE
MONSTERSYSTEM::MONSTERSYSTEM( void )
{
	mDataNum = 0;
	mDATA = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL MONSTERSYSTEM::CheckValidElement( int tArrayIndex )
{
	int index01;
	int index02;

	if( mDATA[tArrayIndex].mIndex == 0 )
	{
		return TRUE;
	}
	if( ( mDATA[tArrayIndex].mIndex < 1 ) || ( mDATA[tArrayIndex].mIndex > 10000 ) )
	{
		return FALSE;
	}
	if( mDATA[tArrayIndex].mIndex != ( tArrayIndex + 1 ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 25 ; index01++ )
	{
		if( mDATA[tArrayIndex].mName[index01] == '\0' )
		{
			break;
		}
	}
	if( index01 == 25 )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 2 ; index01++ )
	{
		for( index02 = 0 ; index02 < 101 ; index02++ )
		{
			if( mDATA[tArrayIndex].mChatInfo[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 101 )
		{
			return FALSE;
		}
	}
#ifdef __GOD__
	if( ( mDATA[tArrayIndex].mType < 1 ) || ( mDATA[tArrayIndex].mType > 13 ) )
#else
	if( ( mDATA[tArrayIndex].mType < 1 ) || ( mDATA[tArrayIndex].mType > 9 ) )
#endif
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mSpecialType < 1 ) || ( mDATA[tArrayIndex].mSpecialType > 44 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mDamageType < 1 ) || ( mDATA[tArrayIndex].mDamageType > 2 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mDataSortNumber < 1 ) || ( mDATA[tArrayIndex].mDataSortNumber > 10000 ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 3 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].mSize[index01] < 1 ) || ( mDATA[tArrayIndex].mSize[index01] > 1000 ) )
		{
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].mSize[3] < 0 ) || ( mDATA[tArrayIndex].mSize[3] > 1000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mSizeCategory < 1 ) || ( mDATA[tArrayIndex].mSizeCategory > 4 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mCheckCollision < 1 ) || ( mDATA[tArrayIndex].mCheckCollision > 2 ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 6 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].mFrameInfo[index01] < 1 ) || ( mDATA[tArrayIndex].mFrameInfo[index01] > 10000 ) )
		{
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].mTotalHitNum < 0 ) || ( mDATA[tArrayIndex].mTotalHitNum > 3 ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 3 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].mHitFrame[index01] < 0 ) || ( mDATA[tArrayIndex].mHitFrame[index01] > 10000 ) )
		{
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].mTotalSkillHitNum < 0 ) || ( mDATA[tArrayIndex].mTotalSkillHitNum > 3 ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 3 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].mSkillHitFrame[index01] < 0 ) || ( mDATA[tArrayIndex].mSkillHitFrame[index01] > 10000 ) )
		{
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].mBulletInfo[0] < 1 ) || ( mDATA[tArrayIndex].mBulletInfo[0] > 10000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mBulletInfo[1] < 1 ) || ( mDATA[tArrayIndex].mBulletInfo[1] > 10000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mSummonTime[0] < 1 ) || ( mDATA[tArrayIndex].mSummonTime[0] > 1000000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mSummonTime[1] < 1 ) || ( mDATA[tArrayIndex].mSummonTime[1] > 1000000 ) )
	{
		return FALSE;
	}
	if( mDATA[tArrayIndex].mSummonTime[0] > mDATA[tArrayIndex].mSummonTime[1] )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mItemLevel < 1 ) || ( mDATA[tArrayIndex].mItemLevel > MAX_LIMIT_LEVEL_NUM ) )
	{
		return FALSE;
	}
#ifdef __GOD__
	if( ( mDATA[tArrayIndex].mMartialItemLevel < 0 ) || ( mDATA[tArrayIndex].mMartialItemLevel > 12 ) )
	{
		return FALSE;
	}
#endif
	if( ( mDATA[tArrayIndex].mRealLevel < 1 ) || ( mDATA[tArrayIndex].mRealLevel > 1000 ) )
	{
		return FALSE;
	}
#ifdef __GOD__
	if( ( mDATA[tArrayIndex].mMartialRealLevel < 0 ) || ( mDATA[tArrayIndex].mMartialRealLevel > 1000 ) )
	{
		return FALSE;
	}
#endif
	if( ( mDATA[tArrayIndex].mGeneralExperience < 0 ) || ( mDATA[tArrayIndex].mGeneralExperience > 100000000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mPatExperience < 0 ) || ( mDATA[tArrayIndex].mPatExperience > 100000000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mLife < 1 ) || ( mDATA[tArrayIndex].mLife > MAX_NUMBER_SIZE ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mAttackType < 1 ) || ( mDATA[tArrayIndex].mAttackType > 6 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mRadiusInfo[0] < 0 ) || ( mDATA[tArrayIndex].mRadiusInfo[0] > 10000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mRadiusInfo[1] < 0 ) || ( mDATA[tArrayIndex].mRadiusInfo[1] > 10000 ) )
	{
		return FALSE;
	}
	if( mDATA[tArrayIndex].mRadiusInfo[0] > mDATA[tArrayIndex].mRadiusInfo[1] )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mWalkSpeed < 0 ) || ( mDATA[tArrayIndex].mWalkSpeed > 1000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mRunSpeed < 0 ) || ( mDATA[tArrayIndex].mRunSpeed > 1000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mDeathSpeed < 0 ) || ( mDATA[tArrayIndex].mDeathSpeed > 1000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mAttackPower < 0 ) || ( mDATA[tArrayIndex].mAttackPower > 100000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mDefensePower < 0 ) || ( mDATA[tArrayIndex].mDefensePower > 100000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mAttackSuccess < 0 ) || ( mDATA[tArrayIndex].mAttackSuccess > 100000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mAttackBlock < 0 ) || ( mDATA[tArrayIndex].mAttackBlock > 100000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mElementAttackPower < 0 ) || ( mDATA[tArrayIndex].mElementAttackPower > 100000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mElementDefensePower < 0 ) || ( mDATA[tArrayIndex].mElementDefensePower > 100000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mCritical < 0 ) || ( mDATA[tArrayIndex].mCritical > 100 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mFollowInfo[0] < 0 ) || ( mDATA[tArrayIndex].mFollowInfo[0] > 100 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mFollowInfo[1] < 0 ) || ( mDATA[tArrayIndex].mFollowInfo[1] > 100 ) )
	{
		return FALSE;
	}
	if( mDATA[tArrayIndex].mFollowInfo[0] > mDATA[tArrayIndex].mFollowInfo[1] )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mDropMoneyInfo[0] < 0 ) || ( mDATA[tArrayIndex].mDropMoneyInfo[0] > 1000000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mDropMoneyInfo[1] < 0 ) || ( mDATA[tArrayIndex].mDropMoneyInfo[1] > 100000000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mDropMoneyInfo[2] < 0 ) || ( mDATA[tArrayIndex].mDropMoneyInfo[2] > 100000000 ) )
	{
		return FALSE;
	}
	if( mDATA[tArrayIndex].mDropMoneyInfo[1] > mDATA[tArrayIndex].mDropMoneyInfo[2] )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 5 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].mDropPotionInfo[index01][0] < 0 ) || ( mDATA[tArrayIndex].mDropPotionInfo[index01][0] > 1000000 ) )
		{
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].mDropPotionInfo[index01][1] < 0 ) || ( mDATA[tArrayIndex].mDropPotionInfo[index01][1] > 99999 ) )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 12 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].mDropItemInfo[index01] < 0 ) || ( mDATA[tArrayIndex].mDropItemInfo[index01] > 1000000 ) )
		{
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].mDropQuestItemInfo[0] < 0 ) || ( mDATA[tArrayIndex].mDropQuestItemInfo[0] > 1000000 ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].mDropQuestItemInfo[1] < 0 ) || ( mDATA[tArrayIndex].mDropQuestItemInfo[1] > 99999 ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 50 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].mDropExtraItemInfo[index01][0] < 0 ) || ( mDATA[tArrayIndex].mDropExtraItemInfo[index01][0] > 1000000 ) )
		{
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].mDropExtraItemInfo[index01][1] < 0 ) || ( mDATA[tArrayIndex].mDropExtraItemInfo[index01][1] > 99999 ) )
		{
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL MONSTERSYSTEM::Init( char *tFileName )
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE *tOriginal;
	DWORD tCompressSize;
	BYTE *tCompress;
	int tDataNum;
	MONSTER_INFO *tDATA;
	BOOL tCheckFirstCreate;

	Free();
#ifdef __WIN32__
	HANDLE hFile;
	hFile = CreateFile( tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}
	if( !ReadFile( hFile, &tOriginalSize, 4, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != 4 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	tOriginal = (BYTE *) GlobalAlloc( GMEM_FIXED, tOriginalSize );
	if( tOriginal == NULL )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !ReadFile( hFile, &tCompressSize, 4, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != 4 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	tCompress = (BYTE *) GlobalAlloc( GMEM_FIXED, tCompressSize );
	if( tCompress == NULL )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !ReadFile( hFile, tCompress, tCompressSize, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != tCompressSize )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !CloseHandle( hFile ) )
	{
		return FALSE;
	}
	if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	mSharedMemSize += 4;
	if( tDataNum != 10000 )
	{
		return FALSE;
	}
	tDATA = (MONSTER_INFO *) GlobalAlloc( GMEM_FIXED, ( tDataNum * sizeof( MONSTER_INFO ) ) );
	if( tDATA == NULL )
	{
		return FALSE;
	}
	CopyMemory( &tDATA[0], &tOriginal[4], ( tDataNum * sizeof( MONSTER_INFO ) ) );
	mSharedMemSize += ( tDataNum * sizeof( MONSTER_INFO ) );
	GlobalFree( tCompress );
	GlobalFree( tOriginal );
	mDataNum = tDataNum;
	mDATA = tDATA;
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( !CheckValidElement( index01 ) )
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_MONSTERSYSTEM" );
	if ( mSharedMemMap == NULL )
	{
		return FALSE;
	}
	if( GetLastError() != ERROR_ALREADY_EXISTS )
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE *) MapViewOfFile( mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize );
	if( mSharedPostMem == NULL )
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4 );
	}
	CopyMemory( &mSharedMonsterData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4 );
	mSharedMemSizeForCheck += 4;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], mDATA, ( mDataNum * sizeof( MONSTER_INFO ) ) );
	}
	mSharedMonsterData.mDATA = (MONSTER_INFO *) &mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += ( mDataNum * sizeof( MONSTER_INFO ) );
	if( mSharedMemSize != mSharedMemSizeForCheck )
	{
		return FALSE;
	}
	mDataNum = 0;
	if( mDATA )
	{
		GlobalFree( mDATA );
		mDATA = NULL;
	}
#else 
	FILE *r_fp = NULL;
	if(!(r_fp = fopen(tFileName, "r"))) {
		return FALSE;
	}
	//LOG_TO_FILE_1("---------------------------- %p\n", r_fp);

	if((nReadByte = fread(&tOriginalSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		return FALSE;
	}
	//LOG_TO_FILE_2("----------------------------^^;; %d %s\n", tOriginalSize, strerror(errno));

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		return FALSE;
	}

	tOriginal = (BYTE *)calloc(1, tOriginalSize );
	if( tOriginal == NULL )
	{
		fclose(r_fp);
		return FALSE;
	}

	if((nReadByte = fread(&tCompressSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		return FALSE;
	}

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		return FALSE;
	}

	tCompress = (BYTE *) calloc(1, tCompressSize );
	if( tCompress == NULL )
	{
		fclose(r_fp);
		return FALSE;
	}

	if((nReadByte = fread(tCompress, 1, tCompressSize, r_fp)) < 0) {
		fclose(r_fp);
		return FALSE;
	}

	if( nReadByte != tCompressSize )
	{
		fclose(r_fp);
		return FALSE;
	}
		fclose(r_fp);

	if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	//LOG_TO_FILE_3("----------- %d ---%s ---%s\n", tCompressSize, tCompress, tOriginal);

	mSharedMemSize = 0;
	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	mSharedMemSize += 4;
	if( tDataNum != 10000 )
	{
		return FALSE;
	}
	tDATA = (MONSTER_INFO *) calloc(1, ( tDataNum * sizeof( MONSTER_INFO ) ) );
	if( tDATA == NULL )
	{
		return FALSE;
	}
	CopyMemory( &tDATA[0], &tOriginal[4], ( tDataNum * sizeof( MONSTER_INFO ) ) );
	mSharedMemSize += ( tDataNum * sizeof( MONSTER_INFO ) );
	free( tCompress );
	free( tOriginal );
	mDataNum = tDataNum;
	mDATA = tDATA;
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( !CheckValidElement( index01 ) )
		{
			return FALSE;
		}
	}

	mSharedMemMap = shmget((key_t)KEY_SHM_MST, mSharedMemSize, 0600 | IPC_CREAT);
	//mSharedMemMap = shmget((key_t)KEY_SHM_MST, mSharedMemSize, 0600 | IPC_CREAT | IPC_EXCL);
	if(mSharedMemMap < 0) {
		if(errno != EEXIST) {
			return FALSE;
		} else {
			mSharedMemMap = shmget((key_t)KEY_SHM_MST, mSharedMemSize, 0);
			if(mSharedMemMap < 0)
				return FALSE;
		}
		tCheckFirstCreate = FALSE;
	} else {
		/*
		mSharedMemMap = shmget((key_t)KEY_SHM_MST, mSharedMemSize, 0);
		if(mSharedMemMap < 0) 
			return FALSE;
		*/
		tCheckFirstCreate = TRUE;
	}

	mSharedPostMem = (BYTE *)shmat(mSharedMemMap, (char *)0, 0);
	if( mSharedPostMem == NULL ) {
		return FALSE;
	}

	mSharedMemSizeForCheck = 0;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4 );
	}
	CopyMemory( &mSharedMonsterData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4 );
	mSharedMemSizeForCheck += 4;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], mDATA, ( mDataNum * sizeof( MONSTER_INFO ) ) );
	}
	mSharedMonsterData.mDATA = (MONSTER_INFO *) &mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += ( mDataNum * sizeof( MONSTER_INFO ) );
	if( mSharedMemSize != mSharedMemSizeForCheck )
	{
		return FALSE;
	}
	mDataNum = 0;
	if( mDATA )
	{
		free( mDATA );
		mDATA = NULL;
	}
#endif
	return TRUE;
}
//FREE
void MONSTERSYSTEM::Free( void )
{
	mDataNum = 0;
	if( mDATA )
	{
		free( mDATA );
		mDATA = NULL;
	}
	if( mSharedPostMem != NULL )
	{
		//UnmapViewOfFile( mSharedPostMem );
		shmdt( mSharedPostMem );
		mSharedPostMem = NULL;
	}
	if( mSharedMemMap != 0 )
	{
		//CloseHandle( mSharedMemMap );
		shmctl(mSharedMemMap, IPC_RMID, 0);
		mSharedMemMap = 0;
	}
}
//SEARCH
MONSTER_INFO * MONSTERSYSTEM::Search( int mIndex )
{
	if( ( mIndex < 1 ) || ( mIndex > mSharedMonsterData.mDataNum ) )
	{
		return NULL;
	}
	if( mSharedMonsterData.mDATA[( mIndex - 1 )].mIndex == 0 )
	{
		return NULL;
	}
	return &mSharedMonsterData.mDATA[( mIndex - 1 )];
}
//SEARCH
MONSTER_INFO * MONSTERSYSTEM::Search( int tMonsterType, int tMonsterSpecialType )
{
	int index01;

	for( index01 = 0 ; index01 < mSharedMonsterData.mDataNum ; index01++ )
	{
		if( mSharedMonsterData.mDATA[index01].mIndex == 0 )
		{
			continue;
		}
		//LOG_TO_FILE_4("---> %d %d %d %d\n", mSharedMonsterData.mDATA[index01].mType, tMonsterType, mSharedMonsterData.mDATA[index01].mSpecialType, tMonsterSpecialType);
		if( ( mSharedMonsterData.mDATA[index01].mType == tMonsterType ) && ( mSharedMonsterData.mDATA[index01].mSpecialType == tMonsterSpecialType ) )
		{
			return &mSharedMonsterData.mDATA[index01];
		}
	}
	//SVR_TRACE();
	return NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_NPCSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
NPCSYSTEM mNPC;
//CREATE
NPCSYSTEM::NPCSYSTEM( void )
{
	mDataNum = 0;
	mDATA = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL NPCSYSTEM::CheckValidElement( int tArrayIndex )
{
	int index01;
	int index02;
	int index03;
	int index04;

	if( mDATA[tArrayIndex].nIndex == 0 )
	{
		return TRUE;
	}
	if( ( mDATA[tArrayIndex].nIndex < 1 ) || ( mDATA[tArrayIndex].nIndex > 500  ) )
	{
		return FALSE;
	}
	if( mDATA[tArrayIndex].nIndex != ( tArrayIndex + 1 ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 25 ; index01++ )
	{
		if( mDATA[tArrayIndex].nName[index01] == '\0' )
		{
			break;
		}
	}
	if( index01 == 25 )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].nSpeechNum < 1 ) || ( mDATA[tArrayIndex].nSpeechNum > 5  ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 5 ; index01++ )
	{
		for( index02 = 0 ; index02 < 5 ; index02++ )
		{
			for( index03 = 0 ; index03 < 51 ; index03++ )
			{
				if( mDATA[tArrayIndex].nSpeech[index01][index02][index03] == '\0' )
				{
					break;
				}
			}
			if( index03 == 51 )
			{
				return FALSE;
			}
		}
	}
	if( ( mDATA[tArrayIndex].nTribe < 1 ) || ( mDATA[tArrayIndex].nTribe > 5  ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].nType < 1 ) || ( mDATA[tArrayIndex].nType > 17  ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].nDataSortNumber2D < 1 ) || ( mDATA[tArrayIndex].nDataSortNumber2D > 10000  ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].nDataSortNumber3D < 1 ) || ( mDATA[tArrayIndex].nDataSortNumber3D > 10000  ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 3 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].nSize[index01] < 1 ) || ( mDATA[tArrayIndex].nSize[index01] > 1000  ) )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 50 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].nMenu[index01] < 1 ) || ( mDATA[tArrayIndex].nMenu[index01] > 2  ) )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 3 ; index01++ )
	{
		for( index02 = 0 ; index02 < 28 ; index02++ )
		{
			if( ( mDATA[tArrayIndex].nShopInfo[index01][index02] < 0 ) || ( mDATA[tArrayIndex].nShopInfo[index01][index02] > 99999  ) )
			{
				return FALSE;
			}
		}
	}
	for( index01 = 0 ; index01 < 3 ; index01++ )
	{
		for( index02 = 0 ; index02 < 8 ; index02++ )
		{
			if( ( mDATA[tArrayIndex].nSkillInfo1[index01][index02] < 0 ) || ( mDATA[tArrayIndex].nSkillInfo1[index01][index02] > 300  ) )
			{
				return FALSE;
			}
		}
	}
	for( index01 = 0 ; index01 < 3 ; index01++ )
	{
		for( index02 = 0 ; index02 < 3 ; index02++ )
		{
			for( index03 = 0 ; index03 < 3 ; index03++ )
			{
				for( index04 = 0 ; index04 < 8 ; index04++ )
				{
					if( ( mDATA[tArrayIndex].nSkillInfo2[index01][index02][index03][index04] < 0 ) || ( mDATA[tArrayIndex].nSkillInfo2[index01][index02][index03][index04] > 300  ) )
					{
						return FALSE;
					}
				}
			}
		}
	}
	for( index01 = 0 ; index01 < 145 ; index01++ )
	{
		for( index02 = 0 ; index02 < 15 ; index02++ )
		{
			if( ( mDATA[tArrayIndex].nGambleCostInfo[index01][index02] < 0 ) || ( mDATA[tArrayIndex].nGambleCostInfo[index01][index02] > 100000000  ) )
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}
//INIT
BOOL NPCSYSTEM::Init( char *tFileName )
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE *tOriginal;
	DWORD tCompressSize;
	BYTE *tCompress;
	int tDataNum;
	NPC_INFO *tDATA;
	BOOL tCheckFirstCreate;

	Free();
#ifdef __WIN32__
	HANDLE hFile;
	hFile = CreateFile( tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}
	if( !ReadFile( hFile, &tOriginalSize, 4, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != 4 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	tOriginal = (BYTE *) GlobalAlloc( GMEM_FIXED, tOriginalSize );
	if( tOriginal == NULL )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !ReadFile( hFile, &tCompressSize, 4, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != 4 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	tCompress = (BYTE *) GlobalAlloc( GMEM_FIXED, tCompressSize );
	if( tCompress == NULL )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !ReadFile( hFile, tCompress, tCompressSize, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != tCompressSize )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !CloseHandle( hFile ) )
	{
		return FALSE;
	}
	if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	mSharedMemSize += 4;
	if( tDataNum != 500 )
	{
		return FALSE;
	}
	tDATA = (NPC_INFO *) GlobalAlloc( GMEM_FIXED, ( tDataNum * sizeof( NPC_INFO ) ) );
	if( tDATA == NULL )
	{
		return FALSE;
	}
	CopyMemory( &tDATA[0], &tOriginal[4], ( tDataNum * sizeof( NPC_INFO ) ) );
	mSharedMemSize += ( tDataNum * sizeof( NPC_INFO ) );
	GlobalFree( tCompress );
	GlobalFree( tOriginal );
	mDataNum = tDataNum;
	mDATA = tDATA;
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( !CheckValidElement( index01 ) )
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_NPCSYSTEM" );
	if ( mSharedMemMap == NULL )
	{
		return FALSE;
	}
	if( GetLastError() != ERROR_ALREADY_EXISTS )
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE *) MapViewOfFile( mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize );
	if( mSharedPostMem == NULL )
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4 );
	}
	CopyMemory( &mSharedNPCData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4 );
	mSharedMemSizeForCheck += 4;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], mDATA, ( mDataNum * sizeof( NPC_INFO ) ) );
	}
	mSharedNPCData.mDATA = (NPC_INFO *) &mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += ( mDataNum * sizeof( NPC_INFO ) );
	if( mSharedMemSize != mSharedMemSizeForCheck )
	{
		return FALSE;
	}
	mDataNum = 0;
	if( mDATA )
	{
		GlobalFree( mDATA );
		mDATA = NULL;
	}
#else
	FILE *r_fp = NULL;
	if(!(r_fp = fopen(tFileName, "r"))) {
		return FALSE;
	}

	if((nReadByte = fread(&tOriginalSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		return FALSE;
	}

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		return FALSE;
	}

	tOriginal = (BYTE *)calloc(1, tOriginalSize );
	if( tOriginal == NULL )
	{
		fclose(r_fp);
		return FALSE;
	}

	if((nReadByte = fread(&tCompressSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		return FALSE;
	}

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		return FALSE;
	}

	tCompress = (BYTE *) calloc(1, tCompressSize );
	if( tCompress == NULL )
	{
		fclose(r_fp);
		return FALSE;
	}

	if((nReadByte = fread(tCompress, 1, tCompressSize, r_fp)) < 0) {
		fclose(r_fp);
		return FALSE;
	}

	if( nReadByte != tCompressSize )
	{
		fclose(r_fp);
		return FALSE;
	}
	fclose(r_fp);

	if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	mSharedMemSize += 4;
	if( tDataNum != 500 )
	{
		return FALSE;
	}

	tDATA = (NPC_INFO *) calloc(1, ( tDataNum * sizeof( NPC_INFO ) ) );
	if( tDATA == NULL )
	{
		return FALSE;
	}
	CopyMemory( &tDATA[0], &tOriginal[4], ( tDataNum * sizeof( NPC_INFO ) ) );
	mSharedMemSize += ( tDataNum * sizeof( NPC_INFO ) );
	free( tCompress );
	free( tOriginal );
	mDataNum = tDataNum;
	mDATA = tDATA;
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( !CheckValidElement( index01 ) )
		{
			return FALSE;
		}
	}

	mSharedMemMap = shmget((key_t)KEY_SHM_NPC, mSharedMemSize, 0600 | IPC_CREAT);
	//mSharedMemMap = shmget((key_t)KEY_SHM_NPC, mSharedMemSize, 0600 | IPC_CREAT | IPC_EXCL);
	if(mSharedMemMap < 0) {
		if(errno != EEXIST) {
			return FALSE;
		} else {
			mSharedMemMap = shmget((key_t)KEY_SHM_NPC, mSharedMemSize, 0);
			if(mSharedMemMap < 0)
				return FALSE;
		}
		tCheckFirstCreate = FALSE;
	} else {
		/*
		mSharedMemMap = shmget((key_t)KEY_SHM_NPC, mSharedMemSize, 0);
		if(mSharedMemMap < 0) 
			return FALSE;
		*/
		tCheckFirstCreate = TRUE;
	}

	mSharedPostMem = (BYTE *)shmat(mSharedMemMap, (char *)0, 0);
	if( mSharedPostMem == NULL ) {
		return FALSE;
	}

	mSharedMemSizeForCheck = 0;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4 );
	}
	CopyMemory( &mSharedNPCData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4 );
	mSharedMemSizeForCheck += 4;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], mDATA, ( mDataNum * sizeof( NPC_INFO ) ) );
	}
	mSharedNPCData.mDATA = (NPC_INFO *) &mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += ( mDataNum * sizeof( NPC_INFO ) );
	if( mSharedMemSize != mSharedMemSizeForCheck )
	{
		return FALSE;
	}
	mDataNum = 0;
	if( mDATA )
	{
		free( mDATA );
		mDATA = NULL;
	}

#endif
	return TRUE;
}
//FREE
void NPCSYSTEM::Free( void )
{
	mDataNum = 0;
	if( mDATA )
	{
		free( mDATA );
		mDATA = NULL;
	}
	if( mSharedPostMem != NULL )
	{
		shmdt( mSharedPostMem );
		mSharedPostMem = NULL;
	}
	if( mSharedMemMap != 0 )
	{
		shmctl( mSharedMemMap, IPC_RMID, 0 );
		mSharedMemMap = 0;
	}
}
//SEARCH
NPC_INFO * NPCSYSTEM::Search( int nIndex )
{
	if( ( nIndex < 1 ) || ( nIndex > mSharedNPCData.mDataNum ) )
	{
		return NULL;
	}
	if( mSharedNPCData.mDATA[( nIndex - 1 )].nIndex == 0 )
	{
		return NULL;
	}
	return &mSharedNPCData.mDATA[( nIndex - 1 )];
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_QUESTSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
QUESTSYSTEM mQUEST;
//CREATE
QUESTSYSTEM::QUESTSYSTEM( void )
{
	mDataNum = 0;
	mDATA = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL QUESTSYSTEM::CheckValidElement( int tArrayIndex )
{
	int index01;
	int index02;

	if( strcmp( mDATA[tArrayIndex].qSubject, "" ) == 0 )
	{
		return TRUE;
	}
	if( ( mDATA[tArrayIndex].qIndex < 1 ) || ( mDATA[tArrayIndex].qIndex > 1000  ) )
	{
		return FALSE;
	}
	if( mDATA[tArrayIndex].qIndex != ( tArrayIndex + 1 ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 51 ; index01++ )
	{
		if( mDATA[tArrayIndex].qSubject[index01] == '\0' )
		{
			break;
		}
	}
	if( index01 == 51 )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].qCategory < 1 ) || ( mDATA[tArrayIndex].qCategory > 4  ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].qStep < 1 ) || ( mDATA[tArrayIndex].qStep > 1000  ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].qLevel < 1 ) || ( mDATA[tArrayIndex].qLevel > 145  ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].qType < 1 ) || ( mDATA[tArrayIndex].qType > 2  ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].qSort < 1 ) || ( mDATA[tArrayIndex].qSort > 8  ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].qSummonInfo[0] < 0 ) || ( mDATA[tArrayIndex].qSummonInfo[0] > 200  ) )
	{
		return FALSE;
	}
	if( ( mDATA[tArrayIndex].qStartNPCNumber < 1 ) || ( mDATA[tArrayIndex].qStartNPCNumber > 500  ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 5 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].qKeyNPCNumber[index01] < 0 ) || ( mDATA[tArrayIndex].qKeyNPCNumber[index01] > 500  ) )
		{
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].qEndNPCNumber < 1 ) || ( mDATA[tArrayIndex].qEndNPCNumber > 500  ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 3 ; index01++ )
	{
		if( ( mDATA[tArrayIndex].qReward[index01][0] < 1 ) || ( mDATA[tArrayIndex].qReward[index01][0] > 6  ) )
		{
			return FALSE;
		}
		if( ( mDATA[tArrayIndex].qReward[index01][1] < 0 ) || ( mDATA[tArrayIndex].qReward[index01][1] > 100000000  ) )
		{
			return FALSE;
		}
	}
	if( ( mDATA[tArrayIndex].qNextIndex < 0 ) || ( mDATA[tArrayIndex].qNextIndex > 1000  ) )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qStartSpeech[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qHurrySpeech[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qProcessSpeech1[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qProcessSpeech2[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qProcessSpeech3[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qProcessSpeech4[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qProcessSpeech5[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qSuccessSpeech[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qFailureSpeech[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	for( index01 = 0 ; index01 < 15 ; index01++ )
	{
		for( index02 = 0 ; index02 < 51 ; index02++ )
		{
			if( mDATA[tArrayIndex].qCallSpeech[index01][index02] == '\0' )
			{
				break;
			}
		}
		if( index02 == 51 )
		{
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL QUESTSYSTEM::Init( char *tFileName )
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE *tOriginal;
	DWORD tCompressSize;
	BYTE *tCompress;
	int tDataNum;
	QUEST_INFO *tDATA;
	BOOL tCheckFirstCreate;

	Free();
#ifdef __WIN32__
	HANDLE hFile;
	hFile = CreateFile( tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}
	if( !ReadFile( hFile, &tOriginalSize, 4, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != 4 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	tOriginal = (BYTE *) GlobalAlloc( GMEM_FIXED, tOriginalSize );
	if( tOriginal == NULL )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !ReadFile( hFile, &tCompressSize, 4, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != 4 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	tCompress = (BYTE *) GlobalAlloc( GMEM_FIXED, tCompressSize );
	if( tCompress == NULL )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !ReadFile( hFile, tCompress, tCompressSize, &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != tCompressSize )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !CloseHandle( hFile ) )
	{
		return FALSE;
	}
	if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	mSharedMemSize += 4;
	if( tDataNum != 1000 )
	{
		return FALSE;
	}
	tDATA = (QUEST_INFO *) GlobalAlloc( GMEM_FIXED, ( tDataNum * sizeof( QUEST_INFO ) ) );
	if( tDATA == NULL )
	{
		return FALSE;
	}
	CopyMemory( &tDATA[0], &tOriginal[4], ( tDataNum * sizeof( QUEST_INFO ) ) );
	mSharedMemSize += ( tDataNum * sizeof( QUEST_INFO ) );
	GlobalFree( tCompress );
	GlobalFree( tOriginal );
	mDataNum = tDataNum;
	mDATA = tDATA;
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( !CheckValidElement( index01 ) )
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_QUESTSYSTEM" );
	if ( mSharedMemMap == NULL )
	{
		return FALSE;
	}
	if( GetLastError() != ERROR_ALREADY_EXISTS )
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE *) MapViewOfFile( mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize );
	if( mSharedPostMem == NULL )
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4 );
	}
	CopyMemory( &mSharedQuestData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4 );
	mSharedMemSizeForCheck += 4;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], mDATA, ( mDataNum * sizeof( QUEST_INFO ) ) );
	}
	mSharedQuestData.mDATA = (QUEST_INFO *) &mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += ( mDataNum * sizeof( QUEST_INFO ) );
	if( mSharedMemSize != mSharedMemSizeForCheck )
	{
		return FALSE;
	}
	mDataNum = 0;
	if( mDATA )
	{
		HeapFree( GetProcessHeap(), 0, mDATA );
		mDATA = NULL;
	}
#else
	FILE *r_fp = NULL;
	if(!(r_fp = fopen(tFileName, "r"))) {
		return FALSE;
	}

	if((nReadByte = fread(&tOriginalSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		return FALSE;
	}

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		return FALSE;
	}

	tOriginal = (BYTE *)calloc(1, tOriginalSize );
	if( tOriginal == NULL )
	{
		fclose(r_fp);
		return FALSE;
	}

	if((nReadByte = fread(&tCompressSize, 1, 4, r_fp)) < 0) {
		fclose(r_fp);
		return FALSE;
	}

	if( nReadByte != 4 )
	{
		fclose(r_fp);
		return FALSE;
	}

	tCompress = (BYTE *) calloc(1, tCompressSize );
	if( tCompress == NULL )
	{
		fclose(r_fp);
		return FALSE;
	}

	if((nReadByte = fread(tCompress, 1, tCompressSize, r_fp)) < 0) {
		fclose(r_fp);
		return FALSE;
	}

	if( nReadByte != tCompressSize )
	{
		fclose(r_fp);
		return FALSE;
	}
	fclose(r_fp);

	if( !mGAME.Decompress( tCompressSize, tCompress, tOriginalSize, tOriginal ) )
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory( &tDataNum, &tOriginal[0], 4 );
	mSharedMemSize += 4;
	if( tDataNum != 1000 )
	{
		return FALSE;
	}
	tDATA = (QUEST_INFO *) calloc( 1, ( tDataNum * sizeof( QUEST_INFO ) ) );
	if( tDATA == NULL )
	{
		return FALSE;
	}
	CopyMemory( &tDATA[0], &tOriginal[4], ( tDataNum * sizeof( QUEST_INFO ) ) );
	mSharedMemSize += ( tDataNum * sizeof( QUEST_INFO ) );
	free( tCompress );
	free( tOriginal );
	mDataNum = tDataNum;
	mDATA = tDATA;
	for( index01 = 0 ; index01 < mDataNum ; index01++ )
	{
		if( !CheckValidElement( index01 ) )
		{
			return FALSE;
		}
	}

	mSharedMemMap = shmget((key_t)KEY_SHM_QUEST, mSharedMemSize, 0600 | IPC_CREAT);
	//mSharedMemMap = shmget((key_t)KEY_SHM_QUEST, mSharedMemSize, 0600 | IPC_CREAT | IPC_EXCL);
	if(mSharedMemMap < 0) {
		if(errno != EEXIST) {
			return FALSE;
		} else {
			mSharedMemMap = shmget((key_t)KEY_SHM_QUEST, mSharedMemSize, 0);
			if(mSharedMemMap < 0)
				return FALSE;
		}
		tCheckFirstCreate = FALSE;
	} else {
		/*
		mSharedMemMap = shmget((key_t)KEY_SHM_QUEST, mSharedMemSize, 0);
		if(mSharedMemMap < 0) 
			return FALSE;
		*/
		tCheckFirstCreate = TRUE;
	}

	mSharedPostMem = (BYTE *)shmat(mSharedMemMap, (char *)0, 0);
	if( mSharedPostMem == NULL ) {
		return FALSE;
	}

	mSharedMemSizeForCheck = 0;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4 );
	}
	CopyMemory( &mSharedQuestData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4 );
	mSharedMemSizeForCheck += 4;
	if( tCheckFirstCreate )
	{
		CopyMemory( &mSharedPostMem[mSharedMemSizeForCheck], mDATA, ( mDataNum * sizeof( QUEST_INFO ) ) );
	}
	mSharedQuestData.mDATA = (QUEST_INFO *) &mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += ( mDataNum * sizeof( QUEST_INFO ) );
	if( mSharedMemSize != mSharedMemSizeForCheck )
	{
		return FALSE;
	}
	mDataNum = 0;
	if( mDATA )
	{
		//free( GetProcessHeap(), 0, mDATA );
		free(mDATA );
		mDATA = NULL;
	}

#endif
	return TRUE;
}
//FREE
void QUESTSYSTEM::Free( void )
{
	mDataNum = 0;
	if( mDATA )
	{
		free( mDATA );
		mDATA = NULL;
	}
	if( mSharedPostMem != NULL )
	{
		shmdt( mSharedPostMem );
		mSharedPostMem = NULL;
	}
	if( mSharedMemMap != 0 )
	{
		shmctl( mSharedMemMap, IPC_RMID, 0 );
		mSharedMemMap = 0;
	}
}
//SEARCH
QUEST_INFO * QUESTSYSTEM::Search( int qTribe, int qStep )
{
	int index01;

	for( index01 = 0 ; index01 < mSharedQuestData.mDataNum ; index01++ )
	{
		if( strcmp( mSharedQuestData.mDATA[index01].qSubject, "" ) == 0 )
		{
			continue;
		}
		if( ( mSharedQuestData.mDATA[index01].qCategory == ( qTribe + 1 ) ) && ( mSharedQuestData.mDATA[index01].qStep == qStep ) )
		{
			return &mSharedQuestData.mDATA[index01];
		}
	}
	return NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_PATSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
PATSYSTEM mPAT;
//CREATE
PATSYSTEM::PATSYSTEM( void )
{
	mMaxRangeValue[0] =  40000000;
	mMaxRangeValue[1] =  80000000;
	mMaxRangeValue[2] = 160000000;
	mMaxRangeValue[3] = 320000000;
}
//INIT
BOOL PATSYSTEM::Init( void )
{
	return TRUE;
}
//FREE
void PATSYSTEM::Free( void )
{
}
//RETURN_GROW_STEP
float PATSYSTEM::ReturnGrowStep( int pIndex, int pGrowUpValue )
{
	int tMaxRangeValueIndex;
	float tDegree;

	if( pGrowUpValue < 1 )
	{
		return 0.0f;
	}
	switch( pIndex )
	{
	case 1002 :
	case 1003 :
	case 1004 :
	case 1005 :
		tMaxRangeValueIndex = 0;
		break;
	case 1006 :
	case 1007 :
	case 1008 :
	case 1009 :
	case 1010 :
	case 1011 :
		tMaxRangeValueIndex = 1;
		break;
	case 1012 :
	case 1013 :
	case 1014 :
	case 1015 :
		tMaxRangeValueIndex = 2;
		break;
	case 1016 :
		tMaxRangeValueIndex = 3;
		break;
	default :
		return 0.0f;
	}
	if( pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex] )
	{
		return 4.0f;
	}
	tDegree = ( (float) pGrowUpValue * 100.0f ) / (float) mMaxRangeValue[tMaxRangeValueIndex];
	if( tDegree < 25.0f )
	{
		return 0.0f;
	}
	else if( tDegree < 50.0f )
	{
		return 1.0f;
	}
	else if( tDegree < 75.0f )
	{
		return 2.0f;
	}
	else if( tDegree < 100.0f )
	{
		return 3.0f;
	}
	else
	{
		return 4.0f;
	}
	return 0.0f;
}
//RETURN_GROW_PERCENT
float PATSYSTEM::ReturnGrowPercent( int pIndex, int pGrowUpValue )
{
	int tMaxRangeValueIndex;

	if( pGrowUpValue < 1 )
	{
		return 0.0f;
	}
	switch( pIndex )
	{
	case 1002 :
	case 1003 :
	case 1004 :
	case 1005 :
		tMaxRangeValueIndex = 0;
		break;
	case 1006 :
	case 1007 :
	case 1008 :
	case 1009 :
	case 1010 :
	case 1011 :
		tMaxRangeValueIndex = 1;
		break;
	case 1012 :
	case 1013 :
	case 1014 :
	case 1015 :
		tMaxRangeValueIndex = 2;
		break;
	case 1016 :
		tMaxRangeValueIndex = 3;
		break;
	default :
		return 0.0f;
	}
	if( pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex] )
	{
		return 100.0f;
	}
	return ( ( (float) pGrowUpValue * 100.0f ) / (float) mMaxRangeValue[tMaxRangeValueIndex] );
}
//RETURN_ATTACK_POWER
float PATSYSTEM::ReturnAttackPower( int pIndex, int pGrowUpValue, int pActivityValue )
{
	if( ( pIndex != 1002 ) && ( pIndex != 1006 ) && ( pIndex != 1007 ) && ( pIndex != 1008 ) && ( pIndex != 1012 ) && ( pIndex != 1013 ) && ( pIndex != 1014 ) && ( pIndex != 1016 ) )
	{
		return 0.0f;
	}

	int tMaxRangeValueIndex;

	if( ( pGrowUpValue < 1 ) || ( pActivityValue < 1 ) )
	{
		return 0.0f;
	}
	switch( pIndex )
	{
	case 1002 :
	case 1003 :
	case 1004 :
	case 1005 :
		tMaxRangeValueIndex = 0;
		break;
	case 1006 :
	case 1007 :
	case 1008 :
	case 1009 :
	case 1010 :
	case 1011 :
		tMaxRangeValueIndex = 1;
		break;
	case 1012 :
	case 1013 :
	case 1014 :
	case 1015 :
		tMaxRangeValueIndex = 2;
		break;
	case 1016 :
		tMaxRangeValueIndex = 3;
		break;
	default :
		return 0.0f;
	}
	if( pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex] )
	{
		return 1100.0f;
	}
	return ( ( (float) pGrowUpValue * 1000.0f ) / (float) mMaxRangeValue[tMaxRangeValueIndex] );
}
//RETURN_DEFENSE_POWER
float PATSYSTEM::ReturnDefensePower( int pIndex, int pGrowUpValue, int pActivityValue )
{
	if( ( pIndex != 1003 ) && ( pIndex != 1006 ) && ( pIndex != 1009 ) && ( pIndex != 1010 ) && ( pIndex != 1012 ) && ( pIndex != 1013 ) && ( pIndex != 1015 ) && ( pIndex != 1016 ) )
	{
		return 0.0f;
	}

	int tMaxRangeValueIndex;

	if( ( pGrowUpValue < 1 ) || ( pActivityValue < 1 ) )
	{
		return 0.0f;
	}
	switch( pIndex )
	{
	case 1002 :
	case 1003 :
	case 1004 :
	case 1005 :
		tMaxRangeValueIndex = 0;
		break;
	case 1006 :
	case 1007 :
	case 1008 :
	case 1009 :
	case 1010 :
	case 1011 :
		tMaxRangeValueIndex = 1;
		break;
	case 1012 :
	case 1013 :
	case 1014 :
	case 1015 :
		tMaxRangeValueIndex = 2;
		break;
	case 1016 :
		tMaxRangeValueIndex = 3;
		break;
	default :
		return 0.0f;
	}
	if( pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex] )
	{
		return 2200.0f;
	}
	return ( ( (float) pGrowUpValue * 2000.0f ) / (float) mMaxRangeValue[tMaxRangeValueIndex] );
}
//RETURN_LIFE_VALUE
float PATSYSTEM::ReturnLifeValue( int pIndex, int pGrowUpValue )
{
	if( ( pIndex != 1004 ) && ( pIndex != 1007 ) && ( pIndex != 1009 ) && ( pIndex != 1011 ) && ( pIndex != 1012 ) && ( pIndex != 1014 ) && ( pIndex != 1015 ) && ( pIndex != 1016 ) )
	{
		return 0.0f;
	}

	int tMaxRangeValueIndex;

	if( pGrowUpValue < 1 )
	{
		return 0.0f;
	}
	switch( pIndex )
	{
	case 1002 :
	case 1003 :
	case 1004 :
	case 1005 :
		tMaxRangeValueIndex = 0;
		break;
	case 1006 :
	case 1007 :
	case 1008 :
	case 1009 :
	case 1010 :
	case 1011 :
		tMaxRangeValueIndex = 1;
		break;
	case 1012 :
	case 1013 :
	case 1014 :
	case 1015 :
		tMaxRangeValueIndex = 2;
		break;
	case 1016 :
		tMaxRangeValueIndex = 3;
		break;
	default :
		return 0.0f;
	}
	if( pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex] )
	{
		return 2200.0f;
	}
	return ( ( (float) pGrowUpValue * 2000.0f ) / (float) mMaxRangeValue[tMaxRangeValueIndex] );
}
//RETURN_MANA_VALUE
float PATSYSTEM::ReturnManaValue( int pIndex, int pGrowUpValue )
{
	if( ( pIndex != 1005 ) && ( pIndex != 1008 ) && ( pIndex != 1010 ) && ( pIndex != 1011 ) && ( pIndex != 1013 ) && ( pIndex != 1014 ) && ( pIndex != 1015 ) && ( pIndex != 1016 ) )
	{
		return 0.0f;
	}

	int tMaxRangeValueIndex;

	if( pGrowUpValue < 1 )
	{
		return 0.0f;
	}
	switch( pIndex )
	{
	case 1002 :
	case 1003 :
	case 1004 :
	case 1005 :
		tMaxRangeValueIndex = 0;
		break;
	case 1006 :
	case 1007 :
	case 1008 :
	case 1009 :
	case 1010 :
	case 1011 :
		tMaxRangeValueIndex = 1;
		break;
	case 1012 :
	case 1013 :
	case 1014 :
	case 1015 :
		tMaxRangeValueIndex = 2;
		break;
	case 1016 :
		tMaxRangeValueIndex = 3;
		break;
	default :
		return 0.0f;
	}
	if( pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex] )
	{
		return 2000.0f;
	}
	return ( ( (float) pGrowUpValue * 1800.0f ) / (float) mMaxRangeValue[tMaxRangeValueIndex] );
}
//-------------------------------------------------------------------------------------------------
