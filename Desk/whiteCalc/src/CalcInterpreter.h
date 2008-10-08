 #ifndef CalcEngine_H
 #define CalcEngine_H

#include "ParserLib/muParser.cpp"
#include "ParserLib/muParserBase.cpp"
#include "ParserLib/muParserBytecode.cpp"
#include "ParserLib/muParserCallback.cpp"
#include "ParserLib/muParserError.cpp"
#include "ParserLib/muParserTokenReader.cpp"

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
