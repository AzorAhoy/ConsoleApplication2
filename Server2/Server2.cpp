// Server2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "winsock2.h"

DWORD WINAPI ClientThread(LPVOID);
void RemoveClient(SOCKET);

SOCKET clients[64];
int numClients;

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(9000);

	bind(listener, (SOCKADDR *) &addr, sizeof(addr));
	listen(listener, 5);

	numClients = 0;

	while (true)
	{
		SOCKET client = accept(listener, NULL, NULL);
		printf("New client accepted: %d\n", client);

		//Luu client vao vi tri cuoi
		clients[numClients] = client;
		numClients++;

		CreateThread(0, 0, ClientThread, &client, 0, 0);
	}
	return 0;
}

DWORD WINAPI ClientThread(LPVOID lpParam) {
	SOCKET client = *(SOCKET *)lpParam;
	char buf[1024];
	int ret;

	while (true)
	{
		ret = recv(client, buf, sizeof(buf), 0);
		if (ret <= 0)
		{
			//Ngat ket noi, xoa client khoi mang
			RemoveClient(client);
			break;
		}
		
		buf[ret] = 0;
		printf("Received from %d: %s\n", client, buf);

		//FWD tin nhan den clients
		//for (int i = 0; i < numClients; i++)
		//{
		//	if (clients[i] == client)
		//	{
		//		send(clients[i],buf, ret, 0);
		//	}
		//}

		//Gui tin nhan den client xac dinh boi id
		char id[64];
		ret = sscanf(buf, "%s", id);
		char * sendBuf = buf + strlen(id) + 1;

		int targetID = atoi(id);
		for (int i = 0; i < numClients; i++)
		{
			if (clients[i] == targetID)
			{
				send(clients[i], sendBuf, strlen(sendBuf), 0);
			}
		}
	}
	closesocket(client);
	return 0;
}

void RemoveClient(SOCKET client) {
	//Tim chi so phan tu
	int i = 0;
	for (; i < numClients; i++)
	{
		if (clients[i] == client)
			break;
	}

	//Xoa phan tu
	if (i < numClients - 1)
	{
		clients[i] = clients[numClients - 1];
		numClients--;
	}
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
