#pragma once
#include "Vertex.h"

class Board;

class Gift
{
private:
	Vertex m_giftPos;
public:
	Gift() = default;
	Gift (Vertex position);

	Vertex getPosition();
	void setPosition(Vertex position);
};