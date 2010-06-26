#include "LoginScene.h"

#include "GameStaticPhysicObject.h"
#include "WeatherManager.h"

    LoginScene::LoginScene(Ogre::RenderWindow  *wnd)
    {
            mWindow = wnd;
        	m_world = 0;
            m_time_step = 0.01;
            m_track = 0;
    }



    void LoginScene::createGui()
    {
      ThirdWar::GUI *gui = ThirdWar::GUI::getInstancePtr();
      MyGUI::ButtonPtr btn = 0;
      MyGUI::WindowPtr wnd = 0;
      LoginListener *ptr = static_cast<LoginListener*>(mFrameListener);


        gui->initialize(mWindow,mSceneMgr);
        gui->load("Login.layout");

        btn = static_cast<MyGUI::ButtonPtr>(gui->getWindow("quitBtn"));
        btn->eventMouseButtonClick = MyGUI::newDelegate(ptr, &LoginListener::buttonClicked );

        btn = static_cast<MyGUI::ButtonPtr>(gui->getWindow("accountBtn"));
        btn->eventMouseButtonClick = MyGUI::newDelegate(ptr, &LoginListener::buttonClicked);


        btn = static_cast<MyGUI::ButtonPtr>(gui->getWindow("optionsBtn"));
        btn->eventMouseButtonClick = MyGUI::newDelegate(ptr, &LoginListener::buttonClicked );

        btn = static_cast<MyGUI::ButtonPtr>(gui->getWindow("creditsBtn"));
        btn->eventMouseButtonClick = MyGUI::newDelegate(ptr, &LoginListener::buttonClicked);


        btn = static_cast<MyGUI::ButtonPtr>(gui->getWindow("loginBTN"));
        btn->eventMouseButtonClick = MyGUI::newDelegate(ptr, &LoginListener::buttonClicked);

        btn = static_cast<MyGUI::ButtonPtr>(gui->getWindow("remSetBtn"));
        btn->eventMouseButtonClick = MyGUI::newDelegate(ptr, &LoginListener::buttonClicked);

        btn = static_cast<MyGUI::ButtonPtr>(gui->getWindow("optOkBtn"));
        btn->eventMouseButtonClick = MyGUI::newDelegate(ptr, &LoginListener::buttonClicked);

        btn = static_cast<MyGUI::ButtonPtr>(gui->getWindow("fullScrBtn"));
        btn->eventMouseButtonClick = MyGUI::newDelegate(ptr, &LoginListener::buttonClicked);
        btn->setButtonPressed( Ogre::Root::getSingleton().getAutoCreatedWindow()->isFullScreen() );


        wnd = static_cast<MyGUI::WindowPtr>(gui->getWindow("registrationWnd"));
        wnd->eventWindowButtonPressed = MyGUI::newDelegate(ptr, &LoginListener::notifyWindowPressed);

        wnd = static_cast<MyGUI::WindowPtr>(gui->getWindow("creditWnd"));
        wnd->eventWindowButtonPressed = MyGUI::newDelegate(ptr, &LoginListener::notifyWindowPressed);

        wnd = static_cast<MyGUI::WindowPtr>(gui->getWindow("optionsWnd"));
        wnd->eventWindowButtonPressed = MyGUI::newDelegate(ptr, &LoginListener::notifyWindowPressed);
    }


    void LoginScene::createManagers()
    {
        mSceneMgr  = Ogre::Root::getSingletonPtr()->createSceneManager( "OctreeSceneManager", "3rd War" );
        m_world    = new OgreOde::World(mSceneMgr);
        m_world->setGravity(Vector3(0,-9.80665,0));
        m_world->setCFM(10e-5);
        m_world->setERP(0.8);
        m_world->setAutoSleep(true);
        m_world->setContactCorrectionVelocity(1.0);
        m_world->getDefaultSpace()->setInternalCollisions(true);

        WeatherManager::getInstancePtr()->setRenderWindow(mWindow);
        WeatherManager::getInstancePtr()->setSceneManager(mSceneMgr);

        mFrameListener = new LoginListener(mWindow, mCamera,m_time_step,m_world,mSceneMgr);
        Ogre::Root::getSingletonPtr()->addFrameListener(mFrameListener);
        Ogre::Root::getSingletonPtr()->addFrameListener(this);
        m_world->setCollisionListener(mFrameListener);
    }



    void LoginScene::createCameras()
    {
     Viewport* vp;

          mCamera = mSceneMgr->createCamera("LoginSceneCamera");
        //  mCamera->setPosition(Vector3(35,5,10));//75,-7,-500
          mCamera->setPosition(Vector3(90,7,-500));//75,-7,-500
        //  mCamera->lookAt( Ogre::Vector3(75,5,10));//75,7,7
          mCamera->lookAt( Ogre::Vector3(110,7,7));//75,7,7
          mCamera->setNearClipDistance( 1 );
          mCamera->setFarClipDistance( 500 );


          vp = mWindow->addViewport(mCamera);

          vp->setOverlaysEnabled(true);
          vp->setBackgroundColour(ColourValue(0,100,0));
          mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    }



    void LoginScene::createScene()
    {
     OgreOde::EntityInformer ei;
     GameStaticPhysicObject *barricada;
     GameStaticPhysicObject *how;
     GameObject *asta,*flag;
     AnimationState *animationState;


            m_currPoint = 0;
            m_factor  = 0.02;
            m_lauched = false;
            m_change = false;
            val = 0;
            m_farClip = 0;


            WeatherManager::getInstancePtr()->setFoggy();
            mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
            mSceneMgr->setShadowColour(ColourValue(0.5,0.5,0.5));
            mSceneMgr->setSkyDome(true,"CloudySky");
            mSceneMgr->setAmbientLight(ColourValue(0.7,0.7,0.7));

            m_track = OgreOde::EntityInformer((new GameObject(mSceneMgr,"TerrenoLogin.mesh"))->getEntity()).createStaticTriangleMesh(m_world, m_world->getDefaultSpace());

            for(int j=0;j<4;j++)
                for(int i=0;i<10;i++)
                {
                    barricada  = new GameStaticPhysicObject(m_world,"Costal.mesh", "",0.002,Vector3(21,1.8,9));
                    barricada->setPosition(Vector3(22*i,j-10,0));//20
                    m_meshes.push_back(barricada);
                }

            how  = new GameStaticPhysicObject(m_world,"Howitzer.mesh","",0.008,Vector3(18,9,45));
            how->setPosition(Vector3(100,0,27));
            m_meshes.push_back(how);

            flag = new GameObject(mSceneMgr,"Bandera.mesh");
            flag->getNode()->setPosition(150,50,15);
            animationState = flag->getEntity()->getAnimationState("OndearLow3");
            animationState->setLoop(true);
            animationState->setEnabled(true);
            mAnimationStates.push_back(animationState);
            m_meshes.push_back(flag);

            asta = new GameObject(mSceneMgr,"Asta.mesh");
            asta->getNode()->setPosition(150,70,15);
            m_meshes.push_back(asta);


            m_bullet = new GameObject(mSceneMgr,"Bala.mesh");
            m_bullet->getNode()->setPosition(0,0,0);
            animationState = m_bullet->getEntity()->getAnimationState("GirarBone");
            animationState->setLoop(true);
            animationState->setEnabled(true);
            mAnimationStates.push_back(animationState);
            m_meshes.push_back(m_bullet);
    }



    bool LoginScene::frameStarted(const FrameEvent& evt)
    {
     float dist;
     int index = 10;
     Vector3 toCam;
     Vector3 expVect;
     GameStaticPhysicObject *obj;


            for(unsigned int i=0; i< mAnimationStates.size();i++)
                    mAnimationStates[i]->addTime(evt.timeSinceLastFrame);

            dist = mCamera->getPosition().distance(Vector3(90,0,-15));

            if( 18 > dist && dist > -18 && !m_change)  //switch from follow to static camera
                m_change = true;

            if( 45 > dist && dist > -45 && !m_lauched )
            {
                m_lauched  = true;  //already exloded
                for(int j=1;j<4;j++)
                    for(int i=0;i<10;i++,index++)
                    {
                        obj     = static_cast<GameStaticPhysicObject*>(m_meshes.at(index));
                        expVect = obj->getBody()->getPosition() - Vector3(0,0,-62) + Vector3(0,50,5);  //Explosion force

                        if( i == 4 || i == 5 )
                               obj->getBody()->addForce(expVect*20*j); //force stronger on the upper part of the barricade
                        else if( i == 3 || i == 6 )
                               obj->getBody()->addForce(expVect*12*j);
                        else if( i == 2 || i == 7 )
                               obj->getBody()->addForce( (expVect*7*j) );
                    }
            }

            if( !m_lauched || !m_change ) //folow
            {
                val += (val < 5) ? 0.04 : 0;
                mCamera->move(Vector3(0,0,val) );
                mCamera->lookAt( Ogre::Vector3(110,-2,7));
                m_bullet->getNode()->setPosition(mCamera->getPosition()+Vector3(0,-2-val*1.8,25) );
            }
            else if( m_farClip < 0.8 ) //static camera
            {
                mSceneMgr->setFog(FOG_LINEAR, ColourValue(m_farClip,m_farClip,m_farClip), 0.0, 1, m_farClip*1000);
                mCamera->move( Ogre::Vector3(65,-8,50) - mCamera->getPosition());
                mCamera->lookAt( Ogre::Vector3(120,9,7));
                m_farClip += 0.002;

                if(m_bullet)
                {
                  GameStaticPhysicObject *casco;

                        mAnimationStates.pop_back();
                        delete m_bullet;
                        m_bullet = 0;

                        casco = new GameStaticPhysicObject(m_world,"Casco.mesh", "",0.002,Vector3(1,1,1));
                        casco->setPosition(Vector3(85,40,27));
                        casco->getBody()->setTorque(Vector3(0.5,0,0.5));
                        m_meshes.push_back(casco);
                }

            }
            return true;
    }



    void LoginScene::destroyScene()
    {
        mSceneMgr->destroyAllLights();

        if( mCamera)
            mSceneMgr->destroyAllCameras();
        if( mFrameListener)
            OGRE_DELETE mFrameListener; mFrameListener = 0;

        mSceneMgr->clearScene();

        if(mSceneMgr)
            Ogre::Root::getSingletonPtr()->destroySceneManager(mSceneMgr);
        if(m_world)
            delete m_world;
    }
