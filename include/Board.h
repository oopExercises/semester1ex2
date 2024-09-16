#pragma once

#include <iostream> 
#include "io.h"
#include <vector>
#include <fstream>
#include "Vertex.h"
#include "Player.h"
#include "Enemy.h"
#include "Cake.h"
#include "Gift.h"
#include "Key.h"
#include "Door.h"

const char cakeChar = '*';
const char giftChar = '$';
const char enemyChar = '&';
const char pacmanChar = 'a';
const char superPacmanChar = '@';
const char keyChar = '%';
const char wallChar = '#';
const char doorChar = 'D';

class Board 
{
private:
	//the character player (pacman)
	Player m_pacman;
	Vertex m_initPlayerPos; //the vertex of the pacman when the game starts
	//the other objects
	std::vector<Enemy> demon;
	std::vector<Vertex> initDemonPos; //the vertexes of the demons when the game starts
	std::vector<Cake> cake;
	std::vector<Gift> gift;
	std::vector<Key> key;
	std::vector<Vertex> door;

	//=============================================================

	std::ifstream file;	//file to read
	std::vector<std::string> map;		//vector of a map
	std::vector<std::string> levels;	//vector of all the levels

	//=============================================================

	int m_number_of_levels;
	bool m_giftIsTaken;
	bool m_super;
	int m_superSteps;
	int m_playerHealth;
	int m_allPoints;
	int m_currentLevel;
	//==============================================================
	//private functons
	int getHeight();

public:
	//constructor
	//the constructor has 3 parameters, the first is the points, the second is the health, the third is the health
	Board(int, int, int);

	void buildMap(int index);
	
	//updating functions
	void updatePlayerPos(Vertex position);
	void updateMap(int, int, char);
	void updateKeys(Vertex);
	void updateScreen(char);
	void updateSuperSteps(int);
	void updateSuperStatus(bool);
	void updateDemonPos(Vertex position, int index);
	void updatePlayerHealth();
	void updatePlayerPoints(int);

	//getting functions
	Player getPlayer();
	std::vector<std::string> getMap();
	int getPlayerPoints();
	int getPlayerHealth();
	Enemy getDemon(int);
	Vertex getInitPlayerPos();
	char getTile(int, int);
	int getNumberOfLevels();
	bool getSuperStatus();
	bool getSuperSteps();
	int getCakeSize();
	int getDemonSize();
	Vertex getDoor(int);

	//removing functions
	void removeKey(int, int);
	void removeCake(int, int);
	void removeGift(int, int);
	void removeDemon(int, int);
	void removeDoor(int,int);

	//reseting position functions
	void resetPlayerPos();
	void resetDemonPos();

	//printing functions
	void printScreen();
	void printMessage(int);
};