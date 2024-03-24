#pragma once

#include "GameObject.h"
#include "Components/Component.h"

class LoadCreateSave : public Component
{
public:
	LoadCreateSave();
	~LoadCreateSave();

	void setWindow(sf::RenderWindow* _window) { window = _window; }
	void setView(sf::View* _view) { view = _view; }
	void setCamera(Maths::Vector2<float>* _camera) { camera = _camera; }

	void CreateSave();
	void LoadSave();

private:
	std::string filename = "save.txt";

	sf::RenderWindow* window = nullptr;
	sf::View* view = nullptr;
	Maths::Vector2<float>* camera = nullptr;
};
