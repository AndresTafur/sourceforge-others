#ifndef _ENTRY_
#define _ENTRY_

#include <wx/wx.h>

//TODO: document everything


class Entry : public  wxTextCtrl
{
public:

	Entry(wxWindow* parent,wxStatusBar *StatBar, int id );

	void Count();

	bool readFile(wxString FileName);

	bool writeFile();

	bool writeFile(wxString FileName);


	void SelectAll();

	wxString getFileName();


	wxString getRelName();

	wxFontData getFontData();

	void setFontData(wxFontData fontData);

	void setFileName(wxString FileName);

private:
wxString fileName;
wxString relName;
wxStatusBar *statbar;
wxFontData FontData;
};

#endif
