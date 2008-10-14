#include "Entry.hh"

	Entry::Entry(wxWindow* parent,wxStatusBar *statBar, int id ): wxTextCtrl(parent,id,wxT(""),wxDefaultPosition,
				    wxDefaultSize,wxTE_MULTILINE|wxTE_DONTWRAP,wxDefaultValidator,_T("entry"))
	{
		m_statbar = statBar;
		wxTextAttr textAttr;
		textAttr = GetDefaultStyle();
		m_fontData.SetColour(textAttr.GetTextColour());
		m_fontData.SetChosenFont(textAttr.GetFont());
	}

	Entry::~Entry()
	{
		delete m_statbar;
	}
	
	void Entry::Count()
	{
	  wxString str;
	  long x, y;

		PositionToXY( GetInsertionPoint(), &x, &y);

		str << wxT("Linea ") <<  y+1 << wxT("     Columna ") << x+1;
		m_statbar->SetStatusText(str, 1);
	}



	bool Entry::readFile(wxString fileName)
	{

	  wxString buff;

	    if( fileName.IsEmpty() )
		return false;

   	    if( LoadFile(fileName) )
	    {
		    m_fileName = fileName;
		    return true;
	    }

	  return false;
	}

	bool Entry::writeFile()
	{
		return writeFile(m_fileName);
	}

	bool Entry::writeFile(wxString fileName)
	{
	    if( fileName.IsEmpty() )
		return false;

 	    if(	SaveFile(fileName) )
	    {
	        m_fileName = fileName;
       	        return true;
	    }

	  return false;
	}

	void Entry::SelectAll()
	{
	    SetSelection(0, GetLastPosition());
	}

	wxString Entry::getFileName()
	{
		return m_fileName;
	}


	wxString Entry::getRelName()
	{
		return m_relName;
	}

	wxFontData Entry::getFontData()
	{
		return m_fontData;
	}

	void Entry::setFontData(wxFontData fontData)
	{
		m_fontData = fontData;
		wxTextAttr textAttr;
		textAttr.SetTextColour(m_fontData.GetColour());
		textAttr.SetFont(m_fontData.GetChosenFont());
		SetStyle(0,GetValue().Len(),textAttr);
		SetDefaultStyle(textAttr);
	}

	void Entry::setFileName(wxString fileName)
	{
		m_fileName = fileName;
		m_relName  = fileName.AfterLast('/');
	}
