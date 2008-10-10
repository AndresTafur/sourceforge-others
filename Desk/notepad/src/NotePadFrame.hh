#ifndef _NOTEPAD_FRAME_
#define _NOTEPAD_FRAME_


#include "Entry.hh"
#include <wx/wx.h>

enum
{
	ID_SB = 100,
	ID_EN,
	ID_GOTO,
 	ID_FORMAT
};

//TODO: document everything


class NotePadFrame : public  wxFrame
{
public:

  NotePadFrame();

	void openDlg(wxCommandEvent &evt);


	void SaveAsDlg();

	void GoToDlg();


	void openFile(wxString str);


	void openFile(wxString str, wxString file);

	void newFile(wxCommandEvent &evt);

	int HaveSaved();

	void SaveFile();

	void Save( wxCommandEvent &evt);


	void SaveAs(wxCommandEvent &evt);


	void Find ( wxCommandEvent &evt);

	void Action(wxCommandEvent &evt);

	void TextEvt(wxCommandEvent &evt);

	void FormatFont(wxCommandEvent &evt);

	void Quit(wxCommandEvent &evt);

	void About(wxCommandEvent &evt);


private:
bool saved;
wxStatusBar *statbar;
Entry  *entry;
DECLARE_EVENT_TABLE();

};

#endif
