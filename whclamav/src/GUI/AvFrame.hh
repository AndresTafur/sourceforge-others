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

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include "rcids.h"
#include "AvNotebook.h"
#include <wx/taskbar.h>

#ifndef _AVFRAME_H_
#define _AVFRAME_H_


class AvFrame : public wxFrame
{
public:


    AvFrame(wxString path);


    void createMenu();

    void createTrayIcon();

    void onTaskClick(wxTaskBarIconEvent &evt);

    void onTaskLClick(wxTaskBarIconEvent &evt);

    void onHome(wxCommandEvent &evt);

    void onScan(wxCommandEvent &evt);

    void onQuit(wxCommandEvent &evt);

    void onClose(wxCloseEvent &evt);

    void onIconize(wxIconizeEvent &evt);

    void onAbout(wxCommandEvent &evt);


protected:
wxBoxSizer  *m_sizer;
wxPanel	    *m_current;
AvNotebook  *m_note;
StatusPanel *m_status;
wxTaskBarIcon *m_trayIcon;
DECLARE_EVENT_TABLE()

};

#endif
