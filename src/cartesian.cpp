class Cartesian
{
public:
    static void DrawPlane(int scale)
    {
        DrawAxis(Horizontal, scale);
        DrawAxis(Vertical, scale);
    }

    static void DrawCoordinates(Vector2 mouseCartesianPosition)
    {
        char text[14];
        snprintf(text, 14, "[%.2f,%.2f]", mouseCartesianPosition.x, mouseCartesianPosition.y);
        DrawText(text, SCREEN_WIDTH - 60, SCREEN_HEIGHT - 20, 10, BLACK);
    }

    static Vector2 GetPosition(Vector2 screenPosition, int scale)
    {
        return (Vector2)
        {
            (screenPosition.x - CENTER_X) / scale,
            (CENTER_Y - screenPosition.y) / scale
        };
    }

private:
    enum Axis
    {
        Horizontal,
        Vertical
    };

    static void DrawAxis(Axis axis, int scale)
    {
        float limit;

        // X axis
        if (axis == Horizontal)
        {
            limit = ceil((float)CENTER_X / scale);
            DrawLine(0, CENTER_Y, SCREEN_WIDTH, CENTER_Y, BLACK);
        }

        // Y axis
        else
        {
            limit = ceil((float)CENTER_Y / scale);
            DrawLine(CENTER_X, 0, CENTER_X, SCREEN_HEIGHT, BLACK);
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
            DrawText(text, negativeEndPos.x + textOffsetX, negativeEndPos.y + textOffsetY, 10, BLACK);
            snprintf(text, 5, "%.2f", i);
            DrawText(text, positiveEndPos.x + textOffsetX, positiveEndPos.y + textOffsetY, 10, BLACK);

            DrawLineV(negativeStartPos, negativeEndPos, BLACK);
            DrawLineV(positiveStartPos, positiveEndPos, BLACK);
        }
    }
};