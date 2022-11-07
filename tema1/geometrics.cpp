#include "geometrics.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* geometrics::CreateTriangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(0, 2 * length, 0), color),
        VertexFormat(corner + glm::vec3(3 * length , length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* geometrics::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    int ratio,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length / ratio, 0), color),
        VertexFormat(corner + glm::vec3(0, length / ratio , 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* geometrics::CreateCircle(
    const std::string& name,
    int centerOfCircleX,
    int centerOfCircleY,
    int radius,
    glm::vec3 color,
    bool fill)
{

    // A triangle with angles of 75, 75, 30.
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(centerOfCircleX, centerOfCircleY, 0), color)
    };

    for (int i = 0; i < 360; i++) {
        vertices.push_back(VertexFormat(glm::vec3(centerOfCircleX + (radius * cos(i * 2 * M_PI / 360)),
            centerOfCircleY + (radius * sin(i * 2 * M_PI / 360)), 0), color));
    }

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 1; i < 360; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    indices.push_back(0);
    indices.push_back(360);
    indices.push_back(1);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}
