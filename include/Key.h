#pragma once
#include "Vertex.h"

class Board;

class Key
{
private:
	Vertex m_keyPos;

public:
	Key() = default;
	Key(Vertex position);

	Vertex getPosition();
	void setPosition(Vertex position);
};

