#include "Facturer.hh"


    Facturer::Facturer(wxWindow *parent) : wxFrame(parent, wxID_ANY, wxT("Factura - No 0001"), wxDefaultPosition, wxSize(700,500),wxCLOSE_BOX|wxTAB_TRAVERSAL|wxRESIZE_BORDER|wxRESIZE_BOX|wxMAXIMIZE_BOX /*|wxFRAME_NO_TASKBAR*/)
    {
        wxBoxSizer   *horizontal = new wxBoxSizer(wxHORIZONTAL);
        wxBoxSizer   *facData    = new wxBoxSizer(wxHORIZONTAL);
        wxBoxSizer   *vertical   = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer   *control    = new wxBoxSizer(wxVERTICAL);


        m_factnum  = new wxTextCtrl(this,FACT_NUM,wxT("0001"));

        wxTextCtrl   *date       = new wxTextCtrl(this,FACT_DATE,wxT("2008/02/19"));
        wxStaticText *factLbl    = new wxStaticText(this,wxID_ANY,wxT("Factura No: "));
        wxStaticText *dateLbl    = new wxStaticText(this,wxID_ANY,wxT("Fecha: "));

        wxButton     *ins        = new wxButton(this,FACT_INS,wxT("&Agregar"));
        wxButton     *del        = new wxButton(this,FACT_DEL,wxT("&Eliminar"));
        wxButton     *inv        = new wxButton(this,FACT_INV,wxT("&Inventario"));

        wxButton     *format     = new wxButton(this,FACT_FORMAT,wxT("&Formato"));
         wxButton    *view       = new wxButton(this,FACT_VIEW,wxT("&Vista previa"));
        wxButton     *print      = new wxButton(this,FACT_PRINT,wxT("Im&primir"));
        wxStaticLine *line       = new wxStaticLine(this,wxID_ANY);




        wxCheckBox   *credit    = new wxCheckBox( this, FACT_CREDIT, wxT("&Credito"),wxDefaultPosition, wxDefaultSize,0, wxDefaultValidator,wxT("credit"));

            m_tot  = new wxStaticText(this,FACT_TOT,wxT("Total: 0"));
            m_grid = new FactureGrid(this,FACT_GRID);

            control->AddSpacer(30);
            control->Add(ins);
            control->AddSpacer(20);
            control->Add(del);
            control->AddSpacer(20);
            control->Add(inv);
            control->AddSpacer(20);
            control->Add(line,1,wxEXPAND,2);

            control->AddSpacer(20);
            control->Add(format);
            control->AddSpacer(20);
            control->Add(view);
            control->AddSpacer(20);
            control->Add(print);
            control->AddSpacer(20);
            control->Add(credit,1,wxALIGN_CENTER_HORIZONTAL);
            control->AddSpacer(20);
            control->Add(m_tot,1,wxALIGN_CENTER_HORIZONTAL);

            facData->Add(factLbl,1,wxTOP|wxSHAPED,5);
            facData->Add(m_factnum,1,wxSHAPED|wxALL,4);
            facData->AddSpacer(40);
            facData->Add(dateLbl,0,wxTOP,6);
            facData->Add(date,1,wxSHAPED|wxALL,5);


            vertical->Add(facData);
            vertical->Add(m_grid,1,wxEXPAND|wxALL,5);


            horizontal->Add(vertical,1,wxEXPAND|wxALL,5);
            horizontal->Add(control,0,wxSHAPED,0);


            this->SetSizer(horizontal);
            this->Layout();
            this->Center();
    }



    void Facturer::onDelete(wxCommandEvent &evt)
    {
       m_grid->DeleteRows( m_grid->GetGridCursorRow() );
    }

    void Facturer::onInsert(wxCommandEvent &evt)
    {
        int row = m_grid->GetGridCursorRow()+1;

            m_grid->InsertRows(row);
            m_grid->SetGridCursor( row,0);
            m_grid->SetReadOnly(row,4);
            m_grid->EnableCellEditControl();
    }

    void Facturer::onView(wxCommandEvent &evt)
    {
            this->SetTitle( wxT("Factura - No ") + m_factnum->GetValue() );
    }


    void Facturer::onSubTotal(wxGridEvent &evt)
    {
         wxString str;
         int col  = evt.GetCol();
         int rows = m_grid->GetNumberRows();
         long tot = 0;
         long val;

            if( col == 2 || col == 3)
            {
              long val1, val2;
              int row = evt.GetRow();

                    m_grid->GetCellValue(row,2).ToLong(&val1,10);
                    m_grid->GetCellValue(row,3).ToLong(&val2,10);

                    str <<  val1 * val2;
                    m_grid->SetCellValue( str, row, 4 );

                    for(int i=0; i < rows; i++)
                    {
                        m_grid->GetCellValue(i,4).ToLong(&val,10);
                        tot += val;
                    }

                    str = wxT("");
                    str << wxT("Total: ") << tot;

                    m_tot->SetLabel(str);
            }
            else if( col == 0 )
            {
                    //TODO: DB Search
            }
    }


    void Facturer::onSearch(wxCommandEvent &evt)
    {
            ( new InventoryFinderDlg(this))->Show();
    }



    void Facturer::onNumberChange(wxCommandEvent &evt)
    {
            this->SetTitle( wxT("Factura - No ") + m_factnum->GetValue() );
    }

    BEGIN_EVENT_TABLE(Facturer,wxFrame)
    EVT_BUTTON(FACT_INS,Facturer::onInsert)
    EVT_BUTTON(FACT_DEL,Facturer::onDelete)
    EVT_BUTTON(FACT_VIEW,Facturer::onView)
    EVT_BUTTON(FACT_INV,Facturer::onSearch)
    EVT_GRID_CELL_CHANGE(Facturer::onSubTotal)
    //EVT_FACT_NUM,Facturer::onNumberChange)
    END_EVENT_TABLE();
