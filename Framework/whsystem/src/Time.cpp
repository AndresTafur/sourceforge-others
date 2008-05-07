#include "Time.hh"



	 WhiteHawkSystem::Time::Time()
	 {
		setTime( time(NULL) );
	 }

	 WhiteHawkSystem::Time::Time(time_t desc)
	 {
		setTime(desc);
	 }


	void WhiteHawkSystem::Time::setTime(time_t desc)
	{
		handler   = desc;
		localTime = localtime(&handler);
	}


	float WhiteHawkSystem::Time::difference(Time obj)
	{
	  return difftime(handler, obj.getHandler());
	}

	std::string WhiteHawkSystem::Time::toString(std::string format)
	{
	  char cad[100];

	   strftime(cad, 100, format.c_str(), localTime);
	   return cad;
	}


	time_t WhiteHawkSystem::Time::getHandler()
	{
	  return handler;
	}


	int WhiteHawkSystem::Time::getYear()
	{
	  return localTime->tm_year + 1900;
	}


	int WhiteHawkSystem::Time::getMonth()
	{
	  return localTime->tm_mon+1;
	}

	int WhiteHawkSystem::Time::getDay()
	{
	  return localTime->tm_mday;
	}

	int WhiteHawkSystem::Time::getDayOfWeek()
	{
	  return localTime->tm_wday+1;
	}

	int WhiteHawkSystem::Time::getDayOfYear()
	{
	  return localTime->tm_yday+1;
	}

	int WhiteHawkSystem::Time::getHour()
	{
	  return localTime->tm_hour;
	}

	int WhiteHawkSystem::Time::getMinute()
	{
	  return localTime->tm_min+1;
	}

	int WhiteHawkSystem::Time::getSecond()
	{
	  return localTime->tm_sec;
	}

    WhiteHawkSystem::Time::~Time()
    {

    }
