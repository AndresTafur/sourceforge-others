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

#ifndef _Thread_
#define _Thread_

#include <pthread.h>

#ifndef WIN32
#include <unistd.h>
#endif


#include "WhiteHawkSystem.hh"
#include "Runnable.hh"

class WhiteHawkSystem::Thread : public WhiteHawkSystem::Runnable
{
public:

    Thread();
    Thread(Runnable *run_obj);

    void          startThread(unsigned long stack_size = 0);
    pthread_t     getThreadHandler();

    void          terminateThread();
    bool          join();
    void          sleep(unsigned long millisecs);

    ~Thread();


private:
pthread_t        m_handler;
pthread_attr_t   m_attr;
pthread_mutex_t  m_mux;
pthread_cond_t   m_cond;
Runnable        *m_runObj;

static void  threadfunc(Runnable *obj);
};
#endif
