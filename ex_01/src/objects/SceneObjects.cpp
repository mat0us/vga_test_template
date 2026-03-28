#include "SceneObjects.h"

#include <cmath>

// ── Geometry Builders (Important Extension Point) ──────────────────────────
// Add new build<Name>Vertices() functions in this file.

std::vector<Vertex> buildCubeVertices()
{
    // Vertex format: { {x, y, z}, {r, g, b} }
    // - position: x (left/right), y (up/down), z (front/back)
    // - color: r (red), g (green), b (blue), each in range 0.0 to 1.0
    return {
        // Front face
        Vertex{ {-0.5f, -0.5f,  0.5f}, {0.90f, 0.20f, 0.20f} },
        Vertex{ { 0.5f, -0.5f,  0.5f}, {0.90f, 0.20f, 0.20f} },
        Vertex{ { 0.5f,  0.5f,  0.5f}, {0.90f, 0.20f, 0.20f} },
        Vertex{ {-0.5f, -0.5f,  0.5f}, {0.90f, 0.20f, 0.20f} },
        Vertex{ { 0.5f,  0.5f,  0.5f}, {0.90f, 0.20f, 0.20f} },
        Vertex{ {-0.5f,  0.5f,  0.5f}, {0.90f, 0.20f, 0.20f} },

        // Back face
        Vertex{ { 0.5f, -0.5f, -0.5f}, {0.20f, 0.80f, 0.30f} },
        Vertex{ {-0.5f, -0.5f, -0.5f}, {0.20f, 0.80f, 0.30f} },
        Vertex{ {-0.5f,  0.5f, -0.5f}, {0.20f, 0.80f, 0.30f} },
        Vertex{ { 0.5f, -0.5f, -0.5f}, {0.20f, 0.80f, 0.30f} },
        Vertex{ {-0.5f,  0.5f, -0.5f}, {0.20f, 0.80f, 0.30f} },
        Vertex{ { 0.5f,  0.5f, -0.5f}, {0.20f, 0.80f, 0.30f} },

        // Left face
        Vertex{ {-0.5f, -0.5f, -0.5f}, {0.20f, 0.45f, 0.90f} },
        Vertex{ {-0.5f, -0.5f,  0.5f}, {0.20f, 0.45f, 0.90f} },
        Vertex{ {-0.5f,  0.5f,  0.5f}, {0.20f, 0.45f, 0.90f} },
        Vertex{ {-0.5f, -0.5f, -0.5f}, {0.20f, 0.45f, 0.90f} },
        Vertex{ {-0.5f,  0.5f,  0.5f}, {0.20f, 0.45f, 0.90f} },
        Vertex{ {-0.5f,  0.5f, -0.5f}, {0.20f, 0.45f, 0.90f} },

        // Right face
        Vertex{ { 0.5f, -0.5f,  0.5f}, {0.95f, 0.75f, 0.20f} },
        Vertex{ { 0.5f, -0.5f, -0.5f}, {0.95f, 0.75f, 0.20f} },
        Vertex{ { 0.5f,  0.5f, -0.5f}, {0.95f, 0.75f, 0.20f} },
        Vertex{ { 0.5f, -0.5f,  0.5f}, {0.95f, 0.75f, 0.20f} },
        Vertex{ { 0.5f,  0.5f, -0.5f}, {0.95f, 0.75f, 0.20f} },
        Vertex{ { 0.5f,  0.5f,  0.5f}, {0.95f, 0.75f, 0.20f} },

        // Top face
        Vertex{ {-0.5f,  0.5f,  0.5f}, {0.70f, 0.30f, 0.90f} },
        Vertex{ { 0.5f,  0.5f,  0.5f}, {0.70f, 0.30f, 0.90f} },
        Vertex{ { 0.5f,  0.5f, -0.5f}, {0.70f, 0.30f, 0.90f} },
        Vertex{ {-0.5f,  0.5f,  0.5f}, {0.70f, 0.30f, 0.90f} },
        Vertex{ { 0.5f,  0.5f, -0.5f}, {0.70f, 0.30f, 0.90f} },
        Vertex{ {-0.5f,  0.5f, -0.5f}, {0.70f, 0.30f, 0.90f} },

        // Bottom face
        Vertex{ {-0.5f, -0.5f, -0.5f}, {0.20f, 0.85f, 0.85f} },
        Vertex{ { 0.5f, -0.5f, -0.5f}, {0.20f, 0.85f, 0.85f} },
        Vertex{ { 0.5f, -0.5f,  0.5f}, {0.20f, 0.85f, 0.85f} },
        Vertex{ {-0.5f, -0.5f, -0.5f}, {0.20f, 0.85f, 0.85f} },
        Vertex{ { 0.5f, -0.5f,  0.5f}, {0.20f, 0.85f, 0.85f} },
        Vertex{ {-0.5f, -0.5f,  0.5f}, {0.20f, 0.85f, 0.85f} },
    };
}

std::vector<Vertex> buildSphereVertices()
{
    // ── Sphere Detail Settings (Important Extension Point) ─────────────────
    // Increase segment counts for smoother sphere, decrease for performance.
    constexpr int latSegments = 18;
    constexpr int lonSegments = 36;
    constexpr float radius = 0.6f;
    constexpr float pi = 3.14159265358979323846f;

    std::vector<Vertex> vertices;
    vertices.reserve(static_cast<size_t>(latSegments * lonSegments * 6));

    auto makeVertex = [radius](float theta, float phi) -> Vertex {
        const float x = radius * std::sin(theta) * std::cos(phi);
        const float y = radius * std::cos(theta);
        const float z = radius * std::sin(theta) * std::sin(phi);

        // Soft vertical gradient based on y coordinate.
        const float t = (y / radius + 1.0f) * 0.5f;
        const float r = 0.35f + 0.60f * t;
        const float g = 0.30f + 0.58f * t;
        const float b = 0.20f + 0.35f * t;

        return Vertex{{x, y, z}, {r, g, b}};
    };

    for (int lat = 0; lat < latSegments; ++lat) {
        const float theta0 = pi * (static_cast<float>(lat) / static_cast<float>(latSegments));
        const float theta1 = pi * (static_cast<float>(lat + 1) / static_cast<float>(latSegments));

        for (int lon = 0; lon < lonSegments; ++lon) {
            const float phi0 = 2.0f * pi * (static_cast<float>(lon) / static_cast<float>(lonSegments));
            const float phi1 = 2.0f * pi * (static_cast<float>(lon + 1) / static_cast<float>(lonSegments));

            const Vertex v00 = makeVertex(theta0, phi0);
            const Vertex v01 = makeVertex(theta0, phi1);
            const Vertex v10 = makeVertex(theta1, phi0);
            const Vertex v11 = makeVertex(theta1, phi1);

            // Two triangles for one quad on the sphere surface.
            vertices.push_back(v00);
            vertices.push_back(v10);
            vertices.push_back(v11);

            vertices.push_back(v00);
            vertices.push_back(v11);
            vertices.push_back(v01);
        }
    }

    return vertices;
}

std::vector<Vertex> buildMoverVertices()
{
    // Asymmetrical tetra-like marker for translation demos.
    // Topology: 4 triangles (12 vertices), GL_TRIANGLES.
    const Vertex a{{-0.45f, -0.25f, -0.20f}, {0.95f, 0.35f, 0.25f}};
    const Vertex b{{ 0.55f, -0.15f, -0.15f}, {0.25f, 0.80f, 0.95f}};
    const Vertex c{{-0.35f,  0.45f, -0.10f}, {0.35f, 0.95f, 0.35f}};
    const Vertex d{{-0.10f, -0.05f,  0.55f}, {0.95f, 0.90f, 0.35f}};

    return {
        // Side 1
        a, b, c,
        // Side 2
        a, b, d,
        // Side 3
        a, c, d,
        // Side 4
        b, c, d,
    };
}
