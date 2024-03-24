#include <iostream>
#include <random>

#include "Scene.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics.hpp"

#include "Components/ShapeRenderer.h"
#include "Components/Collider.h"
#include "Components/PlayerRenderer.h"
#include "Components/PlanteRenderer.h"
#include "Components/CreatureRenderer.h"
#include "Components/MenuPlante.h"
#include "Components/MenuSaveRenderer.h"
#include "Components/LoadCreateSave.h"
#include "Components/Journal.h"
#include "Components/JournalDonnees.h"

Scene::Scene()
{
	//poule : conditions : une tomate
	Conditions pouleConditionsCreature;

	Conditions pouleConditionsPlante;
	std::vector<int> conditionPoulePlante1{41, 1};
	pouleConditionsPlante.addCondition(conditionPoulePlante1);

	std::vector<Conditions> pouleConditions{pouleConditionsCreature, pouleConditionsPlante};
	conditionsCreature.emplace(1, pouleConditions);

	//vache : conditions : deux blé une poule
	Conditions vacheConditionsCreature;
	std::vector<int> conditionVacheCreature1{1, 1};
	vacheConditionsCreature.addCondition(conditionVacheCreature1);

	Conditions vacheConditionsPlante;
	std::vector<int> conditionVachePlante1{23, 2};
	vacheConditionsPlante.addCondition(conditionVachePlante1);

	std::vector<Conditions> vacheConditions{vacheConditionsCreature, vacheConditionsPlante};
	conditionsCreature.emplace(0, vacheConditions);

	//ice climber : conditions : 1 légume de chaque
	Conditions ICsConditionsCreature;

	Conditions ICsConditionsPlante;

	std::vector<int> conditionICsPlante1{ 47, 2 };
	ICsConditionsPlante.addCondition(conditionICsPlante1);
	std::vector<Conditions> ICsConditions{ ICsConditionsCreature, ICsConditionsPlante };
	conditionsCreature.emplace(2, ICsConditions);
}

void Scene::Update(float deltaTime, sf::Event event)
{
	GameObject* player = GetGameObject("Player");
	GameObject* menuPlante = GetGameObject("MenuPlante");
	GameObject* menuSave = GetGameObject("MenuSave");
	GameObject* journal = GetGameObject("Journal");

	auto playerid = std::find(gameObjects.begin(), gameObjects.end(), player);
	if (playerid != gameObjects.end()) 
	{
		std::rotate(playerid, playerid+1, gameObjects.end());
	}

	auto menuPlanteid = std::find(gameObjects.begin(), gameObjects.end(), menuPlante);
	if (menuPlanteid != gameObjects.end())
	{
		std::rotate(menuPlanteid, menuPlanteid + 1, gameObjects.end());
	}

	auto journalid = std::find(gameObjects.begin(), gameObjects.end(), journal);
	if (journalid != gameObjects.end())
	{
		std::rotate(journalid, journalid + 1, gameObjects.end());
	}

	auto menuSaveid = std::find(gameObjects.begin(), gameObjects.end(), menuSave);
	if (menuSaveid != gameObjects.end())
	{
		std::rotate(menuSaveid, menuSaveid + 1, gameObjects.end());
	}
	
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		gameObjects[i]->Update(deltaTime, event);
	}
	spawnCreature();
}

void Scene::Render(sf::RenderWindow* _window)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

GameObject* Scene::GetGameObject(std::string name)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetName() == name)
		{
			return gameObjects[i];
		}
	}
	return nullptr;
}

GameObject* Scene::GetGameObject(int id)
{
	return gameObjects[id];
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetSceneOwner(this);
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);
	return gameObject;
}

void Scene::RemoveGameObject(GameObject* _gameObject)
{
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), _gameObject), gameObjects.end());
}

Collider* Scene::CreateWalls(const std::string& name, float positionX, float positionY)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionX, positionY));

	Collider* collider = gameObject->CreateComponent<Collider>();
	collider->SetWidth(16.0f);
	collider->SetHeight(16.0f);

	return collider;
}

GameObject* Scene::CreateDummyGameObject(const std::string& name, float position, const sf::Color color)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(position, position));

	Collider* collider = gameObject->CreateComponent<Collider>();
	collider->SetWidth(20.0f);
	collider->SetHeight(20.0f);

	ShapeRenderer* shapeRenderer = gameObject->CreateComponent<ShapeRenderer>();
	shapeRenderer->SetColor(color);

	return gameObject;
}

GameObject* Scene::PlayerAsset(const std::string& name, float positionX, float positionY)
{
	GameObject* playerObject = CreateGameObject(name);
	playerObject->SetPosition(Maths::Vector2f(positionX, positionY));

	PlayerRenderer* playerRenderer = playerObject->CreateComponent<PlayerRenderer>();
	playerRenderer->SetSprite(0);

	return playerObject;
}

GameObject* Scene::Plante(const std::string& name, float positionX, float positionY, int id, bool actif)
{
	GameObject* planteObject = CreateGameObject(name);
	planteObject->SetPosition(Maths::Vector2f(positionX, positionY));
	planteObject->SetID(id);

	PlanteRenderer* planteRenderer = planteObject->CreateComponent<PlanteRenderer>();
	planteRenderer->SetID(id);
	planteRenderer->SetSprite(id);
	planteRenderer->SetGrowthTime(id);
	if (actif == false)
	{
		planteObject->Desactivate();
	}

	return planteObject;
}

GameObject* Scene::Creature(const std::string& name, float positionX, float positionY, int id, bool actif)
{
	GameObject* creatureObject = CreateGameObject(name);
	creatureObject->SetPosition(Maths::Vector2f(positionX, positionY));
	creatureObject->SetID(id);

	CreatureRenderer* creatureRenderer = creatureObject->CreateComponent<CreatureRenderer>();
	creatureRenderer->SetSprite(id);
	if (actif == false)
	{
		creatureObject->Desactivate();
	}

	return creatureObject;
}

GameObject* Scene::CreateMenuPlante(const std::string& name, sf::RenderWindow* window, Maths::Vector2<float>* camera, sf::View* view)
{
	GameObject* menuPlante = CreateGameObject(name);

	MenuPlante* menuPlanteComponent = menuPlante->CreateComponent<MenuPlante>();
	menuPlanteComponent->setWindow(window);
	menuPlanteComponent->setView(view);
	menuPlanteComponent->setCamera(camera);

	return menuPlante;
}

GameObject* Scene::CreateMenuSave(const std::string& name, sf::RenderWindow* window, Maths::Vector2<float>* camera, sf::View* view)
{
	GameObject* menuSave = CreateGameObject(name);

	MenuSaveRenderer* menuSaveRendererComponent = menuSave->CreateComponent<MenuSaveRenderer>();
	menuSaveRendererComponent->setWindow(window);
	menuSaveRendererComponent->setView(view);
	menuSaveRendererComponent->setCamera(camera);

	LoadCreateSave* loadCreateSaveComponent = menuSave->CreateComponent<LoadCreateSave>();
	loadCreateSaveComponent->setWindow(window);
	loadCreateSaveComponent->setView(view);
	loadCreateSaveComponent->setCamera(camera);

	return menuSave;
}

GameObject* Scene::CreateJournal(const std::string name, sf::RenderWindow* window, Maths::Vector2<float>* camera, sf::View* view)
{
	GameObject* journal = CreateGameObject(name);

	Journal* journalComponent = journal->CreateComponent<Journal>();
	journalComponent->setWindow(window);
	journalComponent->setView(view);
	journalComponent->setCamera(camera);

	JournalDonnees* journalDonneesComponent = journal->CreateComponent<JournalDonnees>();

	return journal;
}

void Scene::spawnCreature()
{
	//On regarde pour toutes les creatures possible si les conditions de spawn sont remplies
	for (int i = 0; i < conditionsCreature.size(); i++)
	{
		//On initialise le nombre de check à vérifier
		int check = 0;

		//On regarde le nombre de check à vérifier
		for (int j = 0; j < conditionsCreature[i].size(); j++)
		{
			check += conditionsCreature[i][j].getCheck();
		}

		//On initialise le nombre de check vérifiés
		int count = 0;

		//On initialise la liste de checks vérifiés
		std::vector<Component*> components;

		int currPlanteCount = 0;
		int currCreatureCount = 0;
		//On regarde le nombre de check vérifiés sur la liste des game objects
		for (int j = 0; j < gameObjects.size(); j++)
		{
			//On vérifie si les game object sont des plantes ou des créatures
			PlanteRenderer* planteComponent = gameObjects[j]->GetComponent<PlanteRenderer>();
			CreatureRenderer* creatureComponent = gameObjects[j]->GetComponent<CreatureRenderer>();

			//On vérifie si la plante est une condition
			if (planteComponent != nullptr && currPlanteCount < conditionsCreature[i][1].getCheck() && planteComponent->GetOwner()->isActif())
			{
				for (int k = 0; k < conditionsCreature[i][1].conditions.size(); k++)
				{
					if (conditionsCreature[i][1].conditions[k][0] == planteComponent->GetID())
					{
						currPlanteCount++;
						count++;
						components.push_back(planteComponent);
					}
				}
			}
			if (creatureComponent != nullptr && currCreatureCount < conditionsCreature[i][0].getCheck() && creatureComponent->GetOwner()->isActif())
			{
				for (int k = 0; k < conditionsCreature[i][0].conditions.size(); k++)
				{
					if (conditionsCreature[i][0].conditions[k][0] == creatureComponent->GetID())
					{
						currCreatureCount++;
						count++;
						components.push_back(creatureComponent);
					}
				}
			}
		}
		if (check == count)
		{
			int X = rand() % 30;
			int Y = rand() % 20;
			Creature("Creature", 16 * X, 16 * Y, i, true);
			GetGameObject("Journal")->GetComponent<JournalDonnees>()->addCreature(i);
			for (int m = 0; m < components.size(); m++)
			{
				components[m]->GetOwner()->Desactivate();
			}
		}
	}
}

int Conditions::getCheck()
{
	int check = 0;
	for (int i = 0; i < conditions.size(); i++)
	{
		check += conditions[i][1];
	}
	return check;
}
