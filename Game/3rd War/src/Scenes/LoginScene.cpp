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
        mFrameListener = new LoginListener(mWindow, mCamera,m_time_step,m_world,mSceneMgr);
        Ogre::Root::getSingletonPtr()->addFrameListener(mFrameListener);
        Ogre::Root::getSingletonPtr()->addFrameListener(this);
    }


    void LoginScene::createGui()
    {
        ThirdWar::GUI::getInstancePtr()->initialize(mWindow,mSceneMgr);
        ThirdWar::GUI::getInstancePtr()->load("Login.layout");
    }


    void LoginScene::createCamera()
    {
        mCamera = mSceneMgr->createCamera("LoginSceneCamera");

       // mCamera->setPosition(Vector3(0,0,0));//75,-7,-500
        mCamera->setPosition(Vector3(95,-7,-500));//75,-7,-500
       // mCamera->lookAt( Ogre::Vector3(75,0,0));//75,7,7
        mCamera->lookAt( Ogre::Vector3(85,7,7));//75,7,7

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
     GameStaticPhysicObject *barricada;
     ColourValue fadeColour(0.8, 0.8, 0.8);
     GameObject *how;


            m_currPoint = 0;
            m_factor  = 0.02;
            m_lauched = false;
            m_change = false;
            val = 0;
            m_farClip = 0;

            m_points.push_back( Vector3(95,0,-15) );


            mSceneMgr->setFog(FOG_LINEAR, fadeColour, 0.0, 10, 1000);
            mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));
            mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
            mSceneMgr->setShadowColour(ColourValue(0.5,0.5,0.5));
            mSceneMgr->setSkyDome(true,"Examples/CloudySky");



            m_world = new OgreOde::World(mSceneMgr);
            m_world->setGravity(Vector3(0,-9.80665,0));
            m_world->setCFM(10e-5);
            m_world->setERP(0.8);
            m_world->setAutoSleep(true);
            m_world->setContactCorrectionVelocity(1.0);


                    m_ground  = new GameObject(mSceneMgr,"Track.mesh");
            m_track = OgreOde::EntityInformer(m_ground->getEntity()).createStaticTriangleMesh(m_world, m_world->getDefaultSpace());




            for(int j=0;j<4;j++)
                for(int i=0;i<10;i++)
                {
                    barricada  = new   GameStaticPhysicObject(m_world,"Costal.mesh", "",Vector3(21,1.8,9));
                    barricada->setPosition(Vector3(22*i,-10+2*j,0));//20
                    m_meshes.push_back(barricada);
                }

            how  = new GameObject(mSceneMgr,"Howitzer.mesh");
            how->getNode()->setPosition(100,-4,10);
            how->getNode()->pitch(Degree(-81));
            m_meshes.push_back(how);

    }


    bool LoginScene::frameStarted(const FrameEvent& evt)
    {
     float dist;
     Vector3 toCam;
     Vector3 expVect;
     int index = 0;
     GameStaticPhysicObject *obj;



            dist = mCamera->getPosition().distance(m_points[m_currPoint]);

            if( 20 > dist && dist > -20 && !m_change)
            {
                m_currPoint++;
                m_change = true;

                if( m_currPoint == m_points.size()  )
                    m_currPoint--;

            }


            if( 45 > dist && dist > -45 && !m_lauched )
            {

                for(int j=0;j<4;j++)
                    for(int i=0;i<10;i++)
                    {
                        obj = static_cast<GameStaticPhysicObject*>(m_meshes.at(index));
                        expVect = ( obj->getBody()->getPosition() - Vector3(102,-11,-62));

                        if(j > 0)
                        {
                            if( i == 4 || i == 5 )
                               obj->getBody()->addForce(expVect*15*j);
                            else if( i == 3 || i == 6 )
                               obj->getBody()->addForce(expVect*10*j);
                            else if( i == 2 || i == 7 )
                               obj->getBody()->addForce(expVect*7*j);
                        }
                        index++;
                    }

                m_lauched  = true;

            }

            if( !m_lauched || !m_change )
            {
                if( val < 40)
                    val+=0.8;
                mCamera->move(Vector3(0,0,val) );
                mCamera->lookAt( Ogre::Vector3(95,7,7));

            }
            else if( m_farClip < 0.8 )
            {
                mSceneMgr->setFog(FOG_LINEAR, ColourValue(0.0+m_farClip,0.0+m_farClip,0.0+m_farClip), 0.0, 1, m_farClip*1000);
                mCamera->move( Vector3(65,-10,50) - mCamera->getPosition());
                mCamera->lookAt( Ogre::Vector3(100,7,7));
                m_farClip += 0.002;
            }

            return true;
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
