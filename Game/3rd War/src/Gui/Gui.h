#ifndef _KOR_GUI_H_
#define _KOR_GUI_H_



#include <Ogre.h>
#include <MyGUI.h>
#include <OIS/OIS.h>
#include <MyGUI_OgrePlatform.h>

namespace ThirdWar
{
    class GUI;
};


class ThirdWar::GUI : public OIS::MouseListener, public Ogre::FrameListener
{
 private:

            explicit GUI();

public:
            static ThirdWar::GUI& getInstance();

            static ThirdWar::GUI* getInstancePtr();

            void buttonClicked(MyGUI::WidgetPtr _widget);

            bool mouseMoved(const OIS::MouseEvent &evt);

            bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

            bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);


            bool frameStarted(const Ogre::FrameEvent &evt);

            void initialize(Ogre::RenderWindow *wnd,Ogre::SceneManager *sceneMgr);

            void load(std::string layout);

            void setSceneManager(Ogre::SceneManager *mgr);

            MyGUI::WidgetPtr getWindow(std::string str);

            static void destroy();

protected:

            void clean();

private:
static ThirdWar::GUI  *sm_instance;
MyGUI::OgrePlatform* mPlatform;
MyGUI::Gui *mGUI;
};
#endif
