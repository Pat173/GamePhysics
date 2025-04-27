#include "core/Application.h"
#include "scenes/TestScene.h"
#include "scenes/Assignment1.h"
#include "scenes/Assignment2.h"
#include "scenes/Session3.h"
#include "scenes/PoolGame.h"

int main(int argc, char** argv) {
    // Add newly created scenes here so that they show up in the menu.
    std::vector<Scene*> scenes = {
        new TestScene(), new Assignment1(), new Assignment2(), new Session3(),
        new PoolGame(),
    };
    Application app(scenes);
    return app.Run();
}
