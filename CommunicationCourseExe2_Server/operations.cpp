#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define SEND_BUFFER_LENGTH 255

void getTimeUsingFormat(char sendBuff[], char formatStr[])
{
	// Get the current time.
	time_t timer;
	time(&timer);
	// Parse the current time to required string
	struct tm * timeInfo = localtime(&timer);
	strftime(sendBuff, SEND_BUFFER_LENGTH, formatStr, timeInfo);
}

void GetTime(char sendBuff[], bool inTicks)
{
	if (inTicks)
	{
		int ticks = GetTickCount();
		_itoa(ticks, sendBuff, 10);
	}
	else
	{
		// Get the current time.
		time_t timer;
		time(&timer);
		// Parse the current time to printable string.
		strcpy(sendBuff, ctime(&timer));
		sendBuff[strlen(sendBuff) - 1] = '\0'; //to remove the new-line from the created string
	}

}

void GetTimeWithoutDate(char sendBuff[])
{
	getTimeUsingFormat(sendBuff, "%H:%M:%S");
}

void GetTimeSinceEpoch(char sendBuff[])
{
	time_t timer;
	time_t seconds = time(&timer);	// Get seconds since epoch of current time as integer
	_itoa(seconds, sendBuff, 10); // Convert int time into string
}