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
    int btnW = 300;
    int btnH = 450;
    int y = (screenHeight / 2) - (btnH / 2);

    // X positions for 4 evenly spaced buttons
    int x1 = (screenWidth * 1 / 8) - (btnW / 2);
    int x2 = (screenWidth * 3 / 8) - (btnW / 2);
    int x3 = (screenWidth * 5 / 8) - (btnW / 2);
    int x4 = (screenWidth * 7 / 8) - (btnW / 2);

    IconButton *qw = new IconButton(x1, y, btnW, btnH, "./resources/qw.png");
    IconButton *q2 = new IconButton(x2, y, btnW, btnH, "./resources/q2.png");
    IconButton *q3 = new IconButton(x3, y, btnW, btnH, "./resources/q3.png");
    IconButton *q4 = new IconButton(x4, y, btnW, btnH, "./resources/q4.png");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    bool shouldClose = false;

    while (!shouldClose) {
        // Detect the key combo: Ctrl + Alt + Q
        if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
            if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) {
                if (IsKeyPressed(KEY_Q)) {
                    shouldClose = true;
                }
            }
        }
        // Update
        //----------------------------------------------------------------------------------
        qw->update();
        q2->update();
        q3->update();
        q4->update();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        qw->draw();
        q2->draw();
        q3->draw();
        q4->draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete qw;
    delete q2;
    delete q3;
    delete q4;
    CloseWindow();
    //--------------------------------------------------------------------------------------
    return 0;
}
