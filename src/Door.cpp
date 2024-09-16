#include "Door.h"

Door::Door(Vertex position)
{
	m_doorPos = position;
}

Vertex Door::getPosition()
{
	return m_doorPos;
}

void Door::setPosition(Vertex position)
{
	m_doorPos = position;
}
