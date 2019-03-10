// TCPServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*. Viết chương trình TCPServer, đợi kết nối ở cổng xác định bởi tham số dòng lệnh. 
	Mỗi khi có client kết nối đến, thì gửi xâu chào được chỉ ra trong một tệp tin xác định, 
	sau đó ghi toàn bộ nội dung client gửi đến vào một tệp tin khác được chỉ ra trong tham số 
	dòng lệnh TCPServer.exe VD: TCPServer.exe 8888 chao.txt client.txt*/


#include "pch.h"
#include <iostream>
#include "winsock2.h"
#include <fstream>
using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

int main(int argc, char *argv[])
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(atoi(argv[1]));

	bind(listener, (SOCKADDR *)&addr, sizeof(addr));
	listen(listener, 5);

	SOCKET client = accept(listener, NULL, NULL);

	// Doc cau chao tu file
	char buf[256];
	FILE *f = fopen(argv[2], "r");
	fgets(buf, sizeof(buf), f);
	fclose(f);

	// Gui cho client
	send(client, buf, strlen(buf), 0);

	f = fopen(argv[3], "w");
	while (true)
	{
		// Nhan du lieu tu client
		int ret = recv(client, buf, sizeof(buf), 0);
		if (ret <= 0)
			break;

		// Them ky tu ket thuc xau
		buf[ret] = 0;
		printf("Received: %s\n", buf);
		// Luu vao file
		fprintf(f, "%s\n", buf);
	}
	fclose(f);

	closesocket(client);
	closesocket(listener);
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