#include "PartitionsWindow.cpp"



class PartitionsPage : public Page
{
public:

	PartitionsPage(wxWindow *parent) : Page(parent)
	{

	   wxBoxSizer    *sizer  = new wxBoxSizer(wxVERTICAL);
	   wxStaticText  *title;
	   wxStaticText  *text;
	   

	        title = new wxStaticText(this,0,_("Configuracion de disco:"),wxDefaultPosition,wxDefaultSize,0,_(""));

	  	text = new wxStaticText(this,wxID_ANY,"Ahora  se procedera  a configurar "
		"los puntos de montaje de las particiones, "
		"debe tener almenos un punto de montaje denominado \"/\".\n\n\n"
		"Para seleccionar los puntos de montaje por favor haga doble click en los directorios:"
		,wxDefaultPosition,wxDefaultSize,0,wxT(""));

		partview = new PartitionsWindow(this);
		

		
		this->SetTargetWindow(this);
		text->Wrap(620);

		sizer->Add(title,0,wxBOTTOM,10);
		sizer->Add(text,0,wxBOTTOM,20);
		sizer->Add(partview,0,wxCENTER);


		partview->FitInside();
		this->SetSizer(sizer);
		this->Fit();
	}


	wxString GetRoot()
	{
	  int items = partview->GetItemCount();
	  int i;
	  wxString str("/dev/hda");

		for(i=0; i < items; i++)
			if( partview->GetItemText(i).CompareTo("/") == 0)
				break;
		
		str << partview->GetPartitionManager()->GetNumOf(i);
		return str;
	}

	void OnPresent()
	{
		partview->OnPresent();
	}


protected:
PartitionsWindow *partview;
};

