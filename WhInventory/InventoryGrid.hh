
#ifndef _INVENTORY_GRID_
#define _INVENTORY_GRID_

#include <wx/grid.h>

class InventoryGrid : public wxGrid
{
public:

        InventoryGrid(wxWindow *parent, int id);

        void onChangeValue(wxGridEvent &evt);

protected:
DECLARE_EVENT_TABLE()
};



#endif
