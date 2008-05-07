#ifndef _WMMANAGER_
#define _WMMANAGER_

#include <WhiteHawkSystem.hh>
#include <Thread.hh>
#include <list>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include "WMEvent.hh"
#include "WMListener.hh"

class WMManager : public WhiteHawkSystem::Thread
{
public:

            WMManager();

            void ThreadRoutine();

            void addListener(WMListener *listener);

            void removeListener(WMListener *listener);

            void onTerminate();

protected:
            void propagateEvent(WMEvent evt);

protected:
std::list<WMListener*> m_handlers;
bool     m_run;
};
#endif
