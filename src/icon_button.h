#pragma once
#include "raylib.h"

class IconButton {

  public:
    IconButton(int x, int y, int w, int h, const char *filename);
    ~IconButton();
    void update();
    void draw();

  private:
    Texture2D icon;
    int x, y;           // top-left position
    int w, h;           // base width/height
    float scale;        // current scale
    float target_scale; // what we're interpolating toward
};
