#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "constants.cpp"
#include "screen.cpp"
#include "mandelbrot.cpp"
#include "cartesian.cpp"

int main()
{
    int scale = 190;
    Vector2 mouseCartesianPosition;
    std::vector<Vector2> linePositions;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mandelbrot set");

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(WHITE);
            mouseCartesianPosition = Cartesian::GetPosition(GetMousePosition(), scale);

            Cartesian::DrawPlane(scale);
            Cartesian::DrawCoordinates(mouseCartesianPosition);

            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                DrawMandelbrotIterations(Mandelbrot::GetIterations(mouseCartesianPosition), scale);
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}