#ifndef _INVENTORY_FINDER_DLG_
#define _INVENTORY_FINDER_DLG_

#include <wx/wx.h>
#include "InventoryViewer.hh"


class InventoryFinderDlg : public InventoryViewer
{
public:

        InventoryFinderDlg(wxWindow *parent);

        void onSelect(wxCommandEvent &evt);

protected:
DECLARE_EVENT_TABLE()
};

#endif
