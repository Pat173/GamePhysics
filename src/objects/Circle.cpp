#include "Circle.h"
#include "scenes/PoolGame.h"
#include "Hole.h"


Circle::Circle(float radius,
               glm::vec2 startPos,
               glm::vec2 startVelocity,
               glm::vec2 startAcceleration,
               bool isMainBall)
    :

      circleRadius(radius),
      circlePosition(startPos),
      velocity(startVelocity),
      acceleration(startAcceleration),
      IsMainBall(isMainBall) {}

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

    velocity *= 1 - m_drag * deltaTime;
}

void Circle::ImpulseSim(glm::vec2 impulse) 
{
    velocity += impulse / mass;


}

void Circle::UpdateArbLine(
                           glm::vec2 lineDir,
                           glm::vec2 lineEnd) {

    glm::vec2 lineStart = lineEnd - lineDir;
    glm::vec2 lineVec = lineEnd - lineStart;
    glm::vec2 normal = glm::normalize(glm::vec2(-lineVec.y, lineVec.x));

    glm::vec2 toCircle = circlePosition - lineStart;

    float t = glm::dot(toCircle, lineVec) / glm::dot(lineVec, lineVec);
    t = glm::clamp(t, 0.0f, 1.0f); 

    glm::vec2 closestPoint = lineStart + t * lineVec;

    glm::vec2 diff = circlePosition - closestPoint;
    float distance = glm::length(diff);

    if (distance < circleRadius) {
        glm::vec2 collisionNormal = glm::normalize(diff);

        if (glm::dot(velocity, collisionNormal) < 0.0f) {
            velocity = glm::reflect(velocity, collisionNormal);
        }


        circlePosition = closestPoint + collisionNormal * circleRadius;
    }
}



void Circle::Impulse( glm::vec2 lineVectorDirection) 
{

    glm::vec2 mousePos = Input::GetMousePos();
    float distance = glm::length(mousePos - circlePosition);

    if (Input::IsMouseDown(0) && distance <= circleRadius) {
        m_mouseClicked = true;
    }
    if (Input::IsMouseReleased(0) && m_mouseClicked) {
        m_mouseClicked = false;
        velocity.x += ((lineVectorDirection.x * 20 ) / mass);
        velocity.y += ((lineVectorDirection.y * 20) / mass);
    }

}

void Circle::TestCircleCollision(Circle& other) {
    float dx = other.circlePosition.x - this->circlePosition.x;
    float dy = other.circlePosition.y - this->circlePosition.y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = this->circleRadius + other.circleRadius;
    float radiusSumSquared = radiusSum * radiusSum;

    if (distanceSquared < radiusSumSquared) {
        float distance = sqrt(distanceSquared);
        glm::vec2 collisionNormal = glm::normalize(glm::vec2(dx, dy));



        if (glm::dot(velocity, collisionNormal) < 0.0f) {
            velocity = glm::reflect(velocity, collisionNormal);
        }

        float overlap = radiusSum - distance;
        circlePosition -= collisionNormal * (overlap / 2.0f);
        other.circlePosition += collisionNormal * (overlap / 2.0f);

        glm::vec2 relativeVelocity = other.velocity - this->velocity;
        float velocityAlongNormal = glm::dot(relativeVelocity, collisionNormal);

        if (velocityAlongNormal > 0)
            return;

        float restitution = 1.0f;

        float impulseMagnitude = -(1.0f + restitution) * velocityAlongNormal;
        impulseMagnitude /= 2.0f;

        glm::vec2 impulse = impulseMagnitude * collisionNormal;

        this->velocity -= impulse;
        other.velocity += impulse; 

    }
}

void Circle::TestScored(Hole& hole, PoolGame& game) {
    float dx = hole.m_holePosition.x - this->circlePosition.x;
    float dy = hole.m_holePosition.y - this->circlePosition.y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = this->circleRadius + hole.m_holeRadius;
    float radiusSquared = radiusSum * radiusSum;

    if (distanceSquared < radiusSquared) {

        if (IsMainBall)
        {
            game.Score = 0;
            game.OnEnable();

        }
        else
        {
            game.Score++;
            ToBeDestroyed = true;
            circlePosition = glm::vec2(0, 0);
        }

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


