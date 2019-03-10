// VD21.cpp : Tao client gui thong diep den netcat server
// 

#include "pch.h"
#include <iostream>

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

//#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"

int VD21()
{
	// Khoi tao Winsock
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// Khoi tao socket
	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Khai bao dia chi server
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9000);

	// Ket noi den server
	int ret = connect(client, (SOCKADDR *)&addr, sizeof(addr));

	if (ret == 0)
	{
		printf("Ket noi thanh cong");
		char msg[] = "Hello server. This is a new client.";
		send(client, msg, strlen(msg), 0);

		// Nhan du lieu tu server
		char buf[256];
		while (true)
		{
			ret = recv(client, buf, sizeof(buf), 0);
			if (ret <= 0)
				break;

			// them ky tu ket thuc xau
			if (ret < 256)
				buf[ret] = 0;

			printf(buf);

			// neu server gui "exit" thi ket thuc chuong trinh client
			if (strncmp(buf, "exit", 4) == 0)
				break;
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