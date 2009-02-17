#include "UpdateDlg.hh"
#include <errno.h>

#undef wxT
#define wxT(data) wxString::FromAscii(data)

UpdateDlg::UpdateDlg(wxWindow *parent) : wxDialog(parent,wxID_ANY,wxT(_("Update")))
{

  wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *ctr = new wxBoxSizer(wxHORIZONTAL);

    m_msg = new wxTextCtrl(this, wxID_ANY,wxT(""), wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);

    m_msg->SetEditable(false);

    ctr->Add( new wxButton(this,wxID_UP,wxT(_("&Update"))),0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);
    ctr->Add( new wxButton(this,wxID_CLEAR,wxT(_("&Clear"))),0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);

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

        fl = popen("freshclam 2>&1","r");
        fd = fileno(fl);
        this->SetTitle( wxT(_("Updating please wait")));


        do
        {
            FD_SET(fd, &readset);
            result = select(fd+1, &readset, NULL, NULL, NULL);


            if(result > 0)
            {
                while( fscanf(fl,"%c",&c) != EOF)
                    str.Append( wxString::FromAscii(c));


                wxMutexGuiEnter();
                m_msg->SetValue( str);
                m_msg->Update();
                this->Update();
                wxMutexGuiLeave();
            }

        } while (result == -1 && errno == EINTR);

        this->SetTitle( wxT(_("Update completed")));

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
    wxMutexGuiEnter();
    this->SetTitle( wxT(_("Updated")));
    wxMutexGuiLeave();
}

BEGIN_EVENT_TABLE(UpdateDlg,wxDialog)
EVT_BUTTON(wxID_UP,UpdateDlg::onStartUpdate)
EVT_BUTTON(wxID_CLEAR,UpdateDlg::onClear)
END_EVENT_TABLE()
