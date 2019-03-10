// VD22.cpp : Tao client ket noi den server genk.vn
// 

#include "pch.h"
#include <iostream>

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

//#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include "ws2tcpip.h"

int VD22()
{
	// Khoi tao Winsock
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// Khoi tao socket
	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Khai bao dia chi server: trong truong hop biet dia chi IP
	/*SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("222.255.239.73");
	addr.sin_port = htons(80);*/

	// Phan giai dia chi tu ten mien
	addrinfo *res;
	SOCKADDR_IN addr;
	int ret = getaddrinfo("genk.vn", "http", NULL, &res);
	if (ret == 0)
		memcpy(&addr, res->ai_addr, res->ai_addrlen);
	else
	{
		printf("Khong phan giai duoc ten mien");
		system("PAUSE");
		return 1;
	}

	// Ket noi den server
	ret = connect(client, (SOCKADDR *)&addr, sizeof(addr));

	if (ret == 0)
	{
		printf("Ket noi thanh cong");
		char msg[] = "GET / HTTP/1.1\r\nHost: genk.vn\r\n\r\n";
		send(client, msg, strlen(msg), 0);

		// Nhan du lieu tu server
		char buf[1024];
		while (true)
		{
			ret = recv(client, buf, sizeof(buf), 0);
			if (ret <= 0)
				break;

			// them ky tu ket thuc xau
			if (ret < sizeof(buf))
				buf[ret] = 0;

			printf(buf);
		}
	}
	else
	{
		printf("Ket noi that bai ret = %d\n", ret);
		ret = WSAGetLastError();
		printf("Ma loi %d", ret);
	}

	closesocket(client);
	WSACleanup();

	system("PAUSE");

	return 0;
}