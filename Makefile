OBJDIR=obj
OUT=bin
SRCDIR=src
LIBDIR=$(SRCDIR)/Core
INITDIR=$(LIBDIR)/Init
RENDDIR=$(SRCDIR)/Rendering
MODELDIR=$(RENDDIR)/Models
TEXDIR=$(RENDDIR)/Texture
CHARACTER=$(LIBDIR)/Game/SpaceGame/Characters
GAMEDIR=$(LIBDIR)/Game
GAMEMANDIR=$(GAMEDIR)/Manager
MANDIR=$(SRCDIR)/Manager
MKDIR=mkdir -p
INC=-I$(INITDIR) -I/usr/local/include/ -I$(GAMEDIR)
LIBFLAGS=-lGLEW -lGLU -lm -lGL -lglut -lassimp
LIBMEMBERS=$(MANDIR)/DebugScene.cpp $(RENDDIR)/Light.cpp $(GAMEMANDIR)/ActorManager.cpp $(GAMEMANDIR)/ObjectManager.cpp $(CHARACTER)/Ship.cpp $(MODELDIR)/Mesh.cpp $(MODELDIR)/LoadedObject.cpp $(RENDDIR)/ObjectLoader.cpp $(TEXDIR)/TextureLoader.cpp $(MODELDIR)/Grid.cpp $(RENDDIR)/Camera.cpp $(MODELDIR)/Model.cpp $(MANDIR)/ModelsManager.cpp $(MODELDIR)/Cube.cpp $(LIBDIR)/ShaderLoader.cpp $(LIBDIR)/GameModels.cpp $(MANDIR)/ShaderManager.cpp $(MANDIR)/SceneManager.cpp $(INITDIR)/InitGLEW.cpp $(INITDIR)/InitGLUT.cpp
OBJMEMBERS=$(OBJDIR)/DebugScene.o $(OBJDIR)/Light.o $(OBJDIR)/ActorManager.o $(OBJDIR)/ObjectManager.o $(OBJDIR)/Ship.o $(OBJDIR)/Mesh.o $(OBJDIR)/LoadedObject.o $(OBJDIR)/ObjectLoader.o $(OBJDIR)/TextureLoader.o $(OBJDIR)/Grid.o $(OBJDIR)/Camera.o $(MODELDIR)/Model.o $(OBJDIR)/ModelsManager.o $(OBJDIR)/Cube.o $(OBJDIR)/ShaderLoader.o $(OBJDIR)/GameModels.o $(OBJDIR)/ShaderManager.o $(OBJDIR)/SceneManager.o $(OBJDIR)/InitGLEW.o $(OBJDIR)/InitGLUT.o

$(OBJDIR)/%.o: $(MANDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(RENDDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(GAMEMANDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(CHARACTER)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(MODELDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(GAMEDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(TEXDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(INITDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(LIBDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

outs:
	$(MKDIR) obj bin

main: $(OBJDIR)/main.o $(OBJMEMBERS)
	g++ -std=c++11 -w -g -o $(OUT)/main $(OBJDIR)/main.o $(OBJMEMBERS) $(LIBFLAGS)

debug: $(OBJDIR)/main.o $(LIBMEMBERS)
	g++ -D _DEBUG -std=c++11 -w -g -o $(OUT)/main src/main.cpp $(LIBMEMBERS)  $(LIBFLAGS)
