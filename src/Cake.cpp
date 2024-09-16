#include "Cake.h"

Cake::Cake(Vertex position)
{
	m_cakePos = position;
}

Vertex Cake::getPosition()
{
	return m_cakePos;
}

void Cake::setPosition(Vertex position)
{
	m_cakePos = position;
}

