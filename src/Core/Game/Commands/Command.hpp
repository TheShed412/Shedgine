#pragma once
#include "../Actor.hpp"

namespace Commands {
    class Command 
    {
        public: 
            virtual ~Command() {}
            virtual void execute(Game::Actor& actor, bool pressed) = 0;
    };

    class ForwardCommand : public Command
    {
        public: 
            virtual ~ForwardCommand() {}
            void virtual execute(Game::Actor& actor, bool pressed) { actor.MoveForward(pressed); }
    };

    class BackwardCommand : public Command
    {
        public: 
            virtual ~BackwardCommand() {}
            void virtual execute(Game::Actor& actor, bool pressed) { actor.MoveBackward(pressed); }
    };

    class RightCommand : public Command
    {
        public: 
            virtual ~RightCommand() {}
            void virtual execute(Game::Actor& actor, bool pressed) { actor.MoveRight(pressed); }
    };

    class LeftCommand : public Command
    {
        public: 
            virtual ~LeftCommand() {}
            void virtual execute(Game::Actor& actor, bool pressed) { actor.MoveLeft(pressed); }
    };
}
