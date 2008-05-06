#include <iostream>
#include <wx/wx.h>
#include <wx/animate.h>
#include <X11/Xlib.h>

//#include "rcids.h"
#include "GUI/AvFrame.hh"


class MyApp: public wxApp
{

   bool OnInit()
    {



     wxString str;
     AvFrame *frame;

      ::wxInitAllImageHandlers();

      str << this->argv[0];

      str   = str.BeforeLast( '/');
      frame = new AvFrame( str);


      frame->Show(TRUE);
      this->SetTopWindow(frame);

    return TRUE;
    }

};

IMPLEMENT_APP_NO_MAIN(MyApp)




int main(int argc, char *argv[])
{
	XInitThreads();

	return wxEntry(argc, argv);
}
