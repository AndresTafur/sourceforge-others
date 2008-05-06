#include "LoginDialog.hh"



        LoginDialog::LoginDialog (wxFrame *parent) : wxDialog(parent,wxID_ANY,wxT("Inicio de session"),wxDefaultPosition, wxSize(500,280),wxDEFAULT_DIALOG_STYLE| wxTAB_TRAVERSAL, wxT("MainDialog") )
        {
            wxBoxSizer       *sizer;
            wxStaticBoxSizer *seSizer;
            wxStaticBoxSizer *serSzer;
            wxBoxSizer       *ctrl;
            wxGridSizer      *sesCtrl;
            wxGridSizer      *servCtl;

            wxButton   *accept;
            wxButton   *cancel;



            sizer   = new wxBoxSizer(wxVERTICAL);
            seSizer = new wxStaticBoxSizer(wxVERTICAL,this,wxT("Sesion"));
            serSzer = new wxStaticBoxSizer(wxVERTICAL,this,wxT("Conexion"));
            ctrl    = new wxBoxSizer(wxHORIZONTAL);

            sesCtrl = new wxGridSizer(2,2);
            servCtl = new wxGridSizer(2,2);

            m_user = new wxTextCtrl(this,wxID_ANY,wxT("ventas"));
            m_pass = new wxTextCtrl(this,wxID_ANY,wxT("ventas123"),wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
            m_host = new wxTextCtrl(this,wxID_ANY,wxT("127.0.0.1"));
            m_port = new wxTextCtrl(this,wxID_ANY,wxT("3306"));

            accept  = new wxButton(this, wxID_OK, wxT("I&ngresar"));
            cancel  = new wxButton(this, wxID_CANCEL, wxT("C&ancelar"));

            accept->SetDefault();

            ctrl->Add(accept,1,wxEXPAND|wxALL,5);
            ctrl->Add(cancel,1,wxEXPAND|wxALL,5);

            sesCtrl->Add( new wxStaticText(this,wxID_ANY,wxT("Usuario:")));
            sesCtrl->Add(m_user,1,wxEXPAND );
            sesCtrl->Add( new wxStaticText(this,wxID_ANY,wxT("Contrasena:")));
            sesCtrl->Add(m_pass,1,wxEXPAND );

            servCtl->Add( new wxStaticText(this,wxID_ANY,wxT("Host:")));
            servCtl->Add(m_host,1,wxEXPAND );
            servCtl->Add( new wxStaticText(this,wxID_ANY,wxT("Puerto:")));
            servCtl->Add(m_port,1,wxEXPAND );

            seSizer->Add(sesCtrl,0,wxEXPAND|wxALL,10);
            serSzer->Add(servCtl,0,wxEXPAND|wxALL,10);


            sizer->Add(seSizer,0,wxEXPAND|wxALL,10);
            sizer->Add(serSzer,0,wxEXPAND|wxALL,10);
            sizer->Add(ctrl,0,wxALIGN_CENTER_HORIZONTAL,10);


            this->SetSizer(sizer);
            this->FitInside();
            this->CentreOnScreen(wxBOTH);
            this->RequestUserAttention(wxUSER_ATTENTION_INFO);
        }

        void LoginDialog::onAccept( wxCommandEvent &evt)
        {
                this->EndModal(0);
        }


        void LoginDialog::onCancel(wxCommandEvent &evt)
        {
            this->EndModal(10);
        }

BEGIN_EVENT_TABLE(LoginDialog,wxDialog)
    EVT_BUTTON(wxID_OK, LoginDialog::onAccept)
    EVT_BUTTON(wxID_CANCEL, LoginDialog::onCancel)
END_EVENT_TABLE()


