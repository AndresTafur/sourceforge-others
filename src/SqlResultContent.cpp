#include "whiteSQL.hh"


   /** Default constructor
    *  set the result content and position
    *
    * @param  row   Row of the result
    * @param  field Field of the result
    * @param  cont  Content of the result
    */

        whiteSQL::ResultContent::ResultContent(long row, long field, std::string cont)
        {
            this->Create(row,field,cont);
        }


   /** Obtains the row position of this result
    *
    * @return  The row of the result
    */

        long whiteSQL::ResultContent::getRow()
        {
            return row;
        }


   /** Obtains the field position of this result
    *
    * @return  The field of the result
    */

        long whiteSQL::ResultContent::getField()
        {
           return field;
        }


   /** Obtains the content string of this result
    *
    * @return  The content of this result
    */

        std::string whiteSQL::ResultContent::getContent()
        {
            return cont;
        }


  /** Sets the result content and position
   *
   * @param  row   Row of the result
   * @param  field Field of the result
   * @param  cont  Content of the result
   */


        void whiteSQL::ResultContent::Create(long row, long field, std::string cont)
        {
            this->row    = row;
            this->cont   = cont;
            this->field  = field;
        }


