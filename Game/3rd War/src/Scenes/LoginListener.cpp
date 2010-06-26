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



    void LoginListener::buttonClicked(MyGUI::WidgetPtr _widget)
    {
      MyGUI::ButtonPtr btn =  static_cast<MyGUI::ButtonPtr>(_widget);
      unsigned int xres, yres;


                if( _widget == ThirdWar::GUI::getInstance().getWindow("quitBtn"))
                        Ogre::Root::getSingletonPtr()->queueEndRendering();

                else if(  _widget == ThirdWar::GUI::getInstance().getWindow("accountBtn"))
                {
                        static_cast<MyGUI::WindowPtr>(ThirdWar::GUI::getInstance().getWindow("registrationWnd"))->setVisibleSmooth(true);
                        _widget->setEnabled(false);
                }
                else if(  _widget == ThirdWar::GUI::getInstance().getWindow("creditsBtn"))
                {
                        static_cast<MyGUI::WindowPtr>(ThirdWar::GUI::getInstance().getWindow("creditWnd"))->setVisibleSmooth(true);
                        _widget->setEnabled(false);
                }
                else if(  _widget == ThirdWar::GUI::getInstance().getWindow("optionsBtn"))
                {
                        static_cast<MyGUI::WindowPtr>(ThirdWar::GUI::getInstance().getWindow("optionsWnd"))->setVisibleSmooth(true);
                        _widget->setEnabled(false);
                }
                else if(  _widget == ThirdWar::GUI::getInstance().getWindow("optOkBtn"))
                {
                        MyGUI::ComboBoxPtr combo = static_cast<MyGUI::ComboBoxPtr>(ThirdWar::GUI::getInstance().getWindow("resolVar"));
                        btn = static_cast<MyGUI::ButtonPtr>(ThirdWar::GUI::getInstance().getWindow("fullScrBtn"));

                        if(  combo->getIndexSelected() == 0 )
                        {
                            xres = 800;yres = 600;
                        }
                        else if(  combo->getIndexSelected() == 1 )
                        {
                            xres = 1024;yres = 768;
                        }
                        else if(  combo->getIndexSelected() == 2 )
                        {
                            xres = 1440;yres = 900;
                        }
                        Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->setFullscreen(btn->getButtonPressed(), xres, yres);
                        Ogre::Root::getSingleton().saveConfig();
                }
                else if(  _widget == ThirdWar::GUI::getInstance().getWindow("remSetBtn"))
                    btn->setButtonPressed(!btn->getButtonPressed() );
                else if(  _widget == ThirdWar::GUI::getInstance().getWindow("fullScrBtn"))
                    btn->setButtonPressed(!btn->getButtonPressed() );
    }

    void LoginListener::notifyWindowPressed(MyGUI::WidgetPtr _widget, const std::string& _name)
    {
      MyGUI::WindowPtr window = static_cast<MyGUI::WindowPtr>(_widget);

            if (_name == "close")
            {
                    window->setVisibleSmooth(false);

                    if( _widget ==  ThirdWar::GUI::getInstance().getWindow("registrationWnd") )
                        static_cast<MyGUI::ButtonPtr>(ThirdWar::GUI::getInstance().getWindow("accountBtn"))->setEnabled(true);
                    else if( _widget ==  ThirdWar::GUI::getInstance().getWindow("creditWnd") )
                        static_cast<MyGUI::ButtonPtr>(ThirdWar::GUI::getInstance().getWindow("creditsBtn"))->setEnabled(true);
                    else if( _widget ==  ThirdWar::GUI::getInstance().getWindow("optionsWnd") )
                        static_cast<MyGUI::ButtonPtr>(ThirdWar::GUI::getInstance().getWindow("optionsBtn"))->setEnabled(true);
            }
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
