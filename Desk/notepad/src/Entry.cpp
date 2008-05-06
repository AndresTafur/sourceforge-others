

class Entry : public  wxTextCtrl
{
public:

	Entry(wxWindow* parent,wxStatusBar *statbar, int id ): wxTextCtrl(parent,id,wxT(""),wxDefaultPosition, 
				    wxDefaultSize,wxTE_MULTILINE|wxTE_DONTWRAP,wxDefaultValidator,_T("entry"))
	{
		this->statbar = statbar;

	}

	void Count()
	{
	  wxString str;
	  long x, y;

		PositionToXY( GetInsertionPoint(), &x, &y);

		str << wxT("Linea ") <<  y+1 << wxT("     Columna ") << x+1;
		statbar->SetStatusText(str, 1);
	}



	bool readFile(wxString fileName)
	{

	  wxString buff;

	    if( fileName.IsEmpty() )
		return false;

   	    if( this->LoadFile(fileName) )
	    {
		    this->fileName = fileName;
		    return true;
	    }

	  return false;
	}

	bool writeFile()
	{
		return writeFile(this->fileName);
	}

	bool writeFile(wxString fileName)
	{
	  FILE *fl;	

	    if( fileName.IsEmpty() )
		return false;
	
 	    if(	this->SaveFile(fileName) )
	    {	
	        this->fileName = fileName;
       	        return true;
	    }	

	  return false;
	}


	
	void SelectAll()
	{
	    this->SetSelection(0, this->GetLastPosition());
	}

	wxString getFileName()
	{
		return fileName;
	}


	wxString getRelName()
	{
		return relName;
	}


	void setFileName(wxString fileName)
	{
		this->fileName = fileName;	
		this->relName  = fileName.AfterLast('/');
	}

private:
wxString fileName;
wxString relName;
wxStatusBar *statbar;
};

