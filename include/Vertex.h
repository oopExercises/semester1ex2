#pragma once


struct Vertex
{
    int m_x;
    int m_y;

    Vertex() = default;
    Vertex(int x, int y) : m_x(x), m_y(y) {}

    int getX();
    int getY();

    void setX(int x);
    void setY(int y);

    bool sameVertex(Vertex point);


};