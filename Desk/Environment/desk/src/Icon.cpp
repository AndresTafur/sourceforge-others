
#include "rcids.h"
#include "Icon.h"



  Icon::Icon(wxWindow *parent,wxBitmap &bmp, wxString name, int x, int y) : wxStaticBitmap(parent, 100, bmp) 
  {
     menu = new wxMenu;

     menu->Append(100, wxT("Abrir"),wxT(""), wxITEM_NORMAL);
     menu->Append(100, wxT("Explorar"),wxT(""), wxITEM_NORMAL);
     menu->AppendSeparator();
     menu->Append(ID_ALIGN, wxT("Renombrar"),wxT("") , wxITEM_NORMAL);
     menu->Append(ID_ALIGN, wxT("Cortar"),wxT("") , wxITEM_NORMAL);
     menu->Append(ID_ALIGN, wxT("Copiar"),wxT("") , wxITEM_NORMAL);
     menu->Append(ID_ALIGN, wxT("Pegar"),wxT("") ,  wxITEM_NORMAL);
     menu->AppendSeparator();
     menu->Append(ID_BGIMAGE, wxT("Propiedades")   ,wxT("")  , wxITEM_NORMAL);

     this->bmp = bmp.ConvertToImage();
	
     this->x = x;
     this->y = y;
     this->SetSize(wxSize(bmp.GetWidth(),bmp.GetHeight()));
     this->SetLabel(wxT("PROBANDOOO!!!"));
	
  }


 void Icon::onRightClick(wxMouseEvent &evt)
 {
      PopupMenu(menu);
 }



BEGIN_EVENT_TABLE(Icon,wxControl)/*
EVT_LEFT_DOWN(Icon::onPressed)
EVT_LEFT_UP(Icon::onClick)
EVT_LEFT_DCLICK(Icon::onDoubleClick)*/
EVT_RIGHT_UP(Icon::onRightClick)
/*
EVT_ENTER_WINDOW(Icon::OnFocus)	
EVT_LEAVE_WINDOW(Icon::OnLost)*/
END_EVENT_TABLE()

