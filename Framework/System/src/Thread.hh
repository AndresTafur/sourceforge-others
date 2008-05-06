#include <pthread.h>
// Thread.h V0.1pre Header File, Provides thread class definition
// © 2003 Elliot Nierman

#ifndef WIN32
#include <unistd.h>
#endif


#ifndef _Thread_
#define _Thread_

#include "WhiteHawkSystem.hh"

enum priority_level { IDLE = 11,
                               LOWEST = 11,
                               BELOW_NORMAL = 11,
                               NORMAL = 11,
                               ABOVE_NORMAL = 11,
                               HIGHEST = 11,
                               TIME_CRITICAL = 11 };



struct thread_var{

    priority_level b_prio;
    int b_trueprio;
    bool b_term;
    bool b_susp;
    bool b_created;
    void * b_exitcode;




    pthread_t           p_handle;
    struct sched_param  p_param;
    pthread_attr_t      p_attr;
    pthread_mutex_t     p_mux;
    pthread_cond_t      p_cond;
};

class WhiteHawkSystem::Thread
{
public:

                               Thread();
    virtual                   ~Thread(){};
    bool                       CreateSuspended();
    bool                       CreateSuspended(unsigned long stack_size);
    bool                       Create();
    bool                       Create(unsigned long stack_size);
    const pthread_t            GetID() const;
    bool                       Execute();
    void                       Resume();
    void                       Suspend();
    void                       Terminate();
    void                       Lock();
    void                       Unlock();
    bool                       SetPriority(priority_level b_prio);
    char *                     GetPriority();
    bool                       Join() const;
    void                       SafePoint();
    void                       Suspend_Thread();
    void                       T_Sleep(unsigned long millisecs);

protected:
    virtual void               ThreadRoutine() = 0; // User overridden
    virtual void	           onTerminate() = 0; // User overriden

private:
    thread_var             T_Var;
    pthread_mutex_t        mutex;

    static void               threadfunc(Thread*);
    static void               susp_threadfunc(Thread*);
    void                      Start();
    void                      Start_Suspended();

};
#endif
