#include "icon_button.h"

IconButton::IconButton(int x, int y, int w, int h, const char *filename) {
    this->icon = LoadTexture(filename);
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
}

IconButton::~IconButton() { UnloadTexture(this->icon); }

void IconButton::update() {
    Vector2 mouse = GetMousePosition();

    // Compute scaled size
    float sw = this->w * this->scale;
    float sh = this->h * this->scale;

    Rectangle bounds = {this->x - (sw - this->w) / 2, // center the growth
                        this->y - (sh - this->h) / 2, sw, sh};

    if (CheckCollisionPointRec(mouse, bounds)) {
        this->target_scale = 1.25f;
    } else {
        this->target_scale = 1.0f;
    }

    // Smooth step toward target
    float smoothing = 0.15f; // smaller = slower
    this->scale = this->scale + (this->target_scale - this->scale) * smoothing;
}

void IconButton::draw() {
    Rectangle src = {0, 0, (float)this->icon.width, (float)this->icon.height};
    Rectangle dst = {(float)(this->x + this->w / 2),
                     (float)(this->y + this->h / 2), this->w * this->scale,
                     this->h * this->scale};
    Vector2 origin = {dst.width / 2, dst.height / 2}; // pivot in center
    DrawTexturePro(this->icon, src, dst, origin, 0.0f, WHITE);
}
