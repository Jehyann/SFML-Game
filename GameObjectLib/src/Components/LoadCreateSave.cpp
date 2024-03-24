#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Components/LoadCreateSave.h"

LoadCreateSave::LoadCreateSave()
{
}

LoadCreateSave::~LoadCreateSave()
{
}

void LoadCreateSave::CreateSave()
{
	std::ofstream savefile(filename.c_str());

	if (savefile.is_open())
	{
		savefile << "GAMEOBJECTS" << std::endl;
		for (int i = 0;i < GetOwner()->GetSceneOwner()->GetGameObjectsSize();i++)
		{
			GameObject* _gameObject = GetOwner()->GetSceneOwner()->GetGameObject(i);
			std::cout << _gameObject->GetName() << std::endl;
			if (_gameObject->GetName() == "Plante" || _gameObject->GetName() == "Creature")
			{
				int boolID = 0;
				if (_gameObject->isActif())
				{
					boolID = 1;
				}
				std::string name = _gameObject->GetName();
				float X = _gameObject->GetPosition().GetX();
				float Y = _gameObject->GetPosition().GetY();
				int id = _gameObject->GetID();
				savefile << name << " " << X << " " << Y << " " << id << " " << boolID << std::endl;
			}
		}
		savefile << "GAMEOBJECTSEND" << std::endl;
	}
	else
	{
		std::cout << "Impossible d'ouvrir la save D:\n";
	}
}

void LoadCreateSave::LoadSave()
{
	std::ifstream savefile(filename);

	if (savefile.is_open())
	{
		std::vector<GameObject*> gameObjects;
		for (int i = 0;i < GetOwner()->GetSceneOwner()->GetGameObjectsSize();i++)
		{
			GameObject* _gameObject = GetOwner()->GetSceneOwner()->GetGameObject(i);
			std::cout << _gameObject->GetName() << std::endl;
			if (_gameObject->GetName() == "Plante" || _gameObject->GetName() == "Creature")
			{
				gameObjects.push_back(_gameObject);
			}
		}
		for (int i = 0; i < gameObjects.size();i++)
		{
			gameObjects[i]->GetSceneOwner()->RemoveGameObject(gameObjects[i]);
			delete gameObjects[i];
		}

		std::string startligne = "GAMEOBJECTS";
		std::string endligne = "GAMEOBJECTSEND";
		std::string ligne;
		bool liredonnees = false;
		bool fin = false;

		while (std::getline(savefile, ligne) && !fin)
		{
			if (ligne == startligne)
			{
				liredonnees = true;
				continue;
			}
			if (ligne == endligne)
			{
				liredonnees = false;
				fin = true;
			}
			if (liredonnees == true)
			{
				std::cout << ligne << std::endl;
				std::istringstream isstream;
				std::string word;

				isstream.str(ligne);
				getline(isstream, word, ' ');
				std::string type = word;

				getline(isstream, word, ' ');
				float positionX = std::stof(word);

				getline(isstream, word, ' ');
				float positionY = std::stof(word);

				getline(isstream, word, ' ');
				int id = std::stoi(word);

				getline(isstream, word, ' ');
				int actifID = std::stoi(word);
				bool actif = true;
				if (actifID == 0)
				{
					actif = false;
				}

				if (type == "Plante")
				{
					GetOwner()->GetSceneOwner()->Plante("Plante", positionX, positionY, id, actif);
				}
				else
				{
					GetOwner()->GetSceneOwner()->Creature("Creature", positionX, positionY, id, actif);
				}

			}
		}
	}
	else
	{
		std::cout << "Impossible d'ouvrir la save D:\n";
	}

}
