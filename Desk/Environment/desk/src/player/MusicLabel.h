
//if we include this file _WITH_MUSIC_ADDON was defined

#ifndef _MUSIC_LABEL_
#define _MUSIC_LABEL_
#include <audiere.h>
#include <wx/wx.h>
#include "WhiteHawkThread.h"



using namespace audiere;

class MusicLabel : public wxBitmapButton, public WhiteHawkThread
{
public:

	MusicLabel(wxWindow *parent, wxString str, wxSize size);


 	void ThreadRoutine();

	bool openFileDlg();

	void openMusic();

	void play();

	void pause();

	void stop();

 	void onAction(wxCommandEvent &evt);

 	void OnClick(wxMouseEvent &evt);

 	void OnRightClick(wxMouseEvent &evt);


protected:
wxMenu *menu, *menu2;
wxString path, str;
wxStaticBitmap *m_bmp;

AudioDevicePtr  device;
OutputStreamPtr sound;
DECLARE_EVENT_TABLE()
};
#endif
