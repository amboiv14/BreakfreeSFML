#include "GameObject.h"

GameObject::GameObject(float x, float y, float width, float height)
:x(x), y(y), width(width), height(height)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
}

bool GameObject::Collides(GameObject* other)
{
	if (x + width > other->x && x < other->x + other->width &&
		y + height > other->y && y < other->y + other->height) {
		return true;
	}
	return false;
}
