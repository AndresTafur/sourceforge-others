#include <wx/wx.h>

#ifndef _ICON_
#define _ICON_

class Icon : public wxStaticBitmap
{
public:


  Icon(wxWindow *parent,wxBitmap &bmp, wxString name = wxT("Nuevo icono"), int x=50, int y=50);

  void onRightClick(wxMouseEvent &evt);


protected:
wxMenu *menu;
wxImage bmp;
wxStaticText   *label;
int x,y, px, py;
DECLARE_EVENT_TABLE()
};
#endif
