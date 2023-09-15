/****************************************************************************

   CTSD : Common Transaction Service

   CopyRight(C) 2003 Sean Kim All Rights reserved.
   Author : Sean Kim (sean@0x31.com)

   $Id: mysql.cpp,v 1.5 2007/11/08 05:47:02 wglee Exp $

   Redistribution and use in source and binary forms, with or with out
   modification, are not permitted without author's permission.

 ****************************************************************************/

#ifdef __USE_DB_POOL__
#ifdef __DBPOOL_USE_MYSQL__

#include <string.h>
#include "cts_mysql.h"

CMySQL::CMySQL(int auto_commit) 
{
	initialized        = false;
	m_hostname_str_ptr = NULL;
	m_dbname_str_ptr   = NULL;
	m_acct_str_ptr     = NULL;
	m_passwd_str_ptr   = NULL;
	m_result_code      = 0;
	m_MYSQL            = NULL;
	m_result_ptr       = NULL;
	m_auto_commit      = auto_commmit;
}

CMySQL::~CMySQL()
{
	if(m_MYSQL) {
		disconnect();
	}
	unset_db_conn_info();
}

int CMySQL::do_ping()
{
    // if connected, return 0;
    return mysql_ping(m_MYSQL);
}

inline void CMySQL::unset_db_conn_info(void) 
{
	if(m_hostname_str_ptr) ::free(m_hostname_str_ptr);
	if(m_dbname_str_ptr) ::free(m_dbname_str_ptr);
	if(m_acct_str_ptr) ::free(m_acct_str_ptr);
	if(m_passwd_str_ptr) ::free(m_passwd_str_ptr);
}

int CMySQL::set_db_conn_info(const char *hostname_str_const_ptr, int port_num, const char *db_name_str_const_ptr,
                                const char *acct_str_const_ptr, const char *passwd_str_const_ptr)
{
	if(initialized) {
		if(m_MYSQL) {
			disconnect();
		}
		unset_db_conn_info();
	} 

	if(!hostname_str_const_ptr || !db_name_str_const_ptr ||
	   !acct_str_const_ptr || !passwd_str_const_ptr ) {
		return -1;
	}

	m_hostname_str_ptr = ::strdup(hostname_str_const_ptr);
	m_dbname_str_ptr = ::strdup(db_name_str_const_ptr);
    m_port_num = static_cast<unsigned int>(port_num);
	m_acct_str_ptr = ::strdup(acct_str_const_ptr);
	m_passwd_str_ptr = ::strdup(passwd_str_const_ptr);

	initialized = true;
	return 1;
}

MYSQL* CMySQL::connect(const char *hostname_str_const_ptr, int port_num, const char *db_name_str_const_ptr,
                        const char *acct_str_const_ptr, const char *passwd_str_const_ptr)
{
	if(set_db_conn_info(hostname_str_const_ptr, port_num, db_name_str_const_ptr,
                        acct_str_const_ptr, passwd_str_const_ptr) < 0) {
		return NULL;
	}

	return connect();
}

MYSQL* CMySQL::connect(string hostname_str_obj, int port_num, string db_name_str_obj,
                        string db_acct_str_obj,  string db_passwd_str_obj)
{
	if(set_db_conn_info(hostname_str_obj.c_str(), port_num, db_name_str_obj.c_str(),
                        db_acct_str_obj.c_str(), db_passwd_str_obj.c_str()) < 0) {
		return NULL;
	}

	return connect();
}

MYSQL* CMySQL::connect(void)
{
	if(!initialized) {
		return NULL;
	}
    m_MYSQL = mysql_init(m_MYSQL);
    if(m_MYSQL == NULL) {
        return NULL;
    }
    
    m_MYSQL = mysql_real_connect(m_MYSQL, m_hostname_str_ptr, m_acct_str_ptr, m_passwd_str_ptr, 
                                 m_dbname_str_ptr, m_port_num, NULL, 0);
    if(!m_MYSQL) {
        return NULL;
    }
	
    if(mysql_autocommit(m_MYSQL, m_auto_commit) != 0) {
        this->disconnect();
        return NULL;
    }
    
	return m_MYSQL;
}

void CMySQL::disconnect(void)
{
	if(m_MYSQL) {
        mysql_close(m_MYSQL);
		m_MYSQL = NULL;
	}
}

int CMySQL::get_result(CFLAG flag)
{
    m_result_ptr = mysql_use_result(m_MYSQL);    
    m_result_code = mysql_errno(m_MYSQL);
    if(m_result_code) {
        m_errmsg_str_obj = mysql_error(m_MYSQL);    
    } else {
		m_errmsg_str_obj = "OK";
	}
    
	if(flag == CLEAR) {
		this->clear_res();
	}
    
    return m_result_code;
}

string &CMySQL::get_error_msg(void)
{
	return m_errmsg_str_obj;
}

my_ulonglong CMySQL::get_affected_rows(void)
{
    return mysql_affected_rows(m_MYSQL);
}

int CMySQL::get_num_rows(void)
{
    return static_cast<int>(mysql_num_rows(m_result_ptr));
}

int CMySQL::get_num_fields(void)
{
    return static_cast<int>(mysql_num_fields(m_result_ptr));
}

MYSQL_RES *CMySQL::get_res(void)
{
	return m_result_ptr;
}

void CMySQL::clear_res(void)
{
    mysql_free_result(m_result_ptr);
}

char *CMySQL::get_value(int row, int field)
{
    int row_count = 0;
    MYSQL_ROW selected_row;
   
    if(get_num_fields() < field) {
        return NULL;
    }
    
    while((selected_row = mysql_fetch_row(m_result_ptr))) {
        if(row_count == row) {
            break;
        }
        row_count++;
    }
    
	return selected_row[field];
}

int CMySQL::exec_query(char *query_str_ptr)
{
	return this->exec_query(query_str_ptr, NOT_CLEAR);
}

int CMySQL::exec_query(string &query_str_ref)
{
	return this->exec_query((char *)query_str_ref.c_str(), NOT_CLEAR);
}

int CMySQL::exec_query(char *query_str_ptr, CFLAG flag)
{
    if(m_MYSQL == NULL) {
        return -1;
    }
    
    mysql_query(m_MYSQL, query_str_ptr);	
	return get_result(flag);
}

unsigned long CMySQL::escape_string(char *to, const char *from, size_t length)
{
    return mysql_real_escape_string(m_MYSQL, to, from, length);
}
#endif
#endif
