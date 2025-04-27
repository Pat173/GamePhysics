#pragma once
#include "core/Application.h"
#include "core/Math.h"
#include "core/Input.h"

class Hole
{
public:
    Hole(glm::vec2 position, float radius)
        : m_holePosition(position), m_holeRadius(radius) {}

    glm::vec2 m_holePosition;
    float m_holeRadius;
};