#pragma once

#include <vector>
#include "Components/Component.h"
#include "Components/Collider.h"

class Mapcollider : public Component
{
public:
	void setwall();
	static std::vector<Collider*> GetWalls() { return walls; }

private:
	static std::vector<Collider*> walls;
};
