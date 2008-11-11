
#include "UpdateDlg.hh"




UpdateDlg::UpdateDlg(wxWindow *parent) : wxDialog(parent,wxID_ANY,wxT("Update"))
{

  wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);

    m_msg = new wxTextCtrl(this, wxID_ANY,wxT(""), wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);

    m_msg->SetEditable(false);

    box->Add(m_msg,1,wxEXPAND|wxALL,5);
    box->Add( new wxButton(this,wxID_OK,wxT("&Update")),0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);

    this->SetSizer(box);
    this->Layout();
}


void UpdateDlg::onStartUpdate(wxCommandEvent &evt)
{

  FILE *fl;
  wxString str;
  char c;

        m_msg->SetValue(wxT(""));
        fl = popen("freshclam","r");
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
        this->SetTitle( wxT("Update"));
}

BEGIN_EVENT_TABLE(UpdateDlg,wxDialog)
EVT_BUTTON(wxID_OK,UpdateDlg::onStartUpdate)
END_EVENT_TABLE()
