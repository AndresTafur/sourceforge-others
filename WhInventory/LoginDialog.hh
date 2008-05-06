
#ifndef _LOGIN_DIALOG_
#define _LOGIN_DIALOG_


#include <wx/wx.h>

class LoginDialog : public wxDialog
{
public:
            LoginDialog(wxFrame *parent);

            void onAccept( wxCommandEvent &evt);

            void onCancel(wxCommandEvent &evt);

protected:
wxTextCtrl *m_user;
wxTextCtrl *m_pass;
wxTextCtrl *m_host;
wxTextCtrl *m_port;
DECLARE_EVENT_TABLE();
};

#endif
