#include <wx/wx.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include "WindowEventManager.hh"
#include "SystemUtils.hh"
#include "WhiteHawkBar.hh"
#include "TaskBar.hh"
#include <X11/Xlib.h>
#include <X11/Xatom.h>

bool WhiteHawkBar::OnInit()
{
	  wxString str;
	  TaskBar *taskbar;
	  SystemUtils *sysUtils = new SystemUtils();
	  WindowEventManager *evtmgr;

        XInitThreads();

            ::wxInitAllImageHandlers();
	    str << this->argv[0];
	    str = str.BeforeLast( '/');

	    taskbar = new TaskBar(str,sysUtils);

        this->SetTopWindow(taskbar);
        taskbar->Show(true);
        taskbar->setAsTaskbar();

        evtmgr = new WindowEventManager(sysUtils,taskbar);
        evtmgr->Create();
        return TRUE;
}


IMPLEMENT_APP(WhiteHawkBar)
