#pragma once

#include <raylib.h>

/********************************************************************
Sprite

Holds information about a single sprite cut from a texture.
********************************************************************/
class Sprite
{
public:
	Sprite() = default;
	bool change(int code);

	Vector2 getImageSize() { return mImageSize; }
	float getImageMax() { return mImageMax; }
	float getImageSpeed() { return mImageSpeed; }

private:
	int mCode{ -1 };
	Texture2D* mTexture{ 0 };
	Vector2 mImageSize{ 0 };
	float mImageMax{ 0 };
	float mImageSpeed{ 0 };

	// Allow drawable objects to use sprite directly
	friend Drawable;
};

