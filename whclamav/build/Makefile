Release: 
	g++  `clamav-config --libs` `clamav-config --libs` `wx-config --cxxflags` `wx-config --libs`  -I ../../Framework/System/ -L ../../Framework/System/ -lclamav -lpthread ../src/*.cpp ../src/FileManager/*.cpp -o ../whitehawkav  -lwhsystem 
	strip ../whitehawkav
