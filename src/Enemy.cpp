#include "Enemy.h"

Enemy::Enemy(Vertex position)
{
	m_enemyPos = position;
}

Vertex Enemy::getPosition()
{
	return m_enemyPos;
}

void Enemy::setPosition(Vertex position)
{
	m_enemyPos = position;
}
