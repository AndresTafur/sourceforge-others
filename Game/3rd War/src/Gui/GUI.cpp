#include "Gui.h"


ThirdWar::GUI* ThirdWar::GUI::sm_instance = 0;

        //TODO: Change resolution (get it from ogre)
        ThirdWar::GUI::GUI()
        {

            mGUI = 0;
            Ogre::Root::getSingleton().addFrameListener(this);

        }

        ThirdWar::GUI& ThirdWar::GUI::getInstance()
        {

                if( !sm_instance)
                    sm_instance = new ThirdWar::GUI();
                return *sm_instance;
        }

        ThirdWar::GUI* ThirdWar::GUI::getInstancePtr()
        {

                if( !sm_instance)
                    sm_instance = new ThirdWar::GUI();
                return sm_instance;
        }


        void ThirdWar::GUI::initialize(Ogre::RenderWindow *wnd,Ogre::SceneManager *sceneMgr)
        {
            Ogre::LogManager::getSingletonPtr()->logMessage("\n\n\n ===================  Initializing MyGUI ===================\n");

            mPlatform = new MyGUI::OgrePlatform();
            mPlatform->initialise(wnd, sceneMgr); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*
            mGUI  = new MyGUI::Gui();
            mGUI->initialise();

            mGUI->load("core_theme_black_blue.xml");
            mGUI->load("core_skin.xml");
        }

        void ThirdWar::GUI::load(std::string layout)
        {
            mGUI->load(layout);
        }


        void ThirdWar::GUI::buttonClicked(MyGUI::WidgetPtr _widget)
        {

        }

        MyGUI::WidgetPtr ThirdWar::GUI::getWindow(std::string str)
        {
            MyGUI::Widget *wid = mGUI->findWidgetT(str,false);

            if(!wid)
                Ogre::LogManager::getSingletonPtr()->logMessage("FAILED OBTAINING WIDGET"+ str);

            return wid;
        }


        bool ThirdWar::GUI::mouseMoved(const OIS::MouseEvent &evt)
        {
            mGUI->injectMouseMove(evt.state.X.abs, evt.state.Y.abs,evt.state.Z.abs);
            return true;

        }

        bool ThirdWar::GUI::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
        {
           mGUI->injectMousePress(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
           return true;
        }

        bool ThirdWar::GUI::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
        {
           mGUI->injectMouseRelease(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
           return true;
        }

        bool ThirdWar::GUI::keyPressed( const OIS::KeyEvent &arg )
        {
            mGUI->injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
            return true;
        }

        bool ThirdWar::GUI::keyReleased( const OIS::KeyEvent &arg )
        {
            mGUI->injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
            return true;
        }

        bool ThirdWar::GUI::frameStarted(const Ogre::FrameEvent &evt)
        {

            return true;
        }



        void ThirdWar::GUI::clean()
        {
            mGUI->shutdown();
            delete mGUI;
            mGUI = 0;
            mPlatform->shutdown();
            delete mPlatform;
            mPlatform = 0;
        }

        void ThirdWar::GUI::destroy()
        {
            sm_instance->clean();
            delete sm_instance;
            sm_instance = 0;
        }
