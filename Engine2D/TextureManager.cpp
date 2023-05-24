#include "TextureManager.h"

TextureMap TextureManager::sTextureMap{ 0 };
TextureInfoFiller TextureManager::sInfoFiller{ 0 };

/********************************************************************
TextureManager::load

Used to populate the texture map. Texture info filler function must
be set before using this function.
********************************************************************/
bool TextureManager::load(int code, const char* path)
{
	if (!sInfoFiller)
		return false;

	TextureInfoPtr newTexturePtr = std::make_shared<TextureInfo>();
	newTexturePtr->code = code;
	if (!sInfoFiller(newTexturePtr))
		return false;

	newTexturePtr->texture = LoadTexture(path);

	sTextureMap.insert({ code, newTexturePtr });
	return true;
}

/********************************************************************
TextureManager::unload

Unloads a specific texture and removes it from the texture map.
********************************************************************/
bool TextureManager::unload(int code)
{
	if (!sTextureMap.count(code))
		return false;

	UnloadTexture(sTextureMap.at(code)->texture);
	sTextureMap.erase(code);
	return true;
}

/********************************************************************
TextureManager::unloadAll

Unloads all textures and clears the texture map.
********************************************************************/
void TextureManager::unloadAll()
{
	for (const auto& texture : sTextureMap)
		unload(texture.first);

	sTextureMap.clear();
}

/********************************************************************
TextureManager::get

Returns the texture with the given code.
********************************************************************/
TextureInfoPtr TextureManager::get(int code)
{
	return (sTextureMap.count(code) ? sTextureMap.at(code) : nullptr);
}