#include "AvPanel.hh"




AvPanel::AvPanel(wxWindow *parent, wxAnimationCtrl *anim, WhiteHawkClamav::Clamav *mgr) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL)
  {
	wxBoxSizer	 *ctrlSizer  = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer   *sizer      = new wxBoxSizer(wxVERTICAL);
	wxGridSizer	 *prgrsSizer = new wxGridSizer(2,2);

		start = new wxButton(this,ID_AVSTART,wxT("Start"));
		stop  = new wxButton(this,ID_AVSTOP,wxT("Stop"));


		bar    = new wxGauge(this,wxID_ANY,100);
		file   = new wxTextCtrl(this, wxID_ANY,wxT(""));


		list  = new wxListCtrl(this,ID_LISTCTRL,wxDefaultPosition,wxDefaultSize,wxLC_REPORT|wxLC_VRULES);
		this->mgr = mgr;
		mgr->setListener(this);
		m_total = mgr->getTotalFiles();

		this->anim = anim;

		stop->Disable();
		file->Disable();



		list->InsertColumn(0, wxString("File"));
		list->InsertColumn(1, wxString("Type"));
		list->InsertColumn(2, wxString("Status"));
		list->SetColumnWidth(0, 300);


		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT("Progress: ")));
		prgrsSizer->Add(bar,0,wxEXPAND);
		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT("Scanning File: ")));
		prgrsSizer->Add(file,0,wxEXPAND);


		ctrlSizer->Add(start,0,wxALIGN_CENTER_HORIZONTAL|wxFIXED_MINSIZE|wxBOTTOM|wxALL,5);
		ctrlSizer->AddSpacer(20);
		ctrlSizer->Add(stop,0,wxALIGN_CENTER_HORIZONTAL|wxFIXED_MINSIZE|wxBOTTOM|wxALL,5);

		sizer->Add(prgrsSizer,0,wxALL|wxEXPAND,10);
		sizer->Add(list,1,wxEXPAND|wxALL,5);
		sizer->Add(ctrlSizer,0,wxALIGN_CENTER_HORIZONTAL);

		this->SetSizer(sizer);
  }


        void AvPanel::setPath(wxString path)
        {
             this->path = path;
        }



		void AvPanel::onVirus(WhiteHawkClamav::ClamFile file)
		{
		  wxString str, str2;
		  int id;
			str << file.getPath().c_str();
			str2 << file.getVirName().c_str();

			list->InsertItem(0,str); //todo include All files here
			list->SetItem(0, 1, str2);
			list->SetItem(0, 2, wxT("Infected"));
        }

		void AvPanel::onScan(WhiteHawkClamav::ClamFile fileName)
		{
		    if( fileName.getId() != 0)
		    {
              wxString str, str2;
              unsigned long percent = (fileName.getId()+1)*100/m_total;

                fprintf(stderr,"%i",m_total);
                str << fileName.getPath().c_str();/*
                str2 << percent << wxT("% - WhiteHawkClamAv");

                wxMutexGuiEnter();
                bar->SetValue(percent);
                file->ChangeValue( str );
                ((wxFrame*)this->GetParent()->GetParent())->SetTitle(str2);
                wxMutexGuiLeave();*/
		    }
		}



		void AvPanel::onFinish()
		{
              wxMutexGuiEnter();
			  start->Enable();
			  stop->Disable();
			  anim->Stop();
			  ((wxFrame*)this->GetParent()->GetParent())->RequestUserAttention(wxUSER_ATTENTION_INFO);
			  wxMutexGuiLeave();
		}


		void AvPanel::onError(WhiteHawkClamav::ClamFile file,std::string errtype )
		{
			fprintf(stderr,"[%s] ",errtype.c_str(), file.getPath().c_str() );
		}



		void AvPanel::OnStart(wxCommandEvent &evt)
		{
			list->DeleteAllItems();

			start->Disable();
			stop->Enable();


			anim->Play();
            file->SetValue(path);
			bar->SetValue(0);
			mgr->startScan(path.ToAscii());
		}


		void AvPanel::OnStop(wxCommandEvent &evt)
		{
			mgr->Terminate();
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
          int  selected = list->GetSelectedItemCount();

            for (int iter=0; iter < selected;)
            {
                item = list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
                if ( item != -1 )
                {
                    WhiteHawkSystem::AbstractFile file(list->GetItemText(item).ToAscii());

                    if( file.Remove() )
                      list->SetItem(item, 2, wxT("Removed"));
                    else
                    {
                      list->SetItem(item, 2, wxT("Error"));
                      wxMessageBox(wxT("There was an error trying to remove file.\n"
                      "Do you have already deleted it?\n"
                      "Do you have permissions?"),wxT("Error"),wxICON_ERROR);
                    }

                    iter++;
                }
            }
        }


BEGIN_EVENT_TABLE(AvPanel,wxPanel)
EVT_BUTTON(ID_AVSTART,AvPanel::OnStart)
EVT_BUTTON(ID_AVSTOP,AvPanel::OnStop)
EVT_LIST_ITEM_RIGHT_CLICK(ID_LISTCTRL,AvPanel::OnListItem)
EVT_MENU(ID_VIR_MOV,AvPanel::onMove)
EVT_MENU(wxID_DELETE,AvPanel::onDel)
END_EVENT_TABLE()
