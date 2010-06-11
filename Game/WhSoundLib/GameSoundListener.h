#ifndef _GAME_SOUND_LISTENER_H_
#define _GAME_SOUND_LISTENER_H_


#include "whSoundLib.h"


class whSoundLib::GameSoundListener
{
  public:

            virtual void onFinished(GameSound *sound) = 0;

};
#endif
