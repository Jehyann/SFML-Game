#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Component.h"

class Collider : public Component
{
public:
	Collider() = default;
	~Collider() override = default;

	float width = 1.0f;
	float height = 1.0f;

	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	void SetWidth(const float _width) { width = _width; }
	void SetHeight(const float _height) { height = _height; }

	static bool IsColliding(const Collider& _colliderA, const Collider& _colliderB);
};
