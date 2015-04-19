#pragma once

struct Place
{
    bool topWall;
    bool leftWall;

    Place() :
        topWall(false),
        leftWall(false)
    {}
};

class Labirint
{
public:
    Labirint(int width, int height);
    ~Labirint();

    void generate();

    int width() const { return m_width; }
    int height() const { return m_height; }
    int currentX() const { return m_currentX; }
    int currentY() const { return m_currentY; }
    int exitX() const { return m_exitX; }
    int exitY() const { return m_exitY; }

    void setCurrent(int x, int y);
    void setExit(int x, int y);

    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    Place &place(int x, int y) { return m_places[x][y]; }
    const Place &currentPlace() const { return m_places[m_currentX][m_currentY]; }
    bool atExit() const { return m_currentX == m_exitX && m_currentY == m_exitY; }
private:
    int m_width;
    int m_height;
    int m_currentX;
    int m_currentY;
    int m_exitX;
    int m_exitY;
    Place **m_places;

    const Place &upPlace() const { return m_places[m_currentX][m_currentY - 1]; }
    const Place &downPlace() const { return m_places[m_currentX][m_currentY + 1]; }
    const Place &leftPlace() const { return m_places[m_currentX - 1][m_currentY]; }
    const Place &rightPlace() const { return m_places[m_currentX + 1][m_currentY]; }
};

