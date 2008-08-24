
#include <wx/wx.h>
#include <wx/animate.h>

#include "rcids.h"
#include <ClamavEvtListener.hh>
#include <Clamav.hh>
#include <ClamFile.hh>


#ifndef _AVPANEL_H_
#define _AVPANEL_H_

#include "../Scanner.hh"
#include <WhiteHawkClamav.hh>

class AvPanel : public wxPanel, public WhiteHawkClamav::ClamavEvtListener
{
public:


        AvPanel(wxWindow *parent, wxAnimationCtrl *anim,wxString str);

		void OnStart(wxCommandEvent &evt);

		void OnStop(wxCommandEvent &evt);

        void onMove(wxCommandEvent &evt);

        void onDel(wxCommandEvent &evt);

        void OnListItem(wxListEvent &evt);


        void onScan(WhiteHawkClamav::ClamFile &file, int totalFiles);

        void onVirus(WhiteHawkClamav::ClamFile &file);

        void onError(WhiteHawkClamav::ClamFile &file,std::string errtype );

        void onFinish();

protected:

wxAnimationCtrl *anim;
wxGauge         *m_bar;
wxTextCtrl      *m_path;
wxTextCtrl      *m_file;
wxListCtrl      *m_list;
wxButton        *start;
wxButton        *stop;
unsigned long m_total;


DECLARE_EVENT_TABLE()
};
#endif

