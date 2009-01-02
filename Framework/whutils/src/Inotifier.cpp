#include "Inotifier.hh"

int WhiteHawkSystem::Inotifier::m_infd = -1;


        WhiteHawkSystem::Inotifier::Inotifier(AbstractFile &file, int fd)
        {
            m_fd   = fd;
            m_file = file;
        }



        WhiteHawkSystem::Inotifier* WhiteHawkSystem::Inotifier::createNotifier(AbstractFile &file)
        {
            if( m_infd < 0)
                m_infd = inotify_init();

                return new Inotifier(file,m_infd);
        }


        void  WhiteHawkSystem::Inotifier::run()
        {
          int size  = sizeof (struct inotify_event);
          int bsize =  1024 * (size + 32);
          int len, i;

            do
            {
               char buf[bsize];

                    i = 0;

                    len = read (m_fd, buf, bsize);

                    if (len == 0)
                         bsize += 16;

                    while (i < len)
                    {
                        struct inotify_event *event;

                        event = (struct inotify_event *) &buf[i];


                        if(event->mask & IN_ACCESS)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onAcess(event);
                        else if(event->mask & IN_MODIFY)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onModify(event);
                        else if(event->mask & IN_ATTRIB)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onAttrib(event);

                        else if(event->mask & IN_CLOSE)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onClose(event);
                        else if(event->mask & IN_CLOSE_NOWRITE)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onCloseNoWrite(event);
                        else if(event->mask & IN_CLOSE_WRITE)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onCloseNoWrite(event);
                        else if(event->mask & IN_OPEN)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onOpen(event);
                        else if(event->mask & IN_MOVE)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onMoved(event);
                        else if(event->mask & IN_MOVED_FROM)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onMovedFrom(event);
                        else if(event->mask & IN_MOVED_TO)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onMovedTo(event);
                        else if(event->mask & IN_DELETE)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onDelete(event);
                        else if(event->mask & IN_DELETE_SELF)
                           for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onDeleteSelf(event);
                        for(std::list<InotifierEvtListener*>::iterator iter = m_lstners.begin(); iter != m_lstners.end(); iter++)
                                 (*iter)->onAnyEvent(event);

                        i += size + event->len; //next event (since read fullfits more than 1 event at a time)
                    }

            }while(m_watch);
        }


        void WhiteHawkSystem::Inotifier::addListener( InotifierEvtListener *obj)
        {
            m_lstners.push_back(obj);
        }

        void WhiteHawkSystem::Inotifier::removeListener( InotifierEvtListener *obj)
        {
           m_lstners.remove (obj);
        }


        void WhiteHawkSystem::Inotifier::startWatching(int mask)
        {
            m_wd = inotify_add_watch (m_fd, m_file.getFullName().c_str(), mask);


            if( m_wd < 0)
                throw (Exception("Failed adding watch","WhiteHawkSystem::Inotifier::startWatching()"));

            m_watch = true;

            this->startThread();
        }

        void WhiteHawkSystem::Inotifier::stopWatching()
        {
            m_watch = false;

            if( inotify_rm_watch (m_fd, m_wd) )
              throw (Exception("Failed stopping watch","WhiteHawkSystem::Inotifier::stopWatching()"));

        }


        void WhiteHawkSystem::Inotifier::closeInotify()
        {
            if( close ( m_infd ) )
                 throw (Exception("Failed stopping inotify fd","WhiteHawkSystem::Inotifier::Destroy()"));
        }
