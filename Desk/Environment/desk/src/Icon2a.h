#include <wx/wx.h>

#ifndef _ICON_
#define _ICON_

class Icon : public wxBitmapButton
{
public:


  Icon(wxWindow *parent,wxBitmap &bmp, wxString name = wxT("Nuevo icono"));

  void onClick(wxMouseEvent &evt);
  void onRightClick(wxMouseEvent &evt);
  void onDoubleClick(wxMouseEvent &evt);
  void OnFocus(wxMouseEvent &evt);
  void OnLost(wxMouseEvent &evt);


protected:
wxMenu *menu;
bool	grabing;
wxStaticText   *label;
DECLARE_EVENT_TABLE()
};
#endif
