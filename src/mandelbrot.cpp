#include "mandelbrot.hpp"

#include "cartesian.hpp"
#include "screen.hpp"

void Mandelbrot::DrawIterations(std::vector<Vector2> iterations, int scale, Color color)
{
    for (int i = 1; i < iterations.size(); i++)
    {
        Vector2 startPosition = GetScreenPosition(iterations[i-1], scale);
        Vector2 endPosition = GetScreenPosition(iterations[i], scale);

        DrawLineV(startPosition, endPosition, color);
    }

    Vector2 cPosition = GetScreenPosition(iterations[1], scale);
    DrawCircleV(cPosition, 2.5, PURPLE);
}

void Mandelbrot::DrawSetBoundaries(std::vector<Vector2>* positions, Color color)
{
    for (Vector2 position : *positions)
    {
        DrawPixelV(position, color);
    }
}

std::vector<Vector2> Mandelbrot::GetIterations(Vector2 screenPoint)
{
    std::vector<Vector2> iterations = { (Vector2) { 0, 0 } };
    std::complex<float> z(0, 0);
    std::complex<float> c(screenPoint.x, screenPoint.y);

    for (int i = 0; i < 100; i++)
    {
        std::complex<float> result = Function(z, c);

        if (isinf(result.real()) || isinf(result.imag()))
        {
            break;
        }

        iterations.push_back((Vector2){ result.real(), result.imag() });
        z = result;
    }

    return iterations;
}

std::vector<Vector2> Mandelbrot::GetStablePositions(int width, int height, int scale)
{
    std::vector<Vector2> positions = { (Vector2) { 0, 0 } };

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Vector2 screenPosition = (Vector2){ (float)i, (float)j };
            Vector2 cartesianPosition = Cartesian::GetPosition(screenPosition, scale);

            std::complex<float> z(0, 0);
            std::complex<float> c(cartesianPosition.x, cartesianPosition.y);

            positions.push_back(screenPosition);

            for (int _ = 0; _ < 500; _++)
            {
                std::complex<float> result = Function(z, c);

                if (isinf(result.real()) || isinf(result.imag()))
                {
                    positions.pop_back();
                    break;
                }

                z = result;
            }
        }
    }

    return positions;
}

// f(z) = z^2 + c
std::complex<float> Mandelbrot::Function(std::complex<float> z, std::complex<float> c)
{
    return z*z + c;
}