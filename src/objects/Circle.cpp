#include "Circle.h"
#include "core/Math.h"

Circle::Circle(float radius, glm::vec2 startPos, glm::vec2 startVelocity, glm::vec2 startAcceleration) :
    circleRadius(radius), circlePosition(startPos), velocity(startVelocity), acceleration(startAcceleration){}

Circle::~Circle(){};

void Circle::Update(float deltaTime, float screenHeight, float screenWidth,  std::vector<glm::vec2> forces) 
{

    acceleration = glm::vec2(0, 0);

    for (int i = 0; i < forces.size(); i++)
    {
        glm::vec2 newAcc = forces[i] / mass;

        acceleration += newAcc;
    }

    velocity = velocity + acceleration * deltaTime;
    circlePosition = circlePosition + velocity * deltaTime;

    if (circlePosition.y > screenHeight - circleRadius)
    {
        velocity.y = -velocity.y;
       //  acceleration.y = -acceleration.y;
        circlePosition.y = screenHeight - circleRadius;
    } 
    if (circlePosition.y < -screenHeight + circleRadius) 
    {
        velocity.y = -velocity.y;
       // acceleration.y = -acceleration.y;
        circlePosition.y = -screenHeight + circleRadius;
    } 
    if (circlePosition.x > screenWidth - circleRadius) 
    {
        velocity.x = -velocity.x;
        acceleration.x = -acceleration.x;
        circlePosition.x = screenWidth - circleRadius;
    } 
    if (circlePosition.x < -screenWidth + circleRadius) 
    {
        velocity.x = -velocity.x;
        acceleration.x = -acceleration.x;
        circlePosition.x = -screenWidth + circleRadius;
    }


}
