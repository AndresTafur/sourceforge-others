#ifndef _CLIENTATTENDERBUILDER_H_
#define _CLIENTATTENDERBUILDER_H_

#include "ClientAttender.h"

class ClientAttenderBuilder
{
 public:

       virtual ClientAttender* getClientAttender() = 0;

 };

#endif // _CLIENTATTENDERBUILDER_H_
