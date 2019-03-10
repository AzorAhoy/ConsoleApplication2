// VD5_Client.cpp : Defines the entry point for the console application.
//
#include "pch.h"
#include <iostream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

//#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
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


int VD5_Client()
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

	system("PAUSE");

	// Ket noi den server
	int ret = connect(client, (SOCKADDR *)&addr, sizeof(addr));

	struct sinhvien sv;
	sv.mssv = 20151234;
	strcpy(sv.hoten, "Nguyen Van A");
	strcpy(sv.lop, "LTU14");
	sv.dToan = 9;
	sv.dHoa = 8;
	sv.dLy = 8.5;

	send(client, (char *)&sv, sizeof(sv), 0);

	/*int n;

	while (1)
	{
		printf("Nhap so nguyen ban phim: ");
		scanf("%d", &n);

		send(client, (char *)&n, sizeof(n), 0);

		if (n == 0)
			break;
	}*/

	closesocket(client);
	WSACleanup();

	return 0;
}