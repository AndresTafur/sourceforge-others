#include <wx/wx.h>


#include "Page.hh"
#include "WelcomePage.hh"
#include "DepsPage.hh"
#include "PrefixPage.hh"
#include "CopyPage.hh"
#include "FinishPage.hh"

#include "InstallerFrame.hh"
#include "Package.hh"

class Installer: public wxApp
{
public:

        bool OnInit()
        {
         wxString str;
	     WelcomePage    *welco;
	     DepsPage       *deps;
	     PrefixPage     *pref;
	     CopyPage       *copyn;
	     FinishPage     *end;

         InstallerFrame *frame;

            pack = new Package("");

            pack->setName("gl chess");
            pack->setTotalDeps(10);

            ::wxInitAllImageHandlers();
            str << this->argv[0];
            str = str.BeforeLast('/');


            frame  = new InstallerFrame(str);
            welco  = new WelcomePage(frame->GetPanel(),pack->getName());
            deps   = new DepsPage(frame->GetPanel());
            pref   = new PrefixPage(frame->GetPanel(),pack);
            copyn  = new CopyPage(frame->GetPanel(),pack);
            end    = new FinishPage(frame->GetPanel(),pack->getName());

            welco->SetNextPage(deps);
            deps->SetNextPage(pref);
            pref->SetNextPage(copyn);
            copyn->SetNextPage(end);

            frame->SetPage(welco);
            frame->SetTitle( pack->getName() + wxT(" - Whitehawk Installer") );

            this->SetTopWindow(frame);
            frame->Show();

           return TRUE;
        }

protected:
Package    *pack;
};



IMPLEMENT_APP(Installer)
