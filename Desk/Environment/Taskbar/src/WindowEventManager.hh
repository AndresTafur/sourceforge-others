#ifndef _WINDOW_EVENT_MANAGER_
#define _WINDOW_EVENT_MANAGER_

#include <list>
#include <Thread.hh>
#include "WindowManager.hh"
#include "WindowList.hh"
#include "TaskBar.hh"


class WindowEventManager : public WhiteHawkUtil::Thread
{
protected:

            WindowEventManager();

public:

        static WindowEventManager* getInstance();

        void run();

        void onTerminate();

        void addListener( WMEventListener *list);

        void removeListener( WMEventListener *list);

        static void destroy();

        ~WindowEventManager();

protected:

       void onEvent(Window,Atom atom);

protected:

std::list<WMEventListener*> m_listeners;
static WindowEventManager *sm_instance;
bool         m_run;

};
#endif
