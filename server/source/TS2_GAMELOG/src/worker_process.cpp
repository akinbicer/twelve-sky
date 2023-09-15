/****************************************************************************
 *
 * CTSD : Common Transaction Service
 *
 * CopyRight(C) 2003 Sean Kim All Rights reserved.
 * Author : Sean Kim (sean@0x31.com)
 *
 * $Id: worker_process.cpp,v 1.29 2007/10/20 08:41:13 wglee Exp $
 *
 * Redistribution and use in source and binary forms, with or with out
 * modification, are not permitted without author's permission.
 *
 ****************************************************************************/

#include "log.h"
#include "local.h"
#include "global.h"
#include "socket.h"
#include "pointer.h"
#include <signal.h>
#include "worker_thread.h"
#include "worker_process.h"
#include "cts_util.h"
#include "H01_MainApplication.h"

using namespace SDLog;
using namespace SDSocket;

static void sig_handler(int signo)
{
	alarm(10);
	//LOG_TO_FILE("!----->alarm test\n");
	//mSERVER.PROCESS_FOR_TIMER();
}

extern CScoreBoard *g_score_board_obj_ptr;
CWorkerProcess::CWorkerProcess(void) 
{
    m_pid = ::getpid();
}

CWorkerProcess::CWorkerProcess(SOCKET listen_socket) throw(Exception) 
{
    set_listen_socket(listen_socket);
    m_pid = ::getpid();
}

CWorkerProcess::~CWorkerProcess(void) 
{
}

void CWorkerProcess::set_listen_socket(SOCKET listen_socket) throw(Exception) 
{
    if(listen_socket < 0) {
        throw Exception(msg_str_obj.c_str(), "Invalid socket is passed.", -1);
    }
    
    m_listen_socket_obj.SetDescriptor(listen_socket);
}

#ifdef __NB__
int CWorkerProcess::set_nonblock(int cli_fd)
{
	int old_flag = 0;

	old_flag = fcntl(cli_fd, F_GETFL);
	return fcntl(cli_fd, F_SETFL, old_flag | O_NONBLOCK);
}
#endif
#define MAX_SIZE_OF_FD      512 
int CWorkerProcess::start_svr_service(void) 
{
	int i = 0;
	int n_read = 0;
	int n_send =0;
	int ret_val = 0;
	struct sigaction act;
	socklen_t cli_len = 0;
	int client_sockfd = -1;
	struct sockaddr_in cli_addr;
#ifdef __EPOLL__
	int res = 0;
	int epfd = -1;
	struct epoll_event ev;
	struct epoll_event *events;
	int listenfd = m_listen_socket_obj.GetDescriptor();
#elif  __POLL__
	int max_num = 0;
	struct pollfd cli_fd[MAX_SIZE_OF_FD];
#endif

	try {
		if(!mSERVER.Init(&ret_val)) {
			LOG_TO_FILE_2("![%s] : ret_val %d\n", __FUNCTION__, ret_val);
			throw Exception("CWorkerProcess::start_svr_service", "server object initialization failed", -1);
		}

		act.sa_handler = sig_handler;
		act.sa_flags = 0;
		sigemptyset(&act.sa_mask);

		sigaction(SIGALRM, &act, 0);
		//alarm(10);
#ifdef __EPOLL__
		events = (struct epoll_event *)malloc(sizeof(events) * MAX_SIZE_OF_FD);

		epfd = epoll_create(MAX_SIZE_OF_FD);
		if(!epfd) {
			LOG_TO_FILE_2("![%s] : %s\n", __FUNCTION__, strerror(errno));
			throw Exception("CWorkerProcess::start_svr_service", "epoll create failed", -2);
		}
		ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
		ev.data.fd = listenfd;
		if(epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) < 0) {
			LOG_TO_FILE_2("![%s] : %s\n", __FUNCTION__, strerror(errno));
			throw Exception("CWorkerProcess::start_svr_service", "epoll control failed", -3);
		}

		for( ; ; ) 
		{
			res = epoll_wait(epfd, events, MAX_SIZE_OF_FD, 1000);
			if(res == -1) {
				if(errno != EINTR) {
					LOG_TO_FILE_2("![%s] : %s\n", __FUNCTION__, strerror(errno));
					throw Exception("CWorkerProcess::start_svr_service", "epoll wait failed", -4);
				}
				continue;
			}

			for(i = 0; i < res; i++) 
			{
				if(events[i].data.fd == listenfd) 
				{
					ProcessResponse(WM_NETWORK_MESSAGE_1, &events[i].data.fd, FD_READ);
				}
			}
		}
#endif
	} catch (Exception e) {
		LOG_TO_FILE_3("![%d] %s (error code = %d) \n", m_pid, e.getMessage().c_str(), e.getCode());
		return -2;
	}
	return 1;
}
