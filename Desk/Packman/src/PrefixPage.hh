
#ifndef _PREFIX_PAGE_
#define _PREFIX_PAGE_

#include <wx/wx.h>
#include "Page.hh"
#include "Package.hh"

class PrefixPage : public Page
{
public:

	  PrefixPage(wxWindow *parent, Package *package);

	  void OnPresent();

};
#endif
