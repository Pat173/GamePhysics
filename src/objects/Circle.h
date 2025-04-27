#pragma once
#include "core/Application.h"
#include "core/Math.h"
#include "core/Input.h"

class Hole;
class PoolGame;

class Circle
{
	public:
		 Circle(float radius, glm::vec2 startPos, glm::vec2 startVelocity, glm::vec2 startAcceleration, bool isMainBall = false);
        ~Circle();
        void Update(float deltaTime, float screenHeight, float screenWidth, std::vector<glm::vec2> forces);
        void UpdateArbLine(glm::vec2 lineDir, glm::vec2 linePoint);
	    void ImpulseSim( glm::vec2 impulse);
	    void Impulse(glm::vec2 lineVectorDirection);
        Circle& operator=(const Circle& other);
        void TestCircleCollision(Circle& other);
        void TestScored(Hole& hole, PoolGame& game);

        glm::vec2 circlePosition;
        float circleRadius;
        glm::vec2 acceleration = glm::vec2(5, -9.81f);
        glm::vec2 velocity = glm::vec2(0, 0);
        float mass = circleRadius * 10;
        bool IsMainBall = false;
        bool ToBeDestroyed = false;

    bool GetIsMouseClicked() { return m_mouseClicked; }

    private:
        bool m_mouseClicked = false;
        float m_drag = 0.5f;

};