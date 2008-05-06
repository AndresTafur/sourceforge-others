
#ifndef _INVENTORY_VIEWER_
#define _INVENTORY_VIEWER_

#include <wx/wx.h>
#include <wx/statline.h>
#include "InventoryGrid.hh"

enum
{
   INV_ADD = 0,
   INV_DEL,
   INV_REP,
   INV_MOD,
   INV_GRID,
   INV_FIND,
};


class InventoryViewer : public wxFrame
{
public:

        InventoryViewer(wxWindow *parent);

        inline wxBoxSizer*    getRightPanel() { return m_ctrl; }
        inline InventoryGrid* getGrid() { return m_grid; }

        void onCheck( wxCommandEvent &evt);
        void onSearch( wxCommandEvent &evt);

        void ShowDefault();


protected:
InventoryGrid *m_grid;
wxButton      *m_add;
wxButton      *m_del;
wxCheckBox    *m_modif;
wxTextCtrl    *m_text;
wxComboBox    *m_menu;
wxBoxSizer    *m_ctrl;
DECLARE_EVENT_TABLE()
};


#endif


