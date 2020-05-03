#include "../Rendering/IGameObject.hpp"

using namespace Rendering;

namespace Controls {

    class Command {
        public:
        virtual ~Command() {}
        virtual void execute(IGameObject& gameObject) = 0;
    };

}