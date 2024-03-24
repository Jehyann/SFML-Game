#pragma once

#include "SFML/Graphics.hpp"
#include "Component.h"

class Journal : public Component
{
public:
	Journal();
	~Journal() override;

	void Render(sf::RenderWindow* _window) override;
	void Update(float deltaTime, sf::Event event) override;

	void LoadJournalSprites();
	void CreateJournalSprites(sf::Texture* texture, float X, float Y, float Width, float Height, int type);

	void setWindow(sf::RenderWindow* _window) { window = _window; }
	void setView(sf::View* _view) { view = _view; }
	void setCamera(Maths::Vector2<float>* _camera) { camera = _camera; }

private:
	sf::Texture* textureJournal = nullptr;
	sf::Texture* texturePlante = nullptr;
	sf::Texture* textureCreature = nullptr;
	std::vector<sf::Sprite*> plantesSprites;
	std::vector<sf::Sprite*> creaturesSprites;
	std::vector<sf::Sprite*> journalSprites;

	bool isOpen = false;
	int numeroPage = 0;

	sf::RenderWindow* window = nullptr;
	sf::View* view = nullptr;
	Maths::Vector2<float>* camera = nullptr;
};
