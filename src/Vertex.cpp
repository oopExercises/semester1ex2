#include "Vertex.h"

int Vertex::getX()
{
	return m_x;

}

int Vertex::getY()
{
	return m_y;
}

void Vertex::setX(int x)
{
	m_x = x;
}

void Vertex::setY(int y)
{
	m_y = y;
}

bool Vertex::sameVertex(Vertex point)
{
	return (m_x == point.getX() && m_y == point.getY());
}
