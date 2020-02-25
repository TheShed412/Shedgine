#pragma once
#include <vector>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <string>

#include "IGameObject.hpp"
#include "VertexFormat.hpp"

namespace Rendering
{
    class ObjectLoader
    {
        private:
            /* data */
            bool hasUvIndexes(std::string face);
        public:
            ObjectLoader(/* args */);
            ~ObjectLoader();
            std::vector<VertexFormat> LoadObject(const std::string& filename);
    };
    
} // namespace Rendering
