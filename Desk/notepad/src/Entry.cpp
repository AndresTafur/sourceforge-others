#include "Entry.hh"


	Entry::Entry(wxWindow* parent,wxStatusBar *StatBar, int id ): wxTextCtrl(parent,id,wxT(""),wxDefaultPosition,
				    wxDefaultSize,wxTE_MULTILINE|wxTE_DONTWRAP,wxDefaultValidator,_T("entry"))
	{
		statbar = StatBar;
		wxTextAttr TextAttr;
		TextAttr = GetDefaultStyle();
		FontData.SetColour(TextAttr.GetTextColour());
		FontData.SetChosenFont(TextAttr.GetFont());
	}

	void Entry::Count()
	{
	  wxString str;
	  long x, y;

		PositionToXY( GetInsertionPoint(), &x, &y);

		str << wxT("Linea ") <<  y+1 << wxT("     Columna ") << x+1;
		statbar->SetStatusText(str, 1);
	}



	bool Entry::readFile(wxString FileName)
	{

	  wxString buff;

	    if( FileName.IsEmpty() )
		return false;

   	    if( LoadFile(FileName) )
	    {
		    fileName = FileName;
		    return true;
	    }

	  return false;
	}

	bool Entry::writeFile()
	{
		return writeFile(fileName);
	}

	bool Entry::writeFile(wxString FileName)
	{
	    if( FileName.IsEmpty() )
		return false;

 	    if(	SaveFile(FileName) )
	    {
	        fileName = FileName;
       	        return true;
	    }

	  return false;
	}


	void Entry::SelectAll()
	{
	    SetSelection(0, this->GetLastPosition());
	}

	wxString Entry::getFileName()
	{
		return fileName;
	}


	wxString Entry::getRelName()
	{
		return relName;
	}

	wxFontData Entry::getFontData()
	{
		return FontData;
	}

	void Entry::setFontData(wxFontData fontData)
	{
		FontData = fontData;
		wxTextAttr TextAttr;
		TextAttr.SetTextColour(FontData.GetColour());
		TextAttr.SetFont(FontData.GetChosenFont());
		SetStyle(0,GetValue().Len(),TextAttr);
		SetDefaultStyle(TextAttr);
	}

	void Entry::setFileName(wxString FileName)
	{
		fileName = FileName;
		relName  = FileName.AfterLast('/');
	}
