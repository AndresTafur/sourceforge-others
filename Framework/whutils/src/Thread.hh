/*  This file is part of WhiteHawkClamav.
 *
 *   WhiteHawkClamav is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   WhiteHawkClamav is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _Thread_
#define _Thread_

#include <pthread.h>

#ifndef WIN32
#include <unistd.h>
#endif


#include "WhiteHawkUtil.hh"
#include "Runnable.hh"


/**
 * Threading class using deatachable pthreads.
 * @see Runable
 */

class WhiteHawkUtil::Thread : public WhiteHawkUtil::Runnable
{
public:

    /**
     * Default constructor using itself as the runnable object.
     */
    Thread();

    /**
     * Constructor which assigns a Runable object to this thread
     * @param run_obj
     */
    Thread(Runnable *run_obj);

    /**
     * starts the this thread.
     * @param stack_size Stack to be used
     */
    void          startThread(unsigned long stack_size = 0);

    /**
     *  returns the pthread handler of this object.
     *  @return pthread_t handler
     */
    pthread_t     getThreadHandler();

    /**
     * Finalizes this thread.
     */
    void          terminateThread();

    /**
     * Waits for this thread to be terminated
     * @return true on sucess, false otherwise
     */
    bool          join();

    /**
     * Sleep funcion, same as usleep in posix and Sleep in ms-windows.
     * @param millisecs Milliseconds to sleep
     */
    static void   sleep(unsigned long millisecs);

    /**
     * Default destructor
     */
    ~Thread();


private:
/**
 * pthread handler
 */
pthread_t        m_handler;

/**
 * pthread atributes
 */
pthread_attr_t   m_attr;

/**
 * pthread mutex handler
 */
pthread_mutex_t  m_mux;

/**
 * pthread condition handler
 */
pthread_cond_t   m_cond;

/**
 * Runable object
 */
Runnable        *m_runObj;

/**
 * Thread function to a p_thread Ansi C.
 */

static void  threadfunc(Runnable *obj);


};
#endif
