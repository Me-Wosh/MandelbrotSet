#include "raylib.h"

class Cartesian
{
public:
    static void DrawPlane(int scale, Color color = GRAY);
    static void DrawCoordinates(Vector2 mouseCartesianPosition, Color color = GRAY);
    static Vector2 GetPosition(Vector2 screenPosition, int scale);

private:
    enum Axis : short;
    static void DrawAxis(Axis axis, int scale, Color color);
};

