/**
 *  \file       rtime.c
 *  \brief      Implementation of RTC abstraction for Win bsp.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.05.17  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña       db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <time.h>

#include "rtime.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static Time t;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
Time *
rtime_get(void)
{
    time_t ltime;
    struct tm *local;

    time(&ltime);
    local = localtime(&ltime);

    t.tm_sec = (unsigned char)local->tm_sec;
    t.tm_min = (unsigned char)local->tm_min;
    t.tm_hour = (unsigned char)local->tm_hour;
    t.tm_mday = (unsigned char)local->tm_mday;
    t.tm_mon = (unsigned char)local->tm_mon;
    t.tm_year = (short)local->tm_year;
    t.tm_wday = (unsigned char)local->tm_wday;
    t.tm_isdst = (unsigned char)local->tm_isdst;

    return &t;
}

/* ------------------------------ End of file ------------------------------ */
