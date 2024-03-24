#pragma once

#include "SFML/Graphics.hpp"
#include "Components/Component.h"

class PlanteRenderer : public Component
{
public:
    PlanteRenderer();
    ~PlanteRenderer() override;

    void Render(sf::RenderWindow* _window) override;
    void Update(float deltaTime, sf::Event event) override;

    void LoadPlantSprites();
    void CreatePlantSprites(sf::Texture* texture, float X, float Y, float Width, float Height, int id);

    int GetID() { return id; }

    void SetID(const int _id) { id = _id; }
    void SetGrowthTime(int _id) { growthTime = growthTimes[_id % 6]; }
    void SetSprite(int id) { planteSprite = plantSprites[id]; }

private:
    sf::Texture* texture = nullptr;
    sf::Sprite* planteSprite = nullptr;
    int id = 0;

    float growth = 0;
    float growthTime = 1;
    std::vector<float> growthTimes = { 1,2,3,4,5,0 };

    static std::map<int, sf::Sprite*> plantSprites;
    static std::vector<sf::Texture*> plantTextures;
};