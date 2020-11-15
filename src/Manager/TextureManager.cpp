#include <iostream>
#include "TextureManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../Core/stb_image.h"

using namespace Graphics::Managers;



TextureManager::TextureManager() {
    
}


TextureManager::~TextureManager() {

}


std::shared_ptr<TexInfo> TextureManager::add(const std::string& filePath) {
    auto it = assets.find(filePath);

    if (it != assets.end()) {
        return it->second;
    }

    int width,  height,  nrComponents;
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
    // blah blah validation blah blah
    TexInfo texInfo = {
        data, width, height, nrComponents
    };
    std::shared_ptr<TexInfo> asset = std::make_shared<TexInfo>(texInfo);

    assets.insert(std::make_pair(filePath, asset));

    return asset;
}


void TextureManager::remove(const std::string& filePath) {
    // probably should do a check if it exists or something
    // and free the texture info
    auto it = assets.find(filePath);

    if (it == assets.end()) {
        return;
    }
    stbi_image_free(it->second.get()->data);
    assets.erase(filePath);
}


bool TextureManager::has(const std::string& filePath) {
    return false;// I don't even know if I'll use this lol
}


std::shared_ptr<TexInfo> TextureManager::get(const std::string& filePath, int* width, int* height, int* nrComponentsh){
    return assets[filePath];
}