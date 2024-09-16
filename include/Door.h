#include "Vertex.h"

class Board;
class Door
{
private:
	Vertex m_doorPos;
public:
	Door() = default;
	Door(Vertex position);

	Vertex getPosition();
	void setPosition(Vertex position);
};