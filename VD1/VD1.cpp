// VD1.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "winsock2.h"
#include "ws2tcpip.h"

int main()
{
	WSADATA wsa;
	WORD version = MAKEWORD(2, 2);

	if (WSAStartup(version, &wsa) == 0)
	{
		printf("Khoi tao thanh cong\n");
	}
	else
	{
		printf("Khoi tao that bai\n");
	}

	addrinfo * result;
	sockaddr_in addr;

	int res = getaddrinfo("genk.vn", "http", NULL, &result);
	if (res == 0)
	{
		printf("Phan giai thanh cong\n");
		memcpy(&addr, result->ai_addr, result->ai_addrlen);

		printf("IP: %s", inet_ntoa(addr.sin_addr));
	}

	system("PAUSE");
	return 0;
}