#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <functional>
#include <unordered_map>
#include <vector>

using EventCallback = std::function<void()>;

class InputManager {
    public:
        static InputManager& getInstance();

        void registerDownCallback(SDL_Scancode scancode, EventCallback callback);
        void registerUpCallback(SDL_Scancode scancode, EventCallback callback);
        void keyDown(SDL_Scancode scancode); 
        void keyUp(SDL_Scancode scancode);
    private:
        InputManager();
        std::unordered_map<Uint32, std::vector<EventCallback>> downCallbacks;
        std::unordered_map<Uint32, std::vector<EventCallback>> upCallbacks;
};

