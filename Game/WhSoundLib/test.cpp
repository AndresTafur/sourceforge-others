#include <stdio.h>
#include "GameSound.h"

int main()
{
   whSoundLib::GameSound obj;

        obj.open("algo.ogg");
        obj.setLoop(true);
        obj.play();


        getchar();
        obj.stop();

}
