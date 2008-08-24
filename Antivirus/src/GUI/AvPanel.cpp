#include "AvPanel.hh"
#include "Exception.hh"


AvPanel::AvPanel(wxWindow *parent, wxAnimationCtrl *anim,wxString path) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL|wxMAXIMIZE_BOX)
  {
	wxBoxSizer	 *ctrlSizer  = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer   *sizer      = new wxBoxSizer(wxVERTICAL);
	wxGridSizer	 *prgrsSizer = new wxGridSizer(2,3);

		start = new wxButton(this,ID_AVSTART,wxT("Start"));
		stop  = new wxButton(this,ID_AVSTOP,wxT("Stop"));


		m_bar  = new wxGauge(this,wxID_ANY,100);
		m_file = new wxTextCtrl(this, wxID_ANY,wxT(""));
		m_path = new wxTextCtrl(this, wxID_ANY,path);


		m_list  = new wxListCtrl(this,ID_LISTCTRL,wxDefaultPosition,wxDefaultSize,wxLC_REPORT|wxLC_VRULES);

        WhiteHawkClamav::Clamav::getInstance()->setPath(path.ToAscii());
        WhiteHawkClamav::Clamav::getInstance()->addListener(this);

		this->anim = anim;

		stop->Disable();
		m_file->SetEditable(false);

		m_list->InsertColumn(0, wxString("File"));
		m_list->InsertColumn(1, wxString("Type"));
		m_list->InsertColumn(2, wxString("Status"));
		m_list->SetColumnWidth(0, 300);


		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT("Progress: ")));
		prgrsSizer->Add(m_bar,0,wxEXPAND);
		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT("Scanning Path: ")));
		prgrsSizer->Add(m_path,0,wxEXPAND);
        prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT("Scanning File: ")));
		prgrsSizer->Add(m_file,0,wxEXPAND);

		ctrlSizer->Add(start,0,wxALIGN_CENTER_HORIZONTAL|wxFIXED_MINSIZE|wxBOTTOM|wxALL,5);
		ctrlSizer->AddSpacer(20);
		ctrlSizer->Add(stop,0,wxALIGN_CENTER_HORIZONTAL|wxFIXED_MINSIZE|wxBOTTOM|wxALL,5);

		sizer->Add(prgrsSizer,0,wxALL|wxEXPAND,10);
		sizer->Add(m_list,1,wxEXPAND|wxALL,5);
		sizer->Add(ctrlSizer,0,wxALIGN_CENTER_HORIZONTAL);

		this->SetSizer(sizer);
  }

  void AvPanel::OnStart(wxCommandEvent &evt)
  {
			m_list->DeleteAllItems();

			start->Disable();
			stop->Enable();
			anim->Play();
			m_bar->SetValue(0);

			try
			{
                    WhiteHawkClamav::Clamav::getInstance()->startScan();
			}
			catch(WhiteHawkSystem::Exception ex)
			{
              wxString err;

                    err << ex.getMessage() << wxT("\n:") << ex.getMethod();
                    wxMessageBox(err,wxT("Error scanning files"),wxICON_ERROR);
			}
  }


  void AvPanel::OnStop(wxCommandEvent &evt)
  {
	 WhiteHawkClamav::Clamav::getInstance()->Terminate();
	 this->onFinish();
  }


		void AvPanel::OnListItem(wxListEvent &evt)
		{
            wxString path;
            wxMenu *context = new wxMenu;

		    if( !evt.GetText().IsEmpty() )
		    {
                    context->Append(ID_VIR_MOV, wxT("Mover a cuarentena"),wxT("Mueve a la carpeta destinada a cuarentena.") , wxITEM_CHECK);
                    context->AppendSeparator();
                    context->Append(wxID_DELETE, wxT("Eliminar"),wxT("Elimina permanentemente el archivo."), wxITEM_NORMAL);
		    }
		    else
		    {
                   context->Append(ID_VIR_MOV, wxT("Mover todo a cuarentena"),wxT("") , wxITEM_CHECK);
                   context->AppendSeparator();
                   context->Append(wxID_DELETE, wxT("Eliminar todo"),wxT(""), wxITEM_NORMAL);
            }
            PopupMenu(context);

		}


        void AvPanel::onMove(wxCommandEvent &evt)
        {
        }


        void AvPanel::onDel(wxCommandEvent &evt)
        {
          long item = -1;
          int  selected = m_list->GetSelectedItemCount();

            for (int iter=0; iter < selected;)
            {
                item = m_list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
                if ( item != -1 )
                {
                    WhiteHawkSystem::AbstractFile file(m_list->GetItemText(item).ToAscii());

                    if( file.Remove() )
                      m_list->SetItem(item, 2, wxT("Removed"));
                    else
                    {
                      m_list->SetItem(item, 2, wxT("Error"));
                      wxMessageBox(wxT("There was an error trying to remove file.\n"
                      "Do you have already deleted it?\n"
                      "Do you have permissions?"),wxT("Error"),wxICON_ERROR);
                    }

                    iter++;
                }
            }
        }

	void AvPanel::onScan(WhiteHawkClamav::ClamFile &file, int totalFiles)
	{
        if( file.getId() != 0)
        {
         wxString str, str2;
         unsigned long percent = (file.getId()+1)*100/totalFiles;

            str << file.getPath().c_str();
            str2 << percent << wxT("% - WhiteHawkClamAv");

                wxMutexGuiEnter();
                ((wxFrame*)  GetParent()->GetParent())->SetTitle(str2);
                m_bar->SetValue(percent);
                m_file->ChangeValue(str.AfterLast('/'));
                m_path->ChangeValue(str.BeforeLast('/'));
                m_file->SetInsertionPointEnd();
                wxMutexGuiLeave();
        }
    }

	void AvPanel::onVirus(WhiteHawkClamav::ClamFile &file)
	 {
		  wxString str, str2;
		  int id;

			str << file.getPath().c_str();
			str2 << file.getVirName().c_str();

			m_list->InsertItem(0,str); //todo include All files here
			m_list->SetItem(0, 1, str2);
			m_list->SetItem(0, 2, wxT("Infected"));
    }

	void AvPanel::onError(WhiteHawkClamav::ClamFile &file,std::string errtype )
	{
			fprintf(stderr,"[%s] ",errtype.c_str(), file.getPath().c_str() );
    }


    void AvPanel::onFinish()
	{
              wxMutexGuiEnter();
              ((wxFrame*)  GetParent()->GetParent())->SetTitle(wxT("WhiteHawkClamAv"));
			  start->Enable();
			  stop->Disable();
			  m_bar->SetValue(0);
			  anim->Stop();
			  wxMutexGuiLeave();
    }


BEGIN_EVENT_TABLE(AvPanel,wxPanel)
EVT_BUTTON(ID_AVSTART,AvPanel::OnStart)
EVT_BUTTON(ID_AVSTOP,AvPanel::OnStop)
EVT_LIST_ITEM_RIGHT_CLICK(ID_LISTCTRL,AvPanel::OnListItem)
EVT_MENU(ID_VIR_MOV,AvPanel::onMove)
EVT_MENU(wxID_DELETE,AvPanel::onDel)
END_EVENT_TABLE()
