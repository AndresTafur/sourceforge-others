#include "InstallerFrame.hh"


InstallerFrame::InstallerFrame(wxString str) : wxFrame(NULL,idle,wxT("WhiteHawk Installer"),wxDefaultPosition,wxSize(640,480),wxDEFAULT_DIALOG_STYLE|wxCENTRE,_("F"))
{

wxBoxSizer     *sizer;
wxStaticBitmap *bitmap;
wxStaticLine   *line;
wxStaticLine   *line2;
wxBoxSizer     *ctrl;



		str += wxT("/data/pix/installer1.png");

		sizer  = new wxBoxSizer(wxVERTICAL);
		bitmap = new wxStaticBitmap(this,wxID_ANY,str,wxDefaultPosition,wxDefaultSize,0,_T("b"));
		line   = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_HORIZONTAL,_("L"));
		panel  = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL);
		line2  = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_HORIZONTAL,_("L2"));


		pnlSzr = new wxBoxSizer(wxVERTICAL);

		prev   = new wxButton(this,ID_PREV,"&Anterior",wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,"b");
		next   = new wxButton(this,ID_NEXT,"&Siguiente",wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,"b");
		ctrl   = new wxBoxSizer(wxHORIZONTAL);


		panel->SetSizer(pnlSzr);

		ctrl->Add(prev,1,wxFIXED_MINSIZE|wxALL,10);
		ctrl->Add(next,1,wxFIXED_MINSIZE|wxALL,10);

		prev->Disable();


		sizer->Add(bitmap);
		sizer->Add(line,0,wxEXPAND|wxALL,10);
		sizer->Add(panel,1,wxEXPAND|wxALIGN_CENTER|wxLEFT|wxRIGHT,10);
		sizer->Add(line2,0,wxEXPAND|wxALL,10);
		sizer->Add(ctrl,0,wxSHAPED|wxALIGN_CENTER|wxALL,2);

		this->CenterOnScreen();
		this->SetSizer(sizer);
		this->Layout();

}


wxPanel* InstallerFrame::GetPanel()
{
	  return panel;
}

void InstallerFrame::SetPage(Page *page)
{
		curr = page;
		pnlSzr->Add(curr);
}

void InstallerFrame::onNext(wxCommandEvent &e)
{

		if( curr->GetNextPage() )
		{
			pnlSzr->Remove(curr);
			curr->Show(false);
			curr = curr->GetNextPage();

			if( curr->isLast())
				next->SetLabel("&Terminar");

			prev->Enable();
			pnlSzr->Add(curr);
			curr->OnPresent();
			curr->Show();
		}
		else
		  this->Destroy();

}

void InstallerFrame::onPrev(wxCommandEvent &e)
{
		if( curr->GetLastPage() )
		{
			pnlSzr->Remove(curr);
			curr->Show(false);
			curr = curr->GetLastPage();

			if(curr->isFirst())
			   prev->Disable();

			next->Enable();
			next->SetLabel("&Siguiente");
			pnlSzr->Add(curr);
			curr->Show();
		}
}

wxButton* InstallerFrame::GetNextButton()
{
		return next;
}

wxButton* InstallerFrame::GetLastButton()
{
		return prev;
}


BEGIN_EVENT_TABLE(InstallerFrame,wxFrame)
EVT_BUTTON(ID_NEXT,InstallerFrame::onNext)
EVT_BUTTON(ID_PREV,InstallerFrame::onPrev)
END_EVENT_TABLE()




