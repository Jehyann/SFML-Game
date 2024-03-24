#include <iostream>

#include "Components/MenuSaveRenderer.h"
#include "Components/LoadCreateSave.h"

MenuSaveRenderer::MenuSaveRenderer()
{
	LoadMenuSaveSprite();
}

MenuSaveRenderer::~MenuSaveRenderer()
{
}

void MenuSaveRenderer::Update(float deltaTime, sf::Event event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::P)
		{
			isOpen = true;
			GetOwner()->GetSceneOwner()->SetPause(true);
		}
	}
	if (isOpen == true)
	{
		sf::Vector2i position = sf::Mouse::getPosition(*window);
		position.x = realPositionX(position.x);
		position.y = realPositionY(position.y);
		sf::Rect<float> rectangleSave(camera->x - 75, camera->y + 4.5, 55.0f, 20.0f);
		sf::Rect<float> rectangleLoad(camera->x + 10, camera->y + 4.5, 55.0f, 20.0f);

		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::M)
			{
				isOpen = false;
				GetOwner()->GetSceneOwner()->SetPause(false);
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (rectangleSave.contains(position.x, position.y))
				{
					GetOwner()->GetComponent<LoadCreateSave>()->CreateSave();
					isOpen = false;
					GetOwner()->GetSceneOwner()->SetPause(false);
				}
				if (rectangleLoad.contains(position.x, position.y))
				{
					GetOwner()->GetComponent<LoadCreateSave>()->LoadSave();
					isOpen = false;
					GetOwner()->GetSceneOwner()->SetPause(false);
				}
			}
		}
	}
}

void MenuSaveRenderer::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	if (isOpen == true)
	{
		const auto position = GetOwner()->GetPosition();
		Sprite->setOrigin(0.0f, 0.0f);
		Sprite->setPosition(camera->x-120, camera->y-65.5);
		Sprite->setScale(sf::Vector2f(1.0f, 1.0f));
		_window->draw(*Sprite);
	}
}

int MenuSaveRenderer::realPositionX(int position)
{
	position *= 240;
	position /= window->getSize().x;
	position += camera->x - 120;
	return position;
}

int MenuSaveRenderer::realPositionY(int position)
{
	position *= 135;
	position /= window->getSize().y;
	position += camera->y - 67, 5;
	return position;
}

void MenuSaveRenderer::LoadMenuSaveSprite()
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile("assets/menuPause.png"))
	{
		std::cout << "MENU PAS CHARGE" << std::endl;
	}

	sf::Sprite* sprite = new sf::Sprite();
	sf::IntRect coordonnees(0, 0, 240, 135);
	sprite->setTexture(*texture);
	sprite->setTextureRect(coordonnees);

	Texture = texture;
	Sprite = sprite;
}
