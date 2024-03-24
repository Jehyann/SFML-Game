#include <iostream>

#include "Components/MenuPlante.h"

MenuPlante::MenuPlante()
{
	LoadMenuPlanteTexture();
}

MenuPlante::~MenuPlante()
{
	delete menuPlanteTexture;
	delete choixCaseTexture;
	delete menuPlanteSprite;
	delete choixCaseSprite;
	delete choixCase2Sprite;
	menuPlanteTexture = nullptr;
	choixCaseTexture = nullptr;
	choixCase2Texture = nullptr;
	menuPlanteSprite = nullptr;
	choixCaseSprite = nullptr;
	choixCase2Sprite = nullptr;
}

void MenuPlante::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);
	if (isOpen == true)
	{
		choixCaseSprite->setOrigin(0.0f, 0.0f);
		choixCaseSprite->setPosition(positionX, positionY);
		choixCaseSprite->setScale(1.0f, 1.0f);
		menuPlanteSprite->setOrigin(0.0f, 0.0f);
		menuPlanteSprite->setPosition(camera->x + 78, camera->y-67.5);
		_window->draw(*choixCaseSprite);
		_window->draw(*menuPlanteSprite);
		
		if (bigOpen == true)
		{
			choixCase2Sprite->setOrigin(0.0f, 0.0f);
			choixCase2Sprite->setPosition(camera->x+menuPlanteCoordonnees[idOpen][0], camera->y+menuPlanteCoordonnees[idOpen][1]);
			_window->draw(*choixCase2Sprite);
		}
	}
}

void MenuPlante::Update(float deltaTime, sf::Event event)
{
	if (!GetOwner()->GetSceneOwner()->isPause())
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left && isOpen == false)
			{
				isOpen = true;
				sf::Vector2i position = sf::Mouse::getPosition(*window);
				position.x = realPositionX(position.x);
				position.y = realPositionY(position.y);
				positionX = position.x - position.x % 16;
				positionY = position.y - position.y % 16;
			}
		}

		if (isOpen == true)
		{
			bigOpen = false;

			sf::Vector2i position = sf::Mouse::getPosition(*window);
			position.x = realPositionX(position.x);
			position.y = realPositionY(position.y);

			for (int i = 0; i < 9; i++)
			{
				sf::Rect<float> rectangle(camera->x + menuPlanteCoordonnees[i][0], camera->y + menuPlanteCoordonnees[i][1], 14.0f, 15.0f);
				if (rectangle.contains(position.x, position.y))
				{
					bigOpen = true;
					idOpen = i;
					if (event.type == sf::Event::MouseButtonReleased)
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							GetOwner()->GetSceneOwner()->Plante("Plante", positionX, positionY, i * 6, true);
							isOpen = false;
							bigOpen = false;
						}
					}
				}
			}

		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				isOpen = false;
			}
		}
	}
}

int MenuPlante::realPositionX(int position)
{
	position *= 240;
	position /= window->getSize().x;
	position += camera->x - 120;
	return position;
}

int MenuPlante::realPositionY(int position)
{
	position *= 135;
	position /= window->getSize().y;
	position += camera->y - 67,5;
	return position;
}

void MenuPlante::LoadMenuPlanteTexture()
{
	sf::Texture* texture1 = new sf::Texture();
	sf::Sprite* sprite1 = new sf::Sprite();
	if (!texture1->loadFromFile("assets/Tiny Wonder Farm/objects&items/MenuPlante.png"))
	{
		std::cout << " Plantage ";
	}
	menuPlanteTexture = texture1;
	menuPlanteSprite = CreateMenuPlanteSprite(texture1, 0, 0, 42, 45);

	sf::Texture* texture2 = new sf::Texture();
	sf::Sprite* sprite2 = new sf::Sprite();
	if (!texture2->loadFromFile("assets/Tiny Wonder Farm/objects&items/choixCase.png"))
	{
		std::cout << " Plantage ";
	}
	choixCaseTexture = texture2;
	choixCaseSprite = CreateMenuPlanteSprite(texture2, 0, 0, 16, 16);

	sf::Texture* texture3 = new sf::Texture();
	sf::Sprite* sprite3 = new sf::Sprite();
	if (!texture3->loadFromFile("assets/Tiny Wonder Farm/objects&items/choixCase2.png"))
	{
		std::cout << " Plantage ";
	}
	choixCase2Texture = texture3;
	choixCase2Sprite = CreateMenuPlanteSprite(texture3, 0, 0, 14, 15);

	for (int i = 0; i < 9; i++)
	{
		int j = 0;
		if (i > 2 && i < 6)
		{
			j = 1;
		}
		if (i > 5)
		{
			j = 2;
		}
		float X = 79 + 13 * (i % 3);
		float Y = -66.5 + 14 * j;
		CreateMenuCoordonnees(X, Y, i);
	}
}

sf::Sprite* MenuPlante::CreateMenuPlanteSprite(sf::Texture* texture, float X, float Y, float Width, float Height)
{
	sf::Sprite* sprite = new sf::Sprite();
	sf::IntRect coordonnees(X, Y, Width, Height);
	sprite->setTexture(*texture);
	sprite->setTextureRect(coordonnees);
	return sprite;
}

void MenuPlante::CreateMenuCoordonnees(float X, float Y, int id)
{
	std::vector<float> coordonnees = { X, Y };
	menuPlanteCoordonnees.emplace(id, coordonnees);
}
