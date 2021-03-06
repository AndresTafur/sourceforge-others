#include "GameStaticPhysicObject.h"



GameStaticPhysicObject::GameStaticPhysicObject(OgreOde::World *world,Ogre::String mesh, Ogre::String name,float density, Ogre::Vector3 size) : GameObject(world->getSceneManager(),mesh,name)
{
  OgreOde::BoxMass mass;

        m_body = new OgreOde::Body(world);
        m_node->attachObject(m_body);

        m_geom = new OgreOde::BoxGeometry(size, world, world->getDefaultSpace());

        mass =  OgreOde::BoxMass(1,size);
        mass.setDensity(density,size);
        m_body->setMass(mass);
        m_geom->setBody(m_body);

 }


 void GameStaticPhysicObject::setPosition(Ogre::Vector3 pos)
 {
    m_body->setPosition(pos);
    m_node->setPosition(pos);
  }

