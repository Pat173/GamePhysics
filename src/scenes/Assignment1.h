#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "core/Simple2DScene.h"
#include "objects/Circle.h"

class Assignment1 : public Simple2DScene
{
public:
    Assignment1();
    ~Assignment1();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment1 Scene"; }

private:
    std::vector<Circle> m_circles = std::vector<Circle>();
    glm::vec2 m_gravity = glm::vec2(0, -9.81);
    float bounds = 20;
};
