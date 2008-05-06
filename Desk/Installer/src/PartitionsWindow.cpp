
#include "PartitionManager.cpp"


class ListItemDialog : public wxDialog
{
public:
		ListItemDialog(wxWindow* parent, wxString str) : wxDialog(parent, 101, wxT("Editar punto de montaje"),wxDefaultPosition, wxDefaultSize,wxDEFAULT_DIALOG_STYLE,wxT(""))
		{
			wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
			wxBoxSizer *hsize = new wxBoxSizer(wxHORIZONTAL);
			wxSizer    *buttons = CreateButtonSizer(wxOK|wxCANCEL);
			wxStaticText *text;
			
			

		       picker = new wxDirPickerCtrl(this,1,wxT("/"),wxT("Picka folder"), wxDefaultPosition,wxDefaultSize,wxDIRP_DEFAULT_STYLE|wxDIRP_USE_TEXTCTRL,wxDefaultValidator,wxT(""));
			
		  	text = new wxStaticText(this,wxID_ANY,"Por favor ingrese la ruta donde sera montado "
			"el dispositivo \"" + str + "\" : ",wxDefaultPosition,wxDefaultSize,0,wxT(""));

			text->Wrap(300);

			hsize->Add(picker,1,wxEXPAND|wxALL,5);

			sizer->Add(text,0,wxALL|wxEXPAND,20);
			sizer->Add(hsize,0,wxALL|wxEXPAND,5);
			sizer->AddSpacer(10);
			sizer->Add(buttons,0,wxCENTRE|wxALL,10);
			this->SetSizer(sizer);
			this->Fit();

		}


		wxString GetPath()
		{
			return picker->GetPath();
		}

protected:
wxDirPickerCtrl *picker;
};



class PartitionsWindow :  public wxListView
{
public:

PartitionsWindow(wxWindow *parent) : wxListView(parent,100,wxDefaultPosition,wxSize(500,300),wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES,wxDefaultValidator,_(""))
	{
	    InsertColumn(0, wxT("Punto de montaje"), wxLIST_FORMAT_LEFT, -1);
	    InsertColumn(1, wxT("Sistema de archivos"), wxLIST_FORMAT_LEFT, -1);
	    InsertColumn(2, wxT("Dispositivo"), wxLIST_FORMAT_LEFT, -1);
	}


	void OnEdit( wxListEvent &e)
	{
	  long id = e.GetIndex();
	  ListItemDialog dlg(this,e.GetLabel());
		if( dlg.ShowModal() == wxID_OK)
			SetItem(e.GetIndex(),0, dlg.GetPath() );
	}


	void OnPresent()
	{
	   bool flag = true;
	
		partmgr  = new PartitionManager();
	
		for(int i=0; i < partmgr->HowManyPartitions(); i++)
		{
			wxString  str( wxT("/dev/hda"));
			wxString  type, buff;

			str  << partmgr->GetNumOf(i);
			type << partmgr->GetTypeOf(i);
			buff = str;

				if( flag && (type.Contains( wxT("reiser")) || type.Contains( wxT("ext"))))
				{
					InsertItem(i,wxT("/"));
					flag = false;
				}
				else
				{
					str.Replace(wxT("/dev/"),wxT("/mnt/"));
					InsertItem(i,str);
				}

				SetItem(i,1,type);
				SetItem(i,2,buff);
			
		}

		this->Layout();
	}


	PartitionManager *GetPartitionManager()
	{
		return partmgr;
	}
	


protected:
PartitionManager *partmgr;

DECLARE_EVENT_TABLE()

};
BEGIN_EVENT_TABLE(PartitionsWindow,wxListCtrl)
EVT_LIST_ITEM_ACTIVATED(100, PartitionsWindow::OnEdit)
END_EVENT_TABLE()
