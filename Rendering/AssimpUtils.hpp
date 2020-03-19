// #pragma once
// #include <assimp/cimport.h>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

// #include "Scene.hpp"

// #define aisgl_min(x,y) (x<y?x:y)
// #define aisgl_max(x,y) (y>x?y:x)

// namespace Rendering {

//     /* ---------------------------------------------------------------------------- */
//     void color4_to_float4(const C_STRUCT aiColor4D *c, float f[4])
//     {
//         f[0] = c->r;
//         f[1] = c->g;
//         f[2] = c->b;
//         f[3] = c->a;
//     }

//     /* ---------------------------------------------------------------------------- */
//     void set_float4(float f[4], float a, float b, float c, float d)
//     {
//         f[0] = a;
//         f[1] = b;
//         f[2] = c;
//         f[3] = d;
//     }

//     void apply_material(const C_STRUCT aiMaterial *mtl)
//     {
//         float c[4];

//         GLenum fill_mode;
//         int ret1, ret2;
//         C_STRUCT aiColor4D diffuse;
//         C_STRUCT aiColor4D specular;
//         C_STRUCT aiColor4D ambient;
//         C_STRUCT aiColor4D emission;
//         ai_real shininess, strength;
//         int two_sided;
//         int wireframe;
//         unsigned int max;

//         set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
//         if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
//             color4_to_float4(&diffuse, c);
//         glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

//         set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
//         if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
//             color4_to_float4(&specular, c);
//         glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

//         set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
//         if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
//             color4_to_float4(&ambient, c);
//         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

//         set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
//         if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
//             color4_to_float4(&emission, c);
//         glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

//         max = 1;
//         ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
//         if(ret1 == AI_SUCCESS) {
//             max = 1;
//             ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
//             if(ret2 == AI_SUCCESS)
//                 glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
//             else
//                 glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
//         }
//         else {
//             glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
//             set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
//             glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
//         }

//         max = 1;
//         if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
//             fill_mode = wireframe ? GL_LINE : GL_FILL;
//         else
//             fill_mode = GL_FILL;
//         glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

//         max = 1;
//         if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
//             glDisable(GL_CULL_FACE);
//         else
//             glEnable(GL_CULL_FACE);
//     }

//     void get_bounding_box_for_node (const C_STRUCT aiNode* nd,
//         C_STRUCT aiVector3D* min,
//         C_STRUCT aiVector3D* max,
//         C_STRUCT aiMatrix4x4* trafo,
//         const aiScene* scene
//     ){
//         C_STRUCT aiMatrix4x4 prev;
//         unsigned int n = 0, t;

//         prev = *trafo;
//         aiMultiplyMatrix4(trafo,&nd->mTransformation);

//         for (; n < nd->mNumMeshes; ++n) {
//             const C_STRUCT aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
//             for (t = 0; t < mesh->mNumVertices; ++t) {

//                 C_STRUCT aiVector3D tmp = mesh->mVertices[t];
//                 aiTransformVecByMatrix4(&tmp,trafo);

//                 min->x = aisgl_min(min->x,tmp.x);
//                 min->y = aisgl_min(min->y,tmp.y);
//                 min->z = aisgl_min(min->z,tmp.z);

//                 max->x = aisgl_max(max->x,tmp.x);
//                 max->y = aisgl_max(max->y,tmp.y);
//                 max->z = aisgl_max(max->z,tmp.z);
//             }
//         }

//         for (n = 0; n < nd->mNumChildren; ++n) {
//             get_bounding_box_for_node(nd->mChildren[n],min,max,trafo,scene);
//         }
//         *trafo = prev;
//     }

//     void get_bounding_box(C_STRUCT aiVector3D* min, C_STRUCT aiVector3D* max, const aiScene* scene)
//     {
//         C_STRUCT aiMatrix4x4 trafo;
//         aiIdentityMatrix4(&trafo);

//         min->x = min->y = min->z =  1e10f;
//         max->x = max->y = max->z = -1e10f;
//         get_bounding_box_for_node(scene->mRootNode,min,max,&trafo, scene);
//     }

//     int loadasset (const char* path, Scene* scene)
//     {
//         /* we are taking one of the postprocessing presets to avoid
//         spelling out 20+ single postprocessing flags here. */
//         scene->scene = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);

//         if (scene) {
//             get_bounding_box(&scene->scene_min,&scene->scene_max, scene->scene);
//             scene->scene_center.x = (scene->scene_min.x + scene->scene_max.x) / 2.0f;
//             scene->scene_center.y = (scene->scene_min.y + scene->scene_max.y) / 2.0f;
//             scene->scene_center.z = (scene->scene_min.z + scene->scene_max.z) / 2.0f;
//             return 0;
//         }
//         return 1;
//     }
// }