// clientinfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*3. Viết chương trình clientinfo thực hiện kết nối đến một máy chủ xác định và gửi thông tin về tên máy, 
danh sách các ổ đĩa có trong máy, kích thước các ổ đĩa. 
Địa chỉ (tên miền) và cổng nhận vào từ tham số dòng lệnh. VD: clientinfo.exe localhost 1234 */

#include "pch.h"
#include <iostream>
#include "winsock2.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <sstream>
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


int main(int argc, char * argv[])
{
	char * host = argv[1];
	char * port = argv[2];
	//std::cout << host<<"  "<<port;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host);
	addr.sin_port = htons(atoi(argv[2]));
	
	//system("PAUSE");
	int ret = connect(client, (SOCKADDR *)&addr, sizeof(addr));

	char buf[1024];
	int offset = 0;
	char computerName[256];
	DWORD nSize;
	GetComputerNameA(computerName, &nSize);
	memcpy(buf, computerName, strlen(computerName) + 1);
	offset += strlen(computerName) + 1;

	char driveString[256];
	DWORD len = GetLogicalDriveStringsA(sizeof(driveString), driveString);
	int numDriver = len / 4;

	memcpy(buf + offset, & numDriver, sizeof(numDriver));
	offset += sizeof(numDriver);

	DWORD sectorsPerCluster;
	DWORD bytesPerSector;
	DWORD numberOfFreeClusters;
	DWORD totalNumberOfClusters;
	double size;

	for (int i = 0; i < numDriver; i++)
	{
		GetDiskFreeSpaceA(
			driveString + i * 4, 
			&sectorsPerCluster, 
			&bytesPerSector, 
			&numberOfFreeClusters, 
			&totalNumberOfClusters
		);
		size = (double)sectorsPerCluster * (double)bytesPerSector * (double)totalNumberOfClusters / (1 << 30);
		
		memcpy(buf + offset, driveString + i * 4, 1);
		offset += 1;

		memcpy(buf + offset, &size, sizeof(size));
		offset += sizeof(size);
	}

	send(client, buf, offset, 0);
	while (true)
	{
		printf("Nhap du lieu: ");
		gets_s(buf, sizeof(buf));
		int t = send(client, buf, strlen(buf), 0);
		//file << buf << "\r\n";
		//file << endl;

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
