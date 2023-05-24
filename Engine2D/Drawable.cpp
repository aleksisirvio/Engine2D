#include "Drawable.h"
#include "Room.h"
#include "ShaderManager.h"

int Drawable::sKey = -1;

/********************************************************************
Drawable::Drawable

Add to instance list when created.
********************************************************************/
Drawable::Drawable(int sprite, float x, float y, int depth)
{
	Room::getActive()->getLists()->add(this, sKey);
}

/********************************************************************
Drawable::~Drawable

Remove from instance list when destroyed.
********************************************************************/
Drawable::~Drawable()
{
	Room::getActive()->getLists()->remove(this, sKey);
}

/********************************************************************
Drawable::draw

Default draw function. Cuts a single image from the animation sprite
sheet and renders it on the screen.
********************************************************************/
void Drawable::draw()
{
	// Progress animation
	mImageIndex += mSprite.mImageSpeed;
	if (mImageIndex > mSprite.mImageMax)
		mImageIndex -= mSprite.mImageMax;

	if (mShader)
		BeginShaderMode(*mShader);

	DrawTexturePro(
		*mSprite.mTexture,
		{
			floor(mImageIndex) * mSprite.mImageSize.x,
			0,
			mSprite.mImageSize.x * mImageScale.x,
			mSprite.mImageSize.y * mImageScale.y
		},
		{
			mDrawPos.x,
			mDrawPos.y,
			mSprite.mImageSize.x,
			mSprite.mImageSize.y
		},
		{ 0, 0 },
		0,
		CLITERAL(Color){255, 255, 255, (unsigned char)(mImageAlpha * 255)}
	);

	if (mShader)
		EndShaderMode();
}

/********************************************************************
Drawable::move

Move object to the given position. Moving Drawables is centralized
to this function so that the anchor position and draw position
are always updated together.
********************************************************************/
void Drawable::move(Vector2 newPos)
{
	mPos = newPos;
	mDrawPos = { newPos.x - mAnchor.x, newPos.y - mAnchor.y };
}

/********************************************************************
Drawable::change

Changes the current sprite of the Drawable. Logic for updating the
sprite is located in the Sprite class.
********************************************************************/
void Drawable::change(int code)
{
	mImageIndex = 0;
	mSprite.change(code);
}

/********************************************************************
Drawable::setShader

Gives the sprite a new shader.
********************************************************************/
void Drawable::setShader(const std::function<void(ShaderPtr, int)>& handler, int key)
{
	mShader = ShaderManager::get(key);
	handler(mShader, key);
}