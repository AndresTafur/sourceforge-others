wxTreeItemId treeId;
wxTreeItemId ID_ROOT;
wxTreeItemId ID_DEV;
wxTreeItemId ID_NET;
wxTreeItemId ID_SO;
wxTreeItemId ID_DESK;
wxTreeItemId ID_GRPUSR;
wxTreeItemId ID_SOFTWARE;

wxTreeItemId ID_USB;
wxTreeItemId ID_DRIVES;
wxTreeItemId ID_SHARE_DEV;
wxTreeItemId ID_NET_CFG;
wxTreeItemId ID_DAEMON;
wxTreeItemId ID_KERNEL;
wxTreeItemId ID_BOOT;
wxTreeItemId ID_SCRSVR;
wxTreeItemId ID_THEME;
wxTreeItemId ID_ACCOUNT;
wxTreeItemId ID_GROUPS;
wxTreeItemId ID_SOFTPACK;
wxTreeItemId ID_SOFTCFG;


#include "Welcome.cpp"
#include "ConnectionCfg.cpp"

enum
{
  CUADERNO = 1,
  INDEX,
};


/** Clase que representa el panel de la derecha en la ventana principal
*   Esta "Monta" y "Desmonta" los paneles de cada item del arbol de la izquierda
*   basado en el id del item.
*   @see Welcome
*   @see ConnectionCfg
*/

class SubPane : public wxPanel
{
public:


/** Constructor por defecto
*   @param parent Padre de este subpanel
*/

    SubPane(wxWindow *parent, wxString &path) : wxPanel(parent,wxID_ANY,wxDefaultPosition, wxDefaultSize,wxSP_3DSASH,wxT("splitterWindow"))
    {
      sizer = new wxBoxSizer(wxVERTICAL);

      cuaderno = new wxNotebook(this, CUADERNO, wxDefaultPosition,wxDefaultSize, wxNB_TOP);
      welcome = new Welcome(cuaderno, path);

      //wxPanel *window2 = new wxPanel(cuaderno, wxID_ANY);

        cuaderno->AddPage(welcome , wxT("Bienvenido"));

        sizer->Add(cuaderno, 1, wxEXPAND, 0);
        SetAutoLayout(true);

        this->SetSizer(sizer);



         sizer->Fit(this);
         sizer->SetSizeHints(this);

        Layout();
    }



/** Metodo que desmonta el panel anterior y monta el actual
*   llamado desde TreeCtrl.
*   @param Item Identificador del item seleccionado en el arbol.
*/

    void OnChange(wxTreeItemId item)
    {

        cuaderno->RemovePage(0);

        if(item == ID_NET_CFG )
            cuaderno->AddPage(new ConnectionCfg(cuaderno) , wxT("Configurar Conexion"));



            /*
            wxTreeItemId ID_DRIVES;
            wxTreeItemId ID_SHARE_DEV;
            wxTreeItemId ID_USB;
            wxTreeItemId ID_DAEMON;
            wxTreeItemId ID_KERNEL;
            wxTreeItemId ID_BOOT;
            wxTreeItemId ID_SCRSVR;
            wxTreeItemId ID_THEME;
            wxTreeItemId ID_ACCOUNT;
            wxTreeItemId ID_GROUPS;
            wxTreeItemId ID_SOFTPACK;
            wxTreeItemId ID_SOFTCFG;*/

    }

protected:
    wxNotebook *cuaderno;
    wxBoxSizer *sizer;
    Welcome    *welcome;

};
