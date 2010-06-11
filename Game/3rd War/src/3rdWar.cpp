#include "Application.h"

int main(int argc, char **argv)
{
    Application app;

    try
    {
        app.startApplication();
        fprintf(stderr,"All components released, expecting libboost exit");
    }
    catch( Exception& e )
    {
            std::cerr << "An exception has occured: " << e.getFullDescription();
    }
    return 0;
}
