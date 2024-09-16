#include "Player.h"

Player::Player(Vertex position)
{
	m_playerPos = position;
	m_health = 3;
	m_points = 0;
}

Vertex Player::getPosition()
{
	return m_playerPos;
}

void Player::setPosition(Vertex position)
{
	m_playerPos = position;
}

void Player::setPoints(int x)
{
	m_points = m_points + x;
}

int Player::getPoints()
{
	return m_points;
}

void Player::setHealth(int x)
{
	m_health = m_health + x;
}

int Player::getHealth()
{
	return m_health;
}

void Player::setSuperStatus(bool s)
{
	m_super = s;
}

bool Player::getSuperStatus()
{
	return m_super;
}
