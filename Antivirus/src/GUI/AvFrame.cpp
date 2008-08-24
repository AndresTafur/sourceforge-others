#include "AvFrame.hh"




AvFrame::AvFrame(wxString path) : wxFrame(NULL,-1,wxT("WhiteHawkClamAv"),wxDefaultPosition,wxSize(600,400),wxMINIMIZE_BOX|wxCLOSE_BOX)
{
    wxBoxSizer  *imgSzr = new wxBoxSizer(wxVERTICAL);
    wxGridSizer *princ  = new wxGridSizer(1,6);
    wxBoxSizer  *vert   = new wxBoxSizer(wxVERTICAL);
                sizer   = new wxBoxSizer(wxHORIZONTAL);

    wxAnimationCtrl  *load;
    wxAnimation anim1;
    wxButton    *home  = new wxButton(this,ID_HOME,wxT("&Status"));
    wxButton    *ssca  = new wxButton(this,ID_SCANF,wxT("Sc&an Files"));
    wxButton    *qar   = new wxButton(this,102,wxT("&Infected"));
    wxButton    *upd   = new wxButton(this,103,wxT("&Update"));
    wxButton    *hlp   = new wxButton(this,104,wxT("&Help"));


        anim1.LoadFile(path+wxT("/data/pix/scan.gif"));
        load = new wxAnimationCtrl(this,wxID_ANY,anim1);
        note = new AvNotebook(this,load,wxID_ANY);
        icon = new wxIcon(path+wxT("/data/pix/icon.png"), wxBITMAP_TYPE_ANY);


        current = status;

        princ->Add(home,0,wxEXPAND|wxBOTTOM,5);
        princ->Add(ssca,0,wxEXPAND|wxBOTTOM,5);
        princ->Add(qar, 0,wxEXPAND|wxBOTTOM,5);
        princ->Add(upd, 0,wxEXPAND|wxBOTTOM,5);
        princ->Add(hlp, 0,wxEXPAND|wxBOTTOM,5);

        imgSzr->Add(load,0,wxALL|wxCENTRE,10);
        imgSzr->Add(princ,0,wxALL,10);


        sizer->Add(imgSzr);
        sizer->Add(note,1,wxEXPAND|wxLEFT,10);


        vert->Add(sizer,1,wxEXPAND);


        this->SetIcon(*icon);
        this->createMenu();
        this->SetSizer(vert);
        this->Centre();
}




void AvFrame::createMenu()
{
    wxMenuBar   *bar    = new wxMenuBar;

    wxMenu      *file   = new wxMenu;
    wxMenu      *config = new wxMenu;
    wxMenu      *help   = new wxMenu;


        bar->Append(file,   wxT("&File"));
        bar->Append(config, wxT("&Configuration"));
        bar->Append(help,   wxT("&Help"));


        file->Append(wxID_OPEN,wxT("&Scan File"), wxT("Scan a selected File"));
        file->AppendSeparator();
        file->Append(wxID_EXIT,wxT("&Quit"), wxT("Sale de este programa"));


        config->Append(wxID_DOWN,wxT("&File magnament"), wxT("Configures the actions taken about files"));
        config->Append(wxID_APPLY,wxT("&Updates"),        wxT("Configures the updates"));
        config->Append(wxID_ADD,wxT("&Scheduler"),      wxT("Configures autoscaning and autoupdating"));

        help->Append(wxID_HELP,wxT("&Help"),wxT("This program help"));
        help->Append(wxID_ABOUT,wxT("&About"), wxT("About this program"));

        this->SetMenuBar(bar);
}




void AvFrame::onHome(wxCommandEvent &evt)
{
    note->insertStatus();
}

void AvFrame::onScan( wxCommandEvent &evt)
{
    note->insertScan();
}


void AvFrame::onQuit(wxCommandEvent &evt)
{
    this->Destroy();
}


void AvFrame::onAbout(wxCommandEvent &evt)
{
    wxAboutDialogInfo info;
    wxString desc;

            desc << wxT("\n\nThis is the antivirus of the WhiteHawk System\nIt's a Frontend for the clamav antivirus.\n");
            desc << wxT("\nClamav version: ") << cl_retver();
            desc << wxT("\nClamav f-ret: ") << cl_retflevel() << wxT("\n");


        info.SetName(wxT("WhitehawkAv"));
        info.SetVersion(wxT("0.0.1"));
        info.SetDescription(desc);
        info.SetWebSite(wxT("http://whsystems.sf.net"));
        info.SetCopyright(wxT("(C) 2007 Jorge Andres Tafur."));
        info.AddDeveloper(wxT("Jorge Andres Tafur"));
        info.SetLicence(wxT

        ("\tWhiteHawkAntivirus an antivirus based on top of clamav.\n"
                  "\t\t\tCopyright (C) 2007  Jorge andres tafur\n\n\n"

    "This program is free software: you can redistribute it and/or modify\n"
    "it under the terms of the GNU General Public License as published by\n"
    "the Free Software Foundation, either version 3 of the License, or\n"
    "any later version.\n\n"

    "This program is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "GNU General Public License for more details.\n\n"

    "You should have received a copy of the GNU General Public License\n"
    "along with this program.  If not, see http://www.gnu.org/licenses/.")
    );

    wxAboutBox(info);
}


BEGIN_EVENT_TABLE(AvFrame,wxFrame)
    EVT_BUTTON(ID_HOME ,AvFrame::onHome)
    EVT_BUTTON(ID_SCANF ,AvFrame::onScan)
    EVT_MENU(wxID_EXIT, AvFrame::onQuit)
    EVT_MENU(wxID_ABOUT, AvFrame::onAbout)
    EVT_MENU(wxID_OPEN, AvFrame::onScan)
END_EVENT_TABLE()

