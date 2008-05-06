
#include "rcids.h"
#include "Background.h"



Background::Background(wxWindow *parent,wxBitmap &bmp) : wxStaticBitmap( parent,100,bmp)
  {
     menu = new wxMenu;

     menu->Append(ID_ORDER, wxT("Ordenar Por Nombre"),wxT(""), wxITEM_NORMAL);
     menu->Append(ID_ALIGN, wxT("Mantener alineado"),wxT("") , wxITEM_CHECK);
     menu->AppendSeparator();
     menu->Append(ID_BGIMAGE, wxT("Cambiar Fondo")   ,wxT("")  , wxITEM_NORMAL);

  }



  void Background::onRightClick(wxMouseEvent &evt)
  {
     PopupMenu(menu);

  }

 void Background::changeImage(wxCommandEvent &evt)
 {
   wxFileDialog* dialog = new wxFileDialog(this, wxT("Seleccione la imagen"), wxT("."), wxT(""), wxT("*.*"), 
		wxFD_DEFAULT_STYLE|wxFD_PREVIEW,wxDefaultPosition,wxDefaultSize, wxT(""));

	dialog->ShowModal();

	bmp = new wxBitmap( dialog->GetPath() );
	this->SetBitmap(*bmp);

 }

BEGIN_EVENT_TABLE(Background,wxStaticBitmap)
EVT_RIGHT_UP(Background::onRightClick)
EVT_MENU(ID_BGIMAGE, Background::changeImage)
END_EVENT_TABLE()
