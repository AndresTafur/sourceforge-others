#include "RunFrame.hh"



RunPanel::RunPanel(wxWindow *parent,wxString &str) : wxPanel(parent,wxID_ANY,wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxWANTS_CHARS, wxT(""))
{
		wxBoxSizer *princ = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer *label = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer *commd = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer *bttns = new wxBoxSizer(wxHORIZONTAL);

		wxButton   *accept = new wxButton(this,wxID_OK,wxT("&Aceptar"));
		wxButton   *cancel = new wxButton(this,wxID_CANCEL,wxT("&Cancelar"));
		wxButton   *browse = new wxButton(this,ID_BRW,wxT("&Examinar"));

		wxStaticText *text = new wxStaticText(this,wxID_ANY,wxT(" Abrir:  "));

		wxStaticText *lbl = new wxStaticText(this,wxID_ANY,
		wxT("  Ingrese la ruta del archivo, programa, carpeta, documento\n  o recurso de") wxT("  internet y whiteHawk lo abrira por usted."));

		path = new wxTextCtrl(this,ID_PTH, wxT(""));

		wxBitmap bmp19( str + wxT("/data/pix/logo.png"),wxBITMAP_TYPE_ANY);
		wxStaticBitmap *map = new wxStaticBitmap(this,wxID_ANY,bmp19);

        accept->SetDefault();

		princ->AddSpacer(20);
		label->Add(map,0,wxALIGN_LEFT|wxALL,2);
		label->Add(lbl,0,wxALIGN_CENTER,2);
		commd->Add(text,0,wxALIGN_RIGHT|wxALL,5);
		commd->Add(path,1,wxEXPAND|wxALL,2);

		bttns->Add(accept,0,wxALL,5);
		bttns->Add(cancel,0,wxALL,5);
		bttns->Add(browse,0,wxALL,5);

		princ->Add(label,0,wxSHAPED|wxLEFT|wxRIGHT,20);
		princ->AddSpacer(7);
		princ->Add(commd,1,wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM,10);
		princ->AddSpacer(6);
		princ->Add(bttns,0,wxALIGN_CENTER|wxALL,2);
		princ->AddSpacer(9);

		path->SetFocus();
		this->SetSizer(princ);
        this->Layout();
		this->Fit();
}


	void RunPanel::exec(wxString str)
	{
		if( NULL == popen(str.ToAscii(),"r"))
            wxMessageBox(wxT("Error al ejecutar la aplicacion"),wxT("Error"),wxICON_ERROR);

	}


	void RunPanel::onAccept(wxCommandEvent &evt)
	{
		 exec(path->GetValue());
		 this->GetParent()->Destroy();
	}


	void RunPanel::onCancel(wxCommandEvent &evt)
	{
	  this->GetParent()->Destroy();
	}


	void RunPanel::onBrowse(wxCommandEvent &evt)
	{
	   wxFileDialog dlg(this,wxT("Por favor seleccione"),wxT(""),wxT(""),wxT("*"),0);

		if( dlg.ShowModal() == wxID_OK)
			path->SetValue( path->GetValue() + dlg.GetPath());
	}


BEGIN_EVENT_TABLE(RunPanel,wxPanel)
EVT_BUTTON(wxID_OK,RunPanel::onAccept)
EVT_BUTTON(wxID_CANCEL,RunPanel::onCancel)
EVT_BUTTON(ID_BRW,RunPanel::onBrowse)
END_EVENT_TABLE()



RunFrame::RunFrame(wxString &str) : wxDialog(NULL,wxID_ANY,wxT("Run"), wxDefaultPosition, wxSize(470,180), wxDEFAULT_DIALOG_STYLE|wxTAB_TRAVERSAL|wxCENTER, wxT(""))
{
	  RunPanel *panel = new RunPanel(this,str);
}
