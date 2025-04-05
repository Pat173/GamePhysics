#include "Circle.h"
#include "core/Math.h"

Circle::Circle(float radius, glm::vec2 startPos, glm::vec2 startAcceleration) : circleRadius(radius), circlePosition(startPos), acceleration(startAcceleration){}

Circle::~Circle(){};

void Circle::Update(float deltaTime, float screenHeight, float screenWidth) {
   
    if (velocity.x > 20 || velocity.y < -20) {
        acceleration.y = 0;
    }
    if (velocity.y > 20 || velocity.y < -20) {
        acceleration.x = 0;
    }
    
    velocity = velocity + acceleration * deltaTime;
    circlePosition = circlePosition + velocity * deltaTime;

    if (circlePosition.y > screenHeight - circleRadius)
    {
        velocity.y = -velocity.y;
        acceleration.y = -acceleration.y;
        circlePosition.y = screenHeight - circleRadius;
    } 
    else if (circlePosition.y < -screenHeight + circleRadius) 
    {
        velocity.y = -velocity.y;
        acceleration.y = -acceleration.y;
        circlePosition.y = -screenHeight + circleRadius;
    } 
    else if (circlePosition.x > screenWidth - circleRadius) 
    {
        velocity.x = -velocity.x;
        acceleration.x = -acceleration.x;
        circlePosition.x = screenWidth - circleRadius;
    } 
    else if (circlePosition.x < -screenWidth + circleRadius) 
    {
        velocity.x = -velocity.x;
        acceleration.x = -acceleration.x;
        circlePosition.x = -screenWidth + circleRadius;
    }


}