#pragma once

#include <map>
#include <memory>
#include <string>

namespace Graphics {
    namespace Managers
    {
        struct TexInfo {
            unsigned char *data;
            int width;
            int height;
            int nrComponents;
        };
        // TODO: generalize for other assets too
        class TextureManager {
            public:
                TextureManager();
                ~TextureManager();
                std::shared_ptr<TexInfo> add(const std::string& filePath);
                void remove(const std::string& filePath);
                bool has(const std::string& filePath);
                std::shared_ptr<TexInfo> get(const std::string& filePath, int* width, int* height, int* nrComponents);
    
            private:
                std::map<std::string, std::shared_ptr<TexInfo>> assets;  
        };
    }
}