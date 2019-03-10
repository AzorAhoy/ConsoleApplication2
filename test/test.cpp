// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
//#include <iostream>
using namespace std;

int main(void)
{

	char filename[] = "Informacije.txt";
	fstream appendFileToWorkWith;

	appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);


	// If file does not exist, Create new file
	if (!appendFileToWorkWith)
	{
		cout << "Cannot open file, file does not exist. Creating new file..";

		appendFileToWorkWith.open(filename, fstream::in | fstream::out | fstream::trunc);
		appendFileToWorkWith << "\n";
		appendFileToWorkWith.close();

	}
	else
	{    // use existing file
		cout << "success " << filename << " found. \n";
		cout << "\nAppending writing and working with existing file" << "\n---\n";

		appendFileToWorkWith << "Appending writing and working with existing file" << "\n---\n";
		appendFileToWorkWith.close();
		cout << "\n";

	}




	return 0;
}