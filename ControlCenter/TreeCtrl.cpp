#include <wx/imaglist.h>


/** Clasee que maneja el arbol de la ventana
*   deriva de wxTreeCtrl, implementa un objeto SubPane para manejar los eventos
*   recibidos del Arbol
*   @see SubPane
*/

class TreeCtrl : public wxTreeCtrl
{
public:



    /** Constructor por defecto, inicializa su super constructor
     *   @param parent Padre del objeto
     */
    TreeCtrl(wxWindow *parent, wxString& path): wxTreeCtrl(parent, treeId, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_SINGLE|wxTR_FULL_ROW_HIGHLIGHT,wxDefaultValidator,wxT("treeCtrl"))
    {
        wxTreeItemData data;
        wxImageList    *imgList = new wxImageList(128, 128,true, 1);
        wxStaticBitmap* bitmap_1;
        wxBitmap bmp( path + wxT("/Data/pix/pc.png"),wxBITMAP_TYPE_ANY);

        wxBitmap bmp2( path + wxT("/Data/pix/devices.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp3( path + wxT("/Data/pix/net.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp4( path + wxT("/Data/pix/so.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp5( path + wxT("/Data/pix/desk.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp6( path + wxT("/Data/pix/grp&usr.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp7( path + wxT("/Data/pix/soft.png"),wxBITMAP_TYPE_ANY);

        wxBitmap bmp8( path + wxT("/Data/pix/usb.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp9( path + wxT("/Data/pix/hard.png"),wxBITMAP_TYPE_ANY);

        wxBitmap bmp10( path + wxT("/Data/pix/share.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp11( path + wxT("/Data/pix/netCfg.png"),wxBITMAP_TYPE_ANY);

        wxBitmap bmp12( path + wxT("/Data/pix/daemon.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp13( path + wxT("/Data/pix/kernel.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp14( path + wxT("/Data/pix/boot.png"),wxBITMAP_TYPE_ANY);

        wxBitmap bmp15( path + wxT("/Data/pix/scrsvr.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp16( path + wxT("/Data/pix/theme.png"),wxBITMAP_TYPE_ANY);

        wxBitmap bmp17( path + wxT("/Data/pix/account.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp18( path + wxT("/Data/pix/group.png"),wxBITMAP_TYPE_ANY);

        wxBitmap bmp19( path + wxT("/Data/pix/softPack.png"),wxBITMAP_TYPE_ANY);
        wxBitmap bmp20( path + wxT("/Data/pix/sofCfg.png"),wxBITMAP_TYPE_ANY);


            imgList->Add(bmp,wxNullBitmap);
            imgList->Add(bmp2,wxNullBitmap);
            imgList->Add(bmp3,wxNullBitmap);
            imgList->Add(bmp4,wxNullBitmap);
            imgList->Add(bmp5,wxNullBitmap);
            imgList->Add(bmp6,wxNullBitmap);
            imgList->Add(bmp7,wxNullBitmap);
            imgList->Add(bmp8,wxNullBitmap);
            imgList->Add(bmp9,wxNullBitmap);
            imgList->Add(bmp10,wxNullBitmap);
            imgList->Add(bmp11,wxNullBitmap);
            imgList->Add(bmp12,wxNullBitmap);
            imgList->Add(bmp13,wxNullBitmap);
            imgList->Add(bmp14,wxNullBitmap);
            imgList->Add(bmp15,wxNullBitmap);
            imgList->Add(bmp16,wxNullBitmap);
            imgList->Add(bmp17,wxNullBitmap);
            imgList->Add(bmp18,wxNullBitmap);
            imgList->Add(bmp19,wxNullBitmap);
            imgList->Add(bmp20,wxNullBitmap);

            this->AssignImageList(imgList);

            ID_ROOT = this->AddRoot(wxT("Equipo"), 0, 0, &data);


            ID_DEV        = this->AppendItem(ID_ROOT,wxT("Dispositivos"), 1, 1, &data);
            ID_NET        = this->AppendItem(ID_ROOT,wxT("Configuracion de Red"), 2, 2, &data);
            ID_SO         = this->AppendItem(ID_ROOT,wxT("Sistema Operativo"), 3, 3, &data);
            ID_DESK       = this->AppendItem(ID_ROOT,wxT("Escritorio"), 4, 4, &data);
            ID_GRPUSR     = this->AppendItem(ID_ROOT,wxT("Grupos y Usuarios"), 5, 5, &data);
            ID_SOFTWARE   = this->AppendItem(ID_ROOT,wxT("Paquetes de Software"), 6, 6, &data);

            ID_USB        = this->AppendItem(ID_DEV ,wxT("Dispositivos USB"), 7, 7, &data);
            ID_DRIVES     = this->AppendItem(ID_DEV ,wxT("Discos Duros"), 8, 8, &data);

            ID_SHARE_DEV  = this->AppendItem(ID_NET ,wxT("Recursos compartidos"), 9, 9, &data);
            ID_NET_CFG    = this->AppendItem(ID_NET ,wxT("Conexiones"), 10, 10, &data);

            ID_DAEMON     = this->AppendItem(ID_SO ,wxT("Demonios"), 11, 11, &data);
            ID_KERNEL     = this->AppendItem(ID_SO ,wxT("Kernel"), 12, 12, &data);
            ID_BOOT       = this->AppendItem(ID_SO ,wxT("Arranque"), 13, 13, &data);


            ID_SCRSVR     = this->AppendItem(ID_DESK ,wxT("Pantalla"), 14, 14, &data);
            ID_THEME      = this->AppendItem(ID_DESK ,wxT("Tema"), 15, 15, &data);

            ID_ACCOUNT    = this->AppendItem(ID_GRPUSR ,wxT("Cuentas"), 16, 16, &data);
            ID_GROUPS     = this->AppendItem(ID_GRPUSR ,wxT("Grupos"), 17, 17, &data);

            ID_SOFTPACK   = this->AppendItem(ID_SOFTWARE ,wxT("Paquetes"), 18, 18, &data);
            ID_SOFTCFG    = this->AppendItem(ID_SOFTWARE ,wxT("Configuracion"), 19, 19, &data);

            this->SetItemBold(ID_ROOT, true);
            this->Expand(ID_ROOT);


    }


   /**   Asigna el puntero al objeto SubPane
     *   @param pane Puntero que recibe el evento
     */

    void setPane(SubPane *pane)
    {
            this->pane = pane;
    }


   /**   Metodo que maneja el cambio de item del arbol,
     *   envia el id del item seleccionado al SubPane
     *   @param evt Evento realizado por el arbol
     */


    void onItemChanged(wxTreeEvent &evt)
    {
        wxTreeItemId item = evt.GetItem();
        pane->OnChange(item);

    }




private:
SubPane   *pane;

DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(TreeCtrl,wxTreeCtrl)
EVT_TREE_SEL_CHANGED(ID_ROOT, TreeCtrl::onItemChanged)
EVT_TREE_SEL_CHANGED(ID_DEV,  TreeCtrl::onItemChanged)
EVT_TREE_SEL_CHANGED(ID_NET,  TreeCtrl::onItemChanged)
EVT_TREE_SEL_CHANGED(ID_SO,   TreeCtrl::onItemChanged)
EVT_TREE_SEL_CHANGED(ID_DESK, TreeCtrl::onItemChanged)
END_EVENT_TABLE()
