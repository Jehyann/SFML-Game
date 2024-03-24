#include "Components/Component.h"

Component::Component(GameObject* owner)
{
	this->owner = owner;
}

void Component::Update(float deltaTime, sf::Event event) {}

void Component::Render(sf::RenderWindow* _window) {}

