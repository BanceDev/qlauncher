#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include "raylib.h"

typedef struct {
    Texture2D icon;
    int x, y;           // top-left position
    int w, h;           // base width/height
    float scale;        // current scale
    float target_scale; // what we're interpolating toward
} icon_button_t;

void create_icon_button(icon_button_t *bt, int x, int y, int w, int h,
                        const char *filename);
void update_icon_button(icon_button_t *bt);
void draw_icon_button(icon_button_t *bt);
void delete_icon_button(icon_button_t *bt);

#endif // ICON_BUTTON_H
