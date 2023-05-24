#pragma once

#include <raylib.h>
#include <unordered_map>
#include <functional>
#include <memory>

/********************************************************************
TextureInfo

Individual texture and information about the animation it holds.
********************************************************************/
struct TextureInfo
{
	int code;
	Texture2D texture;
	Vector2 imageSize;
	float imageMax;
	float imageSpeed;
};

using TextureInfoPtr = std::shared_ptr<TextureInfo>;
using TextureMap = std::unordered_map<int, TextureInfoPtr>;
using TextureInfoFiller = std::function<bool(TextureInfoPtr)>;

/********************************************************************
TextureManager

Manages textures in program memory.
********************************************************************/
class TextureManager
{
public:
	static bool load(int code, const char* path);
	static bool unload(int code);
	static void unloadAll();
	static TextureInfoPtr get(int code);

private:
	static TextureMap sTextureMap;
	static TextureInfoFiller sInfoFiller;
};