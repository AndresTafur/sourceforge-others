#include <wx/wx.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include "config.h"
#include "DeskFrame.h"




class Desk: public wxApp
{

        bool OnInit()
        {
	  wxString str;
            ::wxInitAllImageHandlers();

	    str << this->argv[0];
	    str = str.BeforeLast( '/');
	    Display *display = GDK_DISPLAY();

            DeskFrame *frame = new DeskFrame(str);


	   GtkWidget *handle = frame->GetHandle();

            this->onAll( GDK_WINDOW_XWINDOW(handle->window)  );
	    gtk_window_set_keep_below(GTK_WINDOW(handle),1);
	    gtk_window_stick(GTK_WINDOW(handle));
        gtk_window_set_type_hint(GTK_WINDOW(handle), GDK_WINDOW_TYPE_HINT_DESKTOP);
	    this->SetTopWindow(frame);
            frame->Show(true);

           return TRUE;
        }


	void onAll(Window window)
	{
		 long desktop = 0xffffffff;
		 Atom deskAtom;
		 Atom windowTypeAtom;
		 Atom type;

		 Display *dsp = XOpenDisplay(NULL);

		deskAtom       = XInternAtom(dsp,"_NET_WM_DESKTOP",1);

		XChangeProperty(dsp,window,deskAtom,XA_CARDINAL,32,PropModeReplace,(unsigned char*)&desktop,1);

/*
		windowTypeAtom = XInternAtom(dsp,"_NET_WM_WINDOW_TYPE",1);

			//TODO: Fix this, note this **** doesn't work.

		type = XInternAtom(dsp, "_NET_WM_WINDOW_TYPE_DESKTOP", 1);


		XChangeProperty(dsp,window,windowTypeAtom,XA_ATOM,32,PropModeReplace,(unsigned char*)&type,1);

*/

	}

};



IMPLEMENT_APP(Desk)
