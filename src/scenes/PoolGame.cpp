#include "PoolGame.h"
#include "core/Draw.h"
#include "imgui.h"

PoolGame::PoolGame() {}

PoolGame::~PoolGame() {}

void PoolGame::OnEnable() {
    m_circles.clear();
    m_holes.clear();

    Circle circle1 = Circle(1, glm::vec2(-8, 0), glm::vec2(3, 0),
                            glm::vec2(0, -9.81f), true);
    m_circles.push_back(circle1);

    glm::vec2 startPos = glm::vec2(5, 0);
    float ballRadius = 1.0f;
    float ballDiameter = ballRadius * 2.0f;
    int rows = 5;

    for (int col = 0; col < rows; ++col) {
        int ballsInCol = col + 1;
        float offsetY = -(ballsInCol - 1) *
                        (ballDiameter / 2.0f);

        for (int row = 0; row < ballsInCol; ++row) {
            glm::vec2 position =
                startPos + glm::vec2(col * ballDiameter * 1.1f,
                                     offsetY + row * ballDiameter);
            Circle circle =
                Circle(1, position, glm::vec2(0), glm::vec2(0, -9.81f));
            m_circles.push_back(circle);
        }
    }

    // Create 6 holes
    Hole hole1(glm::vec2(-m_screenWidth, -m_screenHeight), 1);
    Hole hole2(glm::vec2(m_screenWidth, -m_screenHeight), 1);
    Hole hole3(glm::vec2(-m_screenWidth, m_screenHeight), 1);
    Hole hole4(glm::vec2(m_screenWidth, m_screenHeight), 1);
    Hole hole5(glm::vec2(0, m_screenHeight), 1);
    Hole hole6(glm::vec2(0, -m_screenHeight), 1);

    m_holes = {hole1, hole2, hole3, hole4, hole5, hole6};
}



void PoolGame::OnDisable() {}

void PoolGame::Update(float deltaTime) {

    for (int i = 0; i < m_circles.size(); i++) {
        std::vector<glm::vec2> forces{};
        forces.push_back(m_gravity * m_circles[i].mass);

        for (int j = i + 1; j < m_circles.size(); j++)
        {
            m_circles[i].TestCircleCollision(m_circles[j]);
        }
        for (int j = 0; j < m_holes.size(); j++) {
            m_circles[i].TestScored(m_holes[j], *this);
        }


        m_circles[i].Update(deltaTime, m_screenHeight, m_screenWidth, forces);
       // m_circles[i].UpdateArbLine( finishPointLine - startPointLine, finishPointLine);

        if (m_circles[i].IsMainBall)
            m_circles[i].Impulse(-GetVectorDirection());
    }



    if (Input::IsMouseClicked(0) == true) {
        m_mouseClicked = true;
        m_clickedMousePos = Input::GetMousePos();
    } else if (Input::IsMouseReleased(0) == true && m_mouseClicked == true) {
        m_clickedMousePos = glm::vec2(0, 0);
        m_mouseClicked = false;
    }

    m_circles.erase(
        std::remove_if(m_circles.begin(), m_circles.end(),
                       [](const Circle& c) { return c.ToBeDestroyed; }),
        m_circles.end());
}

void PoolGame::Draw() {
    for (int i = 0; i < m_circles.size(); i++) {

        if (m_circles[i].GetIsMouseClicked()) {
            glm::vec2 direction = GetVectorDirection();
            glm::vec2 impulse = (-direction * 10.0f);

            Circle futureCircle = m_circles[i];
            std::vector<glm::vec2> forces{};
            forces.push_back(m_gravity * m_circles[i].mass);

            futureCircle.ImpulseSim(impulse);
            futureCircle.Update(0.1f, m_screenHeight, m_screenWidth, forces);
            // futureCircle.UpdateArbLine(finishPointLine - startPointLine, finishPointLine);

            for (int s = 0; s < 30; ++s) {
                Draw::SetColor(ImColor(0, 255, 0, 125));

                futureCircle.Update(0.1f, m_screenHeight, m_screenWidth, forces);
               // futureCircle.UpdateArbLine(finishPointLine - startPointLine, finishPointLine);



                Draw::Circle(futureCircle.circlePosition,
                             futureCircle.circleRadius, false);
            }

            Draw::SetColor(ImColor(0, 255, 0, 255));
        }

        if (m_circles[i].IsMainBall) {
            Draw::SetColor(ImColor(255, 255, 255, 255));
        } else {
            Draw::SetColor(ImColor(255, 0, 0, 255));
        }
        Draw::Circle(m_circles[i].circlePosition, m_circles[i].circleRadius,
                     false);
    }

    for (int i = 0; i < m_holes.size(); i++) {
        Draw::SetColor(ImColor(0, 255, 0, 255));
        Draw::Circle(m_holes[i].m_holePosition, m_holes[i].m_holeRadius, true);
    }

    Draw::SetColor(ImColor(0, 0, 255, 255));
    

   // glm::vec2 centerOfLine = (startPointLine + finishPointLine) * 0.5f;
   // Draw::Line(centerOfLine, centerOfLine + normal * 2.0f);
   // Draw::SetColor(ImColor(255, 255, 255, 255));
   // Draw::Line(startPointLine, finishPointLine);


    Draw::Line(glm::vec2(-m_screenWidth, -m_screenHeight), glm::vec2(m_screenWidth, -m_screenHeight));
    Draw::Line(glm::vec2(-m_screenWidth, -m_screenHeight), glm::vec2(-m_screenWidth, m_screenHeight));
    Draw::Line(glm::vec2(-m_screenWidth, m_screenHeight), glm::vec2(m_screenWidth, m_screenHeight));
    Draw::Line(glm::vec2(m_screenWidth, -m_screenHeight), glm::vec2(m_screenWidth, m_screenHeight));

    
    if (m_mouseClicked == true) {
        Draw::SetColor(ImColor(255, 0, 0, 255));
        Draw::Line(m_clickedMousePos, Input::GetMousePos());
        Draw::SetColor(ImColor(255, 255, 255, 255));
    }

}

glm::vec2 PoolGame::GetVectorDirection() {
    glm::vec2 mousePos = Input::GetMousePos();

    return mousePos - m_clickedMousePos;
}

void PoolGame::SpawnCircle(glm::vec2 position,
                           glm::vec2 velocity,
                           glm::vec2 acceleration)

{
    Circle circle = Circle(1, position, velocity, acceleration);
    m_circles.push_back(circle);
}

void PoolGame::DrawGUI() {
    ImGui::Begin("Inspector");
    if (ImGui::Button("Reset", ImVec2(100, 33)))
    {
        OnEnable();
    }

    if (ImGui::Button("Spawn Ball", ImVec2(100, 33))) {
        SpawnCircle(m_newCirclePos, m_newCircleVelocity, m_newCircleAcc);
    }
    ImGui::DragFloat2("New Circle Position", &m_newCirclePos[0], 0.1f, 0.0f, 0.0f);
    ImGui::DragFloat2("New Circle Velocity", &m_newCircleVelocity[0], 0.1f, 0.0f, 0.0f);
    ImGui::DragFloat2("New Circle Acc", &m_newCircleAcc[0], 0.1f, 0.0f, 0.0f);
    ImGui::Text("Score: %d", Score);

    ImGui::End();
}