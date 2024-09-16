#include "Gift.h"

Gift::Gift(Vertex position)
{
	m_giftPos = position;
}

Vertex Gift::getPosition()
{
	return m_giftPos;
}

void Gift::setPosition(Vertex position)
{
	m_giftPos = position;
}

