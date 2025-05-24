#include "MyTime.h"
string SectoString(double sec)
{
	int seconds = (int)sec;
	int hours = seconds / 3600;
	int minutes = (seconds % 3600) / 60;
	int secs = seconds % 60;
	string hh = (hours < 10) ? "0" + to_string(hours) : to_string(hours);
	string mm = (minutes < 10) ? "0" + to_string(minutes) : to_string(minutes);
	string ss = (secs < 10) ? "0" + to_string(secs) : to_string(secs);
	return hh + ":" + mm + ":" + ss;
}