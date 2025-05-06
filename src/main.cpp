#include <iostream>
#include <string>
#include "raylib.h"
#include "cartesian.hpp"
#include "mandelbrot.hpp"
#include "constants.cpp"

int main()
{
    const auto stopwatchStart = std::chrono::high_resolution_clock::now();

    int scale = 190;
    Vector2 mouseCartesianPosition;
    std::vector<Vector2> stablePositions = Mandelbrot::GetStablePositions(SCREEN_WIDTH, SCREEN_HEIGHT, scale);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mandelbrot set");
    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);

    const auto stopwatchEnd = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(stopwatchEnd - stopwatchStart);
    printf("Started in: %lld milliseconds", milliseconds.count());

    while (!WindowShouldClose())
    {
        mouseCartesianPosition = Cartesian::GetPosition(GetMousePosition(), scale);

        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
        {
            ShowCursor();
        }

        BeginDrawing();

            ClearBackground(WHITE);

            Mandelbrot::DrawSetBoundaries(&stablePositions);

            Cartesian::DrawPlane(scale);
            Cartesian::DrawCoordinates(mouseCartesianPosition);

            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                HideCursor();
                Mandelbrot::DrawIterations(Mandelbrot::GetIterations(mouseCartesianPosition), scale);
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}