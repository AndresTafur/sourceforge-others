#include "LoginScene.h"

#include "GameStaticPhysicObject.h"

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

        mCamera->setPosition(Vector3(400,7,400));
        mCamera->lookAt( Ogre::Vector3(0,7,0));
        mCamera->setNearClipDistance( 1 );
        mCamera->setFarClipDistance( 500 );
    }


    void LoginScene::createViewports()
    {
     Viewport* vp = mWindow->addViewport(mCamera);

            vp->setOverlaysEnabled(true);
            vp->setBackgroundColour(ColourValue(0,100,0));
            mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

    }

    void LoginScene::createSceneManager()
    {
        mSceneMgr  = Ogre::Root::getSingletonPtr()->createSceneManager( "OctreeSceneManager", "3rd War" );
    }


    void LoginScene::createScene()
    {
     OgreOde::EntityInformer ei;
     GameStaticPhysicObject *barricada[100];


            mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));
            mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
            mSceneMgr->setShadowColour(ColourValue(0.5,0.5,0.5));
            mSceneMgr->setSkyDome(true,"Examples/CloudySky");



            m_world = new OgreOde::World(mSceneMgr);
            m_world->setGravity(Vector3(0,-9.80665,0));
            m_world->setCFM(7e-5);
            m_world->setERP(0.1);
            m_world->setAutoSleep(true);
            m_world->setContactCorrectionVelocity(1.0);


            m_ground  = new GameObject(mSceneMgr,"Track.mesh");
            m_track = OgreOde::EntityInformer(m_ground->getEntity()).createStaticTriangleMesh(m_world, m_world->getDefaultSpace());


             barricada[0]  = new   GameStaticPhysicObject(m_world,"Costal.mesh", "Sack0");
             barricada[0]->setPosition(Vector3(0,5,0));
             barricada[1]  = new   GameStaticPhysicObject(m_world,"Costal.mesh", "Sack1");
             barricada[1]->setPosition(Vector3(-40,50,0));
             barricada[2]  = new   GameStaticPhysicObject(m_world,"Costal.mesh", "Sack2");
             barricada[2]->setPosition(Vector3(-20,5,0));
             barricada[3]  = new   GameStaticPhysicObject(m_world,"Costal.mesh", "Sack3");
             barricada[3]->setPosition(Vector3(-40,5,0));



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
