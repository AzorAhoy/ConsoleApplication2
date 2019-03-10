// test2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#define _WIN32_WINNT 0x0500
#define MAX 256

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <sstream>
#include <string>
#include <iostream>
#include <string>
#include <direct.h>
// initial value
TCHAR szDrive[] = _T(" A:");
#define MAX 256

void main(int argc, char * argv[])
{
	TCHAR buffer[256] = TEXT("");
	TCHAR szDescription[8][32] = { TEXT("NetBIOS"),
		TEXT("DNS hostname"),
		TEXT("DNS domain"),
		TEXT("DNS fully-qualified"),
		TEXT("Physical NetBIOS"),
		TEXT("Physical DNS hostname"),
		TEXT("Physical DNS domain"),
		TEXT("Physical DNS fully-qualified") };
	int cnf = 0;
	DWORD dwSize = sizeof(buffer);

	for (cnf = 0; cnf < ComputerNameMax; cnf++)
	{
		if (!GetComputerNameEx((COMPUTER_NAME_FORMAT)cnf, buffer, &dwSize))
		{
			_tprintf(TEXT("GetComputerNameEx failed (%d)\n"), GetLastError());
			return;
		}
		else _tprintf(TEXT("%s: %s\n"), szDescription[cnf], buffer);

		dwSize = _countof(buffer);
		ZeroMemory(buffer, dwSize);
	}
	DWORD mydrives = 100;// buffer length
	wchar_t lpBuffer[100];// buffer for drive string storage
	//char lpBuffer[100];
	DWORD test = GetLogicalDriveStrings(mydrives, lpBuffer);
	DWORD test2 = GetLogicalDrives();
	printf("The logical drives of this machine are:%lu\n\n", test);
	char * b = (char*)lpBuffer;
	//std::wstring ws(lpBuffer);
	//// your new String
	//std::string str(ws.begin(), ws.end());
	//// Show String
	//std::cout << str;

	for (int i = 0; i < sizeof(lpBuffer); i++) { 
		//if ((char *) lpBuffer[i] >= "a" && (char *)  lpBuffer[i] <= "Z")
		//{
			printf("%c", lpBuffer[i]);
		//}
		
	}
	printf("\n");

	DWORD uDriveMask = GetLogicalDrives();
	printf("The bitmask of the logical drives in hex: %0X\n", uDriveMask);
	printf("The bitmask of the logical drives in decimal: %d\n", uDriveMask);
	if (uDriveMask == 0)
		printf("\nGetLogicalDrives() failed with failure code: %d\n", GetLastError());
	else
	{
		printf("\nThis machine has the following logical drives:\n");
		while (uDriveMask)
		{// use the bitwise AND, 1–available, 0-not available
			if (uDriveMask & 1)
				printf("%s\n", szDrive);
			// increment... 
			++szDrive[1];
			// shift the bitmask binary right
			uDriveMask >>= 1;
		}
		printf("\n ");
	}
	//return 0;

	BOOL  fResult;
	unsigned __int64 i64FreeBytesToCaller,
		i64TotalBytes,
		i64FreeBytes;
	fResult = GetDiskFreeSpaceEx(L"C:\\",
		(PULARGE_INTEGER)&i64FreeBytesToCaller,
		(PULARGE_INTEGER)&i64TotalBytes,
		(PULARGE_INTEGER)&i64FreeBytes);
	if (fResult)
	{
		printf("\n\nGetDiskFreeSpaceEx reports\n\n");
		printf("Available space to caller = %I64u MB\n",
			i64FreeBytesToCaller / (1024 * 1024));
		printf("Total space               = %I64u MB\n",
			i64TotalBytes / (1024 * 1024));
		printf("Free space on drive       = %I64u MB\n",
			i64FreeBytes / (1024 * 1024));
	}

	DWORD d = GetLogicalDrives();
	int i;
	TCHAR Drive[] = _T("A:\\");
	for (i = 0; i < 26; i++)
	{
		if (d & (1 << i))
		{
			Drive[0] = _T('A') + i;
			GetDiskFreeSpaceEx(Drive, .....);
		}
	}
}
