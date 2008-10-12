#ifndef _WM_EVENT_MANAGER_
#define _WM_EVENT_MANAGER_

#include <X11/Xlib.h>


class WMEventListener
{
public:

        virtual void onEvent(Window &wnd, Atom &atom) = 0;


};
#endif
