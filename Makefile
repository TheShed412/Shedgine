OBJDIR=obj
OUT=bin
LIBDIR=Core
INITDIR=$(LIBDIR)/Init
RENDDIR=Rendering
MODELDIR=$(RENDDIR)/Models
TEXDIR=$(RENDDIR)/Texture
MANDIR=Manager
MKDIR=mkdir -p
INC=-I$(INITDIR)
LIBFLAGS=-lGLEW -lGLU -lm -lGL -lglut
LIBMEMBERS=$(RENDDIR)/ObjectLoader.cpp $(TEXDIR)/TextureLoader.cpp $(MODELDIR)/Grid.cpp $(RENDDIR)/Camera.cpp $(MODELDIR)/Model.cpp $(MANDIR)/ModelsManager.cpp $(MODELDIR)/Cube.cpp $(MODELDIR)/Triangle.cpp $(LIBDIR)/ShaderLoader.cpp $(LIBDIR)/GameModels.cpp $(MANDIR)/ShaderManager.cpp $(MANDIR)/SceneManager.cpp $(INITDIR)/InitGLEW.cpp $(INITDIR)/InitGLUT.cpp

$(OBJDIR)/%.o: %.cpp
	g++ -std=c++11 -g -c -o $@ $<

outs:
	$(MKDIR) obj bin

main: $(OBJDIR)/main.o $(LIBMEMBERS)
	g++ -std=c++11 -w -g -o $(OUT)/main main.cpp $(LIBMEMBERS)  $(LIBFLAGS)
