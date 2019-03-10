// Server1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "winsock2.h"
#include <iostream>

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	unsigned long ul = 1;
	ioctlsocket(listener, FIONBIO, &ul);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(9000);

	bind(listener, (SOCKADDR *) &addr,sizeof(addr));
	listen(listener, 5);

	char buf[256];
	int ret;

	SOCKET clients[64];
	int numClients = 0;

	while (true)
	{
		SOCKET client = accept(listener, NULL, NULL);
		if (client == INVALID_SOCKET)
		{
			ret = WSAGetLastError();
			if (ret != WSAEWOULDBLOCK)
			{
				break;
			}
		}
		else
		{
			printf("New client accepted: %d\n", client);
			clients[numClients] = client;
			numClients++;
		}

		for (int i = 0; i < numClients; i++)
		{
			ret = recv(clients[i], buf, sizeof(buf), 0);
			if (ret == SOCKET_ERROR)
			{
				ret = WSAGetLastError();
			}
			else
			{
				buf[ret] = 0;
				printf("Received: %s\n", buf);
			}
		}
	}
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
