#include "InputHandler.hpp"

using namespace Input;

Commands::Command* InputHandler::handleInput(unsigned char key) {

    if (key == SDLK_w) {
        return w_;
    }
    if (key == SDLK_a) {
        return a_;
    }
    if (key == SDLK_s) {
        return s_;
    }
    if (key == SDLK_d) {
        return d_;
    }

    return NULL;
}

void InputHandler::bindW(Commands::Command* command) {
    this->w_ = command;
}

void InputHandler::bindA(Commands::Command* command) {
    this->a_ = command;
}

void InputHandler::bindS(Commands::Command* command) {
    this->s_ = command;
}

void InputHandler::bindD(Commands::Command* command) {
    this->d_ = command;
}