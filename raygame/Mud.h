#pragma once
#include "Actor.h"
class Mud :
	public Actor
{
public:
	Mud(float x, float y);
	void draw() override;
};

