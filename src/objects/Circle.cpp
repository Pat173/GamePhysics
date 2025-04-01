#include "Circle.h"
#include "core/Math.h"

Circle::Circle(float radius, glm::vec2 startPos) : circleRadius(radius), circlePosition(startPos), isUp(false){}

Circle::~Circle(){};

void Circle::Update(float deltaTime)

{
    if (circlePosition.y > 10) {
        isUp = false;
    } else if (circlePosition.y < circleRadius) {
        isUp = true;
        velocity = -velocity;
    }

    velocity = velocity + gravity * deltaTime;
    circlePosition.y = circlePosition.y + velocity * deltaTime;

}