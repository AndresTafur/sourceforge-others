#ifndef _GAMEPHYSICSTATICOBJECT_
#define _GAMEPHYSICSTATICOBJECT_

#include "GameObject.h"
#include <OgreOde_Core.h>

class GameStaticPhysicObject : public GameObject
{
public:

        GameStaticPhysicObject(OgreOde::World *world,Ogre::String mesh, Ogre::String name, Ogre::Vector3 size = Ogre::Vector3(1,1,1));

        inline OgreOde::Body* getBody() { return m_body; }

        void setGeometry(OgreOde::Geometry *geom);

private:
OgreOde::Body  *m_body;
OgreOde::Geometry *m_geom;
};
#endif
