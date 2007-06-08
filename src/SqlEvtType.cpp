#include "whiteSQL.hh"
//#include "SqlEvtType.hh"

	/** Default (and the only one) Constructor
	 *  @param id     identifier of the event
	 *  @param descr  Description of the event
         */

	whiteSQL::SqlEvtType::SqlEvtType(int id, std::string descr)
	{
		this->id  = id;
		this->des = descr;
	}


	/** Obtains the id of this event
	 *  @return returns the identifier of the event
         */

	int whiteSQL::SqlEvtType::getId()
	{
	  return id;
	}


	/** Obtains the Description of this event
	 *  @return returns the description of the event
         */

	std::string whiteSQL::SqlEvtType::getDescription()
	{
	  return des;
	}
