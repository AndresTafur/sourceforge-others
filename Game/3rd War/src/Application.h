#ifndef _APPLICATION_
#define _APPLICATION_

#include <Ogre.h>
#include <OgreConfigFile.h>
#include <OgreOde_Core.h>
#include "ApplicationFrameListener.h"

using namespace Ogre;
using namespace OgreOde;
using namespace OgreOde_Prefab;
using namespace OgreOde_Loader;


#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <CoreFoundation/CoreFoundation.h>
std::string macBundlePath();
#endif



class Application
{
public:

    /// Standard constructor
    Application();


    virtual ~Application();

    /// Start the example
    virtual void startApplication();


protected:
    // These internal methods package up the stages in the startup process
    /** Sets up the application - returns false if the user chooses to abandon configuration. */
    virtual bool setup(void);

    /** Configures the application - returns false if the user chooses to abandon configuration. */
    virtual bool configure(void);

    virtual void chooseSceneManager(void) = 0;

    virtual void createCamera(void) = 0;

    virtual void createFrameListener(void) = 0;

    virtual void createScene(void) = 0;    // pure virtual - this has to be overridden

    virtual void destroyScene(void){}    // Optional to override this

    virtual void createViewports(void);

    virtual void createGui(void) = 0;

    /// Method which will define the source of resources (other than current folder)
    virtual void setupResources(void);

	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener(void) { }

	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources(void);


protected:
    Root *mRoot;
    Camera* mCamera;
    SceneManager* mSceneMgr;
    ApplicationFrameListener* mFrameListener;
    RenderWindow* mWindow;
	Ogre::String mResourcePath;

};
#endif
