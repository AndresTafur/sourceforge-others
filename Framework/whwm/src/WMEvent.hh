#ifndef _WMEVENT_
#define _WMEVENT_

#include <X11/Xlib.h>
#include <string>

class WMEvent
{
public:
        inline WMEvent() {}

        WMEvent(Window window = NULL,int evtType = NULL, std::string name = "");

        void setEvtType(int evtType);

        void setEvtName(std::string name);

        void setWindow(Window window);

        inline int getEvtType() { return m_evtType; }

        inline std::string getEvtName() { return m_name; }

        inline Window getWindow() { return m_window; }

protected:
int         m_evtType;
std::string m_name;
Window      m_window;
};
#endif
