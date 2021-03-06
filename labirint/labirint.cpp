#include "labirint.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

Labirint::Labirint(int width, int height) :
    m_width(width), m_height(height),
    m_currentX(0),
    m_currentY(0),
    m_exitX(0),
    m_exitY(0)
{
    createArrays(width, height);
}

Labirint::~Labirint()
{
    deleteArrays();
}

void printTags(const std::vector<int> &tags)
{
    for (int i = 0; i < tags.size(); ++i)
        std::cout << tags[i] << ", ";
    std::cout << std::endl;
}

void Labirint::generate()
{
    if (!m_places)
        return;
    std::vector<Place> column(m_height);
    std::vector<int> tags(m_height);
    int nextTag = m_height;
    for (int i = m_height - 1; i >= 0; --i)
        tags[i] = i;
    for (int x = m_width - 1; x >= 0; --x) {
        //printTags(tags);
        for (int y = m_height - 1; y >= 0; --y) {
            column[y].topWall = false;
            if (column[y].leftWall)
                tags[y] = nextTag++;
            column[y].leftWall = false;
        }
        for (int y = m_height - 1; y > 0; --y) {
            if (tags[y] == tags[y - 1] || rand() % 2) {
                column[y].topWall = true;
            }
            else {
                int tag = tags[y - 1];
                for (int yy = m_height - 1; yy >= 0; --yy) {
                    if (tags[yy] == tag)
                        tags[yy] = tags[y];
                }
            }
        }
        if (x == 0) {
            break;
        }
        int card = 0;
        int prevTag = -1;
        for (int y = m_height - 1; y >= 0; --y) {
            if (card > 0 && tags[y] != prevTag) {
                column[y + rand() % card + 1].leftWall = false;
                card = 0;
            }
            card++;
            prevTag = tags[y];
            column[y].leftWall = rand() % 2;
        }
        if (card > 0)
            column[rand() % card].leftWall = false;
        for (int y = m_height - 1; y >= 0; --y)
            place(x, y) = column[y];
    }
    //printTags(tags);
    for (int y = m_height - 1; y > 0; --y) {
        if (tags[y] != tags[y - 1]) {
            int tag = tags[y - 1];
            for (int yy = m_height - 1; yy >= 0; --yy) {
                if (tags[yy] == tag)
                    tags[yy] = tags[y];
            }
            place(0, y).topWall = false;
        }
        else
            place(0, y).topWall = column[y].topWall;
        place(0, y).leftWall = true;
    }
}

void Labirint::generate(int width, int height)
{
    deleteArrays();
    createArrays(width, height);
    generate();
}

void Labirint::save(const char *fileName) const
{
    if (!m_places)
        return;
    std::fstream f(fileName, std::ios_base::out);
    if (!f.is_open())
        return;
    f << m_width << std::endl;
    f << m_height << std::endl;
    f << m_currentX << std::endl;
    f << m_currentY << std::endl;
    f << m_exitX << std::endl;
    f << m_exitY << std::endl;
    for (int j = 0; j < m_height; ++j) {
        for (int i = 0; i < m_width; ++i) {
            f.put(place(i, j).leftWall ? '|' : ' ');
            f.put(place(i, j).topWall ? '^' : ' ');
        }
        f << std::endl;
    }
}

void Labirint::load(const char *filename)
{
    std::fstream f(filename, std::ios_base::in);
    if (!f.is_open())
        return;

    deleteArrays();
    f >> m_width >> m_height;
    if (m_width <= 0 || m_height <= 0)
        return;
    createArrays(m_width, m_height);

    f >> m_currentX >> m_currentY >> m_exitX >> m_exitY;

    if (m_currentX < 0) m_currentX = 0;
    if (m_currentX >= m_width) m_currentX = m_width - 1;
    if (m_currentY < 0) m_currentY = 0;
    if (m_currentY >= m_height) m_currentY = m_height - 1;
    if (m_exitX < 0) m_exitX = 0;
    if (m_exitX >= m_width) m_exitX = m_width - 1;
    if (m_exitY < 0) m_exitY = 0;
    if (m_exitY >= m_height) m_exitY = m_height - 1;

    std::string line;
    while (!f.eof() && line.empty())
        std::getline(f, line);

    for (int j = 0; j < m_height; ++j) {
        int len = line.size() / 2;
        if (len > m_width)
            len = m_width;
        for (int i = 0; i < len; ++i) {
            place(i, j).leftWall = line[2 * i] == '|';
            place(i, j).topWall = line[2 * i + 1] == '^';
        }
        if (f.eof())
            break;
        std::getline(f, line);
    }
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
    markTrace(upTrace());
    m_currentY--;
    return true;
}

bool Labirint::moveDown()
{
    if (m_currentY == m_height - 1 || downPlace().topWall)
        return false;
    markTrace(downTrace());
    m_currentY++;
    return true;
}

bool Labirint::moveLeft()
{
    if (m_currentX == 0 || currentPlace().leftWall)
        return false;
    markTrace(leftTrace());
    m_currentX--;
    return true;
}

bool Labirint::moveRight()
{
    if (m_currentX == m_width - 1 || rightPlace().leftWall)
        return false;
    markTrace(rightTrace());
    m_currentX++;
    return true;
}

void Labirint::markTrace(const Trace &nextTrace)
{
    currentTrace() = nextTrace == PlacePath ? PlaceVisited : PlacePath;
}

void Labirint::deleteArrays()
{
    if (m_places) {
        for (int i = 0; i < m_width; ++i)
            delete [] m_places[i];
        delete [] m_places;
        m_places = 0;
    }
    if (m_traces) {
        for (int i = 0; i < m_width; ++i)
            delete [] m_traces[i];
        delete [] m_traces;
        m_traces = 0;
    }
}

void Labirint::createArrays(int width, int height)
{
    m_places = new Place*[width];
    for (int i = 0; i < width; ++i)
        m_places[i] = new Place[height];
    m_traces = new Trace*[width];
    for (int i = 0; i < width; ++i) {
        m_traces[i] = new Trace[height];
        for (int j = 0; j < height; ++j)
            m_traces[i][j] = PlaceNotVisited;
    }
    m_width = width;
    m_height = height;
}
