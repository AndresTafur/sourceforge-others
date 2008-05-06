/***************************************************************
 * Name:      conexionHawkMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Camilo Rodríguez (candres68@hotmail.com)
 * Created:   2007-07-29
 * Copyright: Camilo Rodríguez ()
 * License:
 **************************************************************/

#include<wx/wx.h>

enum
{
    ID_CONEXION,
    ID_DESCONEXION,
    ID_ABOUT
};

class conexionHawk : public wxApp
{
    public:
        virtual bool OnInit();
};

class FrameDios : public wxFrame
{
    public:
        FrameDios();

    protected:
        void OnQuit(wxCommandEvent& salir);
        void acercade(wxCommandEvent& acerca);
        void Conectarse(wxCommandEvent& conectar);
        void Desconectarse(wxCommandEvent& desconectar);

    private:
        DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP(conexionHawk)

bool conexionHawk :: OnInit()
{
    FrameDios *frame=new FrameDios;
    frame->Show(true);

    return true;
}

FrameDios :: FrameDios() :wxFrame(NULL,wxID_ANY,_T("conexionHawk"))
{
    wxMenu *menu=new wxMenu;
    wxMenu *menu2=new wxMenu;

    menu->Append(wxID_EXIT,_T("&Cerrar\tAlt-F4"),_T("Cerrar la aplicación"));
    menu2->Append(ID_ABOUT,_T("&Acerca de..."),_T("Información del programa"));

    wxMenuBar *barra=new wxMenuBar();

    barra->Append(menu,_T("&Archivo"));
    barra->Append(menu2,_T("A&yuda"));
    SetMenuBar(barra);


    wxButton *Conectar=new wxButton(this,ID_CONEXION,_T("Conectar"),wxPoint(40,20),wxDefaultSize);
    wxButton *Desconectar=new wxButton(this,ID_DESCONEXION,_T("Desconectar"),wxPoint(40,60),wxDefaultSize);
    this->CreateStatusBar(2, wxST_SIZEGRIP);

}

BEGIN_EVENT_TABLE(FrameDios,wxFrame)
    EVT_MENU(wxID_EXIT,FrameDios::OnQuit)
    EVT_MENU(ID_ABOUT,FrameDios::acercade)
    EVT_BUTTON(ID_CONEXION,FrameDios :: Conectarse)
    EVT_BUTTON(ID_DESCONEXION,FrameDios :: Desconectarse)

END_EVENT_TABLE()

void FrameDios :: OnQuit(wxCommandEvent& WXUNUSED(salir))
{
    Close(true);
}

void FrameDios :: Conectarse(wxCommandEvent& conectar)
{
    wxMessageBox(_T("Hola"),_T("Hola"),wxOK|wxICON_INFORMATION,NULL);
    system("pon dsl-provider");
}

void FrameDios :: Desconectarse(wxCommandEvent& desconectar)
{
    system("poff dsl-provider");
}

void FrameDios :: acercade(wxCommandEvent& acerca)
{
    wxMessageBox(_T("Creado por: Camilo Rodríguez"),_T("Acerca de..."),wxOK | wxICON_EXCLAMATION,NULL);
}
