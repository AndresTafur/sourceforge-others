
#ifndef _COPY_PAGE_
#define _COPY_PAGE_

#include <wx/wx.h>
#include "Page.hh"
#include "Package.hh"

class CopyPage : public Page
{
public:

	  CopyPage(wxWindow *parent, Package *package);

	  void OnPresent();

};
#endif
