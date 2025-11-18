#pragma once

class Vector2D
{
    int x, y;

public:
    int getX() const; // Geter za X
    int getY() const; // Geter za Y

    void setX(int); // Seter za X
    void setY(int); // Seter za Y

    void print() const; // Ispis za klasu
};