#include "UpdateDlg.hh"
#include <errno.h>
#include "ClamLayer/ClamavInstance.hh"

#undef wxT
#define wxT(data) wxString::FromAscii(data)

UpdateDlg::UpdateDlg(wxWindow *parent) : wxDialog(parent,wxID_ANY,wxT(_("Update")))
{

  wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *ctr = new wxBoxSizer(wxHORIZONTAL);

    m_msg = new wxTextCtrl(this, wxID_ANY,wxT(""), wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
    m_upd = new wxButton(this,wxID_UP,wxT(_("&Update")));

    m_msg->SetEditable(false);

    ctr->Add( m_upd ,0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);
    ctr->Add( new wxButton(this,wxID_CLEAR,wxT(_("&Clear"))) ,0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);

    box->Add(m_msg,1,wxEXPAND|wxALL,5);
    box->Add(ctr,0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);



    this->SetSizer(box);
    this->Layout();
}


void UpdateDlg::run()
{
FILE *fl;
char c;
int fd;
int result;
wxString str;
fd_set readset;

        FD_ZERO(&readset);

        fl = popen("gksu freshclam 2>&1","r");
        fd = fileno(fl);
        this->SetTitle( wxT(_("Updating please wait")));
        m_upd->Disable();

        do
        {
            FD_SET(fd, &readset);
            result = select(fd+1, &readset, NULL, NULL, NULL);


            if(result > 0)
                while( fscanf(fl,"%c",&c) != EOF)
                {
                    wxMutexGuiEnter();
                    m_msg->SetValue( m_msg->GetValue()+wxString::FromAscii(c));
                    m_msg->SetInsertionPointEnd();
                    m_msg->Update();
                    wxMutexGuiLeave();
                }
        }while (result == -1 && errno == EINTR);

        this->SetTitle( wxT(_("Update completed")));
        wxMutexGuiEnter();
        WhiteHawkClamav::ClamavInstance::getInstance()->loadDatabase();
        m_msg->SetValue( m_msg->GetValue()+wxString::FromAscii("\nUpdate Completed..."));
        m_msg->SetInsertionPointEnd();
        m_msg->Update();
        wxMutexGuiLeave();
        pclose(fl);

}


void UpdateDlg::onStartUpdate(wxCommandEvent &evt)
{
        m_msg->Clear();
        this->SetTitle( wxT(_("Updating please wait")));
        this->startThread();
}


void UpdateDlg::onClear(wxCommandEvent &evt)
{
    m_msg->Clear();
}

void UpdateDlg::onTerminate()
{

}

BEGIN_EVENT_TABLE(UpdateDlg,wxDialog)
EVT_BUTTON(wxID_UP,UpdateDlg::onStartUpdate)
EVT_BUTTON(wxID_CLEAR,UpdateDlg::onClear)
END_EVENT_TABLE()
