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

#ifndef _INOTIFIER_HH_
#define _INOTIFIER_HH_


#include <list>

#include "inotify-nosys.h"

#include "Thread.hh"
#include "Exception.hh"
#include "AbstractFile.hh"
#include "InotifierEvtListener.hh"




/**
 * Default inotify class builder.
 */

class WhiteHawkUtil::Inotifier : public WhiteHawkUtil::Thread
{
private:

        /**
         * Default constructor. Creates a notification object of a file/folder.
         */

        Inotifier(AbstractFile &file, int fd);

public:


        /**
         * Creates a new notifier of a file.
         *  @param file File to be watched.
         *  @return Inotifier watcher instance
         */
        static Inotifier* createNotifier(AbstractFile &file);

        /**
         *  Thread entry point.
         */
        //TODO: make this private

        void run();


        /**
         * Adds a listener to the current watcher object
         * @param obj Pointer to a listener object
         */

        void addListener( InotifierEvtListener *obj);

        /**
         * Removes a listener to the current watcher object
         * @param obj Pointer to a listener object
         */

        void removeListener( InotifierEvtListener *obj);

        /**
         *  Start watching the current file using a mask.
         *  @param mask Events to  be catched
         */

        void startWatching(int mask = IN_ALL_EVENTS);

        /**
         *  Stops the current watch.
         */
        void stopWatching();

        /**
         *  Free all resource of the inotify main instance
         */
        static void closeInotify();

private:

/**
 * Watch descriptor
 */

int m_wd;

/**
 * File descriptor
 */

int m_fd;

/**
 * flag being watched.
 */
bool m_watch;

/**
 * current watched file.
 */
AbstractFile m_file;

/**
 * Inotfy listeners list.
 */
std::list<InotifierEvtListener*> m_lstners;

/**
 * inotify file descriptor
 */

static int m_infd;
};
#endif
