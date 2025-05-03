class Mandelbrot
{
public:
    static std::vector<Vector2> GetIterations(Vector2 c)
    {
        std::vector<Vector2> iterations;
        auto z = (Vector2){ 0, 0 };

        for (int i = 0; i < 1000; i++)
        {
            Vector2 result = Function(z, c);

            if (isinf(result.x) || isinf(result.y))
            {
                break;
            }

            iterations.push_back(result);
            z = result;
        }

        return iterations;
    }

private:
    // f(z) = z^2 + c
    static Vector2 Function(Vector2 z, Vector2 c)
    {
        return Vector2Add(Vector2MultiplyV(z, z), c);
    }
};