#include <iostream>
#include "Components/CreatureRenderer.h"

std::vector<sf::Texture*> CreatureRenderer::creatureTextures;

CreatureRenderer::CreatureRenderer()
{
}

CreatureRenderer::~CreatureRenderer()
{
    delete creatureSprite;
    creatureSprite = nullptr;
}

void CreatureRenderer::Update(float deltaTime, sf::Event event)
{
    if (!GetOwner()->GetSceneOwner()->isPause())
    {
        spriteUpdateTimer += deltaTime;
        updateSprite(spriteUpdateTimer);
    }
}

void CreatureRenderer::Render(sf::RenderWindow* _window)
{
    Component::Render(_window);

    const auto position = GetOwner()->GetPosition();
    creatureSprite->setOrigin(sf::Vector2f(0.f, 0.f));
    creatureSprite->setPosition(position.x, position.y);
    creatureSprite->setScale(sf::Vector2f(1.0f, 1.0f));
    _window->draw(*creatureSprite);
}

void CreatureRenderer::CreateCreatureSprites(sf::Texture* texture, float X, float Y, float Width, float Height, int _spriteID, float frame)
{
    sf::Sprite* creatureSprite = new sf::Sprite();
    sf::IntRect coordonnees(X, Y, Width, Height);
    creatureSprite->setTexture(*texture);
    creatureSprite->setTextureRect(coordonnees);
    creatureSprites.emplace(_spriteID, creatureSprite);
    frameTime.push_back(frame);
}

void CreatureRenderer::LoadCreatureSprites(int creatureID)
{
    sf::Texture* PinkCow = new sf::Texture();
    sf::Texture* BlueChicken = new sf::Texture();
    sf::Texture* ICs = new sf::Texture();

    if (PinkCow->loadFromFile("assets/animals/cow/Pink cow animation sprites.png") && BlueChicken->loadFromFile("assets/Sprout Lands/Animals/Chicken/chicken blue.png") && ICs->loadFromFile("assets/animals/ICs/ICssprites.png"))
    {
        creatureTextures.push_back(PinkCow);
        creatureTextures.push_back(BlueChicken);
        creatureTextures.push_back(ICs);
    }
    else
    {
        std::cout << " Pourquoi il charge pas le poulet là ";
    }

    id = creatureID;

    // Vache rose
    if (creatureID == 0)
    {
        CreateCreatureSprites(PinkCow, 0, 0, 32, 32, 0, 0.5);
        CreateCreatureSprites(PinkCow, 64, 0, 32, 32, 1, 0.5);
        CreateCreatureSprites(PinkCow, 32, 0, 32, 32, 2, 0.5);
        CreateCreatureSprites(PinkCow, 64, 0, 32, 32, 3, 0.5);
    }

    // Poule Bleue
    if (creatureID == 1)
    {
        //Idle
        CreateCreatureSprites(BlueChicken, 0, 48, 16, 16, 0, 5);
        CreateCreatureSprites(BlueChicken, 16, 48, 16, 16, 1, 0.125);
        CreateCreatureSprites(BlueChicken, 48, 48, 16, 16, 2, 0.0625);
        CreateCreatureSprites(BlueChicken, 48, 48, 16, 16, 3, 0.0625);
        CreateCreatureSprites(BlueChicken, 64, 48, 16, 16, 4, 0.0625);
        CreateCreatureSprites(BlueChicken, 80, 48, 16, 16, 5, 0.0625);
        CreateCreatureSprites(BlueChicken, 96, 48, 16, 16, 6, 3);
        CreateCreatureSprites(BlueChicken, 80, 48, 16, 16, 7, 0.0625);
        CreateCreatureSprites(BlueChicken, 64, 48, 16, 16, 8, 0.0625);
        CreateCreatureSprites(BlueChicken, 48, 48, 16, 16, 9, 0.0625);
        CreateCreatureSprites(BlueChicken, 48, 48, 16, 16, 10, 0.0625);
        CreateCreatureSprites(BlueChicken, 16, 48, 16, 16, 11, 0.125);

       /*
        // Idle
        CreateCreatureSprites(BlueChicken, 48, 0, 16, 16, 0, 0);

        // Idle 1
        CreateCreatureSprites(BlueChicken, 0, 0, 16, 16, 10, 0.125);
        CreateCreatureSprites(BlueChicken, 16, 0, 16, 16, 11, 0.125);
        CreateCreatureSprites(BlueChicken, 32, 0, 16, 16, 12, 0.125);

        // Idle2
        CreateCreatureSprites(BlueChicken, 0, 176, 16, 16, 20);
        CreateCreatureSprites(BlueChicken, 16, 176, 16, 16, 21);
        CreateCreatureSprites(BlueChicken, 32, 176, 16, 16, 22);
        CreateCreatureSprites(BlueChicken, 48, 176, 16, 16, 23);
        CreateCreatureSprites(BlueChicken, 32, 176, 16, 16, 24);
        CreateCreatureSprites(BlueChicken, 48, 176, 16, 16, 25);
        CreateCreatureSprites(BlueChicken, 32, 176, 16, 16, 26);
        CreateCreatureSprites(BlueChicken, 48, 176, 16, 16, 27);
        CreateCreatureSprites(BlueChicken, 64, 176, 16, 16, 28);
        CreateCreatureSprites(BlueChicken, 80, 176, 16, 16, 29);

        // Idle3
        CreateCreatureSprites(BlueChicken, 0, 48, 16, 16, 30);
        CreateCreatureSprites(BlueChicken, 16, 48, 16, 16, 31);
        CreateCreatureSprites(BlueChicken, 32, 48, 16, 16, 32);
        CreateCreatureSprites(BlueChicken, 48, 48, 16, 16, 33);
        CreateCreatureSprites(BlueChicken, 64, 48, 16, 16, 34);
        CreateCreatureSprites(BlueChicken, 80, 48, 16, 16, 35);
        CreateCreatureSprites(BlueChicken, 96, 48, 16, 16, 36);
        */

    }
    if (creatureID == 2)
    {
        CreateCreatureSprites(ICs, 0, 0, 25, 27, 0, 5);
        CreateCreatureSprites(ICs, 25, 0, 25, 27, 1, 0.0625);
        CreateCreatureSprites(ICs, 50, 0, 25, 27, 2, 0.0625);
        CreateCreatureSprites(ICs, 75, 0, 25, 27, 3, 0.25);
        CreateCreatureSprites(ICs, 50, 0, 25, 27, 4, 0.0625);
        CreateCreatureSprites(ICs, 25, 0, 25, 27, 5, 0.0625);
    }
 
    creatureSprite = creatureSprites[0];
}

void CreatureRenderer::updateSprite(float timer)
{
    sf::Sprite* sprite = nullptr;
    int sprite_id;
    if (timer >= frameTime[currframe])
    {
        idle++;
        spriteUpdateTimer = 0;
    }
    sprite_id = idle % (creatureSprites.size());
    currframe = sprite_id;
    sprite = creatureSprites[currframe];

    creatureSprite = sprite;
}
