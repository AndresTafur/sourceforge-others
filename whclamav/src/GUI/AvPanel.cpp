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

#undef wxT
#define wxT(data) wxString::FromAscii(data)




AvPanel::AvPanel(wxWindow *parent,wxTopLevelWindow *top) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL|wxMAXIMIZE_BOX)
  {
	wxBoxSizer   *sizer      = new wxBoxSizer(wxVERTICAL);
	wxGridSizer	 *prgrsSizer = new wxGridSizer(2,3);

    wxBoxSizer	 *virbtnsSzr = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer	 *virctrlSzr = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer	 *ctrlSizer  = new wxBoxSizer(wxHORIZONTAL);

    wxButton     *remove  = new wxButton(this,ID_VIR_DEL, wxT(_("&Remove")));
    wxButton     *quaran  = new wxButton(this,ID_VIR_MOV, wxT(_("Q&uarantine")));
    wxButton     *select  = new wxButton(this,ID_SELECT_ALL, wxT(_("&Select All")));


        m_frame = top;


		m_start = new wxButton(this,ID_AVSTART, wxT(_("Start")));
		m_stop  = new wxButton(this,ID_AVSTOP, wxT(_("Stop")));

        m_path  = new wxDirPickerCtrl(this,ID_DIALOG,wxT("/"));
		m_bar   = new wxGauge(this,wxID_ANY,100);
		m_file  = new wxTextCtrl(this, wxID_ANY,wxT(""));
		m_fold  = new wxTextCtrl(this, wxID_ANY,wxT(""));

		m_list  = new wxListCtrl(this,ID_LISTCTRL,wxDefaultPosition,wxDefaultSize,wxLC_REPORT|wxLC_VRULES);

		m_stop->Disable();
		m_fold->SetEditable(false);
		m_file->SetEditable(false);
		m_path->SetPath(wxT("/"));


		m_list->InsertColumn(0, wxString( wxT(_("File"))));
		m_list->InsertColumn(1, wxString( wxT(_("Type"))));
		m_list->InsertColumn(2, wxString( wxT(_("Status"))));
		m_list->SetColumnWidth(0, 250);

        virbtnsSzr->Add(remove,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
        virbtnsSzr->Add(quaran,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
        virbtnsSzr->Add(select,0,wxALL|wxALIGN_CENTER_VERTICAL,5);

        virctrlSzr->Add(m_list,1,wxEXPAND|wxALL,5);
        virctrlSzr->Add(virbtnsSzr,0,wxALL|wxALIGN_CENTER_VERTICAL,5);

		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT(_("Progress: "))));
		prgrsSizer->Add(m_bar,0,wxEXPAND);
		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT(_("Scanning Path: "))));
		prgrsSizer->Add(m_path,0,wxEXPAND);
		prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT(_("Current Folder: "))));
		prgrsSizer->Add(m_fold,0,wxEXPAND);
        prgrsSizer->Add( new wxStaticText(this,wxID_ANY,wxT(_("Current File: "))));
		prgrsSizer->Add(m_file,0,wxEXPAND);

		ctrlSizer->Add(m_start,0,wxALIGN_CENTER_HORIZONTAL|wxFIXED_MINSIZE|wxBOTTOM|wxALL,5);
		ctrlSizer->AddSpacer(20);
		ctrlSizer->Add(m_stop,0,wxALIGN_CENTER_HORIZONTAL|wxFIXED_MINSIZE|wxBOTTOM|wxALL,5);

		sizer->Add(prgrsSizer,0,wxALL|wxEXPAND,10);
		sizer->Add(virctrlSzr,1,wxEXPAND|wxALL,5);
		sizer->Add(ctrlSizer,0,wxALIGN_CENTER_HORIZONTAL);

		this->SetSizer(sizer);

		/*
		 * Disabled since it causes segfault on program exit
		 */
		//this->SetDropTarget(this);
  }

  void AvPanel::startScanning(wxString str)
  {
    WhiteHawkClamav::ClamavInstance *claminst;
    WhiteHawkClamav::ClamavScanner  *scanner;

            m_path->SetPath(str);
            m_file->ChangeValue(wxT(""));
            m_fold->ChangeValue(wxT(""));
			m_list->DeleteAllItems();
			m_start->Disable();
			m_stop->Enable();
			m_bar->SetValue(0);
			m_path->Disable();
            m_current = 0;
            m_total   = -1;

            scanner   = WhiteHawkClamav::ClamavInstance::getScanner();
            claminst  = WhiteHawkClamav::ClamavInstance::getInstance();


            this->startThread();

            #ifdef wxCharArray
            scanner->setPath(m_path->GetPath().ToAscii().data());
            #else
            scanner->setPath(m_path->GetPath().ToAscii());
            #endif

            if(!claminst->isDbLoaded())
            {
                m_frame->SetTitle(wxT(_("Loading database - WhiteHawkClamAv")));
                claminst->loadDatabase();
            }

            scanner->removeListener(this);
            scanner->addListener(this);
            scanner->startScan();

  }


  void AvPanel::OnStart(wxCommandEvent &evt)
  {
        startScanning(m_path->GetPath());
  }


  void AvPanel::run()
  {
    #ifdef wxCharArray
    WhiteHawkUtil::AbstractFile path(m_path->GetPath().ToAscii().data());
    #else
    WhiteHawkUtil::AbstractFile path(m_path->GetPath().ToAscii());
    #endif

        m_total = WhiteHawkUtil::SystemPath::getCount(path).getFilesCount();
  }


  void AvPanel::OnStop(wxCommandEvent &evt)
  {
     try
     {
        if( WhiteHawkClamav::ClamavInstance::getScanner()->isRunning())
            WhiteHawkClamav::ClamavInstance::getScanner()->terminateThread();

        m_frame->SetTitle(wxT(_("WhiteHawkClamAv")));
        m_start->Enable();
        m_stop->Disable();
        m_bar->SetValue(0);
        m_path->Enable();

     }
     catch(WhiteHawkUtil::Exception e)
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
                    context->Append(ID_VIR_MOV, wxT(_("Move to Quarantine")),wxT(_("Moves to the quarantine folder.")) , wxITEM_CHECK);
                    context->AppendSeparator();
                    context->Append(wxID_DELETE, wxT(_("Delete")),wxT(_("Delets the file.")), wxITEM_NORMAL);
		    }
		    else
		    {
                   context->Append(ID_VIR_MOV, wxT(_("Move all to Quarantine")),wxT("") , wxITEM_CHECK);
                   context->AppendSeparator();
                   context->Append(wxID_DELETE, wxT(_("Deletes everything")),wxT(""), wxITEM_NORMAL);
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
            wxMessageBox(wxT(_("Not implemented yet.\n")),wxT(_("Error")),wxICON_ERROR);
        }


        void AvPanel::onDel(wxCommandEvent &evt)
        {
          long item = -1;
          int iter=0;
          int  selected = m_list->GetSelectedItemCount();

            if( wxMessageDialog(this,wxT(_("Are you sure to delete the selected files?")), wxT(_("Virus removal")), wxYES_NO).ShowModal() == wxID_YES)
                while (iter < selected)
                {
                    item = m_list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);

                    if( item != -1)
                    {
                        #ifdef wxCharArray
                        WhiteHawkUtil::AbstractFile file(m_list->GetItemText(item).ToAscii().data());
                        #else
                        WhiteHawkUtil::AbstractFile file(m_list->GetItemText(item).ToAscii());
                        #endif

                        if( file.exist())
                        {
                            if( file.Remove() )
                                m_list->SetItem(item, 2, wxT(_("Removed")));
                            else
                            {
                                m_list->SetItem(item, 2, wxT(_("Error")));
                                wxMessageBox(wxT(_("There was an error trying to remove file.\nDo you have permissions?")),wxT(_("Error")),wxICON_ERROR);
                                break;
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





	void AvPanel::onScan(WhiteHawkClamav::ClamFile &file)
	{
         wxString str1, str2;
         unsigned long percent;

                percent = (++m_current)*100/m_total;

                str2 << percent << wxT("% - WhiteHawkClamAv");

                wxMutexGuiEnter();
                m_frame->SetTitle(str2);
                m_bar->SetValue(percent);
                m_file->ChangeValue(wxT(file.getName().c_str()));
                m_fold->ChangeValue(wxT(file.getPath().c_str()));
                wxMutexGuiLeave();
    }

	void AvPanel::onVirus(WhiteHawkClamav::ClamFile &file)
	 {
		  wxString str, str2;

			str << wxT(file.getFullName().c_str());
			str2 << wxT(file.getVirName().c_str());

            wxMutexGuiEnter();
			m_list->InsertItem(0,str); //todo include All files here
			m_list->SetItem(0, 1, str2);
			m_list->SetItem(0, 2, wxT(_("Infected")));
			wxMutexGuiLeave();
    }


    bool AvPanel::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
    {
      WhiteHawkClamav::ClamavInstance *claminst;
      WhiteHawkClamav::ClamavScanner  *scanner;
      size_t nFiles = filenames.GetCount();
      wxString msg = wxT(_("Scan finished "));
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
                            m_frame->SetTitle(wxT(_("Loading database - WhiteHawkClamAv")));
                            this->Update();
                            claminst->loadDatabase();
                    }

                    m_frame->SetTitle(wxT(_("Starting scan - WhiteHawkClamAv")));

                    for ( size_t n = 0; n < nFiles; n++ )
                    {
                       str = filenames[n];
                       #ifdef wxCharArray
                       WhiteHawkClamav::ClamFile file(str.ToAscii().data());
                       #else
                       WhiteHawkClamav::ClamFile file(str.ToAscii());
                       #endif

                        m_file->ChangeValue( str.AfterLast('/') );
                        m_fold->ChangeValue( str.BeforeLast('/') );

                        if( scanner->scanFile(file) )
                        {
                            wxString str, str2;

                                str << wxT(file.getPath().c_str());
                                str2 << wxT(file.getVirName().c_str());

                                m_list->InsertItem(0,str); //todo include All files here
                                m_list->SetItem(0, 1, str2);
                                m_list->SetItem(0, 2, wxT(_("Infected")));
                        }

                    }

                    if( m_list->GetItemCount() == 0)
                       str = wxT(_("no virus found"));
                    else
                      str = wxT(_("virus found."));

                    m_start->Enable();
                    m_stop->Disable();
                    m_bar->SetValue(0);
                    m_path->Enable();
                    m_frame->SetTitle(wxT("WhiteHawkClamAv"));
                    wxMessageBox(msg,wxT(_("Scan finished")),wxICON_INFORMATION);
			}
			catch(WhiteHawkUtil::Exception ex)
			{
              wxString err;
                    ex.print();

                    err << wxT(ex.getMessage().c_str()) << wxT("\n:") << wxT(ex.getMethod().c_str());
                    wxMessageBox(err,wxT(_("Error scanning files")),wxICON_ERROR);
			}
        return true;
    }


	void AvPanel::onError(WhiteHawkClamav::ClamFile &file,std::string errtype )
	{
			fprintf(stderr,"[%s %s] ",errtype.c_str(), file.getPath().c_str() );
    }


    void AvPanel::onFinish()
	{
	  wxString title = wxT(_("Scan Finished "));


              if( m_list->GetItemCount() == 0)
                  title.Append(wxT(_("No virus found")));

              title.Append(wxT(" - WhiteHawkClamAv"));
              wxMutexGuiEnter();
              m_frame->SetTitle(title);
              m_frame->RequestUserAttention(wxUSER_ATTENTION_ERROR);
			  m_start->Enable();
			  m_stop->Disable();
			  m_bar->SetValue(0);
			  m_path->Enable();
			  wxMutexGuiLeave();
    }


    void AvPanel::onTerminate() { }



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
