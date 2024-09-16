#pragma once
#include "Vertex.h"

class Board;

class Cake
{
private:
	Vertex m_cakePos;

public:
	Cake() = default;
	Cake(Vertex position);

	Vertex getPosition();
	void setPosition(Vertex position);
};

