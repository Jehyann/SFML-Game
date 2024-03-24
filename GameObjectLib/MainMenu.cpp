#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("assets/Pixeled.ttf"))
	{
		std::cout << "File not found";
	}

	//~~~~New Game~~~~//
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::Green);
	mainMenu[0].setString("New Game");
	mainMenu[0].setCharacterSize(50);
	mainMenu[0].setPosition(400, 200);

	//~~~~Continue~~~~//
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::Green);
	mainMenu[1].setString("Continue");
	mainMenu[1].setCharacterSize(50);
	mainMenu[1].setPosition(400, 300);

	//~~~~Option~~~~//
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::Green);
	mainMenu[2].setString("Option");
	mainMenu[2].setCharacterSize(50);
	mainMenu[2].setPosition(400, 400);


	//~~~~Quit~~~~//
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color::Green);
	mainMenu[3].setString("Quit");
	mainMenu[3].setCharacterSize(50);
	mainMenu[3].setPosition(400, 500);

	MainMenuSelected = 0;
	mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
}

MainMenu::~MainMenu() {}

void MainMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; ++i)
	{
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp()
{
	if (MainMenuSelected >= 0)
	{
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Green);

		MainMenuSelected--;
		if (MainMenuSelected < 0)
		{
			MainMenuSelected = Max_main_menu - 1;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
	}
}

void MainMenu::MoveDown()
{
	if (MainMenuSelected < Max_main_menu)
	{
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Green);
		MainMenuSelected++;
		if (MainMenuSelected == Max_main_menu)
		{
			MainMenuSelected = 0;

		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
	}
}
