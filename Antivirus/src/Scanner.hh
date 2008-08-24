#ifndef _SCANNER_
#define _SCANNER_

#include <WhiteHawkClamav.hh>
#include <ClamavEvtListener.hh>
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
