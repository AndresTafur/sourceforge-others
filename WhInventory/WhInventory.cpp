#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>

#include "MainFrame.hh"



class MyApp: public wxApp
{


   bool OnInit()
    {
        ::wxInitAllImageHandlers();
	MainFrame *frame = new MainFrame( );

        frame->Show(true);
        frame->runMainDlg();
        this->SetTopWindow(frame);
    return TRUE;
    }

};

IMPLEMENT_APP(MyApp)


