#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "operations.h"

#define SEND_BUFFER_LENGTH		255
#define SECONDS_PER_MINUTE		60
#define SECONDS_PER_HOUR		60 * SECONDS_PER_MINUTE
#define SECONDS_PER_DAY			24 * SECONDS_PER_HOUR
#define TOKYO_UTC_DIFF			9
#define MELBOURNE_UTC_DIFF		10
#define SAN_FRANCISCO_UTC_DIFF	-7
#define PORTO_UTC_DIFF			1
#define IS_SUPPORTED_POSITION	8
//#define MAX_TIME_FOR_TIMER		3 * SECONDS_PER_MINUTE
#define MAX_TIME_FOR_TIMER		3

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
	getTimeUsingFormat(sendBuff, "%X");
}

void GetTimeSinceEpoch(char sendBuff[])
{
	time_t timer;
	time_t seconds = time(&timer);	// Get seconds since epoch of current time as integer
	_itoa(seconds, sendBuff, 10); // Convert int time into string
}

void GetTimeWithoutDateOrSeconds(char sendBuff[])
{
	getTimeUsingFormat(sendBuff, "%H:%M");
}

void GetYear(char sendBuff[])
{
	getTimeUsingFormat(sendBuff, "%Y");
}

void GetMonthAndDay(char sendBuff[])
{
	getTimeUsingFormat(sendBuff, "%B %d");
}

void GetSecondsSinceBeginingOfMonth(char sendBuff[])
{
	time_t timer;
	time(&timer);
	struct tm * timeInfo = localtime(&timer);	// Get time struct
	int daySeconds = timeInfo->tm_mday * SECONDS_PER_DAY;
	int hourSeconds = timeInfo->tm_hour * SECONDS_PER_HOUR;
	int minuteSeconds = timeInfo->tm_min * SECONDS_PER_MINUTE;
	int seconds = timeInfo->tm_sec;
	int secondsSinceBegMonth = daySeconds + hourSeconds + minuteSeconds + seconds;
	_itoa(secondsSinceBegMonth, sendBuff, 10);
}

void GetWeekOfYear(char sendBuff[])
{
	getTimeUsingFormat(sendBuff, "%U");
}

void GetDaylightSavings(char sendBuff[])
{
	// Get the current time.
	time_t timer;
	time(&timer);
	// Check the daylight savings status
	struct tm * timeInfo = localtime(&timer);
	strcpy(sendBuff, timeInfo->tm_isdst ? "active" : "inactive");
}

void GetTimeWithoutDateInCity(char sendBuff[], char city[])
{
	time_t utc_now = time(NULL);
	time_t timeInCity;
	int hoursDiff = 0;
	bool isSupported = false;
	if (strcmp(city, "tokyo") == 0)
	{
		isSupported = true;
		hoursDiff = TOKYO_UTC_DIFF;
	}
	else if (strcmp(city, "melbourne") == 0)
	{
		isSupported = true;
		hoursDiff = MELBOURNE_UTC_DIFF;
	}
	else if (strcmp(city, "san francisco") == 0)
	{
		isSupported = true;
		hoursDiff = SAN_FRANCISCO_UTC_DIFF;
	}
	else if (strcmp(city, "porto") == 0)
	{
		isSupported = true;
		hoursDiff = PORTO_UTC_DIFF;
	}

	// Add the hours diff in seconds to the utc time
	timeInCity = utc_now + (hoursDiff * SECONDS_PER_HOUR);
	// Parse the current time to required string
	struct tm * timeInfo = gmtime(&timeInCity);
	strftime(sendBuff, SEND_BUFFER_LENGTH, "%X", timeInfo);
	// Add a byte to let the client know if the city was suppored or not
	sendBuff[IS_SUPPORTED_POSITION] = isSupported ? '1' : '0';
	sendBuff[IS_SUPPORTED_POSITION + 1] = '\0';
}

void MeasureTimeLap(char sendBuff[], int * lapTimer)
{
	if (*lapTimer == TIMER_INACTIVE)
	{
		StartTimer(lapTimer);
		strcpy(sendBuff, "Started timer!");
	}
	else
	{
		int timeLapsed = CheckTimer(lapTimer, true);
		if (timeLapsed > MAX_TIME_FOR_TIMER)
		{
			StartTimer(lapTimer);
			strcpy(sendBuff, "Started timer!");
		}
		else
		{
			char lapBuff[255];
			_itoa(timeLapsed, lapBuff, 10);
			sprintf(sendBuff, "Lap time is %s seconds.", lapBuff);
		}
	}
}

void StartTimer(int *lapTimer)
{
	time_t timer;
	*lapTimer = time(&timer);
}

int CheckTimer(int *lapTimer, bool reset)
{
	time_t timer;
	time_t secondsSinceEpoch = time(&timer);
	int timeLapsed = secondsSinceEpoch - (*lapTimer);
	if (reset)
		*lapTimer = TIMER_INACTIVE;
	return timeLapsed;
}