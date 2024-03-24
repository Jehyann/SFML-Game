#include <iostream>

#include "Components/Journal.h"
#include "Components/JournalDonnees.h"

Journal::Journal()
{
	LoadJournalSprites();
}

Journal::~Journal()
{
	delete textureJournal;
	delete texturePlante;
	textureJournal = nullptr;
	texturePlante = nullptr;
}

void Journal::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	if (isOpen == true)
	{
		const auto position = GetOwner()->GetPosition();
		sf::Sprite* sprite = journalSprites[0];
		sprite->setOrigin(0.0f, 0.0f);
		sprite->setPosition(camera->x-85, camera->y - 60);
		sprite->setScale(sf::Vector2f(1.0f, 1.0f));
		_window->draw(*sprite);

		std::vector<int> plantedonnees = GetOwner()->GetComponent<JournalDonnees>()->GetPlanteDonnees();
		for (int i = 0;i < plantedonnees.size();i++)
		{
			if (plantedonnees[i] == 1)
			{
				sf::Sprite* planteSprite = plantesSprites[i];
				planteSprite->setOrigin(0.0f, 0.0f);
				planteSprite->setPosition(camera->x - 75, camera->y-50+i*10);
				planteSprite->setScale(sf::Vector2f(0.5f, 0.5f));
				_window->draw(*planteSprite);
			}
		}
		std::vector<int> creaturedonnees = GetOwner()->GetComponent<JournalDonnees>()->GetCreatureDonnees();
		for (int i = 0;i < creaturedonnees.size();i++)
		{
			if (creaturedonnees[i] == 1)
			{
				sf::Sprite* creatureSprite = creaturesSprites[i];
				creatureSprite->setOrigin(0.0f, 0.0f);
				creatureSprite->setPosition(camera->x +15, camera->y - 50 + i * 30);
				creatureSprite->setScale(sf::Vector2f(0.67f, 0.67f));
				_window->draw(*creatureSprite);
			}
		}
	}
}

void Journal::Update(float deltaTime, sf::Event event)
{
	if (!GetOwner()->GetSceneOwner()->isPause())
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::J)
			{
				isOpen = true;
				GetOwner()->GetSceneOwner()->SetPause(true);
			}
		}
	}
	if (isOpen == true)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::M)
			{
				isOpen = false;
				GetOwner()->GetSceneOwner()->SetPause(false);
			}
		}
	}
}

void Journal::LoadJournalSprites()
{
	sf::Texture* texture1 = new sf::Texture();
	sf::Texture* texture2 = new sf::Texture();
	sf::Texture* texture3 = new sf::Texture();

	if (texture1->loadFromFile("assets/journal.png") && texture2->loadFromFile("assets/Tiny Wonder Farm/objects&items/items.png") && texture3->loadFromFile("assets/animals/creaturesSprites.png"))
	{
		textureJournal = texture1;
		texturePlante = texture2;
		textureCreature = texture3;
		
	}
	else
	{
		std::cout << "Pas le temps de regler ce probleme la c'est dimanche" << std::endl;
	}

	CreateJournalSprites(texture1, 0, 0, 170, 120, 0);
	CreateJournalSprites(texture1, 170, 0, 28, 14, 0);
	CreateJournalSprites(texture1, 170, 14, 28, 14, 0);

	CreateJournalSprites(texture2, 0, 0, 16, 16, 1);
	CreateJournalSprites(texture2, 16, 0, 16, 16, 1);
	CreateJournalSprites(texture2, 32, 0, 16, 16, 1);
	CreateJournalSprites(texture2, 48, 0, 16, 16, 1);
	CreateJournalSprites(texture2, 64, 0, 16, 16, 1);
	CreateJournalSprites(texture2, 80, 0, 16, 16, 1);
	CreateJournalSprites(texture2, 96, 0, 16, 16, 1);
	CreateJournalSprites(texture2, 112, 0, 16, 16, 1);
	CreateJournalSprites(texture2, 128, 0, 16, 16, 1);

	CreateJournalSprites(texture3, 0, 26, 27, 17, 2);
	CreateJournalSprites(texture3, 0, 43, 11, 11, 2);
	CreateJournalSprites(texture3, 0, 0, 20, 26, 2);

}

void Journal::CreateJournalSprites(sf::Texture* texture, float X, float Y, float Width, float Height, int type)
{
	sf::Sprite* Sprite = new sf::Sprite();
	sf::IntRect coordonnees(X, Y, Width, Height);
	Sprite->setTexture(*texture);
	Sprite->setTextureRect(coordonnees);

	if (type == 0)
	{
		journalSprites.push_back(Sprite);
	}
	if (type == 1)
	{
		plantesSprites.push_back(Sprite);
	}
	if (type == 2)
	{
		creaturesSprites.push_back(Sprite);
	}
}
