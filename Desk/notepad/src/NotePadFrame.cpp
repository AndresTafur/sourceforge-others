#include "Entry.cpp"


enum
{
	ID_SB = 100,
	ID_EN,
	ID_GOTO,

};


class NotePadFrame : public  wxFrame
{
public:

  NotePadFrame() : wxFrame(NULL,wxID_ANY,wxT("WhiteHawkNotePad"), wxDefaultPosition, wxDefaultSize,  wxDEFAULT_FRAME_STYLE, wxT("WhiteHawkNotePad"))
        {
            wxMenuBar   *bar    = new wxMenuBar;
	    wxBoxSizer  *sizer   = new wxBoxSizer(wxVERTICAL);

	    wxMenu      *file   = new wxMenu;
            wxMenu      *edit   = new wxMenu;
            wxMenu      *view   = new wxMenu;
            wxMenu      *help   = new wxMenu;


		bar->Append(file, wxT("&Archivo"));
                bar->Append(edit, wxT("&Editar"));
                bar->Append(view, wxT("&Ver"));
                bar->Append(help, wxT("A&yuda"));

		file->Append(wxID_OPEN,wxT("&Abrir"), wxT("Abre un documento"));
		file->Append(wxID_SAVE,wxT("&Guardar"), wxT("Guarda el documento actual"));
		file->Append(wxID_SAVEAS,wxT("Guardar &como"), wxT("Guarda en un nuevo documento"));
		file->AppendSeparator();
		file->Append(wxID_EXIT,wxT("&Salir"), wxT("Sale de este programa"));

		edit->Append(wxID_UNDO,wxT("&Deshacer"),wxT("Deshace la accion"));
		edit->Append(wxID_REDO,wxT("&Rehacer"),wxT("Rehace la accion"));
		edit->AppendSeparator();

		edit->Append(wxID_SELECTALL,wxT("Seleccionar &todo"),wxT("Selecciona el texto"));
		edit->AppendSeparator();

		edit->Append(ID_GOTO,wxT("&Ir a"), wxT("Va a la linea"));
		edit->Append(wxID_CUT,wxT("Cor&tar"), wxT("Corta la seleccion"));
		edit->Append(wxID_COPY,wxT("&Copiar"),wxT("Copia la seleccion"));
		edit->Append(wxID_PASTE,wxT("&Pegar"),wxT("Pega  la seleccion"));

		view->Append(ID_SB, wxT("&Barra de estado"), wxT("Muestra u oculta esta barra"));

		help->Append(wxID_HELP,wxT("&Ayuda"),wxT("Ayuda de este programa"));
		help->Append(wxID_ABOUT,wxT("A&cerca de"), wxT("Acerca de este programa"));

		statbar = this->CreateStatusBar();
		statbar->SetFieldsCount(2, NULL);

		entry = new  Entry(this,statbar,ID_EN);

		sizer->Add(entry,1,wxEXPAND,0);
		this->Centre();
		this->SetSizer(sizer);
                this->SetMenuBar(bar);
                this->Layout();
        }





	void openDlg(wxCommandEvent &evt)
	{
 	  wxFileDialog dlg(this, _T("Open file"),_T(""),_T("*"), _T("*"),wxFD_OPEN|
			wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, wxT("filedlg"));


		if( dlg.ShowModal() == wxID_OK)
				openFile(dlg.GetPath(), dlg.GetFilename());

	}


	void SaveAsDlg()
	{
	  wxFileDialog dlg(this, _T("Save file"),_T(""),_T("*"), _T("*"),wxFD_SAVE|
			wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize, wxT("filedlg"));

		if( dlg.ShowModal() == wxID_OK)
		{
			entry->setFileName( dlg.GetPath());
			SaveFile();
		}
	}

	void GoToDlg()
	{
	  wxTextEntryDialog dlg(this, wxT("Ir a la linea:"),wxT("Ir a"),wxT(""), wxOK|wxCANCEL | wxCENTRE,wxDefaultPosition);
	  long val;

		if( dlg.ShowModal() == wxID_OK )
		{
			dlg.GetValue().ToLong(&val,10);
			entry->SetInsertionPoint( entry->XYToPosition(0, val)-1);
			entry->Count();
		}

	}


	void openFile(wxString str)
	{
	    entry->readFile( str );
	    saved = true;
	}


	void openFile(wxString str, wxString file)
	{
	    openFile(str);
	    this->SetTitle( file + wxT(" - ") + wxT("WhiteHawkNotePad") );
	}




	void SaveFile()
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



	void Save( wxCommandEvent &evt)
	{
		SaveFile();
	}


	void SaveAs(wxCommandEvent &evt)
	{
	   SaveAsDlg();
	}


	void Action(wxCommandEvent &evt)
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



	void TextEvt(wxCommandEvent &evt)
	{
		if( saved == true)
		{
			this->SetTitle( wxT("*") + this->GetTitle());
			saved = false;
		}
		entry->Count();
	}



	void Quit(wxCommandEvent &evt)
	{
		exit(0);
	}


	void About(wxCommandEvent &evt)
	{
	  wxMessageBox(_T("Este es el block de notas de whiteHawk")
		      wxT("\n\nDesarrollada por Jorge Andres Tafur (c) 2007")
		     ,wxT("Acerca de..."), wxOK| wxICON_INFORMATION,this);
	}

private:
bool saved;
wxStatusBar *statbar;
Entry  *entry;
DECLARE_EVENT_TABLE();

};

BEGIN_EVENT_TABLE(NotePadFrame,wxFrame)


EVT_MENU(wxID_EXIT, NotePadFrame::Quit)
EVT_MENU(wxID_ABOUT, NotePadFrame::About)
EVT_MENU(wxID_OPEN, NotePadFrame::openDlg)
EVT_MENU(wxID_SAVE, NotePadFrame::Save)
EVT_MENU(wxID_SAVEAS, NotePadFrame::SaveAs)

EVT_MENU(wxID_CUT, NotePadFrame::Action)
EVT_MENU(wxID_COPY, NotePadFrame::Action)
EVT_MENU(wxID_REDO, NotePadFrame::Action)
EVT_MENU(wxID_UNDO, NotePadFrame::Action)
EVT_MENU(wxID_PASTE, NotePadFrame::Action)

EVT_MENU(wxID_SELECTALL, NotePadFrame::Action)

EVT_MENU(ID_SB, NotePadFrame::Action)
EVT_MENU(ID_GOTO, NotePadFrame::Action)

EVT_TEXT(ID_EN, NotePadFrame::TextEvt)

END_EVENT_TABLE()
