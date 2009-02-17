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

#ifndef _RUNNABLE_
#define _RUNNABLE_

/**
 * Interface to an object wich will be running in a thread
 */

class WhiteHawkUtil::Runnable
{
public:

        /**
         *  Virtual method wich will be runned in thread.
         */
        virtual void run() = 0;

        /**
         * Tests if the thread is running.
         *  @return True if is running, false otherwise.
         */
        inline bool isRunning() { return m_running;}

        /**
         * Change the running status flag (should'n be called directly)
         *  @param stat true if is running, false otherwise.
         */
        inline void setRunning(bool stat) { m_running = stat;}

        /**
         * Function called within the thread at the end of the
         * excecution.
         */
        virtual void onTerminate() {};

        /**
         * Default virtual destructor
         */
        inline virtual ~Runnable() {};

protected:
/**
 * flag if the object is running in a thread.
 */
bool m_running;
};


#endif
