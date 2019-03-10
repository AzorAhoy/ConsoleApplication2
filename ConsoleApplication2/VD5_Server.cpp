// VD5_Server.cpp : Defines the entry point for the console application.
//
#include "pch.h"
#include <iostream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

//#include "stdafx.h"

#include "winsock2.h"

struct sinhvien
{
	int mssv;
	char hoten[32];
	char lop[16];
	float dToan;
	float dLy;
	float dHoa;
};

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(9000);

	bind(listener, (SOCKADDR *)&addr, sizeof(addr));
	listen(listener, 5);

	SOCKET client = accept(listener, NULL, NULL);

	char buf[256];
	int ret = recv(client, buf, sizeof(buf), 0);

	buf[ret] = 0;
	printf("Received: %s\n", buf);

	struct sinhvien sv;
	memcpy(&sv, buf, sizeof(sv));

	int d;
	//int ret;

	while (1)
	{
		ret = recv(client, (char *)&d, 4, 0);
		if (ret <= 0)
			break;

		printf("Received: %d\n", d);
	}

	closesocket(client);
	closesocket(listener);

	system("PAUSE");

	WSACleanup();

	return 0;
}