
#ifndef _INSTALLER_FRAME_
#define _INSTALLER_FRAME_


#include <wx/wx.h>
#include <wx/tooltip.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <wx/filepicker.h>
#include "Page.hh"

enum Id
{
  idle = wxID_ANY,
  ID_NEXT,
  ID_PREV,
};


class InstallerFrame : public wxFrame
{
public:

    InstallerFrame(wxString str);

	wxPanel* GetPanel();

	void SetPage(Page *page);

	void onNext(wxCommandEvent &e);

	void onPrev(wxCommandEvent &e);

	wxButton* GetNextButton();

	wxButton* GetLastButton();



protected:
wxButton   *next;
wxButton   *prev;
wxPanel	   *panel;
wxBoxSizer *pnlSzr;
Page	   *curr;


DECLARE_EVENT_TABLE()
};
#endif

