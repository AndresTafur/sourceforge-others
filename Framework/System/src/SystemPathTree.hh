
#ifndef _WH_SPATH_TREE_
#define _WH_SPATH_TREE_

#include "WhiteHawkSystem.hh"
#include "AbstractFile.hh"

class WhiteHawkSystem::SystemPathTree
{
public:

          virtual int onFile( WhiteHawkSystem::AbstractFile file ) = 0;


};
#endif
