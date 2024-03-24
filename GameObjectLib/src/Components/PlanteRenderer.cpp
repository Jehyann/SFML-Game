#include <iostream>

#include "Components/PlanteRenderer.h"
#include "Components/JournalDonnees.h"

std::map<int, sf::Sprite*> PlanteRenderer::plantSprites;
std::vector<sf::Texture*> PlanteRenderer::plantTextures;

PlanteRenderer::PlanteRenderer()
{
    LoadPlantSprites();
}

PlanteRenderer::~PlanteRenderer()
{
    delete texture;
    delete planteSprite;
    texture = nullptr;
    planteSprite = nullptr;
}

void PlanteRenderer::Render(sf::RenderWindow* _window)
{
    Component::Render(_window);

    const auto position = GetOwner()->GetPosition();
    planteSprite->setOrigin(sf::Vector2f(0.f, 0.f));
    planteSprite->setPosition(position.x+2.31, position.y+2.31);
    planteSprite->setScale(sf::Vector2f(0.67f, 0.67f));
    _window->draw(*planteSprite);
}

void PlanteRenderer::Update(float deltaTime, sf::Event event)
{
    if (!GetOwner()->GetSceneOwner()->isPause())
    {
        if (growthTime != 0)
        {
            growth += deltaTime;
            if (growth > growthTime)
            {
                id++;
                SetID(id);
                this->GetOwner()->SetID(id);
                growth = 0;
                SetGrowthTime(GetID());
                planteSprite = plantSprites[id];
                if (growthTime == 0)
                {
                    GetOwner()->GetSceneOwner()->GetGameObject("Journal")->GetComponent<JournalDonnees>()->addPlante((id+1)/6-1);
                }
            }
        }
    }
}

void PlanteRenderer::CreatePlantSprites(sf::Texture* texture, float X, float Y, float Width, float Height, int id)
{
    sf::Sprite* plantSprite = new sf::Sprite();
    sf::IntRect coordonnees(X, Y, Width, Height);
    plantSprite->setTexture(*texture);
    plantSprite->setTextureRect(coordonnees);
    plantSprites.emplace(id, plantSprite);
}

void PlanteRenderer::LoadPlantSprites()
{
    sf::Texture* texture1 = new sf::Texture();
    sf::Texture* texture2 = new sf::Texture();
    if (texture1->loadFromFile("assets/Tiny Wonder Farm/objects&items/plants.png") &&
        texture2->loadFromFile("assets/Tiny Wonder Farm/objects&items/items.png"))
    {
        plantTextures.push_back(texture1);
        plantTextures.push_back(texture2);
    }
    else
    {
        std::cout << "YOU DUMMY!!!!";
    }

    //Citrouille
    CreatePlantSprites(texture1, 0, 0, 16, 16, 0);
    CreatePlantSprites(texture1, 16, 0, 16, 16, 1);
    CreatePlantSprites(texture1, 32, 0, 16, 16, 2);
    CreatePlantSprites(texture1, 48, 0, 16, 16, 3);
    CreatePlantSprites(texture1, 64, 0, 16, 16, 4);
    CreatePlantSprites(texture2, 0, 0, 16, 16, 5);

    //Fraise
    CreatePlantSprites(texture1, 0, 16, 16, 16, 30);
    CreatePlantSprites(texture1, 16, 16, 16, 16, 31);
    CreatePlantSprites(texture1, 32, 16, 16, 16, 32);
    CreatePlantSprites(texture1, 48, 16, 16, 16, 33);
    CreatePlantSprites(texture1, 64, 16, 16, 16, 34);
    CreatePlantSprites(texture2, 80, 0, 16, 16, 35);

    //Carotte
    CreatePlantSprites(texture1, 0, 32, 16, 16, 12);
    CreatePlantSprites(texture1, 16, 32, 16, 16, 13);
    CreatePlantSprites(texture1, 32, 32, 16, 16, 14);
    CreatePlantSprites(texture1, 48, 32, 16, 16, 15);
    CreatePlantSprites(texture1, 64, 32, 16, 16, 16);
    CreatePlantSprites(texture2, 32, 0, 16, 16, 17);

    //Patate
    CreatePlantSprites(texture1, 0, 48, 16, 16, 24);
    CreatePlantSprites(texture1, 16, 48, 16, 16, 25);
    CreatePlantSprites(texture1, 32, 48, 16, 16, 26);
    CreatePlantSprites(texture1, 48, 48, 16, 16, 27);
    CreatePlantSprites(texture1, 64, 48, 16, 16, 28);
    CreatePlantSprites(texture2, 64, 0, 16, 16, 29);

    //Choux
    CreatePlantSprites(texture1, 0, 64, 16, 16, 6);
    CreatePlantSprites(texture1, 16, 64, 16, 16, 7);
    CreatePlantSprites(texture1, 32, 64, 16, 16, 8);
    CreatePlantSprites(texture1, 48, 64, 16, 16, 9);
    CreatePlantSprites(texture1, 64, 64, 16, 16, 10);
    CreatePlantSprites(texture2, 16, 0, 16, 16, 11);

    //Blé
    CreatePlantSprites(texture1, 0, 80, 16, 16, 18);
    CreatePlantSprites(texture1, 16, 80, 16, 16, 19);
    CreatePlantSprites(texture1, 32, 80, 16, 16, 20);
    CreatePlantSprites(texture1, 48, 80, 16, 16, 21);
    CreatePlantSprites(texture1, 64, 80, 16, 16, 22);
    CreatePlantSprites(texture2, 48, 0, 16, 16, 23);

    //Tomate
    CreatePlantSprites(texture1, 0, 96, 16, 16, 36);
    CreatePlantSprites(texture1, 16, 96, 16, 16, 37);
    CreatePlantSprites(texture1, 32, 96, 16, 16, 38);
    CreatePlantSprites(texture1, 48, 96, 16, 16, 39);
    CreatePlantSprites(texture1, 64, 96, 16, 16, 40);
    CreatePlantSprites(texture2, 96, 0, 16, 16, 41);

    //Aubergine
    CreatePlantSprites(texture1, 0, 112, 16, 16, 42);
    CreatePlantSprites(texture1, 16, 112, 16, 16, 43);
    CreatePlantSprites(texture1, 32, 112, 16, 16, 44);
    CreatePlantSprites(texture1, 48, 112, 16, 16, 45);
    CreatePlantSprites(texture1, 64, 112, 16, 16, 46);
    CreatePlantSprites(texture2, 112, 0, 16, 16, 47);

    //Ognon
    CreatePlantSprites(texture1, 0, 128, 16, 16, 48);
    CreatePlantSprites(texture1, 16, 128, 16, 16, 49);
    CreatePlantSprites(texture1, 32, 128, 16, 16, 50);
    CreatePlantSprites(texture1, 48, 128, 16, 16, 51);
    CreatePlantSprites(texture1, 64, 128, 16, 16, 52);
    CreatePlantSprites(texture2, 128, 0, 16, 16, 53);
}