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

void DrawMandelbrotIterations(std::vector<Vector2> iterations, int scale)
{
    for (int i = 1; i < iterations.size(); i++)
    {
        Vector2 startPosition = GetScreenPosition(iterations[i-1], scale);
        Vector2 endPosition = GetScreenPosition(iterations[i], scale);

        DrawLineV(startPosition, endPosition, RED);
    }
}