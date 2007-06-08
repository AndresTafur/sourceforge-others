
/** This class manages all of the events and Errors
 *  NOTE: you must override this class (this is an abstract class)
 */
 

class whiteSQL::SqlEngineEvent
{
public:

	/** Method called when an event ocurrs (TODO make this useful)
	 *  @param evt    Type and description of the event
	 *  @see  whiteSQL::SqlEvtType
         */

	virtual void OnEvent(SqlEvtType *evt) = 0;


	/** Method called when an error ocurrs 
	 *  @param evt    Type and description of the event
	 *  @see  whiteSQL::SqlEvtType
         */

	virtual void OnError(SqlEvtType *evt) = 0;

};
