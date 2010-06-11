#ifndef _PLAYER_FLAG_HH_
#define _PLAYER_FLAG_HH_

#include "../GameObject.h"

class PlayerFlag : public GameObject
{
 public:

        PlayerFlag( Ogre::SceneManager *sceneMgr, double secs, const Ogre::Vector3 &vect);

        inline void startTime() { m_time1 = time(0); };

        inline void addSecs(double secs) { m_secs += secs;}

        inline float getSecs() { return (m_secs - difftime(time(0), m_time1)); }

        std::string getFormatedTime();

 private:
 time_t m_time1;
 float m_secs;
};
#endif
