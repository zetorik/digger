#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_audio.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "../include/game.hpp"
#include "../include/utils.hpp"
#include "../include/player.hpp"
#include "../include/input_manager.hpp"
#include "../include/rock.hpp"
#include "../include/collision_manager.hpp"
#include "../include/explosion.hpp"
#include "../include/texture_manager.hpp"
#include "../include/ore.hpp"
#include "../include/audio_manager.hpp"

const Vec2 WINDOW_SIZE(640, 480);
const float BASE_ROCK_DELAY = 1;
const int ROCK_DAMAGE = 10;
const float ROCK_SPEED = 10;
const std::string MUSIC_PATH = "assets/music.wav";
const std::string HIT_PATH = "assets/hit.wav";
const std::string DEATH_SOUND_PATH = "assets/pipe.wav";
const std::string FONT_PATH = "assets/font.ttf";
const std::string EHH = "assets/ehh.png";
const float MIN_ORE_DELAY = 0.5;
const float MAX_ORE_DELAY = 10;

Game::Game():
    m_inputManager(InputManager::getInstance()) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();

    m_window = SDL_CreateWindow("Digger", WINDOW_SIZE.x, WINDOW_SIZE.y, SDL_WINDOW_OPENGL);
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    SDL_SetRenderVSync(m_renderer, 1);

    TextureManager::getInstance().setRenderer(m_renderer);

    m_player = std::make_unique<Player>(m_renderer, WINDOW_SIZE);
    CollisionManager::getInstance().addCollidable(m_player.get());

    m_music = AudioManager::getInstance().getSound(MUSIC_PATH);
    m_music->play();

    m_hitSound = AudioManager::getInstance().getSound(HIT_PATH);
    m_deathSound = AudioManager::getInstance().getSound(DEATH_SOUND_PATH);

    auto& gen = globalRandomEngine();
    m_oreDelayDistrib = std::uniform_real_distribution<float>(MIN_ORE_DELAY, MAX_ORE_DELAY);
    
    m_font = TTF_OpenFont(FONT_PATH.c_str(), 25);
    m_textEngine = TTF_CreateRendererTextEngine(m_renderer);
    m_text = TTF_CreateText(m_textEngine, m_font, "0", 0);

    m_rockDelay = BASE_ROCK_DELAY;
    m_oreDelay = m_oreDelayDistrib(gen); 
    m_rockTimer = 0;
    m_oreTimer = 0;
    m_running = true; 

    mainLoop();

    SDL_DestroyWindow(m_window);
    TTF_Quit();
    SDL_Quit();
}

void Game::pollEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                m_running = false;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.repeat) {
                    break;
                }

                m_inputManager.keyDown(event.key.scancode);

                break;
            case SDL_EVENT_KEY_UP:
                if (event.key.repeat) {
                    break;
                }

                m_inputManager.keyUp(event.key.scancode);

                break;
        }
    }
}

void Game::spawnRock() {
    auto& gen = globalRandomEngine();

    std::uniform_real_distribution<float> distrib(0, 1);

    Vec2 pos(distrib(gen), distrib(gen));

    Vec2 direction = -Vec2(pos.x - 0.5, pos.y - 0.5);
    direction = direction.normalized();

    pos += -direction * 0.3;

    pos *= WINDOW_SIZE;

    std::unique_ptr<Rock> rock = std::make_unique<Rock>(m_renderer, pos, direction, ROCK_SPEED);

    Rock* rockRaw = rock.get();

    m_updateArr.push_back(std::move(rock));

    CollisionManager::getInstance().addCollidable(rockRaw);
}

void Game::spawnExplosion(const Vec2& pos) {
    std::unique_ptr<Explosion> exp = std::make_unique<Explosion>(m_renderer, pos);

    m_updateArr.push_back(std::move(exp));
}

void Game::spawnOre() {
    auto& gen = globalRandomEngine();

    std::uniform_real_distribution<float> distrib(0, 1);
    std::uniform_int_distribution<> oreDistrib(1, 12);

    Vec2 pos(distrib(gen), distrib(gen));

    pos = (pos * WINDOW_SIZE).clamped(Vec2(), WINDOW_SIZE - Vec2(45, 45));

    OreType type;

    switch (oreDistrib(gen)) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            type = OreType::Iron; 
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            type = OreType::Uranium;
            break;
        default:
            type = OreType::Cobalt;
            break;
    }

    std::unique_ptr<Ore> ore = std::make_unique<Ore>(m_renderer, pos, type);
    Ore* oreRaw = ore.get();

    m_updateArr.push_back(std::move(ore));

    CollisionManager::getInstance().addCollidable(oreRaw);
}

void Game::mainLoop() {
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    float deltaTime = 0;
    double fpsTimer = 0.0;
    int frameCount = 0;

    while (m_running) {
        last = now;
        now  = SDL_GetPerformanceCounter();
        deltaTime = static_cast<float>(now - last) / SDL_GetPerformanceFrequency();
        
        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 1.0) { // every 1 second
            std::cout << "FPS: " << frameCount << std::endl;
            fpsTimer = 0.0;
            frameCount = 0;
        }

        pollEvents();

        SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);  // Clear color
        SDL_RenderClear(m_renderer);

        m_rockTimer += deltaTime;
        m_oreTimer += deltaTime;

        if (m_rockTimer > m_rockDelay) {
            m_rockTimer -= m_rockDelay;
            m_rockDelay -= 0.004;
            
            spawnRock();
        }

        if (m_oreTimer > m_oreDelay) {
            m_oreTimer -= m_oreDelay;
            
            spawnOre();

            auto& gen = globalRandomEngine();

            m_oreDelay = m_oreDelayDistrib(gen);
        }

        m_player->update(deltaTime);
        
        for (size_t i = 0; i < m_updateArr.size(); /* increment inside */) {
            if (m_updateArr[i]->isDestroying()) {
                m_updateArr.erase(m_updateArr.begin() + i);  // unique_ptr deleted here, object destroyed
                                                             // don't increment i because vector shrinks
            } else {
                m_updateArr[i]->update(deltaTime);
                ++i;
            }
        }

        if (m_player->isDestroying()) {
            m_running = false;
        }

        std::vector<ICollidable*> collisions = CollisionManager::getInstance().getCollisions(m_player.get());

        if (!collisions.empty() && m_prevCollisions != collisions) {
            bool collidedWithRock = false;
            bool collidedWithOre = false;
            int fractals = 0;

            for (ICollidable* collidable : collisions) {
                if (collidable->tagCollidable == "Rock") {
                    collidedWithRock = true;
                    
                    Rock* rock = static_cast<Rock*>(collidable);
                    rock->planDestroy();

                    break;
                } else if (collidable->tagCollidable == "Ore") {
                    collidedWithOre = true;

                    Ore* ore = static_cast<Ore*>(collidable);
                    fractals = ore->getPrice();
                    ore->planDestroy();
                    
                    break;
                }
            }
            
            if (collidedWithRock) {
                m_player->takeDamage(ROCK_DAMAGE);
                m_hitSound->play();
                spawnExplosion(m_player->getPosition());

                if (m_player->getHealth() <= 0) {
                    m_deathSound->play();
                    m_deathSound->play();
                }
                //std::cout << m_player->getHealth() << std::endl;
            } else if (collidedWithOre) {
                m_player->addFractals(fractals);
                m_player->spin();
                TTF_DestroyText(m_text);
                m_text = TTF_CreateText(m_textEngine, m_font, (std::to_string(m_player->getFractals())).c_str(), 0);
            }
        }

        if (m_player->getHealth() <= 0) {
            std::string t = "You died with " + std::to_string(m_player->getFractals()) + " fractals..."; 
            TTF_Text* deathText = TTF_CreateText(m_textEngine, m_font, t.c_str(), 0);

            SDL_FRect r = {100, 250, 150, 150};
            TTF_DrawRendererText(deathText, 50, 200);
            SDL_RenderTexture(m_renderer, TextureManager::getInstance().getTexture(EHH), NULL, &r);
        }

        m_prevCollisions = collisions;

        TTF_DrawRendererText(m_text, 600, 30);

        SDL_RenderPresent(m_renderer);
    }
}

