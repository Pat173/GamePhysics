#include "Session3.h"
#include "core/Draw.h"
#include "imgui.h"

Session3::Session3() {}

Session3::~Session3() {}

void Session3::OnEnable() {
    Circle circle1 =
        Circle(1, glm::vec2(-8, 8), glm::vec2(3, 3), glm::vec2(0, -9.81f));

    m_circles.push_back(circle1);
}

void Session3::OnDisable() {}

void Session3::Update(float deltaTime) {
    for (int i = 0; i < m_circles.size(); i++) {
        std::vector<glm::vec2> forces{};
        forces.push_back(m_gravity * m_circles[i].mass);

        m_circles[i].UpdateArbLine(deltaTime, bounds, bounds, forces, line);
    }
}

void Session3::Draw() {
    for (int i = 0; i < m_circles.size(); i++) {

        Draw::SetColor(ImColor(255, 255, 255, 255));
        Draw::Circle(m_circles[i].circlePosition, m_circles[i].circleRadius,
                     false);
    }

    Draw::SetColor(ImColor(0, 0, 255, 255));
    

    Draw::Line(glm::vec2(0, 0), glm::normalize(glm::vec2(-line.y, line.x)));
    Draw::SetColor(ImColor(255, 255, 255, 255));
    Draw::Line(glm::vec2(0,0), line);


    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(bounds, -bounds));
    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(-bounds, bounds));
    Draw::Line(glm::vec2(-bounds, bounds), glm::vec2(bounds, bounds));
    Draw::Line(glm::vec2(bounds, -bounds), glm::vec2(bounds, bounds));

    

}

void Session3::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}