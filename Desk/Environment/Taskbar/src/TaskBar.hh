
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

     TaskBar(wxString str, SystemUtils *sysUtils);

     wxButton* createDeskButton();

	 void ShowMenu( wxCommandEvent &evt);

	 WindowList* getWndListPanel();

 	 void showDeskSelector(wxCommandEvent &evt);

 	 void onChangeDesk(int desknum);

	 void changeDesk(wxCommandEvent &evt);


protected:
wxMenu *m_menu;
wxString path;
wxButton *m_deskbtn;
wxCircleToggleButton *btn;


WhiteHawkMenuFrame  *frame;
WindowList *list;
TrayPanel  *tray;
int m_coordy;

Clock *date;
SystemUtils  *m_sysUtils;
DECLARE_EVENT_TABLE();

};

#endif
