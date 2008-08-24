#include "AvNotebook.h"
#include "FileSelectionDialog.hh"


    AvNotebook::AvNotebook(wxWindow *parent, wxAnimationCtrl *load,int id) : wxAuiNotebook(parent, id,wxDefaultPosition,wxDefaultSize,wxAUI_NB_TOP|wxAUI_NB_CLOSE_ON_ALL_TABS|wxAUI_NB_TAB_MOVE|wxAUI_NB_WINDOWLIST_BUTTON)
    {
        wxRect *out, out2;
        int * ext;


            this->load = load;

            status  = new StatusPanel(this,clammgr);
            this->AddPage(status, wxT("Status"));
    }



    void AvNotebook::insertStatus()
    {
        if( this->GetPageIndex(status) == wxNOT_FOUND )
        {
            status = new StatusPanel(this,clammgr);
            if( this->GetPageCount() < 1)
                this->AddPage(status, wxT("Status"),true);
            else
                this->InsertPage(0,status, wxT("Status"),true);
        }
    }


    void AvNotebook::insertScan()
    {
         if( this->GetPageIndex(scan) == wxNOT_FOUND )
         {

             FileSelectionDialog dlg(this);

             if( dlg.ShowModal() == wxID_OK)
             {
                scan = new AvPanel(this,load,dlg.getFullPath());
                scan->Show(false);

                this->AddPage(scan, wxT("Scan"), true);
             }
         }
         else
         {
            this->RemovePage(GetPageIndex(scan));
            scan->Destroy();
            insertScan();
         }
    }
