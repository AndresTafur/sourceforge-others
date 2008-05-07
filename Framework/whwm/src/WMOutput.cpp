#include "WMOutput.hh"
#include "WMInstance.hh"

    void WMOutput::send(Atom property,int data1, int data2, int data3, int data4)
    {
            send(WMInstance::getRoot(),property,data1,data2,data3,data4);

    }



    void WMOutput::send(Window window, Atom property,int data1, int data2, int data3, int data4)
    {
	  XClientMessageEvent xevent;

			xevent.type         = ClientMessage;
			xevent.window       = window;

			xevent.message_type = property;
			xevent.format = 32;

			xevent.data.l[0]    = data1;
			xevent.data.l[1]    = data2;
			xevent.data.l[2]    = data3;
			xevent.data.l[4]    = data4;

			XSendEvent(WMInstance::getDisplay(),WMInstance::getRoot(), false, SubstructureNotifyMask, (XEvent*)&xevent);
    }

