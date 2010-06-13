#include "LoginListener.h"

#include "GameStaticPhysicObject.h"

LoginListener::LoginListener(RenderWindow* win, Camera* cam, Real time_step, OgreOde::World *world) : ApplicationFrameListener(win, cam)
{
            m_paused  = false;
            m_world   = world;
            m_cam     = cam;
            m_currPoint = 0;
//            flag = false;

            m_stepper = new OgreOde::StepHandler(m_world, OgreOde::StepHandler::QuickStep, time_step, 0.25, 1);
            m_stepper = new OgreOde::ForwardFixedStepHandler(m_world, StepHandler::QuickStep, time_step, 0.25, 1);
            m_stepper->setAutomatic(OgreOde::StepHandler::AutoMode_PostFrame, Ogre::Root::getSingletonPtr());
            Root::getSingleton().setFrameSmoothingPeriod(5.0f);


            m_points.push_back( Vector3(100,100,100) );
            m_points.push_back( Vector3(-70,0,70) );


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
float dist,factor = 0.3;
Vector3 toCam;

        if( mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q) )
			return false;


    	if(mKeyboard->isKeyDown(OIS::KC_I) )
		{
			std::ostringstream ss;
			ss << "screenshot_" << ++mNumScreenShots << ".png";
			mWindow->writeContentsToFile(ss.str());
			mTimeUntilNextToggle = 0.5;
		}


       // if(flag == true)
        {
                dist = m_cam->getPosition().distance(m_points[m_currPoint]);
                if( 1 > dist && dist > -1 )
                {
                    m_currPoint++;
                    factor = 0.3;
                    if( m_currPoint == m_points.size()  )
                        m_currPoint--;
                }

                toCam = m_points.at(m_currPoint) - m_cam->getPosition();
                toCam = toCam*factor;

                m_cam->move(toCam);
                mCamera->lookAt( Ogre::Vector3(0,0,0));
        }

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
