#include "LoginScene.h"


    LoginScene::LoginScene(Ogre::RenderWindow  *wnd)
    {
            mWindow = wnd;
        	m_world = 0;
            m_time_step = 0.01;
            m_track = 0;
    }


    void LoginScene::createFrameListener()
    {
        mFrameListener = new LoginListener(mWindow, mCamera,m_time_step,m_world);
        Ogre::Root::getSingletonPtr()->addFrameListener(mFrameListener);
    }


    void LoginScene::createGui()
    {
        ThirdWar::GUI::getInstancePtr()->initialize(mWindow,mSceneMgr);
        ThirdWar::GUI::getInstancePtr()->load("Login.layout");
    }


    void LoginScene::createCamera()
    {
        mCamera = mSceneMgr->createCamera("LoginSceneCamera");

        mCamera->setPosition(Vector3(-200,0,100));
        mCamera->lookAt(mCamera->getPosition() + Ogre::Vector3(0,0.7,-100));
        mCamera->setNearClipDistance( 1 );
        mCamera->setFarClipDistance( 500 );
    }


    void LoginScene::createViewports()
    {
     Viewport* vp = mWindow->addViewport(mCamera);

            vp->setOverlaysEnabled(true);
            vp->setBackgroundColour(ColourValue(0,0,0));
            mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

    }

    void LoginScene::createSceneManager()
    {
        mSceneMgr  = Ogre::Root::getSingletonPtr()->createSceneManager( "OctreeSceneManager", "3rd War" );
    }


    void LoginScene::createScene()
    {
     OgreOde::EntityInformer ei;
     ColourValue fadeColour(0.1, 0.1, 0.1);


  //          mWindow->getViewport(0)->setBackgroundColour(fadeColour);
 //           mSceneMgr->setFog(FOG_LINEAR, fadeColour, 0.0, 10, 250);
            mSceneMgr->setAmbientLight(ColourValue(0.3, 0.3, 0.3));
            mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
            mSceneMgr->setShadowColour(ColourValue(0.5,0.5,0.5));


            m_world = new OgreOde::World(mSceneMgr);
            m_world->setGravity(Vector3(0,-9.80665,0));
            m_world->setCFM(7e-5);
            m_world->setERP(0.1);
            m_world->setAutoSleep(true);
            m_world->setContactCorrectionVelocity(1.0);


            m_ground  = new GameObject(mSceneMgr,"Track.mesh");

            m_track = OgreOde::EntityInformer(m_ground->getEntity()).createStaticTriangleMesh(m_world, m_world->getDefaultSpace());
    }



    void LoginScene::destroyScene()
    {


        mSceneMgr->destroyAllLights();
        if( mCamera) mSceneMgr->destroyAllCameras();
        if( mFrameListener)OGRE_DELETE mFrameListener; mFrameListener = 0;
        mSceneMgr->clearScene();

        if(mSceneMgr) Ogre::Root::getSingletonPtr()->destroySceneManager(mSceneMgr);

        if(m_world) delete m_world;

    }
