#include "Application.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
std::string macBundlePath()
{
    char path[1024];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    assert(mainBundle);

    CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
    assert(mainBundleURL);

    CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
    assert(cfStringRef);

    CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);

    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);

    return std::string(path);
}
#endif



    Application::Application()
    {
        mFrameListener = 0;
        mRoot = 0;
        #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            mResourcePath = macBundlePath() + "/Contents/Resources/";
        #else
            mResourcePath = "";
        #endif
    }
    /// Standard destructor
    Application::~Application()
    {
    }

    void Application::startApplication()
    {
        if (!setup())
            return;

        LogManager::getSingletonPtr()->logMessage("\n\n\n=================== Starting Ogre rendering system ===================\n");
        mRoot->startRendering();
        mRoot->queueEndRendering();
        destroyScene();
    }

    // These internal methods package up the stages in the startup process
    /** Sets up the application - returns false if the user chooses to abandon configuration. */
    bool Application::setup()
    {

		String pluginsPath;
		// only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
		pluginsPath = mResourcePath + "plugins.cfg";
#endif


        mRoot = OGRE_NEW Root(pluginsPath, mResourcePath + "ogre.cfg", mResourcePath + "Ogre.log");

        setupResources();

        bool carryOn = configure();
        if (!carryOn) return false;

        chooseSceneManager();
        createCamera();
        createViewports();
        createGui();

        // Set default mipmap level (NB some APIs ignore this)
        TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// Create any resource listeners (for loading screens)
		createResourceListener();
		loadResources();
        createScene();
        createFrameListener();

        return true;
    }
    /** Configures the application - returns false if the user chooses to abandon configuration. */
    bool Application::configure()
    {
        mRoot->loadPlugin("Plugin_CgProgramManager");
        if(!mRoot->restoreConfig())
           if( !mRoot->showConfigDialog())
                return false;

        mWindow = mRoot->initialise(true,"King of the road");
        return true;
    }



    void Application::createViewports()
    {
        Viewport* vp = mWindow->addViewport(mCamera);

            vp->setOverlaysEnabled(true);
            vp->setBackgroundColour(ColourValue(0,0,0));
            mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    }

    void Application::setupResources()
    {
        ConfigFile cf;
        cf.load(mResourcePath + "resources.cfg");

        ConfigFile::SectionIterator seci = cf.getSectionIterator();

        String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            ConfigFile::SettingsMultiMap *settings = seci.getNext();
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;

                #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
                ResourceGroupManager::getSingleton().addResourceLocation(
                    String(macBundlePath() + "/" + archName), typeName, secName);
                #else
                ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
                #endif
            }
        }
    }

	void Application::loadResources()
	{
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

