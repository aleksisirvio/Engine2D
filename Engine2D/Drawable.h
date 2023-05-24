#pragma once

#include <raylib.h>
#include <functional>
#include <memory>

#include "GameObject.h"
#include "Sprite.h"

using ShaderPtr = std::shared_ptr<Shader>;

/********************************************************************
Drawable

Parent for all objects that must be drawn every frame.
********************************************************************/
class Drawable : private GameObject
{
public:
	Drawable(int sprite, float x, float y, int depth);
	~Drawable() override;
	void draw() override;
	virtual void move(Vector2 newPos);
	void change(int code);

	Vector2 getPos() { return mPos; }

	void setShader(const std::function<void(ShaderPtr, int)>& handler, int key);

	static void setKey(int newKey) { sKey = newKey; }

private:
	Vector2 mAnchor{ 0 };
	Vector2 mPos{ 0 };
	Vector2 mDrawPos{ 0 };
	Sprite mSprite;
	float mImageIndex{ 0 };
	float mImageAlpha{ 0 };
	Vector2 mImageScale{ 0 };
	ShaderPtr mShader = nullptr;

	static int sKey;
};

