/**
 *  This Class manages one result ( content and position )given by the SqlResultManager
 *
 * @see    whiteSQL::SqlResult
 */

class whiteSQL::ResultContent
{
public:


   /** Default constructor
    *  set the result content and position
    *
    * @param  row   Row of the result
    * @param  field Field of the result
    * @param  cont  Content of the result
    */

        ResultContent(long row, long field, std::string cont);


   /** Obtains the row position of this result
    *
    * @return  The row of the result
    */

        long getRow();

   /** Obtains the field position of this result
    *
    * @return  The field of the result
    */

        long getField();


   /** Obtains the content string of this result
    *
    * @return  The content of this result
    */

        std::string getContent();

  /** Sets the result content and position
   *
   * @param  row   Row of the result
   * @param  field Field of the result
   * @param  cont  Content of the result
   */


        void Create(long row, long field, std::string cont);



protected:

 /** Specific row of this result
  */
 long row;

 /** Specific field of this result
  */
 long field;

 /** Content of this result
  */
 std::string cont;
};
