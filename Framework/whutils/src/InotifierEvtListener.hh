/*  This file is part of WhiteHawkClamav.

    WhiteHawkClamav is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WhiteHawkClamav is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _INOTIFIER_LISTENER_HH_
#define _INOTIFIER_LISTENER_HH_

/**
 * Interface to define listeners for inotify
 * @see Inotify
 */

class WhiteHawkUtil::InotifierEvtListener
{
public:

    /**
     * Called when a file has been created into a watched folder
     * @param evt Event with all required information
     */
    inline virtual void onCreate(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been accesed
     * @param evt Event with all required information
     */
    inline virtual void onAcess(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been modified
     * @param evt Event with all required information
     */
    inline virtual void onModify(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder atrributes has been altered
     * @param evt Event with all required information
     */
    inline virtual void onAttrib(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been closed
     * @param evt Event with all required information
     */
    inline virtual void onClose(struct inotify_event *evt){};


    /**
     * Called when a whatched file/folder has been closed without writting.
     * @param evt Event with all required information
     */
    inline virtual void onCloseNoWrite(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been closed with writting.
     * @param evt Event with all required information
     */
    inline virtual void onCloseWrite(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been opened.
     * @param evt Event with all required information
     */
    inline virtual void onOpen(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been moved.
     * @param evt Event with all required information
     */
     inline virtual void onMoved(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been moved, giving the from information.
     * @param evt Event with all required information
     */
     inline virtual void onMovedFrom(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been moved, giving the to information.
     * @param evt Event with all required information
     */
     inline virtual void onMovedTo(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been deleted.
     * @param evt Event with all required information
     */
     inline virtual void onDelete(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has been deleted by itself.
     * @param evt Event with all required information
     */
     inline virtual void onDeleteSelf(struct inotify_event *evt){};

    /**
     * Called when a whatched file/folder has notfied any event (even those already catched).
     * @param evt Event with all required information
     */
     inline virtual void onAnyEvent(struct inotify_event *evt){};


};

#endif
