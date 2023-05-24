#pragma once

#include "GameObject.h"

/********************************************************************
Updatable

Parent for all objects that must be updated every frame.
********************************************************************/
class Updatable : private GameObject
{
public:
	Updatable();
	~Updatable() override;
	void update() override { /* No default implementation, usage widely varies */ };

	static void setKey(int newKey) { sKey = newKey; }

private:
	static int sKey;
};
