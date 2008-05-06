

class Frame : public wxFrame, public WhiteHawkThread
{
public:
    
          Frame(wxString str): wxFrame(NULL,wxID_ANY, wxT(""),wxDefaultPosition,wxSize(600,487),wxFRAME_NO_TASKBAR|wxSTAY_ON_TOP|wxBORDER_NONE)
          {
               wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
               wxBoxSizer *icons = new wxBoxSizer(wxHORIZONTAL);

		wxAnimation anim1,anim2,anim3;

		anim1.LoadFile(str+wxT("/data/start.gif"));
		anim2.LoadFile(str+wxT("/data/wm.gif"));
		anim3.LoadFile(str+wxT("/data/desk.gif"));


               wxStaticBitmap *map = new wxStaticBitmap(this,wxID_ANY, wxBitmap( str + wxT("/data/splash.png")));

               load = new wxAnimationCtrl(this,wxID_ANY,anim1);
               man  = new wxAnimationCtrl(this,wxID_ANY,anim2);
               desk = new wxAnimationCtrl(this,wxID_ANY,anim3);
                



		icons->Add(load,0,wxEXPAND|wxLEFT,20);
		icons->Add(man, 0,wxEXPAND|wxLEFT,20);
		icons->Add(desk,0,wxEXPAND|wxLEFT,20);


                sizer->Add(map);
                sizer->Add(icons,0,wxEXPAND|wxTOP,5);

                this->Center();
                this->SetBackgroundColour(wxColor("WHITE"));
                this->SetSizer(sizer);
                
                
          }
    
	bool loadWhiteHawk(const char *path)
	{
		popen(path,"r");
		return true;
	}
    
    	void ThreadRoutine()
	{
		popen("metacity","r");

		load->Play();
		loadWhiteHawk("./Taskbar");
		T_Sleep(800);
		load->Stop();

		man->Play();
		loadWhiteHawk("./desk");
		T_Sleep(800);
		man->Stop();

		desk->Play();
		T_Sleep(800);
		desk->Stop();

		man->Play();
		
		this->Destroy();
		exit(0);
	}

    
protected:    
wxAnimationCtrl *man;    
wxAnimationCtrl *load;    
wxAnimationCtrl *desk;
    
    
};
