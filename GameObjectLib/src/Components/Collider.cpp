#include "Components/Collider.h"

bool Collider::IsColliding(const Collider& _colliderA, const Collider& _colliderB)
{
	const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();
	return (positionA.x < positionB.x + _colliderB.GetWidth() && positionA.x + _colliderA.GetWidth() > positionB.x && positionA.y < positionB.y + _colliderB.GetHeight() && positionA.y + _colliderA.GetHeight() > positionB.y);
}