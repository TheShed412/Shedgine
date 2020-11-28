#pragma once
#include "../../../../../Rendering/Models/Model.hpp"
#include "../../../../../Rendering/VertexFormat.hpp"
#include "../../../../../Core/Init/WindowInfo.hpp"

/**
 * This will need to be abstracted better from the game code. As of right now it is in the game code
 * but is using OpenGL directly. I will want to better hide this so that I can use other gls when implementing
 * (Metal, Vulkan, whatever)
*/

using namespace Rendering;

namespace Game {

    namespace Crosshairs {

        class SimpleCross : public Models::Model {
            public:
                SimpleCross(int width, int height);
                ~SimpleCross();
        
                void Create();
                virtual void Update() override final;
                virtual void Draw() override final;
                virtual void processKeyboard(Movement direction, float deltaTime) override final;

            private:
                int screenWidth;
                int screenHeight;
                int vectors;
                std::vector<VertexFormat> makeCrosshair();
        };
    }
}