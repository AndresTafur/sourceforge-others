#include "CalcInterpreter.h"

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
