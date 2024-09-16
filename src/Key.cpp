#include "Key.h"

Key::Key(Vertex position)
{
	m_keyPos = position;
}

Vertex Key::getPosition()
{
	return m_keyPos;
}

void Key::setPosition(Vertex position)
{
	m_keyPos = position;
}


