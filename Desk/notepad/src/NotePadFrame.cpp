#include "NotePadFrame.hh"
#include <wx/fontdlg.h>
#include <wx/aboutdlg.h>


 NotePadFrame::NotePadFrame() : wxFrame(NULL,wxID_ANY,wxT("WhiteHawkNotePad"), wxDefaultPosition, wxDefaultSize,  wxDEFAULT_FRAME_STYLE, wxT("WhiteHawkNotePad"))
        {
         wxMenuBar   *bar    = new wxMenuBar;
  	     wxBoxSizer  *sizer   = new wxBoxSizer(wxVERTICAL);
  	     wxMenu      *file   = new wxMenu;
         wxMenu      *edit   = new wxMenu;
         wxMenu      *view   = new wxMenu;
         wxMenu      *help   = new wxMenu;
	     wxMenu	*format = new wxMenu;


            bar->Append(file, wxT("&FIle"));
            bar->Append(edit, wxT("&Edit"));
            bar->Append(format,wxT("&Format"));
            bar->Append(view, wxT("&View"));
            bar->Append(help, wxT("&Help"));

            file->Append(wxID_NEW,wxT("&New"),wxT("New document"));
            file->Append(wxID_OPEN,wxT("&Open"), wxT("Opens a new document"));
            file->Append(wxID_SAVE,wxT("&Save"), wxT("Saves current document"));
            file->Append(wxID_SAVEAS,wxT("Save &As"), wxT("Saves in a new file "));
            file->AppendSeparator();
            file->Append(wxID_EXIT,wxT("&Quit"), wxT("Leaves this program"));

            edit->Append(wxID_UNDO,wxT("&Undo"),wxT("Undo last action"));
            edit->Append(wxID_REDO,wxT("&Redo"),wxT("Redp last action"));
            edit->AppendSeparator();
            edit->Append(wxID_CUT,wxT("Cu&t"), wxT("Cuts current selection"));
            edit->Append(wxID_COPY,wxT("&Copy"),wxT("Copy current selection"));
            edit->Append(wxID_PASTE,wxT("&Paste"),wxT("Paste current selection"));
            edit->AppendSeparator();
            edit->Append(wxID_SELECTALL,wxT("&Select All"),wxT("Selects all of the text"));
            edit->AppendSeparator();
            edit->Append(wxID_FIND,wxT("&Find"),wxT("Search for an expression"));
            edit->Append(wxID_REPLACE,wxT("&Replace"),wxT("Search and replace an expression")); //todo
            edit->AppendSeparator();
            edit->Append(ID_GOTO,wxT("&Go to"), wxT("Go to line"));
            view->Append(ID_SB, wxT("&Status bar"), wxT("Shows/Hides the status bar"));
            format->Append(ID_FORMAT,wxT("Font..."),wxT("change font, size")); //todo
            help->Append(wxID_HELP,wxT("&Help"),wxT("Shows the help"));
            help->Append(wxID_ABOUT,wxT("&About"), wxT("About this program"));

            statbar = this->CreateStatusBar();
            statbar->SetFieldsCount(2, NULL);

            entry = new  Entry(this,statbar,ID_EN);

            sizer->Add(entry,1,wxEXPAND,0);
            this->Centre();
            this->SetSizer(sizer);
            this->SetMenuBar(bar);
            this->Layout();
        }


	void NotePadFrame::openDlg(wxCommandEvent &evt)
	{
 	  wxFileDialog dlg(this, _T("Open file"),_T(""),_T("*"), _T("*"),wxFD_OPEN|
			wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, wxT("filedlg"));


		if( dlg.ShowModal() == wxID_OK)
				openFile(dlg.GetPath(), dlg.GetFilename());

	}


	void NotePadFrame::SaveAsDlg()
	{
	  wxFileDialog dlg(this, _T("Save file"),_T(""),_T("*"), _T("*"),wxFD_SAVE|
			wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize, wxT("filedlg"));

		if( dlg.ShowModal() == wxID_OK)
		{
			entry->setFileName( dlg.GetPath());
			SaveFile();
		}
	}

	void NotePadFrame::GoToDlg()
	{
	  wxTextEntryDialog dlg(this, wxT("Go to line:"),wxT("Go to"),wxT(""), wxOK|wxCANCEL | wxCENTRE,wxDefaultPosition);
	  long val;

		if( dlg.ShowModal() == wxID_OK )
		{
			dlg.GetValue().ToLong(&val,10);
			entry->SetInsertionPoint( entry->XYToPosition(0, val)-1);
			entry->Count();
		}

	}


	void NotePadFrame::openFile(wxString str)
	{
	    entry->readFile( str );
	    saved = true;
	}


	void NotePadFrame::openFile(wxString str, wxString file)
	{
	    openFile(str);
	    this->SetTitle( file + wxT(" - ") + wxT("WhiteHawkNotePad") );
	}

	void NotePadFrame::newFile(wxCommandEvent &evt)
	{
		int i = HaveSaved();
		if (i==wxID_YES || i==wxID_NO)
		{
			entry->Clear();
			saved = false;
			this->SetTitle( wxT("WhiteHawkNotePad") );
			entry->setFileName(wxT(""));
		}
	}

	int NotePadFrame::HaveSaved()
	{
		int i;
		if (!saved)
		{
			wxMessageDialog dlg(this,wxT("Current changes will be lost. Save changes?"),wxT("Not Saved"), wxYES | wxNO | wxCANCEL | wxICON_ERROR , wxDefaultPosition);
			i = dlg.ShowModal();
			if (i==wxID_YES)
				SaveFile();
		}
		else
			i = wxID_YES;
		return i;

	}

	void NotePadFrame::SaveFile()
	{
	    if( !entry->getFileName().IsEmpty() )
	    {
		if( entry->writeFile() )
		{
		  wxString title;

			saved = true;
			title = this->GetTitle();
			this->SetTitle( entry->getRelName() + wxT(" - WhiteHawkNotePad")  );
		}
	    }
	    else
		SaveAsDlg();
	}

	void NotePadFrame::Save( wxCommandEvent &evt)
	{
		SaveFile();
	}


	void NotePadFrame::SaveAs(wxCommandEvent &evt)
	{
	   SaveAsDlg();
	}


	void NotePadFrame::Find ( wxCommandEvent &evt)
	{
		wxString findValue;
		wxTextEntryDialog dlg(this, wxT("Text to find:"),wxT("Find"),wxT(""), wxOK|wxCANCEL | wxCENTRE,wxDefaultPosition);
		if( dlg.ShowModal() == wxID_OK )
		{
			findValue = dlg.GetValue();
			int i = entry->GetValue().Find(findValue);
			if (i==wxNOT_FOUND)
			{
        			{
        				wxMessageDialog dlg(this,wxT("Could not find" + findValue),wxT("Failed"), wxOK | wxICON_ERROR , wxDefaultPosition);
					dlg.ShowModal();
        			}
			}
			else
			{
				entry->SetSelection(i,i + findValue.Len());
			}

		}
	}

	void NotePadFrame::Action(wxCommandEvent &evt)
	{
		switch( evt.GetId())
		{
		  case wxID_CUT:
			entry->Cut();
			break;

		  case wxID_COPY:
			entry->Copy();
			break;

		  case wxID_PASTE:
			entry->Paste();
			break;

		  case wxID_REDO:
			entry->Redo();
			break;

		  case wxID_UNDO:
			entry->Undo();
			break;

		  case wxID_SELECTALL:
			entry->SelectAll();
			break;

		  case ID_SB:
		 	if( statbar->IsShown() )
			  statbar->Show(false);
			else
			  statbar->Show(true);
			break;



		  case ID_GOTO:
			GoToDlg();
			break;


		}


	}

	void NotePadFrame::TextEvt(wxCommandEvent &evt)
	{
		if( saved == true)
		{
			this->SetTitle( wxT("*") + this->GetTitle());
			saved = false;
		}
		entry->Count();
	}

	void NotePadFrame::FormatFont(wxCommandEvent &evt)
	{
		wxFontData fd;
		fd = entry->getFontData();
		//statbar->SetStatusText(fd.GetChosenFont().GetFaceName());
		wxFontDialog dlg(this,fd);
		if (dlg.ShowModal()==wxID_OK)
		{
			entry->setFontData(dlg.GetFontData());
		}
	}

	void NotePadFrame::Quit(wxCommandEvent &evt)
	{
		int i = HaveSaved();
		if (i==wxID_YES || i==wxID_NO)
			exit(0);
	}

	void NotePadFrame::About(wxCommandEvent &evt)
    {
      wxAboutDialogInfo info;
      wxString desc;

        desc << wxT("\n\nWelcome to WhiteHawk notepad."
                    "\nWhiteHawk notepad is a simple editor \nideal for your WhiteHawk Desktop.\n\n");

        info.SetName(wxT("WhiteHawk notepad"));
        info.SetVersion(wxT("0.0.1"));
        info.SetDescription(desc);
        info.SetWebSite(wxT("http://whsystems.sf.net"));
        info.SetCopyright(wxT("Copyright (C) 2007 (lostmarbles)."));
        info.AddDeveloper(wxT("lostmarbles"));
        info.AddDeveloper(wxT("Jorge Andres Tafur"));
        info.SetLicence(wxT

        ("\tWhiteHawkNotepad a simple text editor.\n"
                  "\t\t\tCopyright (C) 2007  (lost marbles)\n\n\n"

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





BEGIN_EVENT_TABLE(NotePadFrame,wxFrame)

EVT_MENU(wxID_NEW, NotePadFrame::newFile)
EVT_MENU(wxID_OPEN, NotePadFrame::openDlg)
EVT_MENU(wxID_SAVE, NotePadFrame::Save)
EVT_MENU(wxID_SAVEAS, NotePadFrame::SaveAs)
EVT_MENU(wxID_EXIT, NotePadFrame::Quit)

EVT_MENU(wxID_UNDO, NotePadFrame::Action)
EVT_MENU(wxID_REDO, NotePadFrame::Action)

EVT_MENU(wxID_CUT, NotePadFrame::Action)
EVT_MENU(wxID_COPY, NotePadFrame::Action)
EVT_MENU(wxID_PASTE, NotePadFrame::Action)

EVT_MENU(wxID_SELECTALL, NotePadFrame::Action)

EVT_MENU(wxID_FIND, NotePadFrame::Find)
EVT_MENU(ID_GOTO, NotePadFrame::Action)
EVT_MENU(ID_FORMAT, NotePadFrame::FormatFont)

EVT_MENU(ID_SB, NotePadFrame::Action)

EVT_TEXT(ID_EN, NotePadFrame::TextEvt)
EVT_MENU(wxID_ABOUT, NotePadFrame::About)
END_EVENT_TABLE()
