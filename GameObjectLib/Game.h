#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Game 
{

	Game(float width, float height);
	~Game();

	void draw(sf::RenderWindow& window);
	void gamesave();

	void gameCamera();


};