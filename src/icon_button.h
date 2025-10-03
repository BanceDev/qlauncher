#pragma once
#include "raylib.h"

class IconButton {

  public:
    IconButton(int x, int y, int w, int h, const char *icon, const char *wall);
    ~IconButton();
    void update();
    void draw();
    bool isHovered() const { return this->hovered; }
    Texture2D getWallTexture() const { return this->wall; }

  private:
    Texture2D icon;
    Texture2D wall;
    int x, y;           // top-left position
    int w, h;           // base width/height
    float scale;        // current scale
    float target_scale; // what we're interpolating toward
    bool hovered;
};
