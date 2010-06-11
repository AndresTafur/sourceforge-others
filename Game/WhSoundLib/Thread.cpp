#include "Thread.h"



    whSoundLib::Thread::Thread() : m_stoprequested(false)
    {
    }


    // Create the thread and start work
    void whSoundLib::Thread::startThread()
    {
        assert(!m_thread);
        m_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Thread::run, this)));
    }

    void whSoundLib::Thread::stopThread() // Note 1
    {
        assert(m_thread);
        m_stoprequested = true;
        m_thread->join();
    }


    void whSoundLib::Thread::run()
    {
        fprintf(stderr,"AQUII");
    }


    whSoundLib::Thread::~Thread()
    {
        stopThread();
    }




