OBJDIR=obj
OUT=bin
SRCDIR=src
LIBDIR=$(SRCDIR)/Core
INITDIR=$(LIBDIR)/Init
RENDDIR=$(SRCDIR)/Rendering
MODELDIR=$(RENDDIR)/Models
TEXDIR=$(RENDDIR)/Texture
CHARACTER=$(LIBDIR)/Game/SpaceGame/Characters
FPS=$(LIBDIR)/Game/FPS/Characters
GAMEDIR=$(LIBDIR)/Game
INPUTDIR=$(GAMEDIR)/Input
GAMEMANDIR=$(GAMEDIR)/Manager
OPENCH=$(LIBDIR)/Game/FPS/Crosshairs/OpenGL
MANDIR=$(SRCDIR)/Manager
MKDIR=mkdir -p
INC=-I${bulletPath}
LIBFLAGS= -lGLEW -lGLU -lm -lGL -lassimp `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
LIBMEMBERS=$(LIBDIR)/EventManager.cpp $(OPENCH)/SimpleCross.cpp $(MANDIR)/TextureManager.cpp $(INPUTDIR)/InputHandler.cpp $(MANDIR)/FPSScene.cpp $(INITDIR)/InitSDL.cpp $(FPS)/Terry.cpp $(RENDDIR)/Light.cpp $(GAMEMANDIR)/ActorManager.cpp $(GAMEMANDIR)/ObjectManager.cpp $(CHARACTER)/Ship.cpp $(MODELDIR)/Mesh.cpp $(MODELDIR)/LoadedObject.cpp $(RENDDIR)/ObjectLoader.cpp $(TEXDIR)/TextureLoader.cpp $(MODELDIR)/Grid.cpp $(RENDDIR)/Camera.cpp $(MODELDIR)/Model.cpp $(MANDIR)/ModelsManager.cpp $(MODELDIR)/Cube.cpp $(LIBDIR)/ShaderLoader.cpp $(LIBDIR)/GameModels.cpp $(MANDIR)/ShaderManager.cpp $(INITDIR)/InitGLEW.cpp
OBJMEMBERS=$(OBJDIR)/EventManager.o $(OBJDIR)/SimpleCross.o $(OBJDIR)/TextureManager.o $(OBJDIR)/InputHandler.o  $(OBJDIR)/FPSScene.o $(OBJDIR)/InitSDL.o $(OBJDIR)/Terry.o $(OBJDIR)/Light.o $(OBJDIR)/ActorManager.o $(OBJDIR)/ObjectManager.o $(OBJDIR)/Ship.o $(OBJDIR)/Mesh.o $(OBJDIR)/LoadedObject.o $(OBJDIR)/ObjectLoader.o $(OBJDIR)/TextureLoader.o $(OBJDIR)/Grid.o $(OBJDIR)/Camera.o $(OBJDIR)/Model.o $(OBJDIR)/ModelsManager.o $(OBJDIR)/Cube.o $(OBJDIR)/ShaderLoader.o $(OBJDIR)/GameModels.o $(OBJDIR)/ShaderManager.o  $(OBJDIR)/InitGLEW.o

$(OBJDIR)/%.o: $(MANDIR)/%.cpp
	g++ -std=c++11 $(INC) -g -c -o $@ $<

$(OBJDIR)/%.o: $(RENDDIR)/%.cpp
	g++ -std=c++11 $(INC) -g -c -o $@ $<

$(OBJDIR)/%.o: $(GAMEMANDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(INPUTDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(CHARACTER)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(FPS)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(OPENCH)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(MODELDIR)/%.cpp
	g++ -std=c++11 $(INC) -g -c -o $@ $<

$(OBJDIR)/%.o: $(GAMEDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(TEXDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(INITDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(LIBDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -std=c++11 $(INC) -g -c -o $@ $<

outs:
	$(MKDIR) obj bin

clean:
	rm obj/*

main: $(OBJDIR)/main.o $(OBJMEMBERS)
	g++ -std=c++11 -w -g -o $(OUT)/main $(OBJDIR)/main.o $(OBJMEMBERS) $(LIBFLAGS)

debug: $(OBJDIR)/main.o $(OBJMEMBERS)
	g++ -D _DEBUG -std=c++11 -w -g -o $(OUT)/main $(OBJDIR)/main.o $(OBJMEMBERS)  $(LIBFLAGS)
