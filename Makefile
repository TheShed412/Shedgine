OBJDIR=obj
OUT=bin
LIBDIR=Core
INITDIR=$(LIBDIR)/Init
RENDDIR=Rendering
MODELDIR=$(RENDDIR)/Models
TEXDIR=$(RENDDIR)/Texture
CHARACTER=$(LIBDIR)/Game/SpaceGame/Characters
MANDIR=Manager
MKDIR=mkdir -p
INC=-I$(INITDIR) -I/usr/local/include/
LIBFLAGS=-lGLEW -lGLU -lm -lGL -lglut -lassimp
LIBMEMBERS= $(CHARACTER)/Ship.cpp $(MODELDIR)/Mesh.cpp $(MODELDIR)/LoadedObject.cpp $(RENDDIR)/ObjectLoader.cpp $(TEXDIR)/TextureLoader.cpp $(MODELDIR)/Grid.cpp $(RENDDIR)/Camera.cpp $(MODELDIR)/Model.cpp $(MANDIR)/ModelsManager.cpp $(MODELDIR)/Cube.cpp $(LIBDIR)/ShaderLoader.cpp $(LIBDIR)/GameModels.cpp $(MANDIR)/ShaderManager.cpp $(MANDIR)/SceneManager.cpp $(INITDIR)/InitGLEW.cpp $(INITDIR)/InitGLUT.cpp

$(OBJDIR)/%.o: %.cpp
	g++ -std=c++11 -g -c -o $@ $<

outs:
	$(MKDIR) obj bin

main: $(OBJDIR)/main.o $(LIBMEMBERS)
	g++ -D _DEBUG -std=c++11 -w -g -o $(OUT)/main main.cpp $(LIBMEMBERS)  $(LIBFLAGS)
