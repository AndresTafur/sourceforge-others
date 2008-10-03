 #ifndef CalcEngine_H
 #define CalcEngine_H

#include "ParserLib/muParser.cpp"
#include "ParserLib/muParserBase.cpp"
#include "ParserLib/muParserBytecode.cpp"
#include "ParserLib/muParserCallback.cpp"
#include "ParserLib/muParserError.cpp"
#include "ParserLib/muParserTokenReader.cpp"

using namespace mu;

class CalcEngine
{
public:
    CalcEngine();

    wxString Process(wxString formula);
};

 #endif
