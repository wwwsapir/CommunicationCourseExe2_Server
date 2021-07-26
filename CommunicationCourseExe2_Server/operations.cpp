#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>

#define SEND_BUFFER_LENGTH 255

void GetTime(char sendBuff[])
{
	// Get the current time.
	time_t timer;
	time(&timer);
	// Parse the current time to printable string.
	strcpy(sendBuff, ctime(&timer));
	sendBuff[strlen(sendBuff) - 1] = '\0'; //to remove the new-line from the created string
}

void GetTimeWithoutDate(char sendBuff[])
{
	// Get the current time.
	time_t timer;
	time(&timer);
	// Parse the current time to required string
	char buffer[80];
	struct tm * timeInfo = localtime(&timer);
	strftime(sendBuff, SEND_BUFFER_LENGTH, "%H:%M:%S", timeInfo);
}