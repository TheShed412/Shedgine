#pragma once
#include "../Actor.hpp"

namespace Commands {
    class Command 
    {
        public: 
            virtual ~Command() {}
            virtual void execute(Game::Actor& actor, int deltaTime) = 0;
    };

    class ForwardCommand : public Command
    {
        public: 
            virtual ~ForwardCommand() {}
            void virtual execute(Game::Actor& actor, int deltaTime) { actor.MoveForward(deltaTime); }
    };

    class BackwardCommand : public Command
    {
        public: 
            virtual ~BackwardCommand() {}
            void virtual execute(Game::Actor& actor, int deltaTime) { actor.MoveBackward(deltaTime); }
    };

    class RightCommand : public Command
    {
        public: 
            virtual ~RightCommand() {}
            void virtual execute(Game::Actor& actor, int deltaTime) { actor.MoveRight(deltaTime); }
    };

    class LeftCommand : public Command
    {
        public: 
            virtual ~LeftCommand() {}
            void virtual execute(Game::Actor& actor, int deltaTime) { actor.MoveLeft(deltaTime); }
    };
}
