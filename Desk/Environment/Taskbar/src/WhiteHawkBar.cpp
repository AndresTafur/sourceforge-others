#include <wx/wx.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include "WindowEventManager.hh"
#include "WhiteHawkBar.hh"
#include "TaskBar.hh"
#include <X11/Xlib.h>
#include <X11/Xatom.h>

bool WhiteHawkBar::OnInit()
{
	  wxString str;
	  TaskBar *taskbar;


            ::wxInitAllImageHandlers();
	    str << this->argv[0];
	    str = str.BeforeLast( '/');

	    taskbar = new TaskBar(str);

        this->SetTopWindow(taskbar);
        taskbar->Show(true);
        taskbar->setAsTaskbar();

         taskbar->getTray()->getSelection();

        WindowEventManager::getInstance()->startThread();

        return TRUE;
}


IMPLEMENT_APP_NO_MAIN(WhiteHawkBar)


int main(int argc, char *argv[])
{
   int ret_val;

	XInitThreads();
	ret_val = wxEntry(argc, argv);

    WindowEventManager::getInstance()->destroy();
    WindowManager::getInstance()->destroy();

	return ret_val;
}
