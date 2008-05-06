    



class CyberFrame : public wxFrame
{
public:
        CyberFrame() : wxFrame(NULL,wxID_ANY, wxT("wxCyberAdministrator"),wxDefaultPosition, wxDefaultSize,wxDEFAULT_FRAME_STYLE,wxT(""))
        {

            wxMenuBar *bar = new wxMenuBar(0);
            wxMenu    *file= new wxMenu;
            wxMenu    *cfg = new wxMenu;
            wxMenu    *dlg = new wxMenu;
            
            wxSplitterWindow *mainSplit = new wxSplitterWindow(this,wxID_ANY,wxDefaultPosition, wxDefaultSize,wxSP_3D,wxT(""));
            wxSplitterWindow *subSplit  = new wxSplitterWindow(mainSplit,wxID_ANY,wxDefaultPosition, wxDefaultSize,wxSP_3D,wxT(""));
            wxSplitterWindow *mess  = new wxSplitterWindow(mainSplit,wxID_ANY,wxDefaultPosition, wxDefaultSize,wxSP_3D,wxT(""));
            
            wxNotebook *book = new wxNotebook(mess,ID_NOTEBOOK,wxDefaultPosition,wxDefaultSize,0,wxT(""));
            wxTreeCtrl *brow = new wxTreeCtrl(subSplit,ID_TREE,wxDefaultPosition,wxDefaultSize,wxLC_ICON,wxDefaultValidator,wxT(""));
            wxListCtrl *list = new wxListCtrl(subSplit,ID_LIST,wxDefaultPosition,wxDefaultSize,wxLC_REPORT|wxLC_SORT_ASCENDING|wxLC_HRULES|wxLC_SINGLE_SEL,wxDefaultValidator,wxT(""));
            
            
                         msg  = new wxListCtrl(mess,ID_MESS,wxDefaultPosition,wxDefaultSize,wxLC_REPORT|wxLC_SINGLE_SEL,wxDefaultValidator,wxT(""));
            Computer    *pc00 = new Computer(book, wxT("PC00"),msg);
            Computer    *pc01 = new Computer(book, wxT("PC01"),msg);
            Computer    *pc02 = new Computer(book, wxT("PC02"),msg);
            Computer    *pc03 = new Computer(book, wxT("PC03"),msg);

            list->InsertColumn(0, wxT("Acciones"),wxLIST_FORMAT_LEFT);
            


            list->InsertItem(0, wxT("Desbloquear"));
            list->InsertItem(1, wxT("Bloquear"));
            list->InsertItem(2, wxT("reiniciar"));
            list->InsertItem(3, wxT("Apagar"));

           

            list->SetFont(wxFont(10,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false, wxT("Tahoma")));
            list->SetColumnWidth(0, wxLIST_AUTOSIZE);

            msg->InsertColumn(0, wxT("Mensajes"),wxLIST_FORMAT_LEFT);
            msg->InsertColumn(1, wxT("Hora"),wxLIST_FORMAT_LEFT);
            msg->SetFont(wxFont(8,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false, wxT("Tahoma")));
            msg->SetColumnWidth(0, 500);
            msg->SetColumnWidth(1, 300);


            book->SetFont( wxFont(8,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD));
    	    book->AddPage(pc00, wxT("PC00"));
    	    book->AddPage(pc01, wxT("PC01"));
    	    book->AddPage(pc02, wxT("PC02"));
    	    book->AddPage(pc03, wxT("PC03"));
            
        	mainSplit->SplitVertically(subSplit,mess,185);
	        subSplit->SplitHorizontally(brow,list,300);
	        mess->SplitHorizontally(book,msg,500);

            file->Append(ID_EXIT, wxT("&Salir"),wxT("Sale de esta aplicacion"),wxITEM_NORMAL);
      
            cfg->Append(0, wxT("&Configurar valores"),wxT("Sale de esta aplicacion"),wxITEM_NORMAL);
            cfg->Append(0, wxT("&Configurar base de datos"),wxT("Sale de esta aplicacion"),wxITEM_NORMAL);
            
            dlg->Append(0, wxT("Estadisticas"),wxT("Sale de esta aplicacion"),wxITEM_NORMAL);
            dlg->Append(0, wxT("Especiales"),wxT("Sale de esta aplicacion"),wxITEM_NORMAL);
            
            bar->Append(file,wxT("&Archivo"));
            bar->Append(cfg,wxT("&Configuracion"));
            bar->Append(dlg,wxT("&Dialogos"));


                
            SetMenuBar(bar);
            CreateStatusBar();

        }
  
        
        void OnClick(wxListEvent &evt)
        {
          wxMenu    *menu = new wxMenu;
          menu->Append(ID_EXIT, wxT("Aplicar a PC00"));
          menu->Append(ID_EXIT, wxT("Aplicar a PC01"));
          menu->Append(ID_EXIT, wxT("Aplicar a PC02"));
          menu->Append(ID_EXIT, wxT("Aplicar a PC03"));
          
          PopupMenu(menu);
        }
    
        void onClean(wxListEvent &evt)
        {
          wxMenu    *menu = new wxMenu;
          menu->Append(ID_CLEAN, wxT("Limpiar mensajes"));

          PopupMenu(menu);
        }
        
        void ClearMess( wxCommandEvent &evt)
        {
             msg->DeleteAllItems();   
        }
    
protected:
DECLARE_EVENT_TABLE();
wxListCtrl *msg;    
};

BEGIN_EVENT_TABLE(CyberFrame, wxFrame)
EVT_LIST_ITEM_RIGHT_CLICK(ID_LIST, CyberFrame::OnClick)
EVT_LIST_ITEM_RIGHT_CLICK(ID_MESS, CyberFrame::onClean)
EVT_MENU(ID_CLEAN,CyberFrame::ClearMess)
END_EVENT_TABLE()
