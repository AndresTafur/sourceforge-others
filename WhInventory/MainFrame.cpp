
#include "MainFrame.hh"
#include "InventoryViewer.hh"
#include "LoginDialog.hh"


        MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, wxT("WhiteHawkInventory"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxVSCROLL | wxHSCROLL, wxT("frame"))
        {
            wxMenuBar  *bar  = new wxMenuBar;
            wxMenu     *progConf = new wxMenu;

            wxMenu *file   = new wxMenu;
            wxMenu *tools  = new wxMenu;
            wxMenu *help   = new wxMenu;


                file->Append(ID_FILE_PRINT_FC,wxT("Imprimir &Codigo de barras"), wxT("Imprime un codigo de barras"), wxITEM_NORMAL);
                file->AppendSeparator();
                file->Append(ID_FILE_QUIT, wxT("&Salir"),wxT("Sale de la aplicacion actual"), wxITEM_NORMAL);

                tools->Append(ID_TOOL_INVENTORY, wxT("&Inventario"),wxT("Abre el inventario"),wxITEM_NORMAL);
                tools->Append(ID_TOOL_FACTURING, wxT("&Facturar"),wxT("Genera una factura"), wxITEM_NORMAL);
                tools->AppendSeparator();
                tools->Append(wxID_ANY,wxT("&Configuraciones"), progConf, wxT("Añade Items, familias, codigos"));


                progConf->Append(ID_TOOL_CFG_FACT, wxT("Configuración de &factura"),   wxT("Modifica el modelo de factura"), wxITEM_NORMAL);
                progConf->Append(ID_TOOL_CFG_PROG, wxT("Configuración de p&rograma"),  wxT("Configura el programa"),    wxITEM_NORMAL);
                progConf->Append(ID_TOOL_CFG_INV,  wxT("Configuración de &inventario"),wxT("Modifica los items"),  wxITEM_NORMAL);


                bar->Append(file , wxT("&Archivo"));
                bar->Append(tools, wxT("&Herramientas"));
                bar->Append(help, wxT("Ay&uda"));


                this->SetMenuBar(bar);
                this->CreateStatusBar();
                this->Maximize(true);
                this->Layout();
        }

     void MainFrame::runMainDlg()
     {
        wxCommandEvent evt;

        LoginDialog log(this);
        MainDialog dlg(this);


          if( log.ShowModal() == 0)
          {

                switch( dlg.ShowModal() )
                {
                    case 0:
                        this->facturer( evt );
                      break;

                    case 1:
                        this->inventory( evt );
                      break;

                    case 2:
                        this->buys( evt );
                      break;
                }
          }
          else
            wxMessageBox(wxT("Nombre o contrasena incorrectos"),wxT("Error"),wxICON_ERROR);

       }

       void MainFrame::facturer(wxCommandEvent &evt)
       {
         Facturer  *fact = new Facturer(this);

            fact->Show();
            //fact->Destroy();
       }

       void MainFrame::inventory(wxCommandEvent &evt)
       {
                InventoryViewer *inventory = new InventoryViewer(this);

                inventory->ShowDefault();
       }

       void MainFrame::buys(wxCommandEvent &evt)
       {

       }

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
    EVT_MENU(ID_TOOL_FACTURING,MainFrame::facturer)
    EVT_MENU(ID_TOOL_INVENTORY,MainFrame::inventory)
END_EVENT_TABLE()
