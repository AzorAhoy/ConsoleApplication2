// TCPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*1. Viết chương trình TCPClient, kết nối đến một máy chủ xác định bởi tên miền hoặc địa chỉ IP. 
	Sau đó nhận dữ liệu từ bàn phím và gửi đến server. 
	Tham số được truyền vào từ dòng lệnh có dạng TCPClient.exe */

#include "pch.h"
#include <iostream>
#include "winsock2.h"
#include <fstream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;
//#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"

int main(int argc, char *argv[])
{
	/*printf("So cac tham so: %d\n", argc);
	for (int i = 0; i < argc; i++)
		printf("Tham so %d: %s\n", i, argv[i]);*/

		// Kiem tra tinh dung dan cua tham so

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));

	connect(client, (SOCKADDR *)&addr, sizeof(addr));

	char buf[256];

	// Nhan cau chao tu server
	int ret = recv(client, buf, sizeof(buf), 0);
	if (ret <= 0)
		return 1;

	buf[ret] = 0;
	
	printf(buf);

	while (true)
	{
		printf("Nhap chuoi ky tu: ");
		gets_s(buf, sizeof(buf));

		send(client, buf, strlen(buf), 0);

		if (strncmp(buf, "exit", 4) == 0)
			break;
	}

	closesocket(client);
	WSACleanup();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
