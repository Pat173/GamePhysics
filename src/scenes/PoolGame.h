#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "core/Simple2DScene.h"
#include "objects/Circle.h"
#include "objects/Hole.h"

class PoolGame : public Simple2DScene {
public:
    PoolGame();
    ~PoolGame();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Session4 Scene"; }

    glm::vec2 GetVectorDirection();
    void SpawnCircle(glm::vec2 position,
                     glm::vec2 velocity,
                     glm::vec2 acceleration);
    int Score = 0;

private:

    std::vector<Circle> m_circles = std::vector<Circle>();
    std::vector<Hole> m_holes = std::vector<Hole>();

    glm::vec2 m_gravity = glm::vec2(0, 0);
    float m_screenHeight = 10;
    float m_screenWidth = 20;
    // glm::vec2 startPointLine = glm::vec2(8, 13);
    // glm::vec2 finishPointLine = glm::vec2(-8, 3);
    glm::vec2 normal;
    bool m_mouseClicked = false;
    glm::vec2 m_clickedMousePos = glm::vec2(0, 0);

    glm::vec2 m_newCirclePos = glm::vec2(0, 0);
    glm::vec2 m_newCircleVelocity = glm::vec2(0, 0);
    glm::vec2 m_newCircleAcc = glm::vec2(0, 0);


};
