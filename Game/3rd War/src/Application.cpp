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
        mRoot = 0;
        #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            mResourcePath = macBundlePath() + "/Contents/Resources/";
        #else
            mResourcePath = "";
        #endif
    }



    void Application::startApplication()
    {
        if (!setup())
            return;

        LogManager::getSingletonPtr()->logMessage("\n\n\n=================== Starting Ogre rendering system ===================\n");
        mRoot->startRendering();
        mRoot->queueEndRendering();
        m_scenes[0]->destroyScene();
    }


    /** Configures the application - returns false if the user chooses to abandon configuration. */
    bool Application::configure()
    {
        if(!mRoot->restoreConfig())
           if( !mRoot->showConfigDialog())
                return false;

        mWindow = mRoot->initialise(true,"3rd War");
        return true;
    }





    // These internal methods package up the stages in the startup process
    /** Sets up the application - returns false if the user chooses to abandon configuration. */
    bool Application::setup()
    {
		String pluginsPath;
		bool carryOn;

                #ifndef OGRE_STATIC_LIB
                    pluginsPath = mResourcePath + "plugins.cfg";
                #endif

                mRoot = OGRE_NEW Root(pluginsPath, mResourcePath + "ogre.cfg", mResourcePath + "Ogre.log");

                setupResources();

                carryOn = configure();

                if (!carryOn)
                    return false;

                // Set default mipmap level (NB some APIs ignore this)
                TextureManager::getSingleton().setDefaultNumMipmaps(5);

                // Create any resource listeners (for loading screens)
                createResourceListener();
                loadResources();


                m_scenes.push_back( new LoginScene(mWindow) );

                m_scenes[0]->createManagers();
                m_scenes[0]->createCameras();
                m_scenes[0]->createGui();
                m_scenes[0]->createScene();
                return true;
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
                ResourceGroupManager::getSingleton().addResourceLocation(String(macBundlePath() + "/" + archName), typeName, secName);
                #else
                ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
                #endif
            }
        }
    }

	void Application::loadResources()
	{
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

    /// Standard destructor
    Application::~Application()
    {
      Ogre::Root::PluginInstanceList list;

        if(mWindow)
            mRoot->detachRenderTarget(mWindow);

        mRoot->getRenderSystem()->unregisterThread();
        mRoot->setRenderSystem(NULL);

        list = mRoot->getInstalledPlugins ();
        for(unsigned int i= 0; i < list.size();i++)
            mRoot->uninstallPlugin (list[i]);

        fprintf(stderr," ================= Deleting last object, expecting segfault (OGRE issue) =================\n\n");
        delete mRoot;
    }
