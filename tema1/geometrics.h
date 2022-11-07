#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace geometrics
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateTriangle(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string& name, int centerOfCircleX, int centerOfCircleY, int radius, glm::vec3 color, bool fill);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, int ratio, bool fill = false);
}
