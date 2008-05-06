#include "Thread.hh"

#ifndef WIN32
#include <unistd.h>
#endif


// Thread.cpp V0.1pre Provides thread class member functions
// © 2003 Elliot Nierman


WhiteHawkSystem::Thread::Thread()
{
        T_Var.b_susp = true;
        T_Var.b_term = false;
        T_Var.b_created = false;
        pthread_attr_init(&T_Var.p_attr);
        pthread_mutex_init(&T_Var.p_mux, NULL);
        pthread_cond_init(&T_Var.p_cond, NULL);
}

bool WhiteHawkSystem::Thread::CreateSuspended()
{
        pthread_attr_init(&T_Var.p_attr);
        Start_Suspended();
        return true;
}

bool WhiteHawkSystem::Thread::CreateSuspended(unsigned long stack_size)
{
        pthread_attr_init(&T_Var.p_attr);
        pthread_attr_setstacksize(&T_Var.p_attr, stack_size);
        Start_Suspended();
        return true;
}

bool WhiteHawkSystem::Thread::Create()
{
        pthread_attr_init(&T_Var.p_attr);
        Start();
    return true;
}

bool WhiteHawkSystem::Thread::Create(unsigned long stack_size)
{
        pthread_attr_init(&T_Var.p_attr);
        pthread_attr_setstacksize(&T_Var.p_attr, stack_size);

        Start();
        return true;
}

bool WhiteHawkSystem::Thread::Execute()
{
        Resume();
        return true;
}


const pthread_t WhiteHawkSystem::Thread::GetID() const
{
        while( T_Var.b_created == true )
	  #ifdef WIN32
            Sleep(100);
	  #else
	    usleep(100*1000);
	  #endif
        return T_Var.p_handle;
}


char * WhiteHawkSystem::Thread::GetPriority()
{
        return NULL;
}


bool WhiteHawkSystem::Thread::Join() const
{
      pthread_join(GetID(), NULL);
        return true;
}

void WhiteHawkSystem::Thread::Resume()
{
        if (!T_Var.b_created)
            Start();
        else
            T_Var.b_susp = false;

        pthread_mutex_lock(&T_Var.p_mux);
        if (T_Var.b_susp == false) pthread_cond_broadcast(&T_Var.p_cond);
            pthread_mutex_unlock(&T_Var.p_mux);
}

void WhiteHawkSystem::Thread::SafePoint()
{
        if (T_Var.b_susp)
            Suspend_Thread();
        if (T_Var.b_term)
	{
            pthread_cancel(T_Var.p_handle);
	    onTerminate();
	}
}


bool WhiteHawkSystem::Thread::SetPriority( priority_level priority )
{
    return false;
}

void WhiteHawkSystem::Thread::T_Sleep(unsigned long millisecs)
{
	#ifdef WIN32
         Sleep(millisecs);
	#endif
	 usleep(millisecs*1000);
}

void WhiteHawkSystem::Thread::Terminate()
{
        T_Var.b_term = true;
	SafePoint();
}


void WhiteHawkSystem::Thread::Suspend()
{
        T_Var.b_susp = true;
}


void WhiteHawkSystem::Thread::Suspend_Thread()
{
        pthread_mutex_lock(&T_Var.p_mux);
        while (T_Var.b_susp == true)
                pthread_cond_wait(&T_Var.p_cond, &T_Var.p_mux);
        pthread_mutex_unlock(&T_Var.p_mux);
}


void WhiteHawkSystem::Thread::threadfunc(Thread * NewThread)
{

        NewThread->T_Var.b_susp = false;
        NewThread->ThreadRoutine();
        NewThread->T_Var.b_term = true;

}


void WhiteHawkSystem::Thread::susp_threadfunc(Thread * NewThread)
{
        NewThread->T_Var.b_susp = true;
        NewThread->ThreadRoutine();
        NewThread->T_Var.b_term = true;
}

void WhiteHawkSystem::Thread::Start(void)
{
        T_Var.b_created = true;
        if (pthread_create(&T_Var.p_handle, &T_Var.p_attr, (void *(*)(void*))&threadfunc, this))
            T_Var.b_created = true;
}


void WhiteHawkSystem::Thread::Start_Suspended(void)
{

       T_Var.b_created = true;

       if (pthread_create(&T_Var.p_handle, &T_Var.p_attr, (void *(*)(void*))&susp_threadfunc, this))
           T_Var.b_term = true;

#ifdef FIFO
      pthread_attr_setschedpolicy(&p_attr, SCHED_FIFO);
#endif

#ifdef RR
       pthread_attr_setschedpolicy(&p_attr, SCHED_RR);
#endif

       pthread_attr_setschedparam(&T_Var.p_attr, &T_Var.p_param);
       T_Var.b_created = true;

}







