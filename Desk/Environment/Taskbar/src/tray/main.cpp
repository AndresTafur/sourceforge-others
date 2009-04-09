#include "bar.h"


class MyFrame : public wxFrame
{
public:


    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame((wxFrame *)NULL, -1, title, pos, size)
    {



    }

};

class App : public wxApp
{

    bool OnInit()
    {
      MyFrame *frame = new MyFrame( _T("Hello World"), wxPoint(50,50), wxSize(450,340) );
      TrayPanel *panel = new TrayPanel(frame);

        frame->Show(TRUE);
        SetTopWindow(frame);
        panel->Show(true);
        frame->Update();

        panel->getSelection();
        panel->startThread();

        return true;
    }


};



IMPLEMENT_APP_NO_MAIN(App)

int main(int argc, char *argv[])
{
   int ret_val;

	XInitThreads();
   ret_val =  wxEntry(argc,argv);

	return ret_val;

}
