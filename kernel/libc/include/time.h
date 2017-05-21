#pragma once


#ifdef __cplusplus
extern "C" {
#endif

typedef long clock_t;
typedef long time_t;

struct tm
{
  int tm_sec;                   /* Seconds.     [0-60] (1 leap second) */
  int tm_min;                   /* Minutes.     [0-59] */
  int tm_hour;                  /* Hours.       [0-23] */
  int tm_mday;                  /* Day.         [1-31] */
  int tm_mon;                   /* Month.       [0-11] */
  int tm_year;                  /* Year - 1900.  */
  int tm_wday;                  /* Day of week. [0-6] */
  int tm_yday;                  /* Days in year.[0-365] */
  int tm_isdst;                 /* DST.         [-1/0/1]*/
  long int tm_gmtoff;           /* Seconds east of UTC.  */
  const char *tm_zone;          /* Timezone abbreviation.  */
};

clock_t clock (void);
double difftime (time_t end, time_t beginning);
time_t mktime (struct tm * timeptr);
time_t time (time_t* timer);
char* asctime (const struct tm * timeptr);
char* ctime (const time_t * timer);
struct tm * gmtime (const time_t * timer);
struct tm * localtime (const time_t * timer);
size_t strftime (char* ptr, size_t maxsize, const char* format,
                 const struct tm* timeptr );


#ifdef __cplusplus
}
#endif
