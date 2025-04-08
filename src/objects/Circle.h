#include "core/Application.h"
#include "core/Math.h"

class Circle
{


	public:
		Circle(float radius, glm::vec2 startPos, glm::vec2 startVelocity, glm::vec2 startAcceleration);
        ~Circle();
	void Update(float deltaTime, float screenHeight, float screenWidth, std::vector<glm::vec2> forces);

        glm::vec2 circlePosition;
        float circleRadius;
        glm::vec2 acceleration = glm::vec2(5, -9.81f);
        glm::vec2 velocity = glm::vec2(0, 0);
        float mass = circleRadius * 10;

	private: 
};