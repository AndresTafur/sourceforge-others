
#ifndef _FINISH_PAGE_
#define _FINISH_PAGE_

#include <wx/wx.h>
#include "Page.hh"
#include "Package.hh"

class FinishPage : public Page
{
public:

	  FinishPage(wxWindow *parent, wxString name);

	  void OnPresent();

};
#endif
