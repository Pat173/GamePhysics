#include "Assignment1.h"

#include "core/Draw.h"
#include "imgui.h"

Assignment1::Assignment1() {}

Assignment1::~Assignment1() {}

void Assignment1::OnEnable()
{
    Circle circle1 =
        Circle(1, glm::vec2(0, 0), glm::vec2(3, 3), glm::vec2(0, -9.81f));
    Circle circle2 = Circle(0.5f, glm::vec2(-1,1) , glm::vec2(-4, 0), glm::vec2(0, -9.81f));
    Circle circle3 = Circle(2, glm::vec2(1,2) , glm::vec2(2, 6), glm::vec2(0, -9.81));

    m_circles.push_back(circle1);
    m_circles.push_back(circle2);
    m_circles.push_back(circle3);
}


void Assignment1::OnDisable() {}

void Assignment1::Update(float deltaTime)
{
    for (int i = 0; i < m_circles.size(); i++) {

        std::vector<glm::vec2> forces{};
        forces.push_back(m_gravity * m_circles[i].mass);

        //if (Input::IsMouseDown(0) == true)


        if (m_circles[i].circlePosition.x < -5)
        {
            glm::vec2 forcefield = glm::vec2(200, 200);
            forces.push_back(forcefield);
        }

        m_circles[i].Update(deltaTime, bounds, bounds, forces);
    }

}

void Assignment1::Draw() {

    for (int i = 0; i < m_circles.size(); i++) {
        Draw::Circle(m_circles[i].circlePosition, m_circles[i].circleRadius,
                     false);
    }

    
    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(bounds, -bounds));
    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(-bounds, bounds));
    Draw::Line(glm::vec2(-bounds, bounds), glm::vec2(bounds, bounds));
    Draw::Line(glm::vec2(bounds, -bounds), glm::vec2(bounds, bounds));

    Draw::Circle(Input::GetMousePos(), 2, true);

}

void Assignment1::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}