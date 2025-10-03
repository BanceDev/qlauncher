#include "icon_button.h"

void create_icon_button(icon_button_t *bt, int x, int y, int w, int h,
                        const char *filename) {
    bt->icon = LoadTexture(filename);
    bt->x = x;
    bt->y = y;
    bt->w = w;
    bt->h = h;
    if (bt->w <= 0)
        bt->w = bt->icon.width;
    if (bt->h <= 0)
        bt->h = bt->icon.height;
    bt->scale = 1.0f;
    bt->target_scale = 1.0f;
}

void update_icon_button(icon_button_t *bt) {
    Vector2 mouse = GetMousePosition();

    // Compute scaled size
    float sw = bt->w * bt->scale;
    float sh = bt->h * bt->scale;

    Rectangle bounds = {bt->x - (sw - bt->w) / 2, // center the growth
                        bt->y - (sh - bt->h) / 2, sw, sh};

    if (CheckCollisionPointRec(mouse, bounds)) {
        bt->target_scale = 1.25f;
    } else {
        bt->target_scale = 1.0f;
    }

    // Smooth step toward target
    float smoothing = 0.15f; // smaller = slower
    bt->scale = bt->scale + (bt->target_scale - bt->scale) * smoothing;
}

void draw_icon_button(icon_button_t *bt) {
    Rectangle src = {0, 0, (float)bt->icon.width, (float)bt->icon.height};
    Rectangle dst = {bt->x + bt->w / 2, bt->y + bt->h / 2, bt->w * bt->scale,
                     bt->h * bt->scale};
    Vector2 origin = {dst.width / 2, dst.height / 2}; // pivot in center
    DrawTexturePro(bt->icon, src, dst, origin, 0.0f, WHITE);
}

void delete_icon_button(icon_button_t *bt) { UnloadTexture(bt->icon); }
