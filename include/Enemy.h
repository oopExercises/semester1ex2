#pragma once
#include "Vertex.h"

class Board;

class Enemy
{
private:
	Vertex m_enemyPos;

public:
	Enemy() = default;
	Enemy(Vertex position);

	Vertex getPosition();
	void setPosition(Vertex position);
};