
#ifndef _CLAMAV_ENGINE_
#define _CLAMAV_ENGINE_


class ClamavEngine
{
public:

        ClamavEngine();

        void loadDatabase(int option);

        bool hasChanged();



public:

static CL_DEFAULT;
static CL_PHISHING;
static CL_PHISHURL;
static CL_PUNWANTED;
protected:

};
