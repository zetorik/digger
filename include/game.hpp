#pragma once

#include "input_manager.hpp"
#include "iupdatable.hpp"
#include "player.hpp"
#include "sound.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <random>
#include <vector>

class Game {
    public:
        Game();
    private:
        void mainLoop();
        void pollEvents();
        void spawnRock();
        void spawnOre();
        void spawnExplosion(const Vec2& pos);
        bool m_running;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        std::unique_ptr<Player> m_player;
        InputManager& m_inputManager;
        float m_rockDelay;
        float m_rockTimer;
        float m_oreDelay;
        std::uniform_real_distribution<float> m_oreDelayDistrib;
        float m_oreTimer;
        TTF_Font* m_font;
        TTF_Text* m_text;
        TTF_TextEngine* m_textEngine;
        std::vector<std::unique_ptr<IUpdatable>> m_updateArr;
        std::vector<ICollidable*> m_prevCollisions;
        Sound* m_hitSound;
        Sound* m_deathSound;
        Sound* m_music;
};
