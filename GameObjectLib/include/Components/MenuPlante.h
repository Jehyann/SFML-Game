#pragma once

#include "SFML/Graphics.hpp"
#include "Components/Component.h"

class MenuPlante : public Component
{
public:
	MenuPlante();
	~MenuPlante() override;

	void Render(sf::RenderWindow* _window) override; // fait tout le rendu
	void Update(float deltaTime, sf::Event event) override;

	void setWindow(sf::RenderWindow* _window) { window = _window; }
	void setView(sf::View* _view) { view = _view; }
	void setCamera(Maths::Vector2<float>* _camera) { camera = _camera; }
	int realPositionX(int position);
	int realPositionY(int position);

	void LoadMenuPlanteTexture();
	sf::Sprite* CreateMenuPlanteSprite(sf::Texture* texture, float X, float Y, float Width, float Height);
	void CreateMenuCoordonnees(float X, float Y, int id);

private:
	sf::Texture* choixCaseTexture = nullptr;
	sf::Sprite* choixCaseSprite = nullptr;
	sf::Texture* choixCase2Texture = nullptr;
	sf::Sprite* choixCase2Sprite = nullptr;
	sf::Texture* menuPlanteTexture = nullptr;
	sf::Sprite* menuPlanteSprite = nullptr;
	std::map<int, std::vector<float>> menuPlanteCoordonnees;

	float positionX, positionY;
	bool isOpen = false;
	bool bigOpen = false;
	int idOpen = 0;
	
	sf::RenderWindow* window = nullptr;
	sf::View* view = nullptr;
	Maths::Vector2<float>* camera = nullptr;
};
