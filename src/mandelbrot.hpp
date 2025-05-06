#include <complex>
#include <vector>
#include "raylib.h"

class Mandelbrot
{
public:
    static void DrawIterations(std::vector<Vector2> iterations, int scale, Color color = RED);
    static void DrawSetBoundaries(std::vector<Vector2>* positions, Color color = BLACK);
    static std::vector<Vector2> GetIterations(Vector2 screenPosition);
    static std::vector<Vector2> GetStablePositions(int width, int height, int scale);

private:
    static std::complex<float> Function(std::complex<float> z, std::complex<float> c);
};