#pragma once

#include "Board.h"
#include "Player.h"
#include "Points.h"

//class Board;

class Controller
{
	
private:
	bool m_gameOver;
	bool m_levelFinished;
	int m_levelNum;
	int m_allPoints;
	int m_health;
	Points m_points;
	
public:
	Controller();
	void runGame();
	void move(int, Board&);
};