#include <wx/wx.h>
#include <wx/tooltip.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <wx/filepicker.h>

#include "Page.cpp"
#include "WelcomePage.cpp"
#include "GPartedPage.cpp"
#include "PartitionsPage.cpp"
#include "InstallerFrame.cpp"
#include "InstallingPage.cpp"


class Installer: public wxApp
{
public:

        bool OnInit()
        {
	  wxString str;
	  WelcomePage    *welco;
	  GPartedPage    *gpart;	
	  PartitionsPage *prtpg; 
	  
	  InstallerFrame *frame;
	   


            ::wxInitAllImageHandlers();
	    str << this->argv[0];
	    str = str.BeforeLast('/'); 

	      


	    frame  = new InstallerFrame(str);
  	    welco  = new WelcomePage(frame->GetPanel());
	    gpart  = new GPartedPage(frame->GetPanel());
	    prtpg  = new PartitionsPage(frame->GetPanel());
	    instl  = new InstallingPage(frame->GetPanel());


	    welco->SetNextPage(gpart);  
	    gpart->SetNextPage(prtpg); 
	    prtpg->SetNextPage(instl);
	    frame->SetPage(welco);

            this->SetTopWindow(frame);
	    frame->Show();

           return TRUE;
        }

	int OnExit()
	{
		instl->Exit();
	}

protected:
InstallingPage *instl;
};



IMPLEMENT_APP(Installer)
