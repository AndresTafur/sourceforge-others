#include "GameObject.h"

unsigned int GameObject::sm_num = 0;


GameObject::GameObject( Ogre::SceneManager *sceneMgr, Ogre::String mesh,std::string name)
{
        if(name.empty())
        {
            char temp[30];
            sprintf(temp,"Mesh%i",GameObject::getMeshNum());
            name = temp;
        }

        m_entity =  sceneMgr->createEntity( name, mesh);
        m_node   = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
        m_node->attachObject(m_entity);
        m_entity->setCastShadows(true);
}


GameObject::GameObject(Ogre::SceneManager *sceneMgr, Ogre::Entity *entity,std::string name)
{
       if(name.empty())
        {
            char temp[30];
            sprintf(temp,"Mesh%i",GameObject::getMeshNum());
            name = temp;
        }

        m_entity =  entity->clone(name);
        m_node   = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
        m_node->attachObject(m_entity);
        m_entity->setCastShadows(true);
}




GameObject::~GameObject()
{
}
