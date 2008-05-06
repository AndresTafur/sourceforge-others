#include "InventoryFinderDlg.hh"


   InventoryFinderDlg::InventoryFinderDlg(wxWindow *parent) : InventoryViewer(parent)
   {
     wxBoxSizer *ctrl  = this->getRightPanel();
     wxButton   *accept  = new wxButton(this,wxID_OK,"&Seleccionar");
     wxWindow   *wnd     = ctrl->GetItem(5)->GetWindow();

        ctrl->Insert(5, accept,1,wxALIGN_CENTER_HORIZONTAL|wxEXPAND,5);
        ctrl->InsertSpacer(6,20);

        this->SetTitle( wxT("Selector de items") );
        this->Layout();
   }


    void InventoryFinderDlg::onSelect(wxCommandEvent &evt)
    {
       int row = m_grid->GetGridCursorRow();
       int col = m_grid->GetGridCursorCol();

            if( m_grid->GetRows() <= 0)
            {
                wxMessageBox( wxT("Por favor realice una busqueda o agregue items.")
                             ,wxT("Error"),wxICON_ERROR);
                return;
            }

    }


BEGIN_EVENT_TABLE(InventoryFinderDlg,InventoryViewer)
    EVT_BUTTON(wxID_OK,InventoryFinderDlg::onSelect)
END_EVENT_TABLE()
