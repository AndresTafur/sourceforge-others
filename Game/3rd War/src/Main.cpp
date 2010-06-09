#include "Main.h"

MainApplication::MainApplication()
{
	_world = 0;
	_time_step = 0.01;
	_track = 0;
}


void MainApplication::chooseSceneManager(void)
{
    mSceneMgr      = mRoot->createSceneManager( "OctreeSceneManager", "King of the road" );
}


void MainApplication::createGui()
{

}

void MainApplication::setupResources(void)
{
	Application::setupResources();

}


void MainApplication::createCamera(void)
{
    mCamera = mSceneMgr->createCamera("PlayerCam");

    mCamera->setPosition(Vector3(-400,100,600));
    mCamera->lookAt(mCamera->getPosition() + Ogre::Vector3(0,0.7,-100));
    mCamera->setNearClipDistance( 1 );
    mCamera->setFarClipDistance( 500 );
}


void MainApplication::createScene(void)
{
    OgreOde::EntityInformer ei;


            mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));
            mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
            mSceneMgr->setShadowColour(ColourValue(0.5,0.5,0.5));
            mSceneMgr->setSkyDome(true,"Examples/CloudySky");


            _world = new OgreOde::World(mSceneMgr);
            _world->setGravity(Vector3(0,-9.80665,0));
            _world->setCFM(7e-5);
            _world->setERP(0.1);
            _world->setAutoSleep(true);
            _world->setContactCorrectionVelocity(1.0);


            m_ground  = new GameObject(mSceneMgr,"Track.mesh");

            _track = OgreOde::EntityInformer(m_ground->getEntity()).createStaticTriangleMesh(_world, _world->getDefaultSpace());
//            m_ground->getEntity()->setUserObject (_track);
            createNature();

}


void MainApplication::createNature()
{
Tree *tree;
char name[30];
unsigned short index;
FILE *file = fopen("Trees.dat","r");
int x, z;

  fprintf(stderr," ================= LOADING TREES ... =================\n\n");

      if( file)
        while ( fscanf(file,"[%i,%i]\n",&x,&z) != EOF )
        {
            sprintf(name,"Tree%i",index);
            tree = new Tree(_world,Ogre::Vector2(x,z) );
            tree->getNode()->setPosition(Ogre::Vector3(x,-13,z));
            tree->getEntity()->setCastShadows(false);
            tree->getNode()->yaw( Ogre::Radian( Math::RangeRandom(0,360)));
            ++index;
        }
}


void MainApplication::destroyScene()
{
    if( m_l) mSceneMgr->destroyAllLights();
    mSceneMgr->clearScene();


}

void MainApplication::createFrameListener()
{
    mFrameListener= new MainListener(mWindow, mCamera,_time_step,mRoot, _world);
    mRoot->addFrameListener(mFrameListener);
}


MainApplication::~MainApplication()
{
  Ogre::Root::PluginInstanceList list;

//        KingOfTheRoad::GUI::getInstance().destroy();


        if( mFrameListener)OGRE_DELETE mFrameListener; mFrameListener = 0;
        if( mCamera) mSceneMgr->destroyAllCameras();
        if(_world) delete _world;
        if(mSceneMgr) mRoot->destroySceneManager(mSceneMgr);
        if(mWindow) mRoot->detachRenderTarget(mWindow);


        mRoot->getRenderSystem()->unregisterThread();
        mRoot->setRenderSystem(NULL);

        list = mRoot->getInstalledPlugins ();


        for(unsigned int i= 0; i < list.size();i++)
            mRoot->uninstallPlugin (list[i]);

        fprintf(stderr," ================= Deleting last object, expecting segfault (OGRE issue) =================\n\n");
        delete mRoot;
}


