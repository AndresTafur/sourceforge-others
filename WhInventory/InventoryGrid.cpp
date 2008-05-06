#include "InventoryGrid.hh"



        InventoryGrid::InventoryGrid(wxWindow *parent, int id) : wxGrid(parent,id)
        {
            this->CreateGrid(0,8);

            this->SetColLabelValue(0, wxT("Item"));
            this->SetColLabelValue(1, wxT("Ubicacion"));
            this->SetColLabelValue(2, wxT("cod. barras"));
            this->SetColLabelValue(3, wxT("cod. barras2"));

            this->SetColLabelValue(4, wxT("Familia"));
            this->SetColLabelValue(5, wxT("Descripcion"));
            this->SetColLabelValue(6, wxT("Cantidad"));
            this->SetColLabelValue(7, wxT("Valor unitario"));
            this->SetGridCursor(0,0);
            this->EnableCellEditControl();
            this->AutoSize();
        }


        void InventoryGrid::onChangeValue(wxGridEvent &evt)
        {
                /* sql << "REPLACE INTO items (item, familia, descr, cantidad, valor) VALUES"
                        "('YF42', 'YF','asd',40,1000)"
                */


        }


BEGIN_EVENT_TABLE(InventoryGrid,wxGrid)
EVT_GRID_CELL_CHANGE(InventoryGrid::onChangeValue)
END_EVENT_TABLE()
