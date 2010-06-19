#include "Thread.h"



    ThirdWar::Thread::Thread() : m_stoprequested(false)
    {
    }


    // Create the thread and start work
    void ThirdWar::Thread::startThread()
    {
        assert(!m_thread);
        m_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Thread::run, this)));
    }

    void ThirdWar::Thread::stopThread() // Note 1
    {
       if(m_thread)
       {
            m_stoprequested = true;
            m_thread->join();
       }
    }


    void ThirdWar::Thread::run()
    {
        fprintf(stderr,"AQUII");
    }


    ThirdWar::Thread::~Thread()
    {
        stopThread();
    }




