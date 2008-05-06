


#ifndef _WHITEHAWK_MENU_
#define _WHITEHAWK_MENU_

#include "wxCircleToggleButton.hh"

enum Id
{
  idle = wxID_ANY,
  ID_RUN,
  ID_CONFIG,
  ID_CALC,
};


class WhiteHawkMenu : public wxMenuItem
{
public:


WhiteHawkMenu(WhiteHawkMenu *parent,int id,const wxString text, const wxString help,const wxBitmap bitmap);


WhiteHawkMenu(WhiteHawkMenu *parent,int id, const wxString text, const wxString help,const wxString bitmap);


WhiteHawkMenu(wxMenu *parent,int id,const wxString text, const wxString help,const wxBitmap bitmap);



WhiteHawkMenu(wxMenu *parent,int id, const wxString text, const wxString help,const wxString bitmap);

	wxMenuItem* Append(wxMenuItem* item);

	wxMenuItem* Append(int id, const wxString &item, const wxString& helpString);


	void AppendSeparator();

	void Break();

	wxMenu* GetMenu();

protected:
wxMenu *menu;
};



class WhiteHawkMenuFrame : public  wxFrame
{
public:

  WhiteHawkMenuFrame(wxString &str, wxCircleToggleButton *btn);

	void OnShowMenu(wxMenuEvent &evt);

	void OnCloseMenu(wxMenuEvent &evt);

	void runMenu(int y);

	void RunProgram(const char *prog);

	void RunDlg( wxCommandEvent &evt);


	void RunCfg( wxCommandEvent &evt);

	void RunTerm( wxCommandEvent &evt);



protected:
wxString path;
wxMenu 	     *menu;
wxCircleToggleButton *btn;
bool vis;
DECLARE_EVENT_TABLE();

};
#endif
