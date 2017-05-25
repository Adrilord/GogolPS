#include "datetime.h"

Showdatetime datetime2Showdatetime(Datetime* datetime)
{
	Showdatetime showdatetime;
  strupdate(showdatetime.year, 0, datetime->year, 4);
  strupdate(showdatetime.month, 0, datetime->month, 2);
  strupdate(showdatetime.day, 0, datetime->day, 2);
  strupdate(showdatetime.hour, 0, datetime->hour, 2);
  strupdate(showdatetime.minute, 0, datetime->minute, 2);
  strupdate(showdatetime.second, 0, datetime->second, 2);
  strupdate(showdatetime.hundredths, 0, datetime->hundredths, 2);

	return showdatetime;
}

void initShowDateTime(Showdatetime* showdatetime)
{
  strupdate(showdatetime.year, 0, "    ", 4);
  strupdate(showdatetime.month, 0, "  ", 2);
  strupdate(showdatetime.day, 0, "  ", 2);
  strupdate(showdatetime.hour, 0, "  ", 2);
  strupdate(showdatetime.minute, 0, "  ", 2);
  strupdate(showdatetime.second, 0, "  ", 2);
  strupdate(showdatetime.hundredths, 0, "  ", 2);
}
