#pragma once

#include "Component.h"

class JournalDonnees : public Component
{
public :
	JournalDonnees();
	~JournalDonnees();

	void addPlante(int id) { plantesDonnees[id] = 1; }
	void addCreature(int id) { creaturesDonnees[id] = 1; }

	std::vector<int> GetPlanteDonnees() { return plantesDonnees; }
	std::vector<int> GetCreatureDonnees() { return creaturesDonnees; }

private :
	std::vector<int> plantesDonnees = { 0,0,0,0,0,0,0,0,0 };
	std::vector<int> creaturesDonnees = { 0,0,0 };
};