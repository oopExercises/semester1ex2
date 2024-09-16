#pragma once
#include "Vertex.h"

class Board;

class Player
{
private:
	Vertex m_playerPos;
	int m_health;
	int m_points;
	bool m_super;

public:
	Player() = default;
	Player(Vertex position);

	Vertex getPosition();
	void setPosition(Vertex position);

	void setHealth(int);
	int getHealth();

	void setSuperStatus(bool s);
	bool getSuperStatus();

	void setPoints(int);
	int getPoints();

	
};