lib_LTLIBRARIES = libwhwm.la
library_includedir=$(includedir)/whiteHawk/whwm
library_include_HEADERS = *.hh

libwhwm_la_SOURCES = WMEvent.cpp  WMListener.cpp  WMInstance.cpp  WMOutput.cpp WMInput.cpp WMManager.cpp   
libwhwm_la_CXXFLAGS = `pkg-config --cflags libwhsystem-1.0`
libwhwm_la_LDFLAGS = -lwhsystem -lpthread -ltar -ldl `pkg-config --libs libwhsystem-1.0`

