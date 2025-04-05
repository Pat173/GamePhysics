#include "Assignment1.h"

#include "core/Draw.h"
#include "imgui.h"

Assignment1::Assignment1() {}

Assignment1::~Assignment1() {}

void Assignment1::OnEnable()
{
    Circle circle1 = Circle(1, glm::vec2(0, 0), glm::vec2(5, -9.81f));
    Circle circle2 = Circle(0.5f, glm::vec2(-2, 2), glm::vec2(-6, -9.81f));
    Circle circle3 = Circle(2, glm::vec2(2, 2), glm::vec2(-3, 3));

    m_circles.push_back(circle1);
    m_circles.push_back(circle2);
    m_circles.push_back(circle3);
}


void Assignment1::OnDisable() {}

void Assignment1::Update(float deltaTime)
{
    for (int i = 0; i < m_circles.size(); i++) {
        m_circles[i].Update(deltaTime, 5, 5);
    }

}

void Assignment1::Draw() {

    for (int i = 0; i < m_circles.size(); i++) {
        Draw::Circle(m_circles[i].circlePosition, m_circles[i].circleRadius,
                     false);
    }

    
    Draw::Line(glm::vec2(-5, -5), glm::vec2(5, -5));
    Draw::Line(glm::vec2(-5, -5), glm::vec2(-5, 5));
    Draw::Line(glm::vec2(-5, 5), glm::vec2(5, 5));
    Draw::Line(glm::vec2(5, -5), glm::vec2(5, 5));
}

void Assignment1::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}