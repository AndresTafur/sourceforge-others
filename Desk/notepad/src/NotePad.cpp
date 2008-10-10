#include <wx/wx.h>
#include "wx/fontdlg.h"
#include "NotePadFrame.hh"

class WhiteCalc: public wxApp
{

        bool OnInit()
        {
            ::wxInitAllImageHandlers();
            NotePadFrame *frame = new NotePadFrame( );

	     if( argc > 1)
		    frame->openFile(argv[1]);

             frame->Show(true);
             this->SetTopWindow(frame);
           return TRUE;
        }


};



IMPLEMENT_APP(WhiteCalc)
