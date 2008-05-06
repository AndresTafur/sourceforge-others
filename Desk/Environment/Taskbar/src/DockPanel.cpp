#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include "DockPanel.hh"


     DockPanel::DockPanel(wxPoint position,wxSize size ): wxFrame(NULL,wxID_ANY,wxT(""),position,size,wxSTAY_ON_TOP|wxFRAME_NO_TASKBAR|wxBORDER_NONE, wxT(""))
     {

	 }


    void DockPanel::setDockable()
    {
      Atom atom;
      GtkWindow *wnd = GTK_WINDOW(this->GetHandle());


        gtk_window_stick(wnd);
        gtk_window_set_type_hint(wnd, GDK_WINDOW_TYPE_HINT_DOCK);
    }


    void DockPanel::setAsTaskbar()
    {
      int data[4];

        data[0]  =  0;
        data[1]  =  0;
        data[2]  =  0;
        data[3]  =  29;


        gdk_property_change (GTK_WIDGET (this->GetHandle())->window,
                gdk_atom_intern ("_NET_WM_STRUT", FALSE),gdk_atom_intern ("CARDINAL", FALSE), 32,
                GDK_PROP_MODE_REPLACE, (guchar *) data, 4);
    }

