#pragma once

#include <tchar.h>
#include <string>
#include <icrsint.h>

#import "msado15.dll" rename ("EOF", "EndOfFile")

/** END_ADO_BINDING�� ������ ���� ��ũ��.
 *
 *  @warning    namespace ���� ������ ADO VC extension�� GS ���̺귯���� 
 *              ���� ����ϱ� ����� ������ �ذ��ϱ� ���� �����Ѵ�.
 */
#define FINISH_ADO_BINDING()   {0, ADODB::adEmpty, 0, 0, 0, 0, 0, 0, 0, FALSE}};\
    return rgADOBindingEntries;}

#ifdef _DEBUG
    #pragma comment (lib, "comsuppwd.lib")
#else
    #pragma comment (lib, "comsuppw.lib")
#endif

class CDailyLog;

namespace GS {
    namespace DB {
        namespace ADO {

            #define GS_DB_ADO_VER   _T ("VER1.7.4")

            /** ADODB�� ����� DB class.
             *
             *  History:
             *      2007-04-04      �ʱ� ����(Ver 1.0) �ۼ�.
             *                      Support only synchronously connection and query.
             *
             *      2007-04-05      ����� �켱 ��û ���� �ݿ�.
             *                      1. Header file �ϳ��� �ʿ��ϵ��� ����.
             *                      2. (IP, PORT, ID, PW)�� �޴� Connect method �߰�.
             *                      3. Disconnect method �߰�.
             *                      4. Log�� default�� ������� �ʵ��� ����.
             *                      5. Reconnect method �߰�.
             *                      6. �α� filter �ɼ��� �����ϰ� ��� �α׸� ����Ѵ�.
             *                      7. Query ���� ���� �ڵ� ����.
             *                         Execute & ExecuteAndReceive method�� ȣ��������,
             *                         ���� connection�� ������ �ִٸ� �ٽ� ������ 
             *                         �õ��غ��� �׷��� �ȵȴٸ� ���и� ��ȯ�Ѵ�.
             *
             *      2007-04-09      ���̳ʸ� ���� �ڵ� �߰�.
             *                      1. BINARY, VARBINARY, IMAGE type support.
             *                      2. VERSION STRING �߰�.
             *
             *      2007-04-10      GetResultCounts ���� ����.
             *                      Command interface�� Execute method�� ����ؼ� SELECT��
             *                      ���� ������ �������� ��� ��ȯ�Ǵ� Recordset instance
             *                      ���� GetRecordCount method�� ȣ���ؼ� ��ȯ�� record��
             *                      ���� ���� �� ���� ������ �־���. 
             *                      �ذ� ������� Command interface ��ſ� Recordset�� 
             *                      ����ؼ� ������ �����ϴ� �Ͱ� ī��Ʈ �ϴ� ��� �߿� 
             *                      ����(VER1.5.1)�� ī��Ʈ �ϵ��� ����.
             *
             *      2007-04-12      ADO VC exntension ��� ��밡���ϵ��� ����(VER1.6.0).
             *                      
             *      2007-04-18      Default�� �α� ��� ������ �������� �ʵ��� ����.
             *                      EnableLog method�� ȣ������ �� ������ �����մϴ�.
             *
             *      2007-04-24      ���� ������ ������ ��� syntax error���� Ȯ���� �� �ִ�
             *                      ��� �߰�(VER1.6.2).
             *
             *      2007-04-24      Syntax error �߰� �ݿ� (VER1.6.3).
             *                      1. ���� ©���ų� �Ѿ�� ���.
             *                      2. NULL ���� ���� �� ���� �ʵ忡 NULL�� INSERT �ϴ� ���.
             *
             *      2007-05-05      IsConnected ���� ���� ���� (VER1.6.4)
             *                      �ϴ� �����ͺ��̽��� ������ �� ���Ŀ� connection�� ��������
             *                      �ʰ� ���������� connection interface�� state property��
             *                      adStateOpen ���·� �����Ǳ� ������ ���̺귯������ ������
             *                      syntax ������ �ƴ϶�� exception handler���� Disconnect 
             *                      method�� ȣ���ϵ��� �Ѵ�.
             *
             *      2007-05-05      Transaction ����� �����մϴ�(VER1.7.0).
             *                      BeginTransaction, EndTransation method �߰�.
             *                      MoveFirst method���� BOF�Ǵ� EOF exception�� �߻��ϴ� ���
             *                      1.6.4 ���� ������Ʈ ������ �߻��ϴ� �����ͺ��̽��� ������
             *                      ���� ������ ����. BOF �Ǵ� EOF exception�� syntax error��
             *                      �����ϵ��� IsSyntaxError method�� ����.
             *
             *      2007-05-07      ������ �߻����� ��� network ��ֿ� ���õ� ��츸
             *                      ������ ������ ����(VER1.7.1)
             *                      BOF �Ǵ� EOF ���� ������ ��쿡�� ������ ���ԵǸ� ���� 
             *                      ������ ���� connect / disconnect�� �ݺ��Ǵ� ������ 
             *                      ���� �ȴ�.
             *
             *      2007-05-07      BEGIN TRANSACTION ���� ������ Ʈ����� ����� �����ϴ� ����
             *                      connection interface�� BeginTrans, CommitTrans �׸���
             *                      RollbackTrans method�� ����ϵ��� ����(VER1.7.2).
             *
             *      2007-05-08      Transaction�� �ɷ� �ִ� ���¿��� �������� ������ �������� 
             *                      �ٽ� ������ ���� ���������� �� �翬���� �ǵ��� ����
             *                      (VER1.7.3)
             *
             *      2007-06-07      �α׸� ������� �ʰ� �Ǿ� �ִ� ��� ������ ����� 
             *                      recordset�� ���� ��� disconnect�� �ϰ� �Ǿ� �ִ�
             *                      ���� ���� (VER1.7.4).
             *
             *  @author     ships.
             *  @ver        1.7.4
             */
            class CGSDBManager
            {
            public:
                CGSDBManager(void);
                ~CGSDBManager(void);

            public:
                /** �α׸� ����� ������ ������� ������ �����Ѵ�.
                 *
                 *  �α׸� ����� ������ ���� ��쿡 �α׸� Ȱ��ȭ ��ų �� ����.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      bEnable     ��� - true / ������� ���� - false.
                 */
                bool    EnableLog (bool bEnable);

                /** DB Manager�� ����ϱ� ���� �ݵ�� ȣ���ؾ� �Ѵ�.
                 *
                 *  DB Manager���� ����ϴ� ��� smart pointer�� �����Ѵ�.
                 *
                 *  ���� �ڵ� :
                 *      0       -       ������ ���.
                 *      1       -       Connection interface ���� ����.
                 *      2       -       Recordset interface ���� ����.
                 *      3       -       Command interface ���� ����.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iCode   �������� ����� ���� �ڵ�.
                 *  @see        InitializeLog.
                 */
                bool    Initialize (int& iCode);

                /** Database�� ���� �Ѵ�.
                 *
                 *  Connection stream(string) sample:
                 *      "Provider=sqloledb;Network Library=DBMSSOCN;Data Source=127.0.0.1, 1433;
                 *       DataBase=Gaion;UID=anonymous;PWD=blahblah;"
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      pConnectionStream   DB ����� ���õ� string.
                 */
                bool    Connect (const TCHAR* pConnectionStream);

                /** Database�� �����Ѵ�.
                 *
                 *  Row interface�� ole db�� ����ϰ� tcp/ip protocol ����ϵ��� fix.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      pIP     SQL server ip address.
                 *  @param      iPort   SQL server port.
                 *  @param      pID     SQL server login id.
                 *  @param      pPW     SQL server login password.
                 */
                bool    Connect (const TCHAR* pIP, const int iPort, 
                                 const TCHAR* pID, const TCHAR* pPW);

                /** �α� ������ ����� ��ο� ���� �̸��� prefix, filter�� �����ش�.
                 *
                 *  InitializeLog method�� ȣ������ ������ �̸� ���ǵ� ��ġ�� 
                 *  ��� �α׸� ����Ѵ�.
                 *
                 *  History:
                 *      2007-04-05  �α� filter�� �ɼǿ��� �����ϰ� ��� LOG�� 
                 *                  ����ϵ��� �����Ѵ�.
                 *
                 *  @param      pPath       �α� ���� ��� ��ġ.
                 *  @param      pPrefix     �α� ���� �̸��� prefix.
                 *  @param      uiMask      �α� ��� ��� filter mask (deprecated).
                 *  @warning    �ݵ�� Initialize method���� ���� ȣ���ؾ� �Ѵ�.
                 *  @warning    �α� ������ ����� path ������ recursive���� 
                 *              �ʱ� ������ ���� ������ �������� ������ ������
                 *              �ݵ�� �̹� �����Ǿ� �־�߸� �Ѵ�. �α׸� 
                 *              ����� ������ �������� �ʴ� ��쿡�� EnableLog
                 *              method�� ����ϴ��� �αװ� ��ϵ��� �ʴ´�.
                 *  @see        Initialize.
                 */
                void    InitializeLog (const TCHAR* pPath, const TCHAR* pPrefix);

                /** ����� �޾ƾ� �ϴ� query���� ����ϴ� ��� ȣ���Ѵ�.
                 *
                 *  ������ ��� query�� ����� ����ȴ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      pQuery      Query statement.
                 *  @param      lAffected   Query�� ������ ���� row count.
                 *  @see        Execute.
                 */
                bool    ExecuteAndReceive (const TCHAR* pQuery, int& iAffected);

                /** ����� ���� �ʴ� query���� ����ϴ� ��� ȣ���Ѵ�.
                 *
                 *  ����� ���� �ʴ� ��쿡�� ExecuteAndReceive method�� ȣ���ص�
                 *  ������ ������ �ʴ´�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      pQuery      Query statement.
                 *  @param      lAffected   Query�� ������ ���� row count.
                 *  @see        ExecuteAndReceive.
                 */
                bool    Execute (const TCHAR* pQuery, int& iAffected);

                /** �����ͺ��̽� ������ ����Ǿ� �ִ��� ��ȯ�Ѵ�.
                 *
                 *  @return     ����Ǿ� �ִ� ��� - true / ���� ��� - false.
                 */
                bool    IsConnected (void);

                /** Query�� ���� ������ ���� row count�� ��ȯ�Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iCounts     Row counts number.
                 *  @warning    Query ���� ����� ���� �� Recordset pointer��
                 *              �̵��ϸ鼭 � �۾��� �� �Ŀ� GetResultCounts
                 *              method�� ȣ���ϸ� �۾� ���̴� pointer�� ���ư�
                 *              �� ���� ������ ���� �ʿ��� ��쿡�� �ݵ�� 
                 *              query ���� �� ���� ���� ȣ���ϵ��� �Ѵ�.
                 */
                bool    GetResultCounts (int& iCounts);

                /** Recordset�� ���� row�� pointer�� �̵��մϴ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 */
                bool    Forward (void);

                /** Recordset�� ���� ó�� row�� pointer�� �̵��մϴ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 */
                bool    MoveFirst (void);

                /** Recordset�� ������ ��ġ�� row�� pointer�� �̵��մϴ�.
                 *
                 *  ���� recordset pointer�� �־��� ���ڸ�ŭ foward �������� 
                 *  �̵��մϴ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iPos    �ű� row�� ��.
                 */
                bool    Move (int iPos);

                /** ���� recordset�� pointer�� �������� ����Ű�� �ִ��� ��ȯ�Ѵ�.
                 *
                 *  @return     ������ - true / �׷��� ���� ��� - false.
                 *  @warning    Recordset pointer�� ���°� ADODB::adStateOpen�� 
                 *              �ƴ� ��쿡�� recordset�� �����Ƿ� �������̶��
                 *              �����ϰ� true�� ��ȯ�Ѵ�.
                 */
                bool    IsEndOfRecordset (void);

                /** Date type�� record �ڷḦ ��ȯ�Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iField      Table field index.
                 *  @param      datetime    Data result.
                 */
                bool    GetDate (int iField, DATE& datetime);

                /** Int type�� record �ڷḦ ��ȯ�Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iField      Table field index.
                 *  @param      iValue      Data result.
                 */
                bool    GetInt (int iField, int& iValue);

                /** Int type�� record �ڷḦ ��ȯ�Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      pFieldName  Table field name.
                 *  @param      iValue      Data result.
                 */
                bool    GetInt (TCHAR* pFieldName, int& iValue);

                /** string type�� record �ڷḦ ��ȯ�Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iField      Table field index.
                 *  @param      pValue      Data result.
                 *  @param      iLength     �Է� ������ ����.
                 */
                bool    GetText (int iField, TCHAR* pValue, int iLength);

                /** Long type�� record �ڷḦ ��ȯ�Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iField      Table field index.
                 *  @param      lValue      Data result.
                 */
                bool    GetLong (int iField, long& lValue);

                /** Float type�� record �ڷḦ ��ȯ�Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iField      Table field index.
                 *  @param      fValue      Data result.
                 */
                bool    GetFloat (int iField, float& fValue);

                /** Double type�� record �ڷḦ ��ȯ�Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iField      Table field index.
                 *  @param      dValue      Data result.
                 */
                bool    GetDouble (int iField, double& dValue);

                //bool    GetBool (int iField, bool& bValue);

                /** Database�� ������ ���´�.
                 *
                 *  @return     ���� - true / ���� - false.
                 */
                bool    Disconnect (void);

                /** Database ������ �������� �Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 */
                bool    Reconnect (void);

                /** ���̳ʸ� �Ķ������ ���� �����Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      pChunk      ���̳ʸ� field�� ����� ���̳ʸ� ����Ÿ.
                 *  @param      dwChunkSize ���̳ʸ� ����Ÿ ũ��.
                 */
                bool    PushBinaryParameter (const TCHAR* pName, LPVOID pChunk, DWORD dwChunkSize);

                /** Parameter�� �ִ� query���� �غ��Ѵ�.
                 *
                 *  Prepared property�� ����ؼ� ����Ÿ���̽� �������� query�� 
                 *  parsing�� �ּ�ȭ�� �� �ֵ��� �Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      pQuery      SQL query.
                 *  @param      bPrepare    Prepared property.
                 */
                bool    PrepareStatement (const TCHAR* pQuery, bool bPrepare = false);

                /** �Ķ���Ͱ� �ִ� query���� �����Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iAffected   Query�� ������ ���� row count.
                 *  @param      bIsResult   ����� �޴� ��� - true / false.
                 */
                bool    Execute (int& iAffected, bool bIsResult = false);

                /** ���̳ʸ� �ʵ��� ���� ��ȯ�Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      iField      Table field index.
                 *  @param      dwChunkSize Binary data size.
                 *  @param      pChunk      Binary data raw stream.
                 */
                bool    GetBinary (int iField, DWORD& dwChunkSize, LPVOID& pChunk);

                /** Database table�� class�� ���� �����Ѵ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      pInstance   Inherited CADORecordBinding instance.
                 */
                bool    Bind (void* pInstance);

                /** Transaction�� �����մϴ�.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @see        EndTransaction.
                 */
                bool    BeginTransaction (void);

                /** Transaction�� �����մϴ�.
                 *
                 *  ���� ����:
                 *      true    -   transaction commit.
                 *      false   -   transaction rollback.
                 *
                 *  @return     ���� - true / ���� - false.
                 *  @param      bIsCommit   ���� ����.
                 *  @see        BeginTransaction.
                 */
                bool    EndTransaction (bool bIsCommit = true);

            private:
                void    WriteProviderErrorLog (ADODB::_ConnectionPtr pConn);
                void    WriteComErrorLog (_com_error& e, bool bExit = true);
                bool    IsOpenRecordset (void);

            protected:
                ADODB::_ConnectionPtr   m_pConnection;      ///< Connection smart pointer.
                ADODB::_RecordsetPtr    m_pRecordset;       ///< Recordset smart pointer.
                ADODB::_CommandPtr      m_pCommand;         ///< Command smart pointer.
                CDailyLog*              m_pLogger;           ///< Log instance.
                bool                    m_bWriteLog;        ///< �α� ��� ����.
                bool                    m_bInitializedLog;  ///< �α� ��� ���� ����.
                bool                    m_bLoggerCreated;   ///< �α� ��� ���� ����.
                std::string             m_ConnectionStream; ///< Connection stream string.
                IADORecordBinding*      m_pBinder;
                std::string             m_LogPath;
                HRESULT                 m_hError;
                bool                    m_bIsTransactionStart;
                bool                    m_bIsTransactionFailed;
            };

        } // End Of ADO.
    }// End Of DB.
} // End Of GS.