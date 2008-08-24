


#ifndef _WH_FILE_INFO_
#define _WH_FILE_INFO_

#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>

#include "Time.hh"

/**
 * Status and information of a file. This class represents the status and the default information of a file.
 * TODO: File permissions.
 */

class WhiteHawkSystem::FileInfo
{
public:

	/**
	 *  Default Constructor.
	 */
	FileInfo();


	/**
	 *	Constructs a FileInfo object based in a path.
	 *	@param	path	path to the file in the system.
	 */
	FileInfo(std::string path);


	/**
	 *	Sets the path to a FileInfo object.
	 *	@param	path	path to the file in the system.
	 */
	void setPath(std::string path);


	/**
	 *	Sets the time of the last access of the file.
	 *	@param	 time time to be placed on last Access.
	 *	@return	 true if sucessfull false other wise
	 * 	@see	 Time
	 */
	bool setLastAccess(WhiteHawkSystem::Time &time);


	/**
	 *	Sets the time of the last modification of the file.
	 *	@param	 time time to be placed on last Modification.
	 *	@return	 true if sucessfull false other wise
	 * 	@see	 Time
	 */
	bool setLastModification(WhiteHawkSystem::Time &time);


	/**
	 *	Sets the permissions (or'ed) to a FileInfo object.
	 *  for user : S_IRWXU, S_IRUSR, S_IWUSR, S_IXUSR
	 *  for group: S_IRGRP, S_IWGRP, S_IXGRP
	 *  for other: S_IROTH, S_IWOTH, S_IXOTH
	 *	@param	mode mode of the file.
	 *  @return true if sucessfully false otherwise.
	 */
    bool setPermission(mode_t mode);

	/**
	 *	Sets the propetary user of a FileInfo object.
	 *	@param	id Id of the user.
	 *  @return true if sucessfully false otherwise.
	 */
    bool setOwner(uid_t id);


	/**
	 *	Sets the propetary group of a FileInfo object.
	 *	@param	id Id of the group.
	 *  @return true if sucessfully false otherwise.
	 */
    bool setGroup(gid_t id);


	/**
	 *	Gets the size of the file
	 *	@return	 size of the file in the system.
	 */
	int getSize();


	/**
	 *	Gets the path of a FileInfo object.
	 *	@return	 path of the file in the system.
	 */
	std::string getPath();

	/**
	 *	Gets the name of a FileInfo object, omitting the path.
	 *	@return	 name of the file in the system.
	 */
	std::string getName();

	/**
	 *	Gets the time of the last access to the file.
	 *	@return	 time of the last acess.
	 * 	@see	 Time
	 */
	WhiteHawkSystem::Time getLastAccess();


	/**
	 *	Gets the time of the last modification of the file.
	 *	@return	 time of the last modification.
	 * 	@see	 Time
	 */

	WhiteHawkSystem::Time getLastModification();

	/**
	 *	Tests if the file exists
	 *	@return	 true if the file is exists, false otherwise .
	 */
    bool exist();

	/**
	 *	Tests if the file is regular (or a hard link).
	 *	@return	 true if the file is regular, false otherwise .
	 */
	bool isFile();

	/**
	 *	Tests if the file has reading permissions for the current user (or a hard link).
	 *	@return	 true if the file is regular, false otherwise .
	 */
	bool isUserReadable();

    /**
	 *	Tests if the file has writing permissions for the current user (or a hard link).
	 *	@return	 true if the file is regular, false otherwise .
	 */
	bool isUserWritable();

    /**
	 *	Tests if the file has executing permissions for the current user (or a hard link).
	 *	@return	 true if the file is regular, false otherwise .
	 */
	bool isUserExecutable();

    /**
	 *	Tests if the file has read/write/execute permissions for the current user (or a hard link).
	 *	@return	 true if the file is regular, false otherwise .
	 */
	bool isUserRWX(); //TODO: File permissions

	/**
	 *	Tests if the file is a soft Link.
	 *	@return	 true if the file is a soft link, false otherwise.
	 */
	bool isLink();


	/**
	 *	Tests if the file is a directory.
	 *	@return	 true if the file is a directory, false otherwise.
	 */
	bool isDirectory();


	/**
	 *	Tests if the file is a special char-device.
	 *	@return	 true if the file is a char-device, false otherwise.
	 */
	bool isCharDevice();

	/**
	 *	Tests if the file is a special block-device.
	 *	@return	 true if the file is a block-device, false otherwise.
	 */
	bool isBlockDevice();


	/**
	 *	Tests if the file is a special stream (First In First Out).
	 *	@return	 true if the file is a FIFO, false otherwise.
	 */
	bool isFIFO();


	/**
	 *	Tests if the file is a socket stream.
	 *	@return	 true if the file is a socket, false otherwise.
	 */
	bool isSocket();

	/**
	 *	Tests if the file is a device (character or block device).
	 *	@return	 true if the file is a device, false otherwise.
	 */
	bool isDevice();


    /**
	 *	Checks if the file has that path.
	 *  @param  path a defined system route of a file.
	 *	@return true if equals, false otherwise.
	 */
    bool operator == (std::string path);


    /**
	 *	Checks if the file doesn't have that path.
	 *  @param  path a defined system route of a file.
	 *	@return true if not equal, false otherwise.
	 */
    bool operator != (std::string path);

protected:

/**
 * Path of the file.
 */
std::string m_path;

/**
 * Default info of the file.
 */
struct stat fileStatus;

/**
 * Access Time.
 * @see Time
 */
WhiteHawkSystem::Time  accTime;

/**
 * Modification Time.
 * @see Time
 */
WhiteHawkSystem::Time  modTime;
};
#endif
