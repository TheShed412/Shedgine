OBJDIR=obj
OUT=bin
SRCDIR=src
LIBDIR=$(SRCDIR)/Core
PHYDIR=$(LIBDIR)/Physics
INITDIR=$(LIBDIR)/Init
RENDDIR=$(SRCDIR)/Rendering
MODELDIR=$(RENDDIR)/Models
TEXDIR=$(RENDDIR)/Texture
CHARACTER=$(LIBDIR)/Game/SpaceGame/Characters
FPS=$(LIBDIR)/Game/FPS/Characters
GAMEDIR=$(LIBDIR)/Game
GAMEMANDIR=$(GAMEDIR)/Manager
MANDIR=$(SRCDIR)/Manager
MKDIR=mkdir -p
INC=-I${bulletPath}
LIBFLAGS=-lBulletCollision -lLinearMath -lBulletDynamics -lGLEW -lGLU -lm -lGL -lglut -lassimp 
LIBMEMBERS=$(PHYDIR)/Debugger/GLDebugDrawer.cpp $(PHYDIR)/PhysicsObject.cpp $(FPS)/Terry.cpp $(MANDIR)/DebugScene.cpp $(RENDDIR)/Light.cpp $(GAMEMANDIR)/ActorManager.cpp $(GAMEMANDIR)/ObjectManager.cpp $(CHARACTER)/Ship.cpp $(MODELDIR)/Mesh.cpp $(MODELDIR)/LoadedObject.cpp $(RENDDIR)/ObjectLoader.cpp $(TEXDIR)/TextureLoader.cpp $(MODELDIR)/Grid.cpp $(RENDDIR)/Camera.cpp $(MODELDIR)/Model.cpp $(MANDIR)/ModelsManager.cpp $(MODELDIR)/Cube.cpp $(LIBDIR)/ShaderLoader.cpp $(LIBDIR)/GameModels.cpp $(MANDIR)/ShaderManager.cpp $(MANDIR)/SceneManager.cpp $(INITDIR)/InitGLEW.cpp $(INITDIR)/InitGLUT.cpp
OBJMEMBERS=$(OBJDIR)/GLDebugDrawer.o $(OBJDIR)/PhysicsObject.o $(OBJDIR)/Terry.o $(OBJDIR)/FPSScene.o $(OBJDIR)/DebugScene.o $(OBJDIR)/Light.o $(OBJDIR)/ActorManager.o $(OBJDIR)/ObjectManager.o $(OBJDIR)/Ship.o $(OBJDIR)/Mesh.o $(OBJDIR)/LoadedObject.o $(OBJDIR)/ObjectLoader.o $(OBJDIR)/TextureLoader.o $(OBJDIR)/Grid.o $(OBJDIR)/Camera.o $(OBJDIR)/Model.o $(OBJDIR)/ModelsManager.o $(OBJDIR)/Cube.o $(OBJDIR)/ShaderLoader.o $(OBJDIR)/GameModels.o $(OBJDIR)/ShaderManager.o $(OBJDIR)/SceneManager.o $(OBJDIR)/InitGLEW.o $(OBJDIR)/InitGLUT.o

$(OBJDIR)/%.o: $(MANDIR)/%.cpp
	g++ -std=c++11 $(INC) -g -c -o $@ $<

$(OBJDIR)/%.o: $(PHYDIR)/%.cpp
	g++ -std=c++11 $(INC) -g -c -o $@ $<

$(OBJDIR)/%.o: $(PHYDIR)/Debugger/%.cpp
	g++ -std=c++11 $(INC) -g -c -o $@ $<

$(OBJDIR)/%.o: $(RENDDIR)/%.cpp
	g++ -std=c++11 $(INC) -g -c -o $@ $<

$(OBJDIR)/%.o: $(GAMEMANDIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(CHARACTER)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

$(OBJDIR)/%.o: $(FPS)/%.cpp
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
