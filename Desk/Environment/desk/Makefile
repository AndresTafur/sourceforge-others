Release:
	$(Gui)
	g++ `wx-config --cxxflags` `wx-config --libs` `pkg-config --libs gtk+-2.0`  `wx-config --cxxflags` `pkg-config --cflags gtk+-2.0` -lX11 -laudiere src/*.cpp src/player/*.cpp -o desk
	strip desk
