#include <list>

#include "inotify-nosys.h"

#include "Thread.hh"
#include "Exception.hh"
#include "AbstractFile.hh"
#include "InotifierEvtListener.hh"


#ifndef _INOTIFIER_HH_
#define _INOTIFIER_HH_

class WhiteHawkSystem::Inotifier : public WhiteHawkSystem::Thread
{
private:

        Inotifier(AbstractFile &file, int fd);

public:

        static Inotifier* createNotifier(AbstractFile &file);

        void run();

        void addListener( InotifierEvtListener *obj);

        void removeListener( InotifierEvtListener *obj);

        void startWatching(int mask = IN_ALL_EVENTS);

        void stopWatching();

        static void closeInotify();

private:
int m_wd;
int m_fd;
bool m_watch;
AbstractFile m_file;
std::list<InotifierEvtListener*> m_lstners;
static int m_infd;
};
#endif
