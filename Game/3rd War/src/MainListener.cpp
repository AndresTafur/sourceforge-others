#include "MainListener.h"

MainListener::MainListener(RenderWindow* win, Camera* cam, Real time_step, Root *root, OgreOde::World *world) : ApplicationFrameListener(win, cam)
{
            m_paused = false;
            _world   = world;
            m_cam    = cam;

            _stepper = new OgreOde::StepHandler(_world, OgreOde::StepHandler::QuickStep, time_step, 0.25, 1);
            _stepper = new OgreOde::ForwardFixedStepHandler(_world, StepHandler::QuickStep, time_step, 0.25, 1);
            _stepper->setAutomatic(OgreOde::StepHandler::AutoMode_PostFrame, root);
            Root::getSingleton().setFrameSmoothingPeriod(5.0f);
            m_trucks.push_back(new PlayerTruck(mCamera,_world,mKeyboard) );
   //         m_trucks.push_back(new Truck(_world,Vector3(-400,0,50)) );
}




bool MainListener::frameStarted(const FrameEvent& evt)
{
        mKeyboard->capture();
        mMouse->capture();

        if (mTimeUntilNextToggle <= 0)
            mTimeUntilNextToggle = 0.5;

        if(!_stepper->isPaused())
              for( std::list<Truck*>::iterator it = m_trucks.begin(); it != m_trucks.end(); it++)
                          (*it)->frameStarted(evt);

        return true;
}


bool MainListener::processUnbufferedKeyInput(const FrameEvent &event)
{/*
        if( mKeyboard->isKeyDown(OIS::KC_N) )
            SoundManager::getInstance()->playNextSong();
        else if( mKeyboard->isKeyDown(OIS::KC_B) )
            SoundManager::getInstance()->playPrevSong();
*/

        if (mKeyboard->isKeyDown(OIS::KC_E))
             _world->setShowDebugGeometries(!_world->getShowDebugGeometries());

        if(mKeyboard->isKeyDown(OIS::KC_P))
        {
             m_paused = !m_paused;
             _stepper->pause(m_paused);
             for( std::list<Truck*>::iterator it = m_trucks.begin(); it != m_trucks.end(); it++)
                       (*it)->pause(m_paused);
        }
		if( mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q) )
			return false;

    	if(mKeyboard->isKeyDown(OIS::KC_I) /*&& mTimeUntilNextToggle <= 0*/)
		{
			std::ostringstream ss;
			ss << "screenshot_" << ++mNumScreenShots << ".png";
			mWindow->writeContentsToFile(ss.str());
			mTimeUntilNextToggle = 0.5;
		}
		if( mKeyboard->isKeyDown(OIS::KC_F2))
            Ogre::Root::getSingleton().showConfigDialog();


        for( std::list<Truck*>::iterator it = m_trucks.begin(); it != m_trucks.end(); it++)
               (*it)->toggle(event);
    return true;
}



MainListener::~MainListener()
{
		WindowEventUtilities::removeWindowEventListener(mWindow, this);
		windowClosed(mWindow);


	if(_stepper) delete _stepper; _stepper=0;

    for( std::list<Truck*>::iterator it = m_trucks.begin(); it != m_trucks.end(); it++)
       if( (*it)) delete (*it);
}
