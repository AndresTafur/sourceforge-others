 #ifndef CalcEngine_H
 #define CalcEngine_H

#include "muparser/muParser.cpp"
#include "muparser/muParserBase.cpp"
#include "muparser/muParserBytecode.cpp"
#include "muparser/muParserCallback.cpp"
#include "muparser/muParserError.cpp"
#include "muparser/muParserTokenReader.cpp"

using namespace mu;

enum base { Decimal = 0, Bin, Hex };

class CalcEngine
{
private:
    base _base;

public:
    CalcEngine();

    wxString NumberToText(double d,int decimal_places);
    wxString Process(wxString formula);
};

 #endif
