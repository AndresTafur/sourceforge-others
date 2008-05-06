#include "SubPane.cpp"
#include "TreeCtrl.cpp"


/**  Clase que genera la ventana principal de la aplicacion, a demas
*    Utiliza una ventana dividida un Arbol y un panel para desplegar la informacion.
*    @see  SubPane
*    @see  TreeCtrl
*/

class ControlCenterFrame : public wxFrame
{
public:

/**   Metodo que inicializa los parametros basicos de la ventana principal y
*     sus subcomponentes.
*    @param title Titulo de la aplicacion.
*    @param pos   Posicion de la ventana principal.
*    @param size  Tamaño de la ventana principal.
*/


    ControlCenterFrame(const wxString& title, const wxPoint& pos, const wxSize& size, wxString& path): wxFrame(NULL,-1,title,pos,size)
    {

        wxSplitterWindow *window = new wxSplitterWindow(this, wxID_ANY,wxDefaultPosition, wxDefaultSize,wxSP_3D,wxT("splitterWindow"));
        SubPane          *pane   = new SubPane(window, path);
        wxMenu *menuFile         = new wxMenu;
        wxMenuBar *menuBar       = new wxMenuBar;
        list           = new TreeCtrl(window, path);


            list->setPane(pane);

            menuFile->Append( wxID_ABOUT, _T("&About...") );
            menuFile->AppendSeparator();
            menuFile->Append( wxID_EXIT, _T("E&xit") );

            menuBar->Append( menuFile, _T("&File") );

            window->SetSplitMode(wxSPLIT_VERTICAL);
            window->SplitVertically(list,pane);

            list->Show(true);
            pane->Show(true);
            window->Show(true);

            this->SetMenuBar( menuBar );
            this->Show(true);

    }

/**   Metodo llamado al presionar el item "salir" del menu archivo
*    @param event  Evento del item del menu.
*/

    void OnQuit(wxCommandEvent& event)
    {
      list->Destroy();
      Close(true);
    }

/**   Metodo llamado al presionar el item "Acerca de" del menu archivo
*    @param event  Evento del item del menu.
*/

    void OnAbout(wxCommandEvent& event)
    {
    wxMessageBox(_T("This is the control center of whiteHawk"),_T("About ControlCenter"), wxOK | wxICON_INFORMATION, this);
    }

protected:
TreeCtrl *list;
DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(ControlCenterFrame,wxFrame)
EVT_MENU(wxID_ABOUT,  ControlCenterFrame::OnAbout )
EVT_MENU(wxID_EXIT ,  ControlCenterFrame::OnQuit )
END_EVENT_TABLE()
