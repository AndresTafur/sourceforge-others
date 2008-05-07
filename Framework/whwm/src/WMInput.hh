#ifndef _WM_INPUT_
#define _WM_INPUT_

#include <X11/Xlib.h>


class WMInput
{
public:

            long query(Atom property, Atom type, void* data);

            long query(Window window,Atom property, Atom type, void* data );

            long getWindows();
};
#endif
