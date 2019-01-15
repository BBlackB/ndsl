#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include "../catch.hpp"
#include "ndsl/net/PipeAndFifo.h"
#define namepth1 "/mnt/unixsocket/pipe1"
#define namepth2 "/mnt/unixsocket/pipe2"

using namespace ndsl::net;
using namespace std;

bool pfflag = false;
void fun(void *a) {pfflag = true;}

bool pfflagsend = false;
static void sendTest(void *a) {pfflagsend = true;}

bool pfflagerror = false;
static void isError(int a, int b){pfflagerror = true;}

bool pfflagrecv = false;
static void recvTest(void *a){pfflagrecv = true;}

TEST_CASE("PipeIpc")
{
	SECTION("pipe")
	{
		EventLoop loop;
		REQUIRE(loop.init() == S_OK);
		
		int fd[2];
		PipeAndFifo *pipe = new PipeAndFifo(&loop);
		REQUIRE(pipe->createPipe(fd) == S_OK);
		
		pipe->onError(isError);
		char *sendbuf = (char *)malloc(sizeof(char) * 10);
		strcpy(sendbuf,"hello son\0");
		REQUIRE(pipe->onSend(sendbuf, strlen("hello son"), 0, sendTest, NULL) == S_OK);
		
		int childpid;
		if ((childpid = fork()) == 0)
		{
			char buf[20];
			memset(buf, 0, sizeof(buf));
			read(fd[1], buf, 20);
			REQUIRE(strcmp("hello son", buf) == 0);
			cout<<"in child"<<endl;
			write(fd[1], buf, 20);
		}else
		{
			sleep(2);
			loop.quit();
			// REQUIRE(loop.loop(&loop) == S_OK);
			char buf[20];
			memset(buf, 0, sizeof(buf));
			if (pipe->onRecv(buf,20, 0, recvTest, NULL) != S_OK)
			{
				cout<<"recv error"<<strerror(errno)<<endl;
			}else
				cout<<"in father recv"<<buf<<endl;
			REQUIRE(strcmp("hello son", buf) == 0);
		cout<<"in father"<<endl;
		}
	}
	
}

