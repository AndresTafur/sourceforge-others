

/**
 * This class sets the Event Type behaivor
 */ 


class whiteSQL::SqlEvtType
{
public:


	/** Default (and the only one) Constructor
	 *  @param id     identifier of the event
	 *  @param descr  Description of the event
         */

	SqlEvtType(int id, std::string descr);


	/** Obtains the id of this event
	 *  @return returns the identifier of the event
         */

	int getId();


	/** Obtains the Description of this event
	 *  @return returns the description of the event
         */

	std::string getDescription();


protected:
 /*
  * ID of the error or event 
  */
int id;

 /*
  * Description of the error or event
  */
std::string des;
};
