

class Entry : public  wxTextCtrl
{
public:

	Entry(wxWindow* parent,wxStatusBar *StatBar, int id ): wxTextCtrl(parent,id,wxT(""),wxDefaultPosition, 
				    wxDefaultSize,wxTE_MULTILINE|wxTE_DONTWRAP,wxDefaultValidator,_T("entry"))
	{
		statbar = StatBar;
		wxTextAttr TextAttr;
		TextAttr = GetDefaultStyle();
		FontData.SetColour(TextAttr.GetTextColour());
		FontData.SetChosenFont(TextAttr.GetFont());
	}

	void Count()
	{
	  wxString str;
	  long x, y;

		PositionToXY( GetInsertionPoint(), &x, &y);

		str << wxT("Linea ") <<  y+1 << wxT("     Columna ") << x+1;
		statbar->SetStatusText(str, 1);
	}



	bool readFile(wxString FileName)
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

	bool writeFile()
	{
		return writeFile(fileName);
	}

	bool writeFile(wxString FileName)
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

	
	void SelectAll()
	{
	    SetSelection(0, this->GetLastPosition());
	}

	wxString getFileName()
	{
		return fileName;
	}


	wxString getRelName()
	{
		return relName;
	}

	wxFontData getFontData()
	{
		return FontData;
	}
	
	void setFontData(wxFontData fontData)
	{
		FontData = fontData;
		wxTextAttr TextAttr;
		TextAttr.SetTextColour(FontData.GetColour());
		TextAttr.SetFont(FontData.GetChosenFont());
		SetStyle(0,GetValue().Len(),TextAttr);
		SetDefaultStyle(TextAttr);
	}

	void setFileName(wxString FileName)
	{
		fileName = FileName;	
		relName  = FileName.AfterLast('/');
	}

private:
wxString fileName;
wxString relName;
wxStatusBar *statbar;
wxFontData FontData;
};

