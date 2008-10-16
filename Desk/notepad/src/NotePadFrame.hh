/**
 *    @brief Notepad Frame class.
 *    Notepad Frame class.
 *    @class  NotePadFrame
 *    @author Lostmarbles
 *    @version 0.1
 */


#ifndef _NOTEPAD_FRAME_
#define _NOTEPAD_FRAME_

#include "Entry.hh"
#include <wx/fontdlg.h>
#include <wx/aboutdlg.h>
#include <wx/fdrepdlg.h>

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
	~NotePadFrame();

	void openDlg(wxCommandEvent &evt);


	void SaveAsDlg();

	void GoToDlg();
	//void SaveAs(wxCommandEvent &evt);
	void OnFindDialog(wxFindDialogEvent& event);
	void ShowFindDialog( wxCommandEvent& WXUNUSED(event) );
	void ShowReplaceDialog( wxCommandEvent& WXUNUSED(event) );

	void openFile(wxString str);

	void openFile(wxString str, wxString file);

	void newFile(wxCommandEvent &evt);

	int HaveSaved();

	void SaveFile();

	void Save( wxCommandEvent &evt);

	void SaveAs(wxCommandEvent &evt);

	void Find (wxString findValue, int searchFlags, bool findNext);
	void Replace (wxString findValue, wxString replaceValue, int searchFlags, bool replaceOnce);

	void Action(wxCommandEvent &evt);

	void TextEvt(wxCommandEvent &evt);

	void FormatFont(wxCommandEvent &evt);

	void Quit(wxCommandEvent &evt);

	void About(wxCommandEvent &evt);


private:
	bool m_saved;
	int m_lastSearchPos;
	wxStatusBar *m_statbar;
	Entry  *m_entry;
	wxFindReplaceDialog *m_dlgFind;
	wxFindReplaceDialog *m_dlgReplace;
	wxFindReplaceData m_findData;
	DECLARE_EVENT_TABLE();

};

#endif
