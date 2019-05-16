#include <sys/types.h>
#include <sys/msg.h>
#include <sys/mman.h>

#include <errno.h>

#include "interface.h"


int posixsrv_port = -1;


int px_connect()
{
	oid_t oid;

	if (lookup("/posixsrv", NULL, &oid) < 0)
		return -ENOSYS;

	posixsrv_port = oid.port;

	return EOK;
}


int px_init()
{
	int err;
	msg_t msg;
	posixsrv_o_t *_o = (void *)msg.o.raw;

	msg.type = posixsrv_init;

	msg.i.data = NULL;
	msg.i.size = 0;
	msg.o.data = NULL;
	msg.o.size = 0;

	if ((err = msgSend(posixsrv_port, &msg)) < 0)
		return err;

	return _o->errno;
}


int px_write(ssize_t *retval, int fd, const void *buf, size_t nbyte)
{
	int err;
	msg_t msg;
	posixsrv_i_t *_i = (void *)msg.i.raw;
	posixsrv_o_t *_o = (void *)msg.o.raw;

	msg.type = posixsrv_write;

	msg.i.data = (void *)buf;
	msg.i.size = nbyte;
	msg.o.data = NULL;
	msg.o.size = 0;

	_i->write.fd = fd;

	if ((err = msgSend(posixsrv_port, &msg)) < 0) {
		*retval = -1;
		return err;
	}

	*retval = _o->write.retval;
	return _o->errno;
}


int px_read(ssize_t *retval, int fd, void *buf, size_t nbyte)
{
	int err;
	msg_t msg;
	posixsrv_i_t *_i = (void *)msg.i.raw;
	posixsrv_o_t *_o = (void *)msg.o.raw;

	msg.type = posixsrv_read;

	msg.i.data = NULL;
	msg.i.size = 0;
	msg.o.data = (void *)buf;
	msg.o.size = nbyte;

	_i->read.fd = fd;

	if ((err = msgSend(posixsrv_port, &msg)) < 0) {
		*retval = -1;
		return err;
	}

	*retval = _o->read.retval;
	return _o->errno;
}


int px_open(int *retval, const char *path, int oflag, mode_t mode)
{
	int err;
	msg_t msg;
	posixsrv_i_t *_i = (void *)msg.i.raw;
	posixsrv_o_t *_o = (void *)msg.o.raw;

	msg.type = posixsrv_open;

	msg.i.data = path;
	msg.i.size = strlen(path) + 1;
	msg.o.data = NULL;
	msg.o.size = 0;

	_i->open.oflag = oflag;
	_i->open.mode = mode;

	if ((err = msgSend(posixsrv_port, &msg)) < 0) {
		*retval = -1;
		return err;
	}

	*retval = _o->open.retval;
	return _o->errno;
}


int px_close(ssize_t *retval, int fd)
{
	int err;
	msg_t msg;
	posixsrv_i_t *_i = (void *)msg.i.raw;
	posixsrv_o_t *_o = (void *)msg.o.raw;

	msg.type = posixsrv_close;

	msg.i.data = NULL;
	msg.i.size = 0;
	msg.o.data = NULL;
	msg.o.size = 0;

	_i->close.fd = fd;

	if ((err = msgSend(posixsrv_port, &msg)) < 0) {
		*retval = -1;
		return err;
	}

	*retval = _o->close.retval;
	return _o->errno;
}


int px_recvfrom(ssize_t *retval, int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len)
{
	int err;
	msg_t msg;
	posixsrv_i_t *_i = (void *)msg.i.raw;
	posixsrv_o_t *_o = (void *)msg.o.raw;

	msg.type = posixsrv_recvfrom;

	msg.i.data = NULL;
	msg.i.size = 0;
	msg.o.data = buffer;
	msg.o.size = length;

	_i->recvfrom.socket = socket;
	_i->recvfrom.flags = flags;

	if ((err = msgSend(posixsrv_port, &msg)) < 0) {
		*retval = -1;
		return err;
	}

	if (address != NULL) {
		*address_len = min(*address_len, _o->recvfrom.address_len);
		memcpy(address, _o->recvfrom.address, *address_len);
	}

	*retval = _o->recvfrom.retval;
	return _o->errno;
}


int px_dup(ssize_t *retval, int fd)
{
	int err;
	msg_t msg;
	posixsrv_i_t *_i = (void *)msg.i.raw;
	posixsrv_o_t *_o = (void *)msg.o.raw;

	msg.type = posixsrv_dup;

	msg.i.data = NULL;
	msg.i.size = 0;
	msg.o.data = NULL;
	msg.o.size = 0;

	_i->dup.fd = fd;

	if ((err = msgSend(posixsrv_port, &msg)) < 0) {
		*retval = -1;
		return err;
	}

	*retval = _o->dup.retval;
	return _o->errno;
}


int px_dup2(ssize_t *retval, int fd1, int fd2)
{
	int err;
	msg_t msg;
	posixsrv_i_t *_i = (void *)msg.i.raw;
	posixsrv_o_t *_o = (void *)msg.o.raw;

	msg.type = posixsrv_dup2;

	msg.i.data = NULL;
	msg.i.size = 0;
	msg.o.data = NULL;
	msg.o.size = 0;

	_i->dup2.fd1 = fd1;
	_i->dup2.fd2 = fd2;

	if ((err = msgSend(posixsrv_port, &msg)) < 0) {
		*retval = -1;
		return err;
	}

	*retval = _o->dup2.retval;
	return _o->errno;
}


int px_pipe(ssize_t *retval, int fd[2])
{
	int err;
	msg_t msg;
	posixsrv_o_t *_o = (void *)msg.o.raw;

	msg.type = posixsrv_pipe;

	msg.i.data = NULL;
	msg.i.size = 0;
	msg.o.data = NULL;
	msg.o.size = 0;

	if ((err = msgSend(posixsrv_port, &msg)) < 0) {
		*retval = -1;
		return err;
	}

	fd[0] = _o->pipe.fd[0];
	fd[1] = _o->pipe.fd[1];

	*retval = _o->pipe.retval;
	return _o->errno;
}


int px_execve(ssize_t *retval, const char *path, char *const argv[], char *const envp[])
{
	int err;
	msg_t msg;
	posixsrv_o_t *_o = (void *)msg.o.raw;
	int i;
	char *p;

	msg.type = posixsrv_execve;

	msg.i.size = strlen(path) + 1;

	if (argv != NULL) {
		for (i = 0; argv[i] != NULL; ++i)
			msg.i.size += strlen(argv[i]) + 1;
	}

	msg.i.size++;

	if (envp != NULL) {
		for (i = 0; envp[i] != NULL; ++i)
			msg.i.size += strlen(envp[i]) + 1;
	}

	if ((p = msg.i.data = mmap(NULL, (msg.i.size + SIZE_PAGE - 1) & ~(SIZE_PAGE - 1), PROT_READ | PROT_WRITE, MAP_NONE, NULL, -1)) == MAP_FAILED) {
		*retval = -1;
		return ENOMEM;
	}
	p = stpcpy(p, path) + 1;

	if (argv != NULL) {
		for (i = 0; argv[i] != NULL; ++i)
			p = stpcpy(p, argv[i]) + 1;
	}

	p = stpcpy(p, "") + 1;

	if (envp != NULL) {
		for (i = 0; envp[i] != NULL; ++i)
			p = stpcpy(p, envp[i]) + 1;
	}

	msg.o.data = NULL;
	msg.o.size = 0;

	if ((err = msgSend(posixsrv_port, &msg)) < 0) {
		*retval = -1;
		return err;
	}

	munmap(msg.i.data, (msg.i.size + SIZE_PAGE - 1) & (SIZE_PAGE - 1));
	*retval = _o->execve.retval;
	return _o->errno;
}
