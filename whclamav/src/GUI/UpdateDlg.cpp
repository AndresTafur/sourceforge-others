
#include "UpdateDlg.hh"




UpdateDlg::UpdateDlg(wxWindow *parent) : wxDialog(parent,wxID_ANY,wxT("Update"))
{

  wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *ctr = new wxBoxSizer(wxHORIZONTAL);

    m_msg = new wxTextCtrl(this, wxID_ANY,wxT(""), wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);

    m_msg->SetEditable(false);

    ctr->Add( new wxButton(this,wxID_UP,wxT("&Update")),0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);
    ctr->Add( new wxButton(this,wxID_CLEAR,wxT("&Clear")),0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);

    box->Add(m_msg,1,wxEXPAND|wxALL,5);
    box->Add(ctr,0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);



    this->SetSizer(box);
    this->Layout();
}


void UpdateDlg::run()
{
FILE *fl;
char c;
wxString str;

        fl = popen("freshclam 2>&1","r");
        this->SetTitle( wxT("Updating please wait"));

        do
        {
           c = fgetc(fl);
            //todo select or poll
           if( c != EOF)
            str << c;
        }while( !feof(fl));

        pclose(fl);
        m_msg->SetValue( m_msg->GetValue() + str);


}


void UpdateDlg::onStartUpdate(wxCommandEvent &evt)
{

        m_msg->Clear();
        this->SetTitle( wxT("Updating please wait"));
        this->startThread();


}


void UpdateDlg::onClear(wxCommandEvent &evt)
{
    m_msg->Clear();
}

void UpdateDlg::onTerminate()
{
    wxMutexGuiEnter();
    this->SetTitle( wxT("Updated"));
    wxMutexGuiLeave();
}

BEGIN_EVENT_TABLE(UpdateDlg,wxDialog)
EVT_BUTTON(wxID_UP,UpdateDlg::onStartUpdate)
EVT_BUTTON(wxID_CLEAR,UpdateDlg::onClear)
END_EVENT_TABLE()
