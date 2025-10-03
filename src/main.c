#include "icon_button.h"
#include "raylib.h"
#include "rlgl.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "qlauncher");
    MaximizeWindow();
    ToggleFullscreen();

    Camera2D camera = {0};
    camera.zoom = 1.0f;

    // Load texture
    icon_button_t qw;
    create_icon_button(&qw, (screenWidth / 4 - 150), (screenHeight / 2 - 225),
                       300, 450, "./resources/qw.png");
    icon_button_t q2;
    create_icon_button(&q2, (screenWidth / 4 - 150), (screenHeight / 2 - 225),
                       300, 450, "./resources/q2.png");
    icon_button_t q3;
    create_icon_button(&q3, (screenWidth / 4 - 150), (screenHeight / 2 - 225),
                       300, 450, "./resources/q3.png");
    icon_button_t q4;
    create_icon_button(&q4, (screenWidth / 4 - 150), (screenHeight / 2 - 225),
                       300, 450, "./resources/q4.png");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        update_icon_button(&qw);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        draw_icon_button(&qw);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete_icon_button(&qw);
    CloseWindow();
    //--------------------------------------------------------------------------------------
    return 0;
}
