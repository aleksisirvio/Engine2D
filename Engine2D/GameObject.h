#pragma once

/********************************************************************
GameObject

All objects stored in InstLists must inherit the common GameObject
interface. Provides empty implementations for step and draw methods.
********************************************************************/
class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void step() { /* Empty */ };
	virtual void draw() { /* Empty */ };

	int getDepth() const { return depth; }

private:
	int depth{ 0 };
};