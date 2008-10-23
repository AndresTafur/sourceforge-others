/*  This file is part of WhiteHawkClamav,
 *  Copyright (C) 2007 - 2008 Jorge Tafur <darkhawk665@users.sf.net>.
 *
 *   WhiteHawkClamav is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   WhiteHawkClamav is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "AvFrame.hh"
#include "UpdateDlg.hh"
#include "TrayIcon.hh"




AvFrame::AvFrame(wxString path) : wxFrame(NULL,-1,wxT("WhiteHawkClamAv"),wxDefaultPosition,wxSize(640,450),wxMINIMIZE_BOX|wxCLOSE_BOX)
{
    wxBoxSizer  *imgSzr = new wxBoxSizer(wxVERTICAL);
    wxGridSizer *princ  = new wxGridSizer(1,6);
    wxBoxSizer  *vert   = new wxBoxSizer(wxVERTICAL);
    wxButton    *home  = new wxButton(this,ID_HOME,wxT("&Status"));
    wxButton    *ssca  = new wxButton(this,ID_SCANF,wxT("Sc&an Files"));
    wxButton    *qar   = new wxButton(this,102,wxT("&Quarantine"));
    wxButton    *upd   = new wxButton(this,ID_UPDAT,wxT("&Update"));
    wxButton    *hlp   = new wxButton(this,104,wxT("&Help"));

    wxAnimationCtrl  *load = NULL;
    wxAnimation anim1;
    wxIcon appIcon(DATA_DIR"/whclicon.png", wxBITMAP_TYPE_ANY);


        m_trayIcon = new MyTaskBarIcon(this);
        SetIcon( appIcon);

        if (!m_trayIcon->SetIcon(appIcon,wxT("whiteHawkClamav")))
            wxMessageBox(wxT("Could not set icon."));

        m_sizer = new wxBoxSizer(wxHORIZONTAL);

        m_note = new AvNotebook(this,load,wxID_ANY);
        m_current = m_status;

        princ->Add(home,0,wxEXPAND|wxBOTTOM,5);
        princ->Add(ssca,0,wxEXPAND|wxBOTTOM,5);
        princ->Add(qar, 0,wxEXPAND|wxBOTTOM,5);
        princ->Add(upd, 0,wxEXPAND|wxBOTTOM,5);
        princ->Add(hlp, 0,wxEXPAND|wxBOTTOM,5);

        imgSzr->AddSpacer(50);
        imgSzr->Add(princ,0,wxALL,10);


        m_sizer->Add(imgSzr);
        m_sizer->Add(m_note,1,wxEXPAND|wxLEFT,10);

        vert->Add(m_sizer,1,wxEXPAND);

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


        config->Append(wxID_DOWN,wxT("&Scan"), wxT("Configures the actions taken about files and folders"));
        config->Append(wxID_CLEAR,wxT("&Quarantine"),      wxT("Configures Quarantine"));
        config->AppendSeparator();
        config->Append(wxID_APPLY,wxT("&Updater"),        wxT("Configures the updates"));
        config->Append(wxID_ADD,wxT("&Scheduler"),      wxT("Configures autoscaning and autoupdating"));

        help->Append(wxID_HELP,wxT("&Help"),wxT("This program help"));
        help->Append(wxID_ABOUT,wxT("&About"), wxT("About this program"));

        this->SetMenuBar(bar);
}


void AvFrame::onUpdate(wxCommandEvent &evt)
{
 UpdateDlg dlg(this);

        dlg.ShowModal();
}

void AvFrame::onHome(wxCommandEvent &evt)
{
    m_note->showStatusPanel();
}

void AvFrame::onScan( wxCommandEvent &evt)
{
    m_note->showScanPanel();
}


void AvFrame::onQuit(wxCommandEvent &evt)
{
    this->Show(false);
}

void AvFrame::onClose(wxCloseEvent &evt)
{
    this->Show(false);
}


void AvFrame::onAbout(wxCommandEvent &evt)
{
    wxAboutDialogInfo info;
    wxString desc;

        desc << wxT("\n\nWelcome to WhiteHawk System antivirus."
                    "\nwhClamav is a frontend of the clamav antivirus \nideal for your WhiteHawk Desktop.\n\n");

        info.SetName(wxT("WhitehawkAv"));
        info.SetVersion(wxT("0.0.1"));
        info.SetDescription(desc);
        info.SetWebSite(wxT("http://whsystems.sf.net"));
        info.SetCopyright(wxT("Copyright (C) 2007 Jorge Andres Tafur."));
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
    EVT_BUTTON(ID_UPDAT ,AvFrame::onUpdate)
    EVT_MENU(wxID_EXIT, AvFrame::onQuit)
    EVT_MENU(wxID_ABOUT, AvFrame::onAbout)
    EVT_MENU(wxID_OPEN, AvFrame::onScan)
    EVT_CLOSE(AvFrame::onClose)
END_EVENT_TABLE()

