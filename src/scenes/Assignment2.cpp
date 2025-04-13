#include "Assignment2.h"
#include "core/Draw.h"
#include "imgui.h"

Assignment2::Assignment2() {}

Assignment2::~Assignment2() {}

void Assignment2::OnEnable() {
    Circle circle1 =
        Circle(1, glm::vec2(0, 0), glm::vec2(3, 3), glm::vec2(0, -9.81f));
    Circle circle2 = Circle(0.5f, glm::vec2(-1, 1), glm::vec2(-4, 0),
                            glm::vec2(0, -9.81f));
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

        m_circles[i].Update(deltaTime, bounds, bounds, forces, -GetVectorDirection());
    }


    if (Input::IsMouseClicked(0) == true) {
        m_mouseClicked = true;
        m_clickedMousePos = Input::GetMousePos();
    } else if (Input::IsMouseReleased(0) == true && m_mouseClicked == true) {
        m_clickedMousePos = glm::vec2(0, 0);
        m_mouseClicked = false;
    }
}

void Assignment2::Draw() {
    for (int i = 0; i < m_circles.size(); i++) {

        if (m_circles[i].GetIsMouseClicked()) {
            glm::vec2 direction = GetVectorDirection();
            glm::vec2 impulse = (-direction * 10.0f);

            PredictTrajectoryWithBounces(m_circles[i], impulse, 30, 0.25f);

            Draw::SetColor(ImColor(0, 255, 0, 255));
        }

        Draw::Circle(m_circles[i].circlePosition, m_circles[i].circleRadius,
                     false);
        Draw::SetColor(ImColor(255, 255, 255, 255));
    }

    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(bounds, -bounds));
    Draw::Line(glm::vec2(-bounds, -bounds), glm::vec2(-bounds, bounds));
    Draw::Line(glm::vec2(-bounds, bounds), glm::vec2(bounds, bounds));
    Draw::Line(glm::vec2(bounds, -bounds), glm::vec2(bounds, bounds));

    if (m_mouseClicked == true)
    {
        Draw::SetColor(ImColor(255, 0, 0, 255));
        Draw::Line(m_clickedMousePos, Input::GetMousePos());
        Draw::SetColor(ImColor(255, 255, 255, 255));
    }

    

}

glm::vec2 Assignment2::GetVectorDirection() {
    glm::vec2 mousePos = Input::GetMousePos();

    return mousePos - m_clickedMousePos;
}

void Assignment2::PredictTrajectoryWithBounces(const Circle& circle,
                                               const glm::vec2& appliedImpulse,
                                               int steps,
                                               float dt) {
    glm::vec2 position = circle.circlePosition;
    glm::vec2 velocity = circle.velocity + appliedImpulse / circle.mass;
    glm::vec2 acceleration = circle.acceleration;
    float radius = circle.circleRadius;

    for (int s = 0; s < steps; ++s) {
        velocity += acceleration * dt;
        position += velocity * dt;

        if (position.x + radius > bounds) {
            position.x = bounds - radius;
            velocity.x *= -1;
        } else if (position.x - radius < -bounds) {
            position.x = -bounds + radius;
            velocity.x *= -1;
        }

        if (position.y + radius > bounds) {
            position.y = bounds - radius;
            velocity.y *= -1;
        } else if (position.y - radius < -bounds) {
            position.y = -bounds + radius;
            velocity.y *= -1;
        }

        Draw::SetColor(ImColor(0, 255, 0, 125));
        Draw::Circle(position, radius, false);
    }

    Draw::SetColor(ImColor(0, 255, 0, 255));
}

void Assignment2::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}