#include "Sprite.h"
#include "TextureManager.h"

/********************************************************************
Sprite::change

Requests a texture and all its info from the texture manager with
the given texture id.
********************************************************************/
bool Sprite::change(int code)
{
	TextureInfoPtr info = TextureManager::get(code);
	if (!info)
		return false;

	mCode = code;
	mTexture = &info->texture;
	mImageSize = info->imageSize;
	mImageMax = info->imageMax;
	mImageSpeed = info->imageSpeed;

	return true;
}