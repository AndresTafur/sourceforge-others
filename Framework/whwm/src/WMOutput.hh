#ifndef _WM_OUTPUT_
#define _WM_OUTPUT_

#include <X11/Xlib.h>

class WMOutput
{
public:

    void send(Atom property,int data1, int data2 = 0, int data3 = 0, int data4 = 0);

    void send(Window window, Atom property,int data1 = 0, int data2 = 0, int data3 = 0, int data4 = 0);

};

#endif

