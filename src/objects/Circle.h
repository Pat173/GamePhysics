#include "core/Application.h"
#include "core/Math.h"

class Circle
{


	public:
		Circle(float radius, glm::vec2 startPos);
        ~Circle();
	void Update(float deltaTime);

        glm::vec2 circlePosition;
        float circleRadius;
        float gravity = -9.81f;
        bool isUp = false;
        float velocity = 0;

	private: 

};