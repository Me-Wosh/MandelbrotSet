#include "cartesian.hpp"

#include <iostream>
#include "screen.hpp"
#include "constants.cpp"

enum Cartesian::Axis : short
{
    Horizontal,
    Vertical
};

void Cartesian::DrawPlane(int scale, Color color)
{
    Cartesian::DrawAxis(Horizontal, scale, color);
    Cartesian::DrawAxis(Vertical, scale, color);
}

void Cartesian::DrawCoordinates(Vector2 mouseCartesianPosition, Color color)
{
    char text[14];
    snprintf(text, 14, "[%.2f,%.2f]", mouseCartesianPosition.x, mouseCartesianPosition.y);
    DrawText(text, SCREEN_WIDTH - 60, SCREEN_HEIGHT - 20, 10, color);
}

Vector2 Cartesian::GetPosition(Vector2 screenPosition, int scale)
{
    return (Vector2)
    {
        (screenPosition.x - CENTER_X) / scale,
        (CENTER_Y - screenPosition.y) / scale
    };
}

void Cartesian::DrawAxis(Axis axis, int scale, Color color)
{
    float limit;

    // X axis
    if (axis == Horizontal)
    {
        limit = ceil((float)CENTER_X / scale);
        DrawLine(0, CENTER_Y, SCREEN_WIDTH, CENTER_Y, color);
    }

    // Y axis
    else
    {
        limit = ceil((float)CENTER_Y / scale);
        DrawLine(CENTER_X, 0, CENTER_X, SCREEN_HEIGHT, color);
    }

    // markers
    for (float i = 0.5; i < limit; i += 0.5)
    {
        float wholePart;
        float fractionalPart = modf(i, &wholePart);
        float markerSize = fractionalPart == 0.5 ? SMALL_MARKER_SIZE : NORMAL_MARKER_SIZE;

        Vector2 negativeStartPos;
        Vector2 negativeEndPos;
        Vector2 positiveStartPos;
        Vector2 positiveEndPos;

        int textOffsetX = 0;
        int textOffsetY = 0;

        if (axis == Horizontal)
        {
            negativeStartPos = GetScreenPosition((Vector2) {i * -1, markerSize}, scale, 1);
            negativeEndPos = GetScreenPosition((Vector2) {i * -1, -markerSize}, scale, 1);

            positiveStartPos = GetScreenPosition((Vector2) {i, markerSize}, scale, 1);
            positiveEndPos = GetScreenPosition((Vector2) {i, -markerSize}, scale, 1);

            textOffsetY = markerSize == SMALL_MARKER_SIZE ? 10 : 5;
        }

        else
        {
            negativeStartPos = GetScreenPosition((Vector2) {-markerSize, i * -1}, 1, scale);
            negativeEndPos = GetScreenPosition((Vector2) {markerSize, i * -1}, 1, scale);

            positiveStartPos = GetScreenPosition((Vector2) {-markerSize, i}, 1, scale);
            positiveEndPos = GetScreenPosition((Vector2) {markerSize, i}, 1, scale);

            textOffsetX = markerSize == SMALL_MARKER_SIZE ? 10 : 5;
        }

        char text[5];
        snprintf(text, 5, "%.2f", i * -1);
        DrawText(text, negativeEndPos.x + textOffsetX, negativeEndPos.y + textOffsetY, 10, color);
        snprintf(text, 5, "%.2f", i);
        DrawText(text, positiveEndPos.x + textOffsetX, positiveEndPos.y + textOffsetY, 10, color);

        DrawLineV(negativeStartPos, negativeEndPos, color);
        DrawLineV(positiveStartPos, positiveEndPos, color);
    }
}