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

#include "Time.hh"



	 WhiteHawkUtil::Time::Time()
	 {
		setTime( time(NULL) );
	 }

	 WhiteHawkUtil::Time::Time(time_t desc)
	 {
		setTime(desc);
	 }


	void WhiteHawkUtil::Time::setTime(time_t desc)
	{
		handler   = desc;
		localTime = localtime(&handler);
	}


	float WhiteHawkUtil::Time::difference(Time &obj)
	{
	  return difftime(handler, obj.getHandler());
	}

	std::string WhiteHawkUtil::Time::toString(std::string format)
	{
	  char cad[100];

	   strftime(cad, 100, format.c_str(), localTime);
	   return cad;
	}


	time_t WhiteHawkUtil::Time::getHandler()
	{
	  return handler;
	}


	int WhiteHawkUtil::Time::getYear()
	{
	  return localTime->tm_year + 1900;
	}


	int WhiteHawkUtil::Time::getMonth()
	{
	  return localTime->tm_mon+1;
	}

	int WhiteHawkUtil::Time::getDay()
	{
	  return localTime->tm_mday;
	}

	int WhiteHawkUtil::Time::getDayOfWeek()
	{
	  return localTime->tm_wday+1;
	}

	int WhiteHawkUtil::Time::getDayOfYear()
	{
	  return localTime->tm_yday+1;
	}

	int WhiteHawkUtil::Time::getHour()
	{
	  return localTime->tm_hour;
	}

	int WhiteHawkUtil::Time::getMinute()
	{
	  return localTime->tm_min+1;
	}

	int WhiteHawkUtil::Time::getSecond()
	{
	  return localTime->tm_sec;
	}

    WhiteHawkUtil::Time::~Time()
    {

    }
