#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/gl.h>

namespace Rendering {

    class Scene {

        // TODO: make this better lol
        public:
            const aiScene* scene = NULL;
            GLuint scene_list = 0;
            C_STRUCT aiVector3D scene_min, scene_max, scene_center;

    };
}