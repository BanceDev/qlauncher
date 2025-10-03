#include "icon_button.h"
#include <raylib.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

IconButton::IconButton(int x, int y, int w, int h, const char *icon,
                       const char *wall, const char *cmd, const char *dir) {
    this->icon = LoadTexture(icon);
    this->wall = LoadTexture(wall);
    this->play = LoadTexture("./resources/play.png");
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    if (this->w <= 0)
        this->w = this->icon.width;
    if (this->h <= 0)
        this->h = this->icon.height;
    this->scale = 1.0f;
    this->target_scale = 1.0f;
    this->hovered = false;
    this->command = cmd;
    this->workdir = dir;
}

IconButton::~IconButton() {
    UnloadTexture(this->icon);
    UnloadTexture(this->wall);
}

void runDetached(const std::string &command, const std::string &workdir) {
    pid_t pid = fork();
    if (pid == 0) {
        setsid();

        if (!workdir.empty()) {
            chdir(workdir.c_str());
        }

        execl("/bin/sh", "sh", "-c", command.c_str(), (char *)NULL);

        _exit(EXIT_FAILURE);
    }
}

void IconButton::update() {
    Vector2 mouse = GetMousePosition();

    // Compute scaled size
    float sw = this->w * this->scale;
    float sh = this->h * this->scale;

    Rectangle bounds = {this->x - (sw - this->w) / 2, // center the growth
                        this->y - (sh - this->h) / 2, sw, sh};

    if (CheckCollisionPointRec(mouse, bounds)) {
        this->target_scale = 1.25f;
        this->hovered = true;
        // Check for click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!this->command.empty()) {
                runDetached(this->command, this->workdir);
            }
        }
    } else {
        this->target_scale = 1.0f;
        this->hovered = false;
    }

    // Smooth step toward target
    float smoothing = 0.15f; // smaller = slower
    this->scale = this->scale + (this->target_scale - this->scale) * smoothing;
}

void IconButton::draw() {
    float scaledW = this->w * this->scale;
    float scaledH = this->h * this->scale;

    Rectangle shadowRect = {this->x + (this->w - scaledW) / 2,
                            this->y + (this->h - scaledH) / 2, scaledW,
                            scaledH};
    Color topLeft = (Color){255, 255, 255, 50};    // fully opaque white
    Color topRight = (Color){255, 255, 255, 0};    // semi-transparent
    Color bottomLeft = (Color){255, 255, 255, 0};  // semi-transparent
    Color bottomRight = (Color){255, 255, 255, 0}; // fully opaque white

    // Draw the main icon on top
    Rectangle src = {0, 0, (float)this->icon.width, (float)this->icon.height};
    Rectangle dst = {(float)(this->x + this->w / 2),
                     (float)(this->y + this->h / 2), scaledW, scaledH};
    Vector2 origin = {dst.width / 2, dst.height / 2};
    DrawTexturePro(this->icon, src, dst, origin, 0.0f, WHITE);
    DrawRectangleGradientEx(shadowRect, topLeft, bottomLeft, topRight,
                            bottomRight);
    if (this->hovered) {
        DrawTexture(this->play, this->x + 50, this->y + 150, WHITE);
    }
}
