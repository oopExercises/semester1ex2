#include "Points.h"

Points::Points()
{
	m_cakePoints = 2;
	m_giftPoints = 5;
	m_enemyPoints = 2;
	m_keyPoints = 7;
	m_endLevelPoints = 50;
}

int Points::getCakePoints()
{
	return m_cakePoints;
}

int Points::getkeyPoints()
{
	return m_keyPoints;
}

int Points::getGiftPoints()
{
	return m_giftPoints;
}

int Points::getEnemyPoints()
{
	return m_enemyPoints;
}

int Points::getEndLevelPoints()
{
	return m_endLevelPoints;
}

