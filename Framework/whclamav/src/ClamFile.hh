#include <WhiteHawkSystem.hh>
#include "WhiteHawkClamav.hh"
#include <AbstractFile.hh>
#include <SystemPath.hh>


#ifndef _CLAMFILE_HH_
#define _CLAMFILE_HH_


/**
 *  This class represents a filenode of the current path list 
 */

class WhiteHawkClamav::ClamFile : public WhiteHawkSystem::AbstractFile
{
public:

	/**
	 *   Default constructor, it sets the path of the file in the system
	 *   @param path Path to the file (absolute or relative)
         */
	ClamFile(std::string path);

	/**
	 *  Sets if the file is/has a virus
	 *  @param stat true if is infected, false otherwise.
         */
	void setInfected( bool stat);


	/**
	 *  This method sets de virus name
	 *  @param virname Registred name of the virus
         */
	void setVirName(std::string virname);


	/**
	 *  Sets the id of this element
         */
	void setId(int id);
		
	/**
	 *  Tests if the file is infected
	 *  @return true if is infected, false otherwise.
	 */
	bool isInfected();

	/**
	 *  Gets the registered name of the virus.
	 *  return the name of the virus, a empty string otherwise
	 */ 
	std::string getVirName();

	/**
	 *  Gets the id of this element
         */
	int getId();

protected:
/**
 *   virus name
 */
std::string virname;

/**
 *   id of the element
 */
int id;

/**
 * true if is infected, false otherwise
 */
bool status;
};

#endif
