OBJDIR=obj
OUT=bin
LIBDIR=lib
MKDIR=mkdir -p
LIBFLAGS=-lXi -lXmu -lglfw -lGLEW -lGLU -lm -lGL -lglut

$(OBJDIR)/%.o: %.cpp
	g++ -std=c++11 -g -c -o $@ $<

outs:
	$(MKDIR) obj bin

main: $(OBJDIR)/main.o
	g++ -std=c++11 -g -o $(OUT)/main main.cpp $(LIBFLAGS)