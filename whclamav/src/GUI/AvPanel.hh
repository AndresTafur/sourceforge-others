/*  This file is part of WhiteHawkClamav,
 *  Copyright (C) 2007 - 2008 Jorge Tafur <darkhawk665@users.sf.net>.
 *
 *   WhiteHawkClamav is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   WhiteHawkClamav is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <wx/wx.h>
#include <wx/dnd.h>
#include <wx/animate.h>
#include <wx/filepicker.h>

#include "rcids.h"
#include "ClamLayer/ClamavEvtListener.hh"
#include "ClamLayer/ClamavInstance.hh"
#include "ClamLayer/ClamFile.hh"


#ifndef _AVPANEL_H_
#define _AVPANEL_H_

#include "../Scanner.hh"
#include "ClamLayer/WhiteHawkClamav.hh"

class AvPanel : public wxPanel, public WhiteHawkClamav::ClamavEvtListener, public wxFileDropTarget
{
public:


        AvPanel(wxWindow *parent, wxAnimationCtrl *anim);

		void OnStart(wxCommandEvent &evt);

		void OnStop(wxCommandEvent &evt);

        void onSelectAll(wxCommandEvent &evt);

        void onMove(wxCommandEvent &evt);

        void onDel(wxCommandEvent &evt);

        void OnListItem(wxListEvent &evt);

        void onSwitchDir(wxFileDirPickerEvent &evt);

        void onScan(WhiteHawkClamav::ClamFile &file, long long totalFiles);

        void onVirus(WhiteHawkClamav::ClamFile &file);

        void onError(WhiteHawkClamav::ClamFile &file,std::string errtype );

        void onFinish();

        bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames);



protected:

wxAnimationCtrl *m_anim;
wxGauge         *m_bar;
wxDirPickerCtrl *m_path;
wxTextCtrl      *m_file;
wxTextCtrl      *m_fold;
wxListCtrl      *m_list;
wxButton        *m_start;
wxButton        *m_stop;
unsigned long m_total;


DECLARE_EVENT_TABLE()
};
#endif

