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

#include "Thread.hh"
#include "Exception.hh"

#ifndef WIN32
#include <unistd.h>
#endif

WhiteHawkUtil::Thread::Thread()
{
        m_runObj = this;
        pthread_attr_init(&m_attr);
        pthread_mutex_init(&m_mux, NULL);
        pthread_cond_init(&m_cond, NULL);
	m_runObj->setRunning(false);
}

WhiteHawkUtil::Thread::Thread(Runnable *obj)
{
        m_runObj = obj;
        pthread_attr_init(&m_attr);
        pthread_mutex_init(&m_mux, NULL);
        pthread_cond_init(&m_cond, NULL);
	m_runObj->setRunning(false);
}


void WhiteHawkUtil::Thread::startThread(unsigned long stack_size)
{
        pthread_attr_init(&m_attr);

        if( stack_size != 0)
            if( pthread_attr_setstacksize(&m_attr, stack_size) != 0)
                WhiteHawkUtil::Exception("Failed assigning thread stack size","WhiteHawkUtil::Thread::Start");

        if(pthread_create(&m_handler, &m_attr, (void *(*)(void*))&threadfunc, m_runObj))
                WhiteHawkUtil::Exception("Failed to create posix thread","WhiteHawkUtil::Thread::Start");
	m_runObj->setRunning(true);
}

pthread_t WhiteHawkUtil::Thread::getThreadHandler()
{
        return m_handler;
}


bool WhiteHawkUtil::Thread::join()
{
      if( pthread_join(m_handler, NULL) == 0)
        return true;
    return false;
}


void WhiteHawkUtil::Thread::sleep(unsigned long millisecs)
{
	#ifdef WIN32
         Sleep(millisecs);
	#endif
	 usleep(millisecs*1000);
}

void WhiteHawkUtil::Thread::terminateThread()
{
	 if( pthread_cancel(m_handler) != 0)
         	throw WhiteHawkUtil::Exception("Can't cancel thread with pthread_cancel","WhiteHawkUtil::Thread::SafePoint");
	 m_runObj->setRunning(false);
}


void WhiteHawkUtil::Thread::threadfunc(Runnable *runObj)
{
        runObj->run();
        runObj->onTerminate();
        runObj->setRunning(false);
        pthread_exit(NULL);
}


WhiteHawkUtil::Thread::~Thread()
{

}
