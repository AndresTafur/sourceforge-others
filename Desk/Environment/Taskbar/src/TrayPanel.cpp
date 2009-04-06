#include "TrayPanel.hh"


	TrayPanel::TrayPanel(wxWindow *parent ) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,0,_(""))
	{/*
        gdk_property_change (GTK_WIDGET (this->GetHandle())->window,
                gdk_atom_intern ("_NET_SYSTEM_TRAY_ORIENTATION", false),
                gdk_atom_intern ("_NET_SYSTEM_TRAY_ORIENTATION", false), 32,
                GDK_PROP_MODE_REPLACE, (guchar *) 0, 1);*/
    }


    void TrayPanel::getSelection()
    {
       char *atom_name = (char*) malloc( sizeof(char) *20  );

       sprintf(atom_name,"_NET_SYSTEM_TRAY_S%u",GDK_SCREEN_XNUMBER( gdk_screen_get_default()));

       Atom sel_name = XInternAtom(GDK_DISPLAY(), atom_name,false);
       Atom opcode   = XInternAtom(GDK_DISPLAY(),"_NET_SYSTEM_TRAY_OPCODE",false);
       Atom data     = XInternAtom(GDK_DISPLAY(),"_NET_SYSTEM_TRAY_MESSAGE_DATA",false);

        gdk_property_change (GTK_WIDGET (this->GetHandle())->window,
                gdk_atom_intern ("_NET_SYSTEM_TRAY_ORIENTATION", FALSE),
                gdk_atom_intern ("_NET_SYSTEM_TRAY_ORIENTATION", FALSE), 32,
                GDK_PROP_MODE_REPLACE, (guchar *) 0, 1);


        XSetSelectionOwner(GDK_DISPLAY(), sel_name, GDK_WINDOW_XWINDOW(this->GetHandle()->window), CurrentTime);


      if (XGetSelectionOwner(GDK_DISPLAY(), sel_name) != GDK_WINDOW_XWINDOW(this->GetHandle()->window))
         wxMessageBox( wxT("No pude iniciar el tray."),wxT("Error"),wxICON_ERROR);

    }

