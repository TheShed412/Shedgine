#pragma once
#include <vector>

#include "IGameObject.hpp"
#include "VertexFormat.hpp"

namespace Rendering
{
    class ObjectLoader
    {
        private:
            /* data */
        public:
            ObjectLoader(/* args */);
            ~ObjectLoader();
            std::vector<VertexFormat> LoadObject();
    };
    
} // namespace Rendering
