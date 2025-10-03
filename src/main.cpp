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
    // After loading the shader
    Shader blurShader = LoadShader(nullptr, "./resources/gaussianBlur.fs");

    float blurSize = 3.0f; // Increased for more visible blur
    int blurSizeLoc = GetShaderLocation(blurShader, "blurSize");
    int blurDirLoc = GetShaderLocation(blurShader, "blurDirection");

    SetShaderValue(blurShader, blurSizeLoc, &blurSize, SHADER_UNIFORM_FLOAT);

    // Create an intermediate render texture for two-pass blur
    RenderTexture2D rtBlurPass = LoadRenderTexture(1920, 1080);
    RenderTexture2D rtBackground = LoadRenderTexture(1920, 1080);
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

    IconButton *qw = new IconButton(x1, y, btnW, btnH, "./resources/qw.png",
                                    "./resources/qw_wall.png");
    IconButton *q2 = new IconButton(x2, y, btnW, btnH, "./resources/q2.png",
                                    "./resources/q2_wall.jpg");
    IconButton *q3 = new IconButton(x3, y, btnW, btnH, "./resources/q3.png",
                                    "./resources/q3_wall.jpg");
    IconButton *q4 = new IconButton(x4, y, btnW, btnH, "./resources/q4.png",
                                    "./resources/q4_wall.jpg");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    bool shouldClose = false;

    while (!shouldClose) {
        // Detect the key combo: Ctrl + Alt + Q
        if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) &&
            (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) &&
            IsKeyPressed(KEY_Q)) {
            shouldClose = true;
        }

        // Update all buttons
        qw->update();
        q2->update();
        q3->update();
        q4->update();

        // Check for any hovered button
        static IconButton *hoveredButton = qw;
        if (qw->isHovered())
            hoveredButton = qw;
        else if (q2->isHovered())
            hoveredButton = q2;
        else if (q3->isHovered())
            hoveredButton = q3;
        else if (q4->isHovered())
            hoveredButton = q4;

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        // In your render loop, replace the blur section:
        if (hoveredButton) {
            // First: render wallpaper to rtBackground
            BeginTextureMode(rtBackground);
            ClearBackground(BLACK);
            DrawTexturePro(hoveredButton->getWallTexture(),
                           {0, 0, (float)hoveredButton->getWallTexture().width,
                            (float)hoveredButton->getWallTexture().height},
                           {0, 0, 1920, 1080}, {0, 0}, 0.0f, WHITE);
            EndTextureMode();

            // Second: horizontal blur pass
            float horizontal[2] = {1.0f, 0.0f};
            SetShaderValue(blurShader, blurDirLoc, horizontal,
                           SHADER_UNIFORM_VEC2);

            BeginTextureMode(rtBlurPass);
            BeginShaderMode(blurShader);
            DrawTextureRec(rtBackground.texture,
                           {0, 0, (float)rtBackground.texture.width,
                            -(float)rtBackground.texture.height},
                           {0, 0}, WHITE);
            EndShaderMode();
            EndTextureMode();

            // Third: vertical blur pass (to screen)
            float vertical[2] = {0.0f, 1.0f};
            SetShaderValue(blurShader, blurDirLoc, vertical,
                           SHADER_UNIFORM_VEC2);

            BeginShaderMode(blurShader);
            DrawTextureRec(rtBlurPass.texture,
                           {0, 0, (float)rtBlurPass.texture.width,
                            -(float)rtBlurPass.texture.height},
                           {0, 0}, WHITE);
            EndShaderMode();
        }
        // Draw all buttons
        qw->draw();
        q2->draw();
        q3->draw();
        q4->draw();

        EndDrawing();
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
