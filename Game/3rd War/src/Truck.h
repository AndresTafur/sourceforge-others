#ifndef _TRUCK_H
#define _TRUCK_H

#include <Ogre.h>
#include <OgreConfigFile.h>
#include <OgreOde_Core.h>
#include <OgreOde_Prefab.h>
#include <OgreOde_Loader.h>
#include <OIS/OIS.h>

#include "player/PlayerFlag.h"


using namespace Ogre;
using namespace OgreOde;



class Truck
{
 public:

        Truck(OgreOde::World *world, Ogre::Vector3 vect = Ogre::Vector3(-400,10,50) );

        void setPosition( Ogre::Vector3 &vect);

        virtual void frameStarted(const FrameEvent& evt);

        void pause(bool pausa);

        virtual void toggle(const FrameEvent& evt) {};

        static short getTruckNumber() { return ++sm_truckNum; }

protected:

std::list<PlayerFlag*> m_vectors;
std::list<PlayerFlag*>::iterator iter;

OgreOde_Prefab::Vehicle *_vehicle;
OgreOde_Loader::DotLoader *m_dotOgreOdeLoader;
Ogre::ParticleSystem *_pSys;
OgreOde::StepHandler *_stepper;


float m_prevAng;

bool m_acel;
static short sm_truckNum;
};

#endif
