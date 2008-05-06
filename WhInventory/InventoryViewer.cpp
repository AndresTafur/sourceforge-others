#include "InventoryViewer.hh"


       InventoryViewer::InventoryViewer(wxWindow *parent) : wxFrame(NULL,wxID_ANY, wxT("Visor de Inventario"), wxDefaultPosition, wxSize(800,430), wxDEFAULT_FRAME_STYLE)
       {
          wxBoxSizer   *horizontal = new wxBoxSizer(wxHORIZONTAL);
          wxBoxSizer   *vertical   = new wxBoxSizer(wxVERTICAL);

          wxButton     *find  = new wxButton(this,INV_FIND,wxT("&Buscar"));

          wxStaticLine *line  = new wxStaticLine(this,wxID_ANY);
          wxArrayString array;


                m_ctrl = new wxBoxSizer(wxVERTICAL);
                m_text = new wxTextCtrl(this,wxID_ANY,wxT(""));

                array.Add(wxT("Ver Todo"));
                array.Add(wxT("Por Item"));
                array.Add(wxT("Por Ubicacion"));
                array.Add(wxT("Por Barras"));
                array.Add(wxT("Por Familia"));
                array.Add(wxT("Por Descripcion"));
                array.Add(wxT("Por Cantidad"));
                array.Add(wxT("Por Valor"));


                m_add   = new wxButton(this,INV_ADD,wxT("&Agregar"));
                m_del   = new wxButton(this,INV_DEL,wxT("&Eliminar"));
                m_menu  = new wxComboBox(this,wxID_ANY,wxT("Ver Todo"), wxDefaultPosition, wxDefaultSize, array);
                m_modif = new wxCheckBox( this, INV_MOD, wxT("&Modificar"));
                m_grid  = new InventoryGrid(this,INV_GRID);


                m_add->Disable();
                m_del->Disable();
                m_grid->SetEditable(false);


                m_ctrl->AddSpacer(30);
                m_ctrl->Add(m_add,1,wxALIGN_CENTER_HORIZONTAL|wxEXPAND);
                m_ctrl->AddSpacer(20);
                m_ctrl->Add(m_del,1,wxALIGN_CENTER_HORIZONTAL|wxEXPAND);
                m_ctrl->AddSpacer(20);
                m_ctrl->Add(m_modif,1,wxALIGN_CENTER_HORIZONTAL|wxEXPAND);

                m_ctrl->Add(line,1,wxEXPAND,2);
                m_ctrl->Add(m_menu,1,wxALIGN_CENTER_HORIZONTAL|wxSHAPED);
                m_ctrl->Add(m_text,0,wxALIGN_CENTER_HORIZONTAL|wxEXPAND);
                m_ctrl->Add(find,1,wxALIGN_CENTER_HORIZONTAL|wxTOP,2);


                vertical->Add(m_grid,1,wxEXPAND|wxALL,5);

                horizontal->Add(vertical,1,wxEXPAND|wxALL,5);
                horizontal->Add(m_ctrl,0,wxSHAPED,0);


                this->SetSizer(horizontal);
                this->Center();
       }

        void InventoryViewer::onCheck( wxCommandEvent &evt)
        {
            bool val = m_modif->IsChecked();

            m_grid->SetEditable(val);
            m_del->Enable(val);
            m_add->Enable(val);


            if(val)
            {
                m_grid->EnableCellEditControl();

            }
        }



        void InventoryViewer::onSearch( wxCommandEvent &evt)
        {

            if( m_menu->GetValue().Cmp( wxT("Ver Todo")) != 0)
            {

                if( m_text->GetValue().IsEmpty() )
                {
                        wxMessageBox( wxT("Por favor ingrese un criterio en el campo de texto"),wxT("Error"),wxICON_ERROR);
                        return;
                }

              return;
            }

        }


        void InventoryViewer::ShowDefault()
        {
           wxButton  *repo  = new wxButton(this,INV_REP,wxT("&Reporte"));

                m_ctrl->Insert(5,repo,1,wxALIGN_CENTER_HORIZONTAL|wxEXPAND);
                m_ctrl->InsertSpacer(6,20);
                this->Layout();
                this->Show(true);
        }


    BEGIN_EVENT_TABLE(InventoryViewer,wxFrame)
    EVT_CHECKBOX(INV_MOD, InventoryViewer::onCheck)
    EVT_BUTTON(INV_FIND,  InventoryViewer::onSearch)
    END_EVENT_TABLE()
