#include "FileSelectionDialog.hh"


    FileSelectionDialog::FileSelectionDialog(wxWindow *parent) :wxDialog(parent, wxID_ANY, wxT("File to scan"),wxDefaultPosition,wxSize(500,400))
    {
        wxBoxSizer   *sizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer   *ctrl  = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText *text  = new wxStaticText(this,wxID_ANY,wxT("Please select the file or folder to be scanned: \n"));


        browser = new wxGenericDirCtrl(this,wxID_ANY,wxDirDialogDefaultFolderStr,wxDefaultPosition,wxDefaultSize,wxDIRCTRL_SHOW_FILTERS|wxDIRCTRL_SELECT_FIRST|wxDIRCTRL_3D_INTERNAL|wxSUNKEN_BORDER);



        sizer->Add(text,0,wxEXPAND|wxALL,5);
        sizer->Add(browser,1,wxEXPAND|wxALL,5);
        sizer->Add( this->CreateButtonSizer(wxOK|wxCANCEL),0,wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL,2);
        this->SetSizer(sizer);

    }



    wxString FileSelectionDialog::getFullPath()
    {
        return browser->GetPath() ;
    }
