#include "ODSocket.h"

#ifdef WIN32
	#pragma comment(lib, "wsock32")
#endif

ODSocket::ODSocket(SOCKET sock){ m_sock = sock; }

ODSocket::~ODSocket(){}

// 初始化winsock DLL
int ODSocket::Init()
{
#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);

	if (WSAStartup(version, &wsaData))
		return -1;
#endif
	return 0;
}

// 清理winsock DLL
int ODSocket::Clean()
{
#ifdef WIN32
	return (WSACleanup());
#endif
	return 0;
}

// 重载运算符 =
ODSocket& ODSocket::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

// 类型转换 SOCKET() 重载
ODSocket::operator SOCKET()
{
	return m_sock;
}

// 创建socket
bool ODSocket::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	if (m_sock == INVALID_SOCKET)
		return false;
	return true;
}

// 连接服务器
bool ODSocket::Connect(const string ip, unsigned short port)
{
	struct sockaddr_in svraddr;

	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip.c_str());
	svraddr.sin_port = htons(port);

	if (connect(m_sock, (struct sockaddr *)&svraddr, sizeof(svraddr)) == SOCKET_ERROR)
		return false;
	return true;
}

// 绑定端口
bool ODSocket::Bind(unsigned short port)
{
	struct sockaddr_in svraddr;

	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);

	// 设置调用close(socket)后,仍可继续重用该socket。调用close(socket)一般不会立即关闭socket，而经历TIME_WAIT的过程。
	int opt = 1;
	if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
		return false;

	if (bind(m_sock, (struct sockaddr *)&svraddr, sizeof(svraddr)) == SOCKET_ERROR)
		return false;

	return true;
}

// 开启监听
bool ODSocket::Listen(int backlog)
{
	if (listen(m_sock, backlog) == SOCKET_ERROR)
		return false;
	return true;
}

// 接受客户端请求
bool ODSocket::Accept(ODSocket &s, char *fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr *)&cliaddr, &addrlen);

	if (sock == SOCKET_ERROR)
		return false;

	s = sock;

	if (fromip != NULL)
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));

	return true;
}

// 发送数据
int ODSocket::Send(const char *buf, int len, int flags)
{
	int bytes;
	int count = 0;

	while (count < len)
	{
		bytes = send(m_sock, buf + count, len - count, flags);
		if (bytes == -1 || bytes == 0)
			return -1;
		count += bytes;
	}

	return count;
}

// 接收数据
int ODSocket::Recv(char *buf, int len, int flags)
{
	return (recv(m_sock, buf, len, flags));
}

// 关闭socket
int ODSocket::Close()
{
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}

// 获取错误信息
int ODSocket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (SOCKET_ERROR);
#endif
}

// 域名解析
bool ODSocket::DnsParse(const char *domain, char *ip)
{
	struct hostent *p;

	if ((p = gethostbyname(domain)) == NULL)
		return false;

	sprintf(ip, "%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0],
		(unsigned char)p->h_addr_list[0][1],
		(unsigned char)p->h_addr_list[0][2],
		(unsigned char)p->h_addr_list[0][3]);

	return true;
}