/*  This file is part of WhiteHawkClamav.

    WhiteHawkClamav is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WhiteHawkClamav is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _WH_TIME_
#define _WH_TIME_

#include <time.h>
#include <string>
#include "WhiteHawkUtil.hh"

/**
 *	just time. This class represents Time ( year, month, week, day, hour, minute, second ).
 */
class WhiteHawkUtil::Time
{
public:


	/**
	 *   Default Constructor. it initialize the object with the current time.
	 */
	 Time();

	/**
	 *
	 *   Default Constructor. it initialize the object with a time_t structure.
	 *   @param desc time_t structure for initializing the obect.
	 */
	 Time(time_t desc);


	/**
	 *
	 *   Sets the time. Sets the current time based on a time_t structure.
	 *   @param desc  time_t structure for setting the obect.
	 */
	 void setTime(time_t desc);

	/**
	 *
	 *  Difference to time objects. Retunrs the difference (in seconds) between two Time objects.
	 *  @param obj Another Time object.
	 *  @return Seconds of difference.
	 */
	 float difference(Time &obj);


	/**
	 *   Gets a string. Obtains a string of the time based using strftime format.
	 *   @param format  Format of the output (strftime style).
	 *   @return A string with the time in strftime style.
	 */
	 std::string toString(std::string format);


	/**
	 *   Gets the default handerl. the time in format struct time_t.
	 *   @return  Current time in time_t struct.
	 */
	 time_t getHandler();


	/**
	 *   Gets the year.
	 *   @return year.
	 */
 	 int getYear();

	/**
	 *   Gets the month.
	 *   @return month.
	 */
	 int getMonth();

	/**
	 *   Gets the day of the month.
	 *   @return day.
	 */
	 int getDay();

	/**
	 *   Gets the day. Gets the day number of the current week.
	 *   @return day of week.
	 */
 	 int getDayOfWeek();

	/**
	 *   Gets the day. Gets the day number of the current year.
	 *   @return day of year.
	 */
 	 int getDayOfYear();

	/**
	 *   Gets the hour.
	 *   @return hour.
	 */
	 int getHour();

	/**
	 *   Gets the minutes.
	 *   @return minutes.
	 */
	 int getMinute();

	/**
	 *   Gets the seconds.
	 *   @return seconds.
	 */
	 int getSecond();


     ~Time();

protected:
/**
 * Ansi C handler. time_t of the ANSI C handler in condensed format.
 */
time_t     handler;

/**
 * Ansi C separated handler. time_t of the ANSI C handler in separate format.
 */
struct tm  *localTime;
};
#endif
