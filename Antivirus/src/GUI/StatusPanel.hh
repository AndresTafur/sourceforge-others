#include <wx/wx.h>


#ifndef _STATUSPANEL_HH_
#define _STATUSPANEL_HH_

#include <Clamav.hh>

class StatusPanel : public wxPanel
{
public:

	StatusPanel(wxWindow *parent, WhiteHawkClamav::Clamav *mgr);

};
#endif

