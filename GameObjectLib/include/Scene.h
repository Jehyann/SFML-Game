#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics.hpp"
#include "GameObject.h"

class GameObject;
class Collider;

class Conditions
{
public:
	void addCondition(std::vector<int> condition) { conditions.push_back(condition); }
	int getCheck();

	std::vector<std::vector<int>> conditions;
};

class Scene
{
public:
	Scene();
	virtual ~Scene() = default;

	void Update(float deltaTime, sf::Event event);
	void Render(sf::RenderWindow* _window);

	GameObject* GetGameObject(std::string name);
	GameObject* GetGameObject(int id);

	int GetGameObjectsSize() { return gameObjects.size(); }

	GameObject* CreateGameObject(const std::string& _name);

	void RemoveGameObject(GameObject* _gameObject);

	Collider* CreateWalls(const std::string& name, float positionX, float positionY);

	GameObject* CreateDummyGameObject(const std::string& name, float position, const sf::Color color);
	GameObject* PlayerAsset(const std::string& name, float positionX, float positionY);
	GameObject* Plante(const std::string& name, float positionX, float positionY, int id, bool actif);
	GameObject* Creature(const std::string& name, float positionX, float positionY, int id, bool actif);
	GameObject* CreateMenuPlante(const std::string& name, sf::RenderWindow* window, Maths::Vector2<float>* camera, sf::View* view);
	GameObject* CreateMenuSave(const std::string& name, sf::RenderWindow* window, Maths::Vector2<float>* camera, sf::View* view);
	GameObject* CreateJournal(const std::string name, sf::RenderWindow* window, Maths::Vector2<float>* camera, sf::View* view);

	void spawnCreature();

	bool isPause() { return pause; }
	void SetPause(bool PAUSE) { pause = PAUSE; }

private:
	std::vector<GameObject*> gameObjects;

	/* 
	On regarde la creature à l'aide de son identifiant
	Chaque créature possède un vector à deux éléments : les plantes et les créatures
	Les deux éléments possède un vector de conditions
	*/
	std::map<int, std::vector<Conditions>> conditionsCreature;
	bool pause = false;
};
