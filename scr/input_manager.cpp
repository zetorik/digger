#include "../include/input_manager.hpp"
#include <SDL3/SDL_events.h>

InputManager::InputManager() {}

InputManager& InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::registerDownCallback(SDL_Scancode scancode, EventCallback callback) {
    downCallbacks[scancode].push_back(callback);
}

void InputManager::registerUpCallback(SDL_Scancode scancode, EventCallback callback) {
    upCallbacks[scancode].push_back(callback);
}

void InputManager::keyDown(SDL_Scancode scancode) {
    auto it = downCallbacks.find(scancode);
    
    if (it != downCallbacks.end()) {
        for (auto& cb : it->second) {
            cb();
        }
    }
}

void InputManager::keyUp(SDL_Scancode scancode) {
    auto it = upCallbacks.find(scancode);
    
    if (it != upCallbacks.end()) {
        for (auto& cb : it->second) {
            cb();
        }
    }
}

