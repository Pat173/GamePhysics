#include "Assignment2.h"
#include "core/Draw.h"
#include "imgui.h"

Assignment2::Assignment2() {}

Assignment2::~Assignment2() {}

void Assignment2::OnEnable() {
    Circle circle1 =
        Circle(1, glm::vec2(0, 0), glm::vec2(3, 3), glm::vec2(0, -9.81f));
    Circle circle2 =
        Circle(0.5f, glm::vec2(-1, 1), glm::vec2(-4, 0), glm::vec2(0, -9.81f));
    Circle circle3 =
        Circle(2, glm::vec2(1, 2), glm::vec2(2, 6), glm::vec2(0, -9.81));

    m_circles.push_back(circle1);
    m_circles.push_back(circle2);
    m_circles.push_back(circle3);
}

void Assignment2::OnDisable() {}

void Assignment2::Update(float deltaTime) {
    for (int i = 0; i < m_circles.size(); i++) {
        std::vector<glm::vec2> forces{};
        forces.push_back(m_gravity * m_circles[i].mass);

        // if (Input::IsMouseDown(0) == true)
        /*
        if (m_circles[i].circlePosition.x < -5) {
            glm::vec2 forcefield = glm::vec2(200, 200);
            forces.push_back(forcefield);
        }*/

        m_circles[i].Update(deltaTime, bounds, bounds, forces);
    }
}

void Assignment2::Draw() {
    for (int i = 0; i < m_circles.size(); i++) {
        Draw::Circle(m_circles[i].circlePosition, m_circles[i].circleRadius,
                     false);
    }

    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(bounds, -bounds));
    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(-bounds, bounds));
    Draw::Line(glm::vec2(-bounds, bounds), glm::vec2(bounds, bounds));
    Draw::Line(glm::vec2(bounds, -bounds), glm::vec2(bounds, bounds));

    Draw::SetColor(ImColor(255,0,0,255));
    Draw::Circle(Input::GetMousePos(), 1.5f, false);
}

void Assignment2::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}