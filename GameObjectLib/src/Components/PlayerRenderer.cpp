#include "Components/PlayerRenderer.h"
#include <iostream>


std::map<int, sf::Sprite*> PlayerRenderer::playerSprites;

PlayerRenderer::PlayerRenderer()
{
	LoadPlayerSprites();
}

PlayerRenderer::~PlayerRenderer()
{
	delete texture;
	delete playerSprite;
	texture = nullptr;
	playerSprite = nullptr;
}


void PlayerRenderer::Update(float deltaTime, sf::Event event)
{
	if (!GetOwner()->GetSceneOwner()->isPause())
	{
		if (moving == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Right * speed * deltaTime);
				moving = true;
				lookingRight = true;
				lookingLeft = false;
				spriteLength = 0.125;

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Left * speed * deltaTime);
				moving = true;
				lookingRight = false;
				lookingLeft = true;
				spriteLength = 0.125;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Up * speed * deltaTime);
				moving = true;
				spriteLength = 0.125;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Down * speed * deltaTime);
				moving = true;
				spriteLength = 0.125;
			}
		}
		spriteUpdateTimer += deltaTime;
		updateSprite(spriteUpdateTimer);
		moving = false;
		spriteLength = 0.5;
	}
}

void PlayerRenderer::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto position = GetOwner()->GetPosition();
	playerSprite->setOrigin(0.0f, 0.0f);
	playerSprite->setPosition(position.x, position.y); // positionne le player
	playerSprite->setScale(sf::Vector2f(1.0f, 1.0f));
	_window->draw(*playerSprite);
}

void PlayerRenderer::CreatePlayerSprites(sf::Texture* texture, float X, float Y, float Width, float Height, int id)
{
	sf::Sprite* playerSprite = new sf::Sprite();
	sf::IntRect coordonnees(X, Y, Width, Height);
	playerSprite->setTexture(*texture);
	playerSprite->setTextureRect(coordonnees);
	playerSprites.emplace(id, playerSprite);
}

void PlayerRenderer::LoadPlayerSprites()
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile("assets/player/playerasset.png"))
	{
		std::cout << " Pourquoi il charge pas le perso là ";
	}

	//idle animation
	CreatePlayerSprites(texture, 0, 0, 24, 24, 0);
	CreatePlayerSprites(texture, 24, 0, 24, 24, 1);
	CreatePlayerSprites(texture, 48, 0, 24, 24, 2);
	CreatePlayerSprites(texture, 72, 0, 24, 24, 3);

	//walkingLeft
	CreatePlayerSprites(texture, 0, 24, 24, 24, 10);
	CreatePlayerSprites(texture, 24, 24, 24, 24, 11);
	CreatePlayerSprites(texture, 48, 24, 24, 24, 12);
	CreatePlayerSprites(texture, 72, 24, 24, 24, 13);
	CreatePlayerSprites(texture, 96, 24, 24, 24, 14);
	CreatePlayerSprites(texture, 120, 24, 24, 24, 15);
	CreatePlayerSprites(texture, 144, 24, 24, 24, 16);
	CreatePlayerSprites(texture, 168, 24, 24, 24, 17);

	//walkingRight
	CreatePlayerSprites(texture, 0, 48, 24, 24, 20);
	CreatePlayerSprites(texture, 24, 48, 24, 24, 21);
	CreatePlayerSprites(texture, 48, 48, 24, 24, 22);
	CreatePlayerSprites(texture, 72, 48, 24, 24, 23);
	CreatePlayerSprites(texture, 96, 48, 24, 24, 24);
	CreatePlayerSprites(texture, 120, 48, 24, 24, 25);
	CreatePlayerSprites(texture, 144, 48, 24, 24, 26);
	CreatePlayerSprites(texture, 168, 48, 24, 24, 27);
}

void PlayerRenderer::updateSprite(float timer)
{
	sf::Sprite* sprite = nullptr;
	int sprite_id;
	if (timer >= spriteLength)
	{
		idle++;
		spriteUpdateTimer = 0;
	}
	if (moving == false)
	{
		sprite_id = idle % 2;
		if (lookingLeft == true)
		{
			sprite = playerSprites[sprite_id];
		}
		else
		{
			sprite = playerSprites[sprite_id + 2];
		}
	}
	else
	{
		if (lookingLeft == true)
		{
			sprite_id = idle % 8;
			sprite = playerSprites[sprite_id + 10];
		}
		else
		{
			sprite_id = idle % 8;
			sprite = playerSprites[sprite_id + 20];
		}
	}
	playerSprite = sprite;
}