#include "ApplicationFrameListener.h"


	ApplicationFrameListener::ApplicationFrameListener(RenderWindow* win, Camera* cam, bool bufferedJoy) : mCamera(cam), mCurrentSpeed(0), mWindow(win), mNumScreenShots(0),
		mTimeUntilNextToggle(0), mFiltering(TFO_BILINEAR),
		mAniso(1), mSceneDetailIndex(0), mInputManager(0), mKeyboard(0), mMouse(0)
	{
		OIS::ParamList pl;
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;


                LogManager::getSingletonPtr()->logMessage("\n\n\n=================== Initializing OIS ===================\n");

                win->getCustomAttribute("WINDOW", &windowHnd);
                windowHndStr << windowHnd;
                pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

                mInputManager = OIS::InputManager::createInputSystem( pl );
                mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
                mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse,true));
                const OIS::MouseState &mouseState = mMouse->getMouseState(); // mMouse is type of OIS::Mouse*


                mouseState.width = 800; // your rendering area width
                mouseState.height = 600; // your rendering area height

                mMouse->setEventCallback(ThirdWar::GUI::getInstancePtr());
                mKeyboard->setBuffered(true);

                WindowEventUtilities::addWindowEventListener(mWindow, this);
                windowResized(win);
	}

	void ApplicationFrameListener::windowResized(Ogre::RenderWindow* rw)
	{
		int mWidth = rw->getWidth();
		int mHeight = rw->getHeight();

            if (mMouse)
            {
                const OIS::MouseState &ms = mMouse->getMouseState();
                ms.width = (int)mWidth;
                ms.height = (int)mHeight;
            }
	}


	//Unattach OIS before window shutdown (very important under Linux)
	void ApplicationFrameListener::windowClosed(RenderWindow* rw)
	{
		//Only close for window that created OIS (the main window in these demos)
		if( rw == mWindow )
			if( mInputManager )
			{
			    mWindow->removeAllListeners();
			    mWindow->removeAllViewports ();

			    if( mKeyboard)
			    {

                    mInputManager->destroyInputObject( mKeyboard );
			    }

                OIS::InputManager::destroyInputSystem(mInputManager);
                mInputManager = 0;
                fprintf(stderr,"======== OIS HAS BEEN SHUTTED DOWN ========\n");

			}

	}




	ApplicationFrameListener::~ApplicationFrameListener()
	{


		WindowEventUtilities::removeWindowEventListener(mWindow, this);
		windowClosed(mWindow);
	}

    bool ApplicationFrameListener::frameStarted(const FrameEvent &evt)
    {

        return true;
    }

	// Override frameRenderingQueued event to process that (don't care about frameEnded)
	bool ApplicationFrameListener::frameRenderingQueued(const FrameEvent& evt)
	{

		if(mWindow->isClosed())
            return false;

        mKeyboard->capture();


		//Check if one of the devices is not buffered
		//if( !mKeyboard->buffered())
		{
	            //handle it
			if( processUnbufferedKeyInput(evt) == false )
			return false;

		}

		return true;
	}

	bool ApplicationFrameListener::frameEnded(const FrameEvent& evt)
	{
		return true;
	}
