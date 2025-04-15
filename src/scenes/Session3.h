#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "core/Simple2DScene.h"
#include "objects/Circle.h"

class Session3 : public Simple2DScene {
public:
    Session3();
    ~Session3();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Session3 Scene"; }

    glm::vec2 GetVectorDirection();

private:

    std::vector<Circle> m_circles = std::vector<Circle>();
    glm::vec2 m_gravity = glm::vec2(0, -9.81);
    float bounds = 20;
    glm::vec2 startPointLine = glm::vec2(8, 13);
    glm::vec2 finishPointLine = glm::vec2(-8, 3);
    glm::vec2 normal;
    bool m_mouseClicked = false;
    glm::vec2 m_clickedMousePos = glm::vec2(0, 0);
};
