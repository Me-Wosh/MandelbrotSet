#include "screen.hpp"

#include "constants.cpp"

Vector2 GetScreenPosition(Vector2 cartesianPosition, int scale)
{
    return (Vector2)
    {
        CENTER_X + cartesianPosition.x * scale,
        CENTER_Y - cartesianPosition.y * scale
    };
}

Vector2 GetScreenPosition(Vector2 cartesianPosition, int scaleX, int scaleY)
{
    return (Vector2)
    {
        CENTER_X + cartesianPosition.x * scaleX,
        CENTER_Y - cartesianPosition.y * scaleY
    };
}