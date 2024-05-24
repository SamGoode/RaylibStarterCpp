#include "MathHeaders/Colour.h"
#include "MathHeaders/Matrix3.h"
#include "MathHeaders/Vector3.h"
#include "Game.h"

#pragma warning( push , 0)
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#pragma warning(pop)

int main(int argc, char* argv[]) {
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1000;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    Game game = Game(screenWidth, screenHeight);

    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        game.update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        game.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}