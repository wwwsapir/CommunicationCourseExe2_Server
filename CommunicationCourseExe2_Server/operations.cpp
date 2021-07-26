#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>

void CreateResponse(char recvMessage[], char sendBuff[])
{
	if (strcmp(recvMessage, "What's the time?")
}

void GetTime(char sendBuff[])
{
	// Get the current time.
	time_t timer;
	time(&timer);
	// Parse the current time to printable string.
	strcpy(sendBuff, ctime(&timer));
	sendBuff[strlen(sendBuff) - 1] = '\0'; //to remove the new-line from the created string
}