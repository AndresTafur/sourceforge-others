#ifndef _WINDOW_EVENT_MANAGER_
#define _WINDOW_EVENT_MANAGER_

#include <Thread.hh>
#include "SystemUtils.hh"
#include "WindowList.hh"
#include "TaskBar.hh"


class WindowEventManager : public WhiteHawkSystem::Thread
{
public:

        WindowEventManager(SystemUtils *sysUtils, TaskBar *bar);

        void ThreadRoutine();

        void onTerminate();

protected:

       void onEvent(Window,Atom atom);

protected:
wxButton *m_button;

SystemUtils *m_sysUtils;
WindowList  *m_list;
TaskBar     *m_bar;
Display     *m_dsp;
Window       m_root;
bool         m_run;

};
#endif
