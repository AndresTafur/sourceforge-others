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

#ifndef _SCANNER_
#define _SCANNER_

#include "ClamLayer/WhiteHawkClamav.hh"
#include "ClamLayer/ClamavEvtListener.hh"
#include <wx/wx.h>

class Scanner : public WhiteHawkClamav::ClamavEvtListener
{
public:

        void setList(wxListCtrl *panel);

        void setFileCtrl(wxTextCtrl *file);

        void setGauge(wxGauge *bar);

    	void onVirus(WhiteHawkClamav::ClamFile &file);

		void onScan(WhiteHawkClamav::ClamFile &fileName, int totalFiles);

        void setPath(wxString path);

		void onFinish();


		void onError(WhiteHawkClamav::ClamFile &file,std::string errtype );

protected:
wxTextCtrl *m_file;
wxListCtrl *m_list;
wxGauge *m_bar;
};


#endif
