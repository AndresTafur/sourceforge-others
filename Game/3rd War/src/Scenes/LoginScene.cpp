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

        mCamera->setPosition(Vector3(500,7,400));//500-7-400
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

             for(int j=0;j<4;j++)
                for(int i=0;i<10;i++)
                {
                    barricada[0]  = new   GameStaticPhysicObject(m_world,"Costal.mesh", "",Vector3(21,1.8,9));
                    barricada[0]->setPosition(Vector3(22*i,-10+2*j,0));//20
                    barricada[0]->getBody()->addForce(Vector3(0,900,-900));
                }



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
