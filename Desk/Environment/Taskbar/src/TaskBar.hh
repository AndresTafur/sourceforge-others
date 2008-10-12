
#ifndef _TASK_BAR_
#define _TASK_BAR_

#include <wx/statline.h>
#include "DockPanel.hh"
#include "WhiteHawkMenuFrame.hh"
#include "WindowList.hh"
#include "TrayPanel.hh"
#include "Clock.hh"

enum
{
  DESKBTN  = 10,
  MENUID,
};


class TaskBar : public DockPanel
{
public:

     TaskBar(wxString str);


	 void ShowMenu( wxCommandEvent &evt);

	 WindowList* getWndListPanel();



protected:
wxString path;
wxButton *m_deskbtn;
wxCircleToggleButton *btn;
wxMenu *m_menu;

WhiteHawkMenuFrame  *frame;
WindowList *list;
TrayPanel  *tray;
int m_coordy;

Clock *date;
DECLARE_EVENT_TABLE();

};

#endif
