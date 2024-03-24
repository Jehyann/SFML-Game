#pragma once

#include "SFML/Graphics.hpp"
#include "Components/Component.h"
#include "Scene.h"

class PlayerRenderer : public Component
{
public:
    PlayerRenderer();
    ~PlayerRenderer() override;

    void Render(sf::RenderWindow* _window) override; // fait tout le rendu
    void Update(float deltaTime, sf::Event event) override;

    void LoadPlayerSprites();
    void CreatePlayerSprites(sf::Texture* texture, float X, float Y, float Width, float Height, int id);
    void updateSprite(float timer);
    void SetSprite(int id) { playerSprite = playerSprites[id]; }

private:
    sf::Texture* texture = nullptr;
    sf::Sprite* playerSprite = nullptr;
    bool moving = false;

    bool lookingLeft = true;
    bool lookingRight = false;

    int idle = 0;
    float spriteUpdateTimer = 0;
    float spriteLength = 0.25;
    float speed = 300.0f;

    static std::map<int, sf::Sprite*> playerSprites;
};