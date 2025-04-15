#include "Circle.h"


Circle::Circle(float radius, glm::vec2 startPos, glm::vec2 startVelocity, glm::vec2 startAcceleration) :

      circleRadius(radius),
      circlePosition(startPos),
      velocity(startVelocity),
      acceleration(startAcceleration) {}

Circle::~Circle(){};

void Circle::Update(float deltaTime,
                    float screenHeight,
                    float screenWidth,
                    std::vector<glm::vec2> forces) {


    acceleration = glm::vec2(0, 0);

    for (int i = 0; i < forces.size(); i++) {
        glm::vec2 newAcc = forces[i] / mass;

        acceleration += newAcc;
    }

    velocity = velocity + acceleration * deltaTime;
    circlePosition = circlePosition + velocity * deltaTime;

    if (circlePosition.y > screenHeight - circleRadius) {
        velocity.y = -velocity.y;
        //  acceleration.y = -acceleration.y;
        circlePosition.y = screenHeight - circleRadius;
    }
    if (circlePosition.y < -screenHeight + circleRadius) {
        velocity.y = -velocity.y;
        // acceleration.y = -acceleration.y;
        circlePosition.y = -screenHeight + circleRadius;
    }
    if (circlePosition.x > screenWidth - circleRadius) {
        velocity.x = -velocity.x;
        acceleration.x = -acceleration.x;
        circlePosition.x = screenWidth - circleRadius;
    }
    if (circlePosition.x < -screenWidth + circleRadius) {
        velocity.x = -velocity.x;
        acceleration.x = -acceleration.x;
        circlePosition.x = -screenWidth + circleRadius;
    }
}

void Circle::UpdateImpulse(float deltaTime, float screenHeight, float screenWidth,  std::vector<glm::vec2> forces, glm::vec2 impulse) 
{
    velocity += impulse / mass;
    Circle::Update(deltaTime, screenHeight, screenWidth, forces);


}


void Circle::Update(float deltaTime, float screenHeight, float screenWidth,  std::vector<glm::vec2> forces, glm::vec2 lineVectorDirection) 
{

    Circle::Update(deltaTime, screenHeight, screenWidth, forces);

    glm::vec2 mousePos = Input::GetMousePos();
    float distance = glm::length(mousePos - circlePosition);

    if (Input::IsMouseDown(0) && distance <= circleRadius) {
        m_mouseClicked = true;
    }
    if (Input::IsMouseReleased(0) && m_mouseClicked) {
        m_mouseClicked = false;
        velocity.x += ((lineVectorDirection.x * 10 ) / mass);
        velocity.y += ((lineVectorDirection.y * 10) / mass);
    }

}

Circle& Circle::operator = (const Circle& other) {
    if (this == &other) return *this;

    circlePosition = other.circlePosition;
    circleRadius = other.circleRadius;
    acceleration = other.acceleration;
    velocity = other.velocity;
    mass = other.mass;

    return *this;
}


