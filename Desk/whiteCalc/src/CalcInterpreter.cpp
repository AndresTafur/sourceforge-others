


class CalcInterpreter
{
public:

        double toDouble(wxString str)
        {
           long tmp;
           double res;
           int  index, pot;

                    index = str.Find( wxT(".") );
                    if( index != wxNOT_FOUND )
                    {
                       pot = (str.SubString(index+1, str.length() )).length();

                       str = (str.SubString(0,index-1)) + str.SubString(index+1, str.length() );

                       str.ToLong(&tmp);

                       return tmp/(pow(10,pot));

                    }
            str.ToDouble(&res);
            return res;
        }

        void setNum1( wxString str)
        {
             num = toDouble(str);
        }

        void setNum2(wxString str)
        {
            num2 = toDouble(str);
        }


        void setOper(int type)
        {
            this->type = type;
        }


        wxString operate()
        {
            wxString str;


            switch(type)
            {
                    case ID_SUS:
                         num2 *= (-1);

                    case ID_SUM:
                         res = num + num2;
                         break;


                    case ID_DIV:
                        num2 = (1/num2);
                    case ID_MUL:
                        res = num * num2;
                        break;

                    default:
                    res = num2;
            }

            str << res;

            return str;
        }


const static int ID_SUM = 0;
const static int ID_MUL = 1;
const static int ID_DIV = 2;
const static int ID_SUS = 3;


private:
int type;
double num, num2, res;
};
