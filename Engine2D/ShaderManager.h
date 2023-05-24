#pragma once

#include <raylib.h>
#include <unordered_map>
#include <memory>

using ShaderPtr = std::shared_ptr<Shader>;
using ShaderMap = std::unordered_map<int, ShaderPtr>;

/********************************************************************
ShaderManager

Manages shaders in the program memory.
********************************************************************/
class ShaderManager
{
public:
	static bool load(int code, const char* path);
	static bool unload(int code);
	static void unloadAll();
	static ShaderPtr get(int code);

private:
	static ShaderMap sShaderMap;
};
