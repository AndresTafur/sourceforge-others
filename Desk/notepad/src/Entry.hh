/**
 *    @brief Text entry class.
 *    Text entry class.
 *    @class  Entry
 *    @author Lostmarbles
 *    @version 0.1
 */

#ifndef _ENTRY_
#define _ENTRY_

#include <wx/wx.h>

class Entry : public  wxTextCtrl
{
public:
	/*
	* Default constructor
	*/
	Entry(wxWindow* parent,wxStatusBar *statBar, int id );
	~Entry();
	void Count();
	bool readFile(wxString fileName);
	bool writeFile();
	bool writeFile(wxString fileName);
	void SelectAll();
	wxString getFileName();
	wxString getRelName();
	wxFontData getFontData();
	void setFontData(wxFontData fontData);
	void setFileName(wxString fileName);

private:
	wxString m_fileName;
	wxString m_relName;
	wxStatusBar *m_statbar;
	wxFontData m_fontData;
};

#endif
