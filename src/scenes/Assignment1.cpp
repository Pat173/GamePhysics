#include "Assignment1.h"

#include "core/Draw.h"
#include "imgui.h"

Assignment1::Assignment1() : circle(1, glm::vec2(0,10)) {}

Assignment1::~Assignment1() {}

void Assignment1::OnEnable()
{
    
}

void Assignment1::OnDisable() {}

void Assignment1::Update(float deltaTime)
{
    circle.Update(deltaTime);
}

void Assignment1::Draw() {


    Draw::Circle(circle.circlePosition, circle.circleRadius);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));
}

void Assignment1::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::DragFloat2("Circle Position", &circle.circlePosition[0], 0.1f);
    ImGui::DragFloat("Circle Radius", &circle.circleRadius, 0.1f);
    ImGui::End();
}