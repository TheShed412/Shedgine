#pragma once
#include "../Commands/Command.hpp"


// TODO: Currently, it executes each one for every time an event is sent. I need to set a boolean and apply it until that bool is false
namespace Input {

    class InputHandler 
    {
        public:
            virtual ~InputHandler() {};
            Commands::Command* handleInput(unsigned char key);
            void bindW(Commands::Command*);
            void bindA(Commands::Command*);
            void bindS(Commands::Command*);
            void bindD(Commands::Command*);

        private:
            Commands::Command* w_;
            Commands::Command* a_;
            Commands::Command* s_;
            Commands::Command* d_;
    };
}