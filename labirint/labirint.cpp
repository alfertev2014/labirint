#include "labirint.h"

#include <vector>
#include <iostream>
#include <stdlib.h>

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

void printTags(const std::vector<int> &tags)
{
    for (int i = 0; i < tags.size(); ++i)
        std::cout << tags[i] << ", ";
    std::cout << std::endl;
}

void Labirint::generate()
{
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
