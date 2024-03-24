#pragma once

#include "Components/Component.h"

class MenuSaveRenderer : public Component
{
public:
	MenuSaveRenderer();
	~MenuSaveRenderer();

	void Update(float deltaTime, sf::Event event) override;
	void Render(sf::RenderWindow* _window) override;

	void setWindow(sf::RenderWindow* _window) { window = _window; }
	void setView(sf::View* _view) { view = _view; }
	void setCamera(Maths::Vector2<float>* _camera) { camera = _camera; }

	int realPositionX(int position);
	int realPositionY(int position);

	void LoadMenuSaveSprite();

private:
	sf::Texture* Texture = nullptr;
	sf::Sprite* Sprite = nullptr;
	bool isOpen = false;

	float positionX, positionY;

	sf::RenderWindow* window = nullptr;
	sf::View* view = nullptr;
	Maths::Vector2<float>* camera = nullptr;
};