#include "LoginListener.h"

#include "GameStaticPhysicObject.h"

LoginListener::LoginListener(RenderWindow* win, Camera* cam, Real time_step, OgreOde::World *world,Ogre::SceneManager *sm) : ApplicationFrameListener(win, cam)
{
            m_paused  = false;
            m_world   = world;
            m_cam     = cam;


            m_stepper = new OgreOde::StepHandler(m_world, OgreOde::StepHandler::QuickStep, time_step, 0.25, 1);
            m_stepper = new OgreOde::ForwardFixedStepHandler(m_world, StepHandler::QuickStep, time_step, 0.25, 1);
            m_stepper->setAutomatic(OgreOde::StepHandler::AutoMode_PostFrame, Ogre::Root::getSingletonPtr());
            Root::getSingleton().setFrameSmoothingPeriod(5.0f);



            dummy = new GameStaticPhysicObject(world,"Dummy.mesh","",Vector3(2,2,2));
            dummy->setPosition(Vector3(102,30,-62));

}




bool LoginListener::frameStarted(const FrameEvent& evt)
{

        mKeyboard->capture();
        mMouse->capture();

        if (mTimeUntilNextToggle <= 0)
            mTimeUntilNextToggle = 0.5;

        /*if(!m_stepper->isPaused())
              for( std::list<Truck*>::iterator it = m_trucks.begin(); it != m_trucks.end(); it++)
                          (*it)->frameStarted(evt);*/

        return true;
}



bool LoginListener::processUnbufferedKeyInput(const FrameEvent &event)
{


        if( mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q) )
			return false;


    	if(mKeyboard->isKeyDown(OIS::KC_I) )
		{
			std::ostringstream ss;
			ss << "screenshot_" << ++mNumScreenShots << ".png";
			mWindow->writeContentsToFile(ss.str());
			mTimeUntilNextToggle = 0.5;
		}


    	if(mKeyboard->isKeyDown(OIS::KC_UP) )
            dummy->getBody()->addForce(Vector3(0,0,1) );
    	if(mKeyboard->isKeyDown(OIS::KC_DOWN) )
            dummy->getBody()->addForce(Vector3(0,0,-1) );
    	if(mKeyboard->isKeyDown(OIS::KC_RIGHT) )
            dummy->getBody()->addForce(Vector3(-1,0,0) );
    	if(mKeyboard->isKeyDown(OIS::KC_LEFT) )
            dummy->getBody()->addForce(Vector3(1,0,0) );

    	if(mKeyboard->isKeyDown(OIS::KC_W) )
            dummy->getBody()->addForce(Vector3(00,5,0) );

    	if(mKeyboard->isKeyDown(OIS::KC_S) )
            dummy->getBody()->addForce(Vector3(00,-5,0) );


    	if(mKeyboard->isKeyDown(OIS::KC_P) )
                fprintf(stderr,"%f, %f, %f",dummy->getNode()->getPosition().x,dummy->getNode()->getPosition().y,dummy->getNode()->getPosition().z);


    /*
        if( mKeyboard->isKeyDown(OIS::KC_N) )
            SoundManager::getInstance()->playNextSong();
        else if( mKeyboard->isKeyDown(OIS::KC_B) )
            SoundManager::getInstance()->playPrevSong();
*/

        if (mKeyboard->isKeyDown(OIS::KC_E))
             m_world->setShowDebugGeometries(!m_world->getShowDebugGeometries());

		if( mKeyboard->isKeyDown(OIS::KC_F2))
            Ogre::Root::getSingleton().showConfigDialog();
    return true;
}



LoginListener::~LoginListener()
{
    WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	if(m_stepper)
        delete m_stepper;

    m_stepper=0;
}
