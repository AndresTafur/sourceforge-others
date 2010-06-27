#ifndef _THIRDWAR_GUI_H_
#define _THIRDWAR_GUI_H_



#include <Ogre.h>
#include <MyGUI.h>
#include <OIS/OIS.h>
#include <MyGUI_OgrePlatform.h>

namespace ThirdWar
{
    class GUI;
};


/**
 * GUI Class. This class manages everything about mygui
 */
class ThirdWar::GUI : public OIS::MouseListener, public OIS::KeyListener,  public Ogre::FrameListener
{
 private:

            /**
             * Explicit default constructor.
             */
            explicit GUI();

public:

            /**
             *  Singleton, Obtains the singleton object of this class as a reference.
             *  @return Reference to the singleton object.
             */
            static ThirdWar::GUI& getInstance();

            /**
             *  Singleton, Obtains the singleton object of this class as a pointer.
             *  @return Pointer to the singleton object.
             */
            static ThirdWar::GUI* getInstancePtr();

            /**
             *  Button clicked event, Performs an operation when a button has been clicked.
             *  @param _widget Button of the event.
             */
            void buttonClicked(MyGUI::WidgetPtr _widget);

            /**
             *  MouseMoved event, Performs an operation when the mouse has been moved.
             *  @param evt Mouse coordinates.
             *  @return true if everithyng i Ok. false otherwise.
             */
            bool mouseMoved(const OIS::MouseEvent &evt);

            /**
             *  MousePressed event, Performs an operation when a mouse button has been presed.
             *  @param evt Mouse Coordinates.
             *  @param id  Mouse button id.
             *  @return true if everithyng i Ok. false otherwise.
             */
            bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

            /**
             *  MousePressed event, Performs an operation when a mouse button has been presed.
             *  @param evt Mouse Coordinates.
             *  @param id  Mouse button id.
             *  @return true if everithyng i Ok. false otherwise.
             */
            bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);


            /**
             *  KeyPressed event, Performs an operation when a key has been presed.
             *  @param arg Key information.
             *  @return true if everithyng i Ok. false otherwise.
             */
            bool keyPressed( const OIS::KeyEvent &arg );


            /**
             *  KeyPressed event, Performs an operation when a key has been presed.
             *  @param arg Key information.
             *  @return true if everithyng i Ok. false otherwise.
             */
            bool keyReleased( const OIS::KeyEvent &arg );


            /**
             *  On frame entered. Updates the devices state every frame.
             *  @param evt Frame information.
             *  @return true if everything is OK.
             */
            bool frameStarted(const Ogre::FrameEvent &evt);


            /**
             *  Start  OIS. Initiallizes Mouse,Keyboard devices, must be called at the very beginning.
             *  @param wnd Render window.
             *  @param SceneMgr Current scene manager.
             */
            void initialize(Ogre::RenderWindow *wnd,Ogre::SceneManager *sceneMgr);


            /**
             *  Load a layout. Loads a set of MyGUI windows defined in the layout file.
             *  @param layout Path to the .layout file.
             */
            void load(std::string layout);

            /**
             *  Sets a scene manager. Changes the current scene manager.
             *  @param mgr New scene manager.
             *  @deprecated
             */
            void setSceneManager(Ogre::SceneManager *mgr);

            /**
             *  Obtains a widget. Obtains a MyGUI widget based on its name.
             *  @param str Widget name.
             *  @return MyGUI Widget pointer.
             */
            MyGUI::WidgetPtr getWindow(std::string str);


            /**
             *  Frees everything. Release devices and Mygui through clean.
             */

            static void destroy();

protected:

            /**
             * Frees everything. Releases everything within the singleton object.
             */

            void clean();

private:
/**
 * Singleton.
 */
static ThirdWar::GUI  *sm_instance;

/**
 * MyGui renger.
 */
MyGUI::OgrePlatform* mPlatform;

/**
 * MyGUI manager.
 */
MyGUI::Gui *mGUI;
};
#endif
