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

            dummy = new GameStaticPhysicObject(world,"Dummy.mesh","",0.001,Vector3(2,2,2));
            dummy->setPosition(Vector3(102,30,-62));
}



bool LoginListener::frameStarted(const FrameEvent& evt)
{
        mKeyboard->capture();
        mMouse->capture();

        if (mTimeUntilNextToggle <= 0)
            mTimeUntilNextToggle = 0.5;

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

        if (mKeyboard->isKeyDown(OIS::KC_E))
             m_world->setShowDebugGeometries(!m_world->getShowDebugGeometries());

    return true;
}

bool LoginListener::collision(Contact* contact)
{
    contact->setBouncyness(0.3);
    contact->setCoulombFriction(18.0);
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
