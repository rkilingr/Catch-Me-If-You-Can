CXXFLAG = -std=c++11
LIBS = -lGL -lGLU -lglut -lSOIL
"CMIYC": main.cpp SOIL.h
	$(CXX) $(CXXFLAG) main.cpp SOIL.h -I. -o $@ $(LIBS) 
