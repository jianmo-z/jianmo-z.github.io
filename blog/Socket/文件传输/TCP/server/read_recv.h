#ifndef __READ_RECV_H__
#define __READ_RECV_H__

#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>

using std::cin;

ssize_t writen(int fd, void * buf, size_t count);

#endif // __READ_RECV_H__
