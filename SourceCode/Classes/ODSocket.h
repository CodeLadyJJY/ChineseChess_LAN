#ifndef _ODSOCKET_H_
#define _ODSOCKET_H_

#ifdef WIN32
	#include <winsock.h>
	typedef int socklen_t;
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <sys/inet.h>
	typedef int SOCKET
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
#endif




#include <iostream>
using namespace std;

class ODSocket {
public:
	int socketID;

	ODSocket(SOCKET sock = INVALID_SOCKET);
	~ODSocket();
	bool Create(int af, int type, int protocol = 0);
	bool Connect(const string ip, unsigned short port);
	bool Bind(unsigned short port);
	bool Listen(int backlog = 5);
	bool Accept(ODSocket &s, char *fromip = NULL);
	int Send(const char *buf, int len, int flags = 0);
	int Recv(char *buf, int len, int flags = 0);
	int Close();
	int GetError();

	// 为win32定义的函数
	static int Init();		// 初始化winsock DLL
	static int Clean();		// 清理winsock DLL

	static bool DnsParse(const char *domain, char *ip);	// 域名解析
	ODSocket& operator = (SOCKET s);
	operator SOCKET();

private:
	SOCKET m_sock;
};

#endif