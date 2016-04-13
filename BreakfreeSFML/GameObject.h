#pragma once
class GameObject
{
public:
	GameObject(float x = 0, float y = 0, float width = 1, float height = 1);
	~GameObject();

	virtual void Update();
	virtual void Draw();

	float x, y;
	float width, height;
	float centerX, centerY;

	bool Collides(GameObject* other);
	
};

