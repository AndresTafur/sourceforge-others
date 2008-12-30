bin_PROGRAMS = whclamav


whclamav_SOURCES = Scanner.cpp whitehawkav.cpp \
		   GUI/AvFrame.cpp  \
		   GUI/TrayIcon.cpp \
		   GUI/AvPanel.cpp \
		   GUI/StatusPanel.cpp \
		   GUI/UpdateDlg.cpp \
		   GUI/ConfigDialog.cpp \
		   ClamLayer/ClamavInstance.cpp \
		   ClamLayer/ClamFile.cpp \
		   ClamLayer/ClamavScanner.cpp

whclamav_CPPFLAGS = -DDATA_DIR=\"$(datadir)\" -DLOCALEDIR=\"$(localedir)\"

whclamav_LDADD = @LIBINTL@ $(WX_LIBS) $(WH_LIBS) $(CLAM_LIBS)  -lclamav

