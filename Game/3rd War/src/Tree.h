#ifndef _TREE_H_
#define _TREE_H_

#include "GameObject.h"
#include <OgreOde_Core.h>

class Tree  : public GameObject
{
public:

        Tree(OgreOde::World *world, const Ogre::Vector2 &size);

        ~Tree();

private:
OgreOde::Body  *m_body;
OgreOde::BoxGeometry *m_geom;
};
#endif
