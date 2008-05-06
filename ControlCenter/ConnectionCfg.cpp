enum
{
    NETCFG_RADIOGRP = 1,
    NETCFG_COMBO,
};

/** Clase que muestra los widgets de configuracion de la red
*   Invocada desde SubPane.
*/

class ConnectionCfg : public wxPanel
{
public:

/** Constructor por defecto
*   @param parent Padre de este objeto.
*/

  ConnectionCfg(wxWindow *parent) : wxPanel(parent,wxID_ANY,wxDefaultPosition, wxDefaultSize,wxSP_3D,wxT("Config"))
  {
     wxBoxSizer   *sizer;
     wxGridSizer  *devGrid;
     wxGridSizer  *cfgGrid;

     wxStaticBoxSizer  *box;
     wxStaticBoxSizer  *boxCfg;

     wxStaticText *label;
     wxComboBox   *combo;
     wxStaticText *labelCfg;


     wxStaticText *labelIP;
     wxStaticText *labelMsk;
     wxStaticText *labelGtw;


     wxArrayString arreglo;
     wxArrayString dev;

     wxTextValidator validator(wxFILTER_NUMERIC, new wxString(wxT("0123456789.")));

      validator.SetBellOnError(true);

      cfgEnable = true;

       sizer     = new wxBoxSizer(wxVERTICAL);
       devGrid   = new wxGridSizer(2,2,5,5);
       cfgGrid   = new wxGridSizer(3,2,5,5);

       label     = new wxStaticText(this,wxID_ANY,wxT("Dispositivo:"),wxDefaultPosition,wxDefaultSize,0,wxT("label"));
       labelCfg  = new wxStaticText(this,wxID_ANY,wxT("Configuracion:"),wxDefaultPosition,wxDefaultSize,0,wxT("label2"));

       labelIP   = new wxStaticText(this,wxID_ANY,wxT("Direccion IP:"),wxDefaultPosition,wxDefaultSize,0,wxT("label"));
       labelMsk  = new wxStaticText(this,wxID_ANY,wxT("Mascara de red:"),wxDefaultPosition,wxDefaultSize,0,wxT("label2"));
       labelGtw  = new wxStaticText(this,wxID_ANY,wxT("Puerta de enlace:"),wxDefaultPosition,wxDefaultSize,0,wxT("label"));

       entryIP   = new wxTextCtrl(this,wxID_ANY,wxT(""),wxDefaultPosition,wxDefaultSize,0,validator,wxT("label"));
       entryMsk  = new wxTextCtrl(this,wxID_ANY,wxT(""),wxDefaultPosition,wxDefaultSize,0,validator,wxT("label2"));
       entryGtw  = new wxTextCtrl(this,wxID_ANY,wxT(""),wxDefaultPosition,wxDefaultSize,0,validator,wxT("label"));



       box       = new wxStaticBoxSizer(wxVERTICAL,this, wxT("Dispositivos"));
       boxCfg    = new wxStaticBoxSizer(wxVERTICAL,this, wxT("Configuracion manual"));

       dev.Add(wxT("/dev/eth0"),1);
       dev.Add(wxT("/dev/eth1"),1);
       arreglo.Add(wxT("Manual"),1);
       arreglo.Add(wxT("Automatica"),1);

       combo    = new wxComboBox(this, NETCFG_COMBO, wxT("/dev/eth0"),wxDefaultPosition,wxDefaultSize,dev,wxCB_READONLY, wxDefaultValidator, wxT("comboBox"));
       comboCfg = new wxComboBox(this, NETCFG_COMBO, wxT("Manual"),wxDefaultPosition,wxDefaultSize,arreglo,wxCB_READONLY, wxDefaultValidator, wxT("comboBox"));

       devGrid->Add(label, 0, wxEXPAND,0);
       devGrid->Add(combo, 0, wxEXPAND,0);
       devGrid->Add(labelCfg, 0, wxEXPAND,0);
       devGrid->Add(comboCfg, 0, wxEXPAND,0);


       cfgGrid->Add(labelIP,0, wxEXPAND,0);
       cfgGrid->Add(entryIP,0, wxEXPAND,0);
       cfgGrid->Add(labelMsk,0, wxEXPAND,0);
       cfgGrid->Add(entryMsk,0, wxEXPAND,0);
       cfgGrid->Add(labelGtw,0, wxEXPAND,0);
       cfgGrid->Add(entryGtw,0, wxEXPAND,0);

       box->AddSpacer(20);
       box->Add(devGrid,0,wxEXPAND,0);
       box->AddSpacer(20);


       boxCfg->AddSpacer(20);
       boxCfg->Add(cfgGrid,0,wxEXPAND,0);
       boxCfg->AddSpacer(20);

       sizer->AddSpacer(20);
       sizer->Add(box,0, wxEXPAND,10);
       sizer->AddSpacer(20);
       sizer->Add(boxCfg, 0, wxEXPAND, 0);
       sizer->AddSpacer(20);

       this->SetAutoLayout(true);
       this->SetSizer(sizer);

       sizer->Fit(this);
       sizer->SetSizeHints(this);


       this->Layout();

  }


  void onCfgChage(wxCommandEvent &evt)
  {
      wxString val;

       val = comboCfg->GetValue();

       if(val.Cmp(wxT("Automatica")) == 0 && cfgEnable == true)
       {
            entryIP->Disable();
            entryMsk->Disable();
            entryGtw->Disable();
            cfgEnable = false;
       }
       else if(val.Cmp(wxT("Manual")) == 0 && cfgEnable == false)
       {
            entryIP->Enable();
            entryMsk->Enable();
            entryGtw->Enable();
            cfgEnable = true;
       }
  }

protected:

wxComboBox *comboCfg;
wxTextCtrl *entryIP;
wxTextCtrl *entryMsk;
wxTextCtrl *entryGtw;
bool cfgEnable;

DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(ConnectionCfg,wxPanel)
EVT_COMBOBOX(NETCFG_COMBO, ConnectionCfg::onCfgChage)
END_EVENT_TABLE()
