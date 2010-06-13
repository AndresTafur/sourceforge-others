#ifndef _GAMEPHYSICSTATICOBJECT_
#define _GAMEPHYSICSTATICOBJECT_

#include "GameObject.h"
#include <OgreOde_Core.h>


/**
 * Represents a Game Mesh object within Physics world. Allow an easy api for setting body and geometry.-
 * @see GameObject
 */
class GameStaticPhysicObject : public GameObject
{
public:

        /**
         * Default Constructor. Creates a phyisic  object.
         * @param world Current Physics world.
         * @param mesh Name of the mesh to be loaded.
         * @param name Name to be assigned to this entity.
         * @param size (Optional) Size of the object (in Physics world).
         */
        GameStaticPhysicObject(OgreOde::World *world,Ogre::String mesh, Ogre::String name, Ogre::Vector3 size = Ogre::Vector3(1,1,1));

        /**
         * Obtains its ODE body.
         * @return Ode body.
         */
        inline OgreOde::Body* getBody() { return m_body; }


        void setPosition(Ogre::Vector3 pos);

        /**
         * Set's its geometry
         * @param geom Geometry to be aplied (ODE geom).
         */
        void setGeometry(OgreOde::Geometry *geom);

private:
OgreOde::Body  *m_body;
OgreOde::Geometry *m_geom;
};
#endif
