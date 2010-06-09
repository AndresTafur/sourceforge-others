#include "Tree.h"


Tree::Tree(OgreOde::World *world,const Ogre::Vector2 &size)  : GameObject(world->getSceneManager(),"Type2Tree5.mesh")
{/*
 OgreOde::BoxMass mass;
 Ogre::Vector3 size2(0.05,0.05,0.05);

        m_body = new OgreOde::Body(world);
        m_body->setPosition(m_node->getPosition());
        m_node->attachObject(m_body);


        mass =  OgreOde::BoxMass(0.05,size2);
        mass.setDensity(0.01, size2);

        m_geom = new OgreOde::BoxGeometry(size2,world);

        m_body->setMass(mass);
        m_geom->setBody(m_body);
        m_entity->setUserObject(m_geom);


		m_body->setOrientation(Ogre::Quaternion(Ogre::Radian(5.0), Ogre::Vector3(0,0,0)));
		m_body->setPosition(Ogre::Vector3(-450,120,300));*/

}


Tree::~Tree()
{
    if( m_geom)
        delete m_geom;
    if( m_body)
        delete m_body;

    m_node->detachAllObjects();
    delete m_node;
}
