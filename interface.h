#ifndef _POSIXSRV_INTERFACE_H_
#define _POSIXSRV_INTERFACE_H_

enum {
	posixsrv_read,
	posixsrv_write,
	posixsrv_open,
	posixsrv_close,
	posixsrv_link,
	posixsrv_unlink,
	posixsrv_fcntl,
	posixsrv_ftruncate,
	posixsrv_lseek,
	posixsrv_dup,
	posixsrv_dup2,
	posixsrv_pipe,
	posixsrv_mkfifo,
	posixsrv_chmod,
	posixsrv_fstat,
	posixsrv_accept,
	posixsrv_accept4,
	posixsrv_bind,
	posixsrv_connect,
	posixsrv_getpeername,
	posixsrv_getsockname,
	posixsrv_getsockopt,
	posixsrv_listen,
	posixsrv_recvfrom,
	posixsrv_sendto,
	posixsrv_socket,
	posixsrv_shutdown,
	posixsrv_setsockopt,
	posixsrv_ioctl,
	posixsrv_utimes,
	posixsrv_poll,
	posixsrv_setpgid,
	posixsrv_getpgid,
	posixsrv_setpgrp,
	posixsrv_getpgrp,
	posixsrv_setsid,
	posixsrv_fork,
	posixsrv_exec,
};

#endif