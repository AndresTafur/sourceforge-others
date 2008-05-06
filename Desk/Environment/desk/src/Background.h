#include <wx/wx.h>

#ifndef _BACKGROUND_
#define _BACKGROUND_

class Background : public wxStaticBitmap
{
public:


  Background(wxWindow *parent,wxBitmap &bmp);


  void onRightClick(wxMouseEvent &evt);

  void changeImage(wxCommandEvent &evt);


protected:
wxMenu *menu;
wxBitmap *bmp;
DECLARE_EVENT_TABLE()
};
#endif
