#ifndef _APPLICATION_
#define _APPLICATION_

#include <Ogre.h>
#include <OgreConfigFile.h>
#include <OgreOde_Core.h>

#include "ApplicationFrameListener.h"
#include "Scenes/SceneBase.h"
#include "Scenes/LoginScene.h"


using namespace Ogre;
using namespace OgreOde;
using namespace OgreOde_Prefab;
using namespace OgreOde_Loader;


#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <CoreFoundation/CoreFoundation.h>
std::string macBundlePath();
#endif


/**
 * Main application. Reads configuration files,load needed plugins and virtual file systems.
 */
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
    /**
     * Sets up the application - returns false if the user chooses to abandon configuration.
     * @return true if sucess.
     */
    virtual bool setup(void);

    /**
     * Configures the application - returns false if the user chooses to abandon configuration.
     * @return true on sucess.
     */
    virtual bool configure(void);


    /// Method which will define the source of resources (other than current folder)
    virtual void setupResources(void);

	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener(void) { }

	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources(void);


protected:
    Root *mRoot;
    RenderWindow* mWindow;
	Ogre::String mResourcePath;
    std::vector<SceneBase*> m_scenes;

};
#endif
