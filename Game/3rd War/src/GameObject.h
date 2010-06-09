#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include <Ogre.h>

class GameObject
{
protected:

            static inline unsigned int getMeshNum(){ return ++sm_num;}

public:

            GameObject( Ogre::SceneManager *sceneMgr, Ogre::String mesh, std::string name = "");

            GameObject( Ogre::SceneManager *sceneMgr, Ogre::Entity *entity,std::string name = "");

            inline Ogre::SceneNode* getNode() { return m_node;}

            inline Ogre::Entity* getEntity() { return m_entity;}

            void setMaterial(Ogre::String material);

            ~GameObject();

protected:
Ogre::SceneNode *m_node;
Ogre::Entity    *m_entity;
static unsigned int sm_num;
};
#endif
