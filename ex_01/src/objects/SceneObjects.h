#ifndef SCENEOBJECTS_H
#define SCENEOBJECTS_H

#include <vector>

#include "../data/Vertex.h"

// ── Geometry Builders (Important Extension Point) ──────────────────────────
// Add declarations for new object meshes here.
std::vector<Vertex> buildCubeVertices();
std::vector<Vertex> buildSphereVertices();
std::vector<Vertex> buildMoverVertices();

#endif // SCENEOBJECTS_H
