#include "read_recv.h" 
#include <unistd.h>
#include <errno.h>


ssize_t writen(int fd, void * buf, size_t count)
{

	size_t nleft = count;
	ssize_t nwrite;
	char * bufp = static_cast<char *>(buf);
	while(nleft > 0)
	{
		if((nwrite = write(fd, bufp, nleft)) < 0)
		{
			if(errno == EINTR)//如果信号被中断，仍然要继续发送数据。
				continue;
			return -1;
		}
		else if(nwrite == 0)
			continue;
		bufp += nwrite;
		nleft -= nwrite;
	}
	return count;
}
