#include "CalcInterpreter.h"

double HandlePercent(double fVal)
{
    return fVal/100;
}

double HandleFactorial(double fVal)
{
    double temp;
    if(fVal<=1) return 1;
    temp = fVal * HandleFactorial(fVal - 1);
    return temp;
}

double HandleMod(double v1, double v2)
{
  return (double)((int)v1 % (int)v2);
}

double static HandleNOT(double v1)
{
  return v1;
}

double HandleXNOR(double v1, double v2)
{
  return !(double)((int)v1^(int)v2);
}

CalcEngine::CalcEngine()
{
    _base = Decimal;
}

wxString CalcEngine::Process(wxString formula)
{
    wxString result = wxT("");

    mu::Parser parser;

    double fVal;
    switch(_base)
    {
        case Decimal:
            parser.AddValIdent(Parser::IsVal);
            break;
        case Bin:
            parser.AddValIdent(Parser::IsBinVal);
            break;
        case Hex:
            parser.AddValIdent(Parser::IsHexVal);
            break;
    }
    parser.DefinePostfixOprt(_T("%"), HandlePercent);
    parser.DefinePostfixOprt(_T("!"), HandleFactorial);
    parser.DefineOprt(_T("mod"), HandleMod, 0);
    parser.DefineOprt(_T("xnor"), HandleXNOR, 0);
    parser.DefineFun(_T("~"), HandleNOT, false);
    parser.SetExpr(formula.c_str());
    try
    {
        fVal = parser.Eval();
        result << fVal;
    }
    catch (Parser::exception_type &e)
    {
        result = e.GetMsg();
    }

    return result;
}
