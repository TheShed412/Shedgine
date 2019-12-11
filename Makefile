OBJDIR=obj
OUT=bin
LIBDIR=Core
INITDIR=$(LIBDIR)/Init
MANDIR=Manager
MKDIR=mkdir -p
INC=-I$(INITDIR)
LIBFLAGS=-lXi -lXmu -lglfw -lGLEW -lGLU -lm -lGL -lglut
LIBMEMBERS=$(LIBDIR)/ShaderLoader.cpp $(LIBDIR)/GameModels.cpp $(MANDIR)/ShaderManager.cpp $(MANDIR)/SceneManager.cpp $(INITDIR)/InitGLEW.cpp $(INITDIR)/InitGLUT.cpp

$(OBJDIR)/%.o: %.cpp
	g++ -std=c++11 -g -c -o $@ $<

outs:
	$(MKDIR) obj bin

main: $(OBJDIR)/main.o $(LIBMEMBERS)
	g++ -std=c++11 -w -g -o $(OUT)/main main.cpp $(LIBMEMBERS)  $(LIBFLAGS)