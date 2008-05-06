
#ifndef _WELCOME_PAGE_
#define _WELCOME_PAGE_

#include <wx/wx.h>
#include "Page.hh"

class WelcomePage : public Page
{
public:

	  WelcomePage(wxWindow *parent, wxString name);

	  void OnPresent();

};
#endif
