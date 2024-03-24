#pragma once

#include "SFML/Graphics.hpp"
#include "Components/Component.h"

class CreatureRenderer : public Component
{
public:
    CreatureRenderer();
    ~CreatureRenderer() override;

    void Render(sf::RenderWindow* _window) override;
    void Update(float deltaTime, sf::Event event) override;

    int GetID() { return id; }

    void LoadCreatureSprites(int creatureID);
    void CreateCreatureSprites(sf::Texture* texture, float X, float Y, float Width, float Height, int spriteID, float frame);
    void updateSprite(float timer);
    void SetSprite(int id) { LoadCreatureSprites(id); }

private:
    sf::Sprite* creatureSprite = nullptr;
    int spriteID;

    int idle = 0;
    int currframe = 0;
    float spriteUpdateTimer = 0;
    float spriteLength = 0.5;

    int id;

    std::map<int, sf::Sprite*> creatureSprites;
    std::vector<float> frameTime;
    static std::vector<sf::Texture*> creatureTextures;
};