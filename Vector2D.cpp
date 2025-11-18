#include "Vector2D.h"
#include <iostream>

int Vector2D::getX() const
{
    return x;
}

int Vector2D::getY() const
{
    return y;
}

void Vector2D::setX(int val)
{
    x = val;
}

void Vector2D::setY(int val)
{
    y = val;
}

void Vector2D::print() const
{
    std::cout << x << ", " << y << std::endl;
}