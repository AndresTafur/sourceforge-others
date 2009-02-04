#ifndef _INOTIFIER_LISTENER_HH_
#define _INOTIFIER_LISTENER_HH_


class WhiteHawkUtil::InotifierEvtListener
{
public:

    inline virtual void onCreate(struct inotify_event *evt){};

    inline virtual void onAcess(struct inotify_event *evt){};

    inline virtual void onModify(struct inotify_event *evt){};

    inline virtual void onAttrib(struct inotify_event *evt){};

    inline virtual void onClose(struct inotify_event *evt){};

    inline virtual void onCloseNoWrite(struct inotify_event *evt){};

    inline virtual void onCloseWrite(struct inotify_event *evt){};

    inline virtual void onOpen(struct inotify_event *evt){};

    inline virtual void onMoved(struct inotify_event *evt){};

    inline virtual void onMovedFrom(struct inotify_event *evt){};

    inline virtual void onMovedTo(struct inotify_event *evt){};

    inline virtual void onDelete(struct inotify_event *evt){};

    inline virtual void onDeleteSelf(struct inotify_event *evt){};

    inline virtual void onAnyEvent(struct inotify_event *evt){};


};

#endif
