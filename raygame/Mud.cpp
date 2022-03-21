#include "Mud.h"
#include "MazeScene.h"
#include "AABBCollider.h"
#include "Transform2D.h"
#include <raylib.h>

Mud::Mud(float x, float y) : Actor(x, y, "Mud")
{
	setStatic(true);
	setCollider(new AABBCollider(Maze::TILE_SIZE / 2, Maze::TILE_SIZE / 2, this));
	getTransform()->setScale({ Maze::TILE_SIZE / 2, Maze::TILE_SIZE / 2 }
	);
}

void Mud::draw()
{
	Actor::draw();
	
	DrawRectangle(getTransform()->getWorldPosition().x - Maze::TILE_SIZE / 2, getTransform()->getWorldPosition().y - Maze::TILE_SIZE / 2, Maze::TILE_SIZE, Maze::TILE_SIZE, DARKBROWN);
}
