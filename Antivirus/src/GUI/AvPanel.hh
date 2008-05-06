
#include <wx/wx.h>
#include <wx/animate.h>

#include "rcids.h"
#include <ClamavEvtListener.hh>
#include <Clamav.hh>
#include <ClamFile.hh>


#ifndef _AVPANEL_H_
#define _AVPANEL_H_


class AvPanel : public wxPanel, public WhiteHawkClamav::ClamavEvtListener
{
public:


        AvPanel(wxWindow *parent, wxAnimationCtrl *anim, WhiteHawkClamav::Clamav *mgr);


        void setPath(wxString path);

		void onVirus(WhiteHawkClamav::ClamFile file);
		void onScan(WhiteHawkClamav::ClamFile fileName);


		void onFinish();


		void onError(WhiteHawkClamav::ClamFile file,std::string errtype );


		void OnStart(wxCommandEvent &evt);

		void OnStop(wxCommandEvent &evt);

        void onMove(wxCommandEvent &evt);

        void onDel(wxCommandEvent &evt);

        void OnListItem(wxListEvent &evt);

protected:

wxAnimationCtrl *anim;
wxGauge         *bar;
wxTextCtrl      *file;
wxListCtrl      *list;
wxButton        *start;
wxButton        *stop;
unsigned long m_total;

WhiteHawkClamav::Clamav  *mgr;
wxString path;

DECLARE_EVENT_TABLE()
};
#endif

