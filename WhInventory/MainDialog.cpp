#include "MainDialog.hh"


        MainDialog::MainDialog (wxFrame *parent) : wxDialog(parent,wxID_ANY,wxT("Modulos"),wxDefaultPosition, wxDefaultSize,wxDEFAULT_DIALOG_STYLE| wxTAB_TRAVERSAL, wxT("MainDialog") )
        {
            wxBoxSizer *sizer;
            wxBoxSizer *sizer2;
            wxButton   *accept;
            wxButton   *cancel;


            str.Add(wxT("Facturar"),1);
            str.Add(wxT("Inventario"),1);
            str.Add(wxT("Compras"),1);


            accept = new wxButton(this, ID_BTN_ACCEPT, wxT("I&ngresar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("button"));
            cancel = new wxButton(this, ID_BTN_CANCEL, wxT("C&ancelar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("button"));
            caja   = new wxListBox(this, ID_LIST, wxDefaultPosition, wxDefaultSize, str, wxLB_SINGLE, wxDefaultValidator, wxT("listBox"));
            sizer  = new wxBoxSizer(wxVERTICAL);
            sizer2 = new wxBoxSizer(wxHORIZONTAL);

            caja->SetSelection(0);
            accept->SetDefault();

            sizer2->Add(accept);
            sizer2->Add(cancel);


            sizer->Add(caja,2,wxEXPAND,0);
            sizer->AddSpacer(20);
            sizer->Add(sizer2,0,wxALIGN_CENTER_HORIZONTAL,0);
            sizer->AddSpacer(20);

            this->SetSizer(sizer);
            this->CentreOnScreen(wxBOTH);
            this->RequestUserAttention(wxUSER_ATTENTION_INFO);


        }

        void MainDialog::onAccept( wxCommandEvent &evt)
        {
            wxArrayInt sel;

                caja->GetSelections(sel);

                if( sel.GetCount() > 0 )
                    this->EndModal(sel.Item(0));
                else
                    wxMessageBox(_T("Por favor seleccione una opcion del menu."),_T("Informacion"),wxOK|wxICON_INFORMATION, this);
        }


        void MainDialog::onCancel(wxCommandEvent &evt)
        {
            this->EndModal(10);
        }

BEGIN_EVENT_TABLE(MainDialog,wxDialog)
    EVT_BUTTON(ID_BTN_ACCEPT, MainDialog::onAccept)
    EVT_BUTTON(ID_BTN_CANCEL, MainDialog::onCancel)
END_EVENT_TABLE()

