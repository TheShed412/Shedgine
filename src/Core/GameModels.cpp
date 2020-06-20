#include "GameModels.hpp"
using namespace Models;
 
GameModels::GameModels()
{
 
}
 
GameModels::~GameModels()
{
 
  std::map<std::string, Model>::iterator it;
  for (it = GameModelList.begin(); it != GameModelList.end(); ++it)
  {
    //delete VAO and VBOs (if many)
    unsigned int* p = &it->second.vao;
    glDeleteVertexArrays(1, p);
    glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
    it->second.vbos.clear();
  }
  GameModelList.clear();
}
 
void GameModels::CreateTriangleModel(const std::string& gameModelName)
{
   unsigned int vao;
   unsigned int vbo;
 
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(glm::vec3( 0.25, -0.25, 0.0),
                                    glm::vec4( 1, 0, 0, 1))); //red
    vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0),
                                    glm::vec4( 0, 1, 0, 1))); //green
    vertices.push_back(VertexFormat(glm::vec3( 0.25, 0.25, 0.0),
                                    glm::vec4( 0, 0, 1, 1))); //blue
 
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);
 
    Model myModel;                            //is allocated on Stack
    myModel.vao = vao;                        //add vao
    myModel.vbos.push_back(vbo);              //add vbo
    GameModelList[gameModelName] = myModel;  //add to std::map
 
}
 
void GameModels::DeleteModel(const std::string& gameModelName)
{
   Model model = GameModelList[gameModelName];
   unsigned int p = model.vao;
   glDeleteVertexArrays(1, &p);
   glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
   model.vbos.clear();
   GameModelList.erase(gameModelName);
 
}
 
unsigned int GameModels::GetModel(const std::string& gameModelName)
{
   return GameModelList[gameModelName].vao;
}