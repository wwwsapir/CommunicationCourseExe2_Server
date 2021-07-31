void GetTime(char sendBuff[], bool inTicks);
void GetTimeWithoutDate(char sendBuff[]);
void GetTimeSinceEpoch(char sendBuff[]);
void GetTimeWithoutDateOrSeconds(char sendBuff[]);
void GetYear(char sendBuff[]);
void GetMonthAndDay(char sendBuff[]);
void GetSecondsSinceBeginingOfMonth(char sendBuff[]);
void GetWeekOfYear(char sendBuff[]);
void GetDaylightSavings(char sendBuff[]);
void GetTimeWithoutDateInCity(char sendBuff[], char city[]);
void MeasureTimeLap(char sendBuff[], int * lapTimer);
void StartTimer(int *lapTimer);
int CheckTimer(int * lapTimer, bool reset);

#define TIMER_INACTIVE -1