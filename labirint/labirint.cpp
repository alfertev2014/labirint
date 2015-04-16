#include "labirint.h"

Labirint::Labirint(int width, int height) :
    m_width(width), m_height(height),
    m_currentX(0),
    m_currentY(0),
    m_exitX(0),
    m_exitY(0)
{
    m_places = new Place*[width];
    for (int i = 0; i < width; ++i)
        m_places[i] = new Place[height];
}

Labirint::~Labirint()
{
    for (int i = 0; i < m_width; ++i)
        delete [] m_places[i];
    delete [] m_places;
}

void Labirint::setCurrent(int x, int y)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;
    m_currentX = x;
    m_currentY = y;
}

void Labirint::setExit(int x, int y)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;
    m_exitX = x;
    m_exitY = y;
}

bool Labirint::moveUp()
{
    if (m_currentY == 0 || currentPlace().topWall)
        return false;
    m_currentY--;
    return true;
}

bool Labirint::moveDown()
{
    if (m_currentY == m_height - 1 || downPlace().topWall)
        return false;
    m_currentY++;
    return true;
}

bool Labirint::moveLeft()
{
    if (m_currentX == 0 || currentPlace().leftWall)
        return false;
    m_currentX--;
    return true;
}

bool Labirint::moveRight()
{
    if (m_currentX == m_width - 1 || rightPlace().leftWall)
        return false;
    m_currentX++;
    return true;
}
