#ifndef _WHSOUNDLIB_THREAD_H_
#define _WHSOUNDLIB_THREAD_H_

#include <boost/thread.hpp>

namespace ThirdWar
{
class Thread;

};

class ThirdWar::Thread
{
public:

    Thread();

    void startThread();

    void stopThread();


    virtual ~Thread();


protected:

    virtual void run();

private:
    volatile bool m_stoprequested;
    boost::shared_ptr<boost::thread> m_thread;
    boost::mutex m_mutex;
};

#endif

