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

#include "AvPanel.hh"
#include "Exception.hh"



AvPanel::AvPanel(wxWindow *parent, wxAnimationCtrl *anim) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL|wxMAXIMIZE_BOX)
  {

	wxBoxSizer   *sizer      = new wxBoxSizer(wxVERTICAL);
	wxGridSizer	 *prgrsSizer = new wxGridSizer(2,3);

    wxBoxSizer	 *virbtnsSzr = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer	 *virctrlSzr = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer	 *ctrlSizer  = new wxBoxSizer(wxHORIZONTAL);


    wxButton     *remove  = new wxButton(this,ID_VIR_DEL,wxT("&Remove"));
    wxButton     *quaran  = new wxButton(this,ID_VIR_MOV,wxT("Q&uarantine"));
    wxButton     *select  = new wxButton(this,ID_SELECT_ALL,wxT("&Select All"));

		m_start = new wxButton(this,ID_AVSTART,wxT("Start"));
		m_stop  = new wxButton(this,ID_AVSTOP,wxT("Stop"));

        m_path = new wxDirPickerCtrl(this,ID_DIALOG,wxT("/"));
		m_bar  = new wxGauge(this,wxID_ANY,100);
		m_file = new wxTextCtrl(this, wxID_ANY,wxT(""));
		m_fold = new wxTextCtrl(this, wxID_ANY,wxT(""));


		m_list  = new wxListCtrl(this,ID_LISTCTRL,wxDefaultPosition,wxDefaultSize,wxLC_REPORT|wxLC_VRULES);

		this->m_anim = anim;

		m_stop->Disable();
		m_fold->SetEditable(false);
		m_file->SetEditable(false);


		m_list->InsertColumn(0, wxString("File"));
		m_list->InsertColumn(1, wxString("Type"));
		m_list->InsertColumn(2, wxString("Status"));
		m_list->SetColumnWidth(0, 240);

        virbtnsSzr->Add(remove,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
        virbtnsSzr->Add(quaran,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
        virbtnsSzr->Add(select,0,wxALL|wxALIGN_CENTER_VERTICAL,5);

        virctrlSzr->Add(m_list,1,wxEXPAND|wxALL,5);
        virctrlSzr->Add(virbtnsSzr,0,wxALL|wxALIGN_CENTER_VERTICAL,5);

		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT("Progress: ")));
		prgrsSizer->Add(m_bar,0,wxEXPAND);
		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT("Scanning Path: ")));
		prgrsSizer->Add(m_path,0,wxEXPAND);
		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT("Current Folder: ")));
		prgrsSizer->Add(m_fold,0,wxEXPAND);
        prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT("Current File: ")));
		prgrsSizer->Add(m_file,0,wxEXPAND);

		ctrlSizer->Add(m_start,0,wxALIGN_CENTER_HORIZONTAL|wxFIXED_MINSIZE|wxBOTTOM|wxALL,5);
		ctrlSizer->AddSpacer(20);
		ctrlSizer->Add(m_stop,0,wxALIGN_CENTER_HORIZONTAL|wxFIXED_MINSIZE|wxBOTTOM|wxALL,5);

		sizer->Add(prgrsSizer,0,wxALL|wxEXPAND,10);
		sizer->Add(virctrlSzr,1,wxEXPAND|wxALL,5);
		sizer->Add(ctrlSizer,0,wxALIGN_CENTER_HORIZONTAL);

		this->SetSizer(sizer);
		this->SetDropTarget(this);

  }

  void AvPanel::OnStart(wxCommandEvent &evt)
  {
    WhiteHawkClamav::ClamavInstance *claminst;
    WhiteHawkClamav::ClamavScanner  *scanner;


            m_file->ChangeValue(wxT(""));
            m_fold->ChangeValue(wxT(""));
			m_list->DeleteAllItems();
			m_start->Disable();
			m_stop->Enable();
			m_bar->SetValue(0);
			m_path->Disable();

			try
			{
                    scanner =  WhiteHawkClamav::ClamavInstance::getScanner();
                    claminst = WhiteHawkClamav::ClamavInstance::getInstance();

                    scanner->setPath(m_path->GetPath().ToAscii());

                    if(!claminst->isDbLoaded())
                    {
                        ((wxFrame*)  GetParent()->GetParent())->SetTitle(wxT("Loading database - WhiteHawkClamAv"));
                        this->Update();
                        claminst->loadDatabase();
                    }

                    ((wxFrame*)  GetParent()->GetParent())->SetTitle(wxT("Starting scan - WhiteHawkClamAv"));
                    scanner->removeListener(this);
                    scanner->addListener(this);
                    scanner->startScan();
			}
			catch(WhiteHawkSystem::Exception ex)
			{
              wxString err;
                    ex.print();

                    err << ex.getMessage() << wxT("\n:") << ex.getMethod();
                    wxMessageBox(err,wxT("Error scanning files"),wxICON_ERROR);
			}
  }


  void AvPanel::OnStop(wxCommandEvent &evt)
  {
     try
     {
         WhiteHawkClamav::ClamavInstance::getScanner()->terminateThread();
        ((wxFrame*)  GetParent()->GetParent())->SetTitle(wxT("WhiteHawkClamAv"));
  	    m_start->Enable();
		m_stop->Disable();
		m_bar->SetValue(0);
		if(m_anim)
           m_anim->Stop();
		m_path->Enable();
     }
     catch(WhiteHawkSystem::Exception e)
     {
            e.print();
     }
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

        void AvPanel::onSelectAll(wxCommandEvent &evt)
        {
            m_list->SetItemState(-1,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
        }

        //TODO: complete this
        void AvPanel::onMove(wxCommandEvent &evt)
        {
            wxMessageBox(wxT("Not implemented yet.\n"),wxT("Error"),wxICON_ERROR);
        }


        void AvPanel::onDel(wxCommandEvent &evt)
        {
          long item = -1;
          int  selected = m_list->GetSelectedItemCount();

            if( wxMessageDialog(this,wxT("Are you sure to delete the selected files?"), wxT("Virus removal"), wxYES_NO).ShowModal() == wxID_YES)
                for (int iter=0; iter < selected;)
                {
                    item = m_list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);

                    if( item != -1)
                    {
                        WhiteHawkSystem::AbstractFile file(m_list->GetItemText(item).ToAscii());
                        if( file.exist())
                        {
                            if( file.Remove() )
                                m_list->SetItem(item, 2, wxT("Removed"));
                            else
                            {
                                m_list->SetItem(item, 2, wxT("Error"));
                                wxMessageBox(wxT("There was an error trying to remove file.\n"
                                "Do you have permissions?"),wxT("Error"),wxICON_ERROR);
                            }
                        }

                        iter++;
                    }
                }
        }

        void AvPanel::onSwitchDir(wxFileDirPickerEvent &evt)
        {
                m_path->SetPath( evt.GetPath() );
        }





	void AvPanel::onScan(WhiteHawkClamav::ClamFile &file, long long totalFiles)
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
                m_fold->ChangeValue(str.BeforeLast('/'));
                wxMutexGuiLeave();
        }
    }

	void AvPanel::onVirus(WhiteHawkClamav::ClamFile &file)
	 {
		  wxString str, str2;

			str << file.getPath().c_str();
			str2 << file.getVirName().c_str();

            wxMutexGuiEnter();
			m_list->InsertItem(0,str); //todo include All files here
			m_list->SetItem(0, 1, str2);
			m_list->SetItem(0, 2, wxT("Infected"));
			wxMutexGuiLeave();
    }


    bool AvPanel::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
    {
      WhiteHawkClamav::ClamavInstance *claminst;
      WhiteHawkClamav::ClamavScanner  *scanner;
      size_t nFiles = filenames.GetCount();
      wxString title = wxT("Scan Finished ");
      wxString str;



			try
			{
                    scanner = WhiteHawkClamav::ClamavInstance::getScanner();
                    claminst = WhiteHawkClamav::ClamavInstance::getInstance();

                    if( !m_start->IsEnabled())
                        return false;


                    m_list->DeleteAllItems();
                    m_start->Disable();
                    m_stop->Enable();
                    m_bar->SetValue(0);
                    m_path->Disable();


                    if(!claminst->isDbLoaded())
                    {
                            ((wxFrame*)  GetParent()->GetParent())->SetTitle(wxT("Loading database - WhiteHawkClamAv"));
                            this->Update();
                            claminst->loadDatabase();
                    }

                    ((wxFrame*)  GetParent()->GetParent())->SetTitle(wxT("Starting scan - WhiteHawkClamAv"));

                    for ( size_t n = 0; n < nFiles; n++ )
                    {
                       str = filenames[n];
                       WhiteHawkClamav::ClamFile file(str.ToAscii());

                        m_file->ChangeValue( str.AfterLast('/') );
                        m_fold->ChangeValue( str.BeforeLast('/') );

                        if( scanner->scanFile(file) )
                        {
                            wxString str, str2;

                                str << file.getPath().c_str();
                                str2 << file.getVirName().c_str();

                                m_list->InsertItem(0,str); //todo include All files here
                                m_list->SetItem(0, 1, str2);
                                m_list->SetItem(0, 2, wxT("Infected"));
                        }

                    }

                    if( m_list->GetItemCount() == 0)
                        title.Append("No virus found - ");


                    m_start->Enable();
                    m_stop->Disable();
                    m_bar->SetValue(0);
                    m_path->Enable();
                    title.Append("WhiteHawkClamAv");
                    ((wxFrame*)  GetParent()->GetParent())->SetTitle(title);
			}
			catch(WhiteHawkSystem::Exception ex)
			{
              wxString err;
                    ex.print();

                    err << ex.getMessage() << wxT("\n:") << ex.getMethod();
                    wxMessageBox(err,wxT("Error scanning files"),wxICON_ERROR);
			}
        return true;
    }


	void AvPanel::onError(WhiteHawkClamav::ClamFile &file,std::string errtype )
	{
			fprintf(stderr,"[%s %s] ",errtype.c_str(), file.getPath().c_str() );
    }


    void AvPanel::onFinish()
	{
	  wxString title = wxT("Scan Finished ");


                if( m_list->GetItemCount() == 0)
                    title.Append("No virus found - ");

                title.Append("WhiteHawkClamAv");
              wxMutexGuiEnter();
              ((wxFrame*)  GetParent()->GetParent())->SetTitle(title);
			  m_start->Enable();
			  m_stop->Disable();
			  m_bar->SetValue(0);
			  m_path->Enable();
			  wxMutexGuiLeave();
    }




BEGIN_EVENT_TABLE(AvPanel,wxPanel)
EVT_BUTTON(ID_AVSTART,AvPanel::OnStart)
EVT_BUTTON(ID_AVSTOP,AvPanel::OnStop)

EVT_BUTTON(ID_VIR_MOV,AvPanel::onMove)
EVT_BUTTON(ID_VIR_DEL,AvPanel::onDel)
EVT_BUTTON(ID_SELECT_ALL,AvPanel::onSelectAll)


EVT_LIST_ITEM_RIGHT_CLICK(ID_LISTCTRL,AvPanel::OnListItem)
EVT_MENU(ID_VIR_MOV,AvPanel::onMove)
EVT_MENU(wxID_DELETE,AvPanel::onDel)
EVT_DIRPICKER_CHANGED(ID_DIALOG, AvPanel::onSwitchDir)
END_EVENT_TABLE()
