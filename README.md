# Shedgine
This is a custom engine that is being made to learn graphics libraries and game engine architecture. This was based off of a series of tutorials I found that no longer exists. Linking to the site will just bring you to a sports betting website, and I don't condone that on this Christian GitHub Repo.

## Building
Right now, this engine can only be built on Linux. I don't own a Windows machine, so anyone who wants to figure that out feel free to. That's not on my radar for now. There are two processes, depending on which branch you use.

### Dev/Game Branch
The `.travis.yml` is a good list of the dependencies that need installed. These commands should install all of them on a Ubuntu based system, other distros can figure it out on their own.

```
sudo apt-get update
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev libglew-dev libglm-dev assimp-utils libassimp-dev g++
```
After installing these, go in to the root directory and do
```
make outs
make main
```
And `./bin/main` should run the engine. On the game and development branches it will load a scene with a ship and be a shitty game I abandonded for what's on the fps branch.

### FPS Branch
This branch will need everything done above, and will need the bullet3 engine built from source.
Follow the build instrcutions on their repo
https://github.com/bulletphysics/bullet3

Keep track of where you put it, and set the `bulletPath` environment variable to the `src` file of the bullet repo. You can add this line to your shells' profile script:
```
export bulletPath={path to bullet library}
```
After that is set, also set the linker library path, this will be important later. Add this to the same profile script.
```
export export LD_LIBRARY_PATH=/usr/local/lib/
```
Next, go through these directories and copy these files to `/usr/local/lib`
```
Bullet3Common - libBullet3Common.a libBullet3Common.so libBullet3Common.so.2.89
Bullet3Dynamics - libBullet3Dynamics.a libBullet3Dynamics.so libBullet3Dynamics.so.2.89
Bullet2FileLoader - libBullet2FileLoader.a libBullet2FileLoader.so libBullet2FileLoader.so.2.89
LinearMath - libLinearMath.a libLinearMath.so libLinearMath.so.2.89
BulletDynamics - libBulletDynamics.a libBulletDynamics.so libBulletDynamics.so.2.89
Bullet3Collision - libBullet3Collisions.a libBullet3Collisions.so libBullet3Collisions.so.2.89
Bullet3Dynamics - libBullet3Dynamics.a libBullet3Dynamics.so libBullet3Dynamics.so.2.89
BulletCollision - libBulletCollision.a libBulletCollision.so libBulletCollision.so.2.89
```
Once those are moved, you should be able to do 
```
make outs
make main
./bin/main fps
```
And it should load a scene as an fps.
