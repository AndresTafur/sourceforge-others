

class ComputerPanel : public wxPanel
{
public:
        ComputerPanel(wxWindow *parent,wxString pcName,wxListCtrl *msg) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL,wxT("")) 
        {
            
            
            wxBoxSizer   *princ  = new wxBoxSizer(wxVERTICAL);
            wxStaticBoxSizer   *adjus  = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Control de tiempo"));
            
            wxStaticText *pcLbl  = new wxStaticText(this, 0, pcName);
            wxGridSizer  *ctrl   = new wxGridSizer(3,2,2,2);

            
            
            panel  = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL,wxT(""));
            check  = new wxCheckBox(this, ID_CHECK, wxT(" Tiempo libre"));
            
            pnlSzr = new wxBoxSizer(wxHORIZONTAL);
            pnlCtr = new wxBoxSizer(wxVERTICAL);
            
            list   = new wxGrid(panel,ID_GRID);
            
            stctr  = new wxTextCtrl(this, 0, wxT("00:00:00"));
            endctr = new wxTextCtrl(this, 0, wxT("00:00:00"));
            rest   = new wxTextCtrl(this, 0, wxT("00:00:00"));            
            val    = new wxTextCtrl(this, 0, wxT(""));

            
            
            start  = new wxButton(this, ID_START, wxT("Iniciar"));
            stop   = new wxButton(this, ID_STOP, wxT("Detener"));
            
            
          
            ctrl->Add(new wxStaticText(this, 0, wxT("Hora de inicio : ")),0,wxRIGHT|wxALL);
            ctrl->Add(stctr,0,wxCENTER|wxALL);
            
            ctrl->Add(new wxStaticText(this, 0, wxT("Tiempo total : ")),0,wxRIGHT|wxALL);
            ctrl->Add(endctr,0,wxCENTER|wxALL);
            
            ctrl->Add(new wxStaticText(this, 0, wxT("Tiempo Pedido : ")),0,wxRIGHT|wxALL);
            ctrl->Add(rest,0,wxCENTER|wxALL);
            
            ctrl->Add(new wxStaticText(this, 0, wxT("Valor total : ")),0,wxRIGHT|wxALL);
            ctrl->Add(val,0,wxCENTER|wxALL);
            
           
            ctrl->Add( new wxStaticText(this, 0, wxT("")));
            ctrl->Add( new wxStaticText(this, 0, wxT("")));
            
            ctrl->Add(start,0,wxCENTER|wxALL);
            ctrl->Add(stop,0,wxCENTER|wxALL);
            
            pcLbl->SetFont( wxFont(40,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,wxT("Lucida")));
            pcLbl->SetForegroundColour(wxT("BLUE"));
            
            check->SetValue(true);
            rest->Disable();
            stctr->Disable();
            endctr->Disable();
            stop->Disable();
            val->Disable();

            MakeItemPanel();

            adjus->Add(ctrl,0,wxALL,2);

            princ->AddSpacer(5);
            princ->Add(pcLbl,0,wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALL);

            princ->AddSpacer(10);
            princ->Add(adjus,0,wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALL,20);
            princ->AddSpacer(10);
            princ->Add(check,0,wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALL);
            princ->AddSpacer(30);
            princ->Add(panel,1,wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxLEFT|wxRIGHT,5);
            
            this->pcName = pcName;
            this->msg = msg;
            this->SetSizer(princ);
        }
    

        void MakeItemPanel()
        {
            wxButton *add = new wxButton(panel,ID_ADD,wxT("&Agregar"));
            wxButton *del = new wxButton(panel,ID_DEL,wxT("&Eliminar"));
            wxButton *cln = new wxButton(panel,ID_DEL,wxT("&Limpiar"));
            
            
            panel->SetSizer(pnlSzr);

            list->CreateGrid(3,3);
            
            list->SetColLabelValue(0, wxT("Servicio"));
            list->SetColLabelValue(1, wxT("Cantidad"));
            list->SetColLabelValue(2, wxT("Subtotal"));
            list->SetLabelBackgroundColour(wxColour("LIGHT GREY"));
            list->Fit();
            list->SetDefaultColSize(215,true);

            pnlCtr->Add(add,0,wxALIGN_CENTER|wxBOTTOM|wxLEFT,5);
            pnlCtr->Add(del,0,wxALIGN_CENTER|wxBOTTOM|wxLEFT,5);
            pnlCtr->Add(cln,0,wxALIGN_CENTER|wxBOTTOM|wxLEFT,5);

            pnlSzr->Add(list,1,wxALIGN_CENTER_HORIZONTAL|wxALL);
            pnlSzr->Add(pnlCtr,0,wxALIGN_CENTER_HORIZONTAL); 
        }
    
        wxString GetPCName()
        {
            return pcName;    
        }
    
    
        void OnStart(wxCommandEvent &event)
        {
         start->SetLabel( wxT("Reiniciar"));
         stop->Enable();
         onStart();
        }

        void OnStop(wxCommandEvent &event)
        {
            check->SetValue(true);
            start->SetLabel( wxT("Iniciar"));
            rest->SetValue( wxT("00:00:00"));
            
            stop->Disable();
            rest->Disable();
            onStop();
        }
    
        void OnCheck(wxCommandEvent &evt)
        {
            if( check->GetValue())
            {
                rest->Disable();
                rest->SetValue( wxT("00:00:00"));
            }
            else
                rest->Enable();
        }
        
        
        virtual void onStart() = 0;
        virtual void onStop() = 0;
        
        
    
protected:    
wxString pcName;
wxTextCtrl *stctr;
wxTextCtrl *endctr;
wxTextCtrl *val;
wxTextCtrl *rest;
wxCheckBox *check;
wxGrid     *list;
wxButton   *start;
wxButton   *stop;
wxListCtrl *msg;
wxPanel    *panel;
wxBoxSizer *pnlSzr;
wxBoxSizer *pnlCtr;

DECLARE_EVENT_TABLE()    

};

BEGIN_EVENT_TABLE(ComputerPanel, wxPanel)
EVT_BUTTON( ID_START,ComputerPanel::OnStart)
EVT_BUTTON( ID_STOP,ComputerPanel::OnStop)
EVT_CHECKBOX(ID_CHECK, ComputerPanel::OnCheck)
END_EVENT_TABLE()
