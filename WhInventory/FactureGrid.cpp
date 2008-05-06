#include "FactureGrid.hh"


    FactureGrid::FactureGrid(wxWindow *parent, int id) : wxGrid(parent,id)
    {
           this->CreateGrid(1, 5);
           this->SetColLabelValue(0, wxT("Item"));
           this->SetColLabelValue(1, wxT("Descripcion"));
           this->SetColLabelValue(2, wxT("Cantidad"));
           this->SetColLabelValue(3, wxT("Valor Unitario"));
           this->SetColLabelValue(4, wxT("Subtotal"));
           this->SetReadOnly(0,4,true);
           this->SetGridCursor(0,0);
           this->AutoSize();
           this->EnableCellEditControl();

    }

    void FactureGrid::onEnter(wxKeyEvent &evt)
    {
        switch( evt.GetKeyCode() )
        {
           case WXK_RETURN:
           case WXK_NUMPAD_ENTER:
           {
              int col =  this->GetGridCursorCol();
              int row =  this->GetGridCursorRow();

                    if( col < 2)
                        this->SetGridCursor(row, 2);
                    else if( col == 3)
                    {
                            if( row ==  this->GetNumberRows()-1)
                            {
                                this->AppendRows(1,true);
                                this->SetReadOnly(row+1,4);
                            }
                            this->SetGridCursor(row+1,0);
                    }
                    else
                        this->SetGridCursor(row, 3);
                   this->EnableCellEditControl();
                }
                break;

                case WXK_DOWN:
                {
                    int row = this->GetGridCursorRow();

                        if( row != this->GetNumberRows()-1)
                           this->SetGridCursor(row+1, this->GetGridCursorCol());
                }
                break;


                case WXK_UP:
                    if( this->GetGridCursorRow() != 0)
                        this->SetGridCursor(this->GetGridCursorRow()-1, this->GetGridCursorCol());
                    break;

                case WXK_LEFT:
                   if( this->GetGridCursorCol() != 0)
                    this->SetGridCursor( this->GetGridCursorRow(),this->GetGridCursorCol()-1);
                   break;

                 case WXK_TAB:
                 case WXK_RIGHT:
                    if( this->GetGridCursorCol() != this->GetNumberCols()-1)
                    {
                        this->SetGridCursor( this->GetGridCursorRow(),this->GetGridCursorCol()+1);
                    }
                    break;

                default:
                {/*
                  int row  = this->GetGridCursorRow();
                  int col  = this->GetGridCursorCol();
                  int code = evt.GetKeyCode();
                  wxString str;


                    if( code >= WXK_NUMPAD0 && code <= WXK_NUMPAD9)
                        code = ( code - WXK_NUMPAD0) + 48;

                      str = (char) code;

                    this->SetCellValue(str,row,col);*/
                    this->EnableCellEditControl();
                }
                break;
            }
        }


    BEGIN_EVENT_TABLE(FactureGrid,wxGrid)
    EVT_KEY_DOWN(FactureGrid::onEnter)
    END_EVENT_TABLE()
