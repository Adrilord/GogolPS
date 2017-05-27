#include "datetime.h"
#include <Arduino.h>

Showdatetime datetime2Showdatetime(Datetime* datetime)
{
	Showdatetime showdatetime;
  int2TabChar(showdatetime.year, 4, datetime->year);
  int2TabChar(showdatetime.month, 2, datetime->month);
  int2TabChar(showdatetime.day, 2, datetime->day);
  int2TabChar(showdatetime.hour, 2, datetime->hour);
  int2TabChar(showdatetime.minute, 2, datetime->minute);
  int2TabChar(showdatetime.second, 2, datetime->second);
  int2TabChar(showdatetime.hundredths, 2, datetime->hundredths);
	return showdatetime;
}

void initShowDateTime(Showdatetime* showdatetime)
{
  strupdate(showdatetime->year, 0, "2000", 4);
  strupdate(showdatetime->month, 0, "01", 2);
  strupdate(showdatetime->day, 0, "01", 2);
  strupdate(showdatetime->hour, 0, "01", 2);
  strupdate(showdatetime->minute, 0, "01", 2);
  strupdate(showdatetime->second, 0, "01", 2);
  strupdate(showdatetime->hundredths, 0, "00", 2);
}
