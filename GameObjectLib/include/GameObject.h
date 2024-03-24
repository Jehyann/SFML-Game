#pragma once
#include <string>
#include <vector>

#include "Maths/Vector2.h"
#include "Components/Component.h"
#include "Scene.h"

class Component;

class Scene;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	std::string GetName() const { return name; }
	Maths::Vector2<float> GetPosition() const { return position; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }
	Scene* GetSceneOwner() const { return owner; }
	Scene* GetOwner() const { return owner; }
	int GetID() const { return id; }

	bool isActif() { return actif; }
	void Desactivate() { actif = false; }

	void SetName(const std::string& _name) { name = _name; }
	void SetPosition(const Maths::Vector2<float>& _position) { position = _position; }
	void SetWidth(float _width) { width = _width; }
	void SetHeight(float _height) { height = _height; }
	void SetSceneOwner(Scene* _owner) { owner = _owner; }
	void SetOwner(Scene* _owner) { owner = _owner; }
	void SetID(int _id) { id = _id; }

	void AddComponent(Component* _component);

	template<typename T>
	T* GetComponent()
	{
		for (Component* component : components)
		{
			T* componentResult = dynamic_cast<T*>(component);
			if (componentResult != nullptr)
				return componentResult;
		}
		return nullptr;
	}

	template<typename T>
	T* CreateComponent()
	{
		T* component = new T();
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}

	void RemoveComponent(Component* _component);
	void Update(float deltaTime, sf::Event event) const;
	void Render(sf::RenderWindow* _window) const;

private:
	std::string name = "GameObject";
	Maths::Vector2<float> position = Maths::Vector2f::Zero;
	float width = 0.0f;
	float height = 0.0f;
	int id = 0;
	bool actif = true;
	std::vector<Component*> components;
	Scene* owner = nullptr;
};
