#include "Session3.h"
#include "core/Draw.h"
#include "imgui.h"

Session3::Session3() {}

Session3::~Session3() {}

void Session3::OnEnable() {

    m_circles.clear();

    Circle circle1 =
        Circle(1, glm::vec2(-8, 8), glm::vec2(3, 3), glm::vec2(0, -9.81f));
    Circle circle2 =
        Circle(1, glm::vec2(4, -8), glm::vec2(3, 3), glm::vec2(0, -9.81f));

    m_circles.push_back(circle1);
    m_circles.push_back(circle2);

    glm::vec2 lineOnOrigin = finishPointLine - startPointLine;
    normal = glm::normalize(glm::vec2(-lineOnOrigin.y, lineOnOrigin.x));
}

void Session3::OnDisable() {}

void Session3::Update(float deltaTime) {

    for (int i = 0; i < m_circles.size(); i++) {
        std::vector<glm::vec2> forces{};
        forces.push_back(m_gravity * m_circles[i].mass);

        m_circles[i].Update(deltaTime, bounds, bounds, forces);
        m_circles[i].UpdateArbLine( finishPointLine - startPointLine, finishPointLine);
        m_circles[i].Impulse(-GetVectorDirection());
    }

    if (Input::IsMouseClicked(0) == true) {
        m_mouseClicked = true;
        m_clickedMousePos = Input::GetMousePos();
    } else if (Input::IsMouseReleased(0) == true && m_mouseClicked == true) {
        m_clickedMousePos = glm::vec2(0, 0);
        m_mouseClicked = false;
    }
}

void Session3::Draw() {
    for (int i = 0; i < m_circles.size(); i++) {

        if (m_circles[i].GetIsMouseClicked()) {
            glm::vec2 direction = GetVectorDirection();
            glm::vec2 impulse = (-direction * 10.0f);

            Circle futureCircle = m_circles[i];
            std::vector<glm::vec2> forces{};
            forces.push_back(m_gravity * m_circles[i].mass);
            futureCircle.ImpulseSim(impulse);
            futureCircle.Update(0.1f, bounds, bounds, forces);
            futureCircle.UpdateArbLine(finishPointLine - startPointLine, finishPointLine);

            for (int s = 0; s < 30; ++s) {
                Draw::SetColor(ImColor(0, 255, 0, 125));
                futureCircle.Update(0.1f, bounds, bounds, forces);
                futureCircle.UpdateArbLine(finishPointLine - startPointLine, finishPointLine);
                Draw::Circle(futureCircle.circlePosition,
                             futureCircle.circleRadius, false);
            }

            Draw::SetColor(ImColor(0, 255, 0, 255));
        }

        Draw::SetColor(ImColor(255, 255, 255, 255));
        Draw::Circle(m_circles[i].circlePosition, m_circles[i].circleRadius,
                     false);
    }

    Draw::SetColor(ImColor(0, 0, 255, 255));
    

    glm::vec2 centerOfLine = (startPointLine + finishPointLine) * 0.5f;
    Draw::Line(centerOfLine, centerOfLine + normal * 2.0f);
    Draw::SetColor(ImColor(255, 255, 255, 255));
    Draw::Line(startPointLine, finishPointLine);


    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(bounds, -bounds));
    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(-bounds, bounds));
    Draw::Line(glm::vec2(-bounds, bounds), glm::vec2(bounds, bounds));
    Draw::Line(glm::vec2(bounds, -bounds), glm::vec2(bounds, bounds));

    
    if (m_mouseClicked == true) {
        Draw::SetColor(ImColor(255, 0, 0, 255));
        Draw::Line(m_clickedMousePos, Input::GetMousePos());
        Draw::SetColor(ImColor(255, 255, 255, 255));
    }

}

glm::vec2 Session3::GetVectorDirection() {
    glm::vec2 mousePos = Input::GetMousePos();

    return mousePos - m_clickedMousePos;
}

void Session3::DrawGUI() {
    ImGui::Begin("Inspector");
    if (ImGui::Button("Reset", ImVec2(100, 33)))
    {
        OnEnable();
    }
    ImGui::End();
}