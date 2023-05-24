#include "ShaderManager.h"

ShaderMap ShaderManager::sShaderMap{ 0 };

/********************************************************************
ShaderManager::load

Loads the shader at the given path info memory and gives it the
given id.
********************************************************************/
bool ShaderManager::load(int code, const char* path)
{
	Shader shader = LoadShader(0, path);
	ShaderPtr shaderPtr = std::make_shared<Shader>(shader);
	sShaderMap.insert({ code, shaderPtr });
	return true;
}

/********************************************************************
ShaderManager::unload

Unloads the shader with the given id from memory and removes it from
the shader map.
********************************************************************/
bool ShaderManager::unload(int code)
{
	if (!sShaderMap.count(code))
		return false;

	UnloadShader(*sShaderMap.at(code));
	return true;
}

/********************************************************************
ShaderManager::unloadAll

Unloads all shaders from memory
********************************************************************/
void ShaderManager::unloadAll()
{
	for (const auto& shader : sShaderMap)
		unload(shader.first);

	sShaderMap.clear();
}

/********************************************************************
ShaderManager::get

Returns a pointer to the shader with the given code.
********************************************************************/
ShaderPtr ShaderManager::get(int code)
{
	return (sShaderMap.count(code) ? sShaderMap.at(code) : nullptr);
}