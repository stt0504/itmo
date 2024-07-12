#pragma once
#include <iostream>
#include <vector>

struct Color {
    int r;
    int g;
    int b;
    Color();
    Color(int r, int g, int b);
};

struct Image {
    uint16_t im_width;
    uint16_t im_height;
    Image(uint16_t height, uint16_t width);
    Color GetColor(int x, int y);
    void SetColor(const Color& color, int x, int y);
    void Export(const std::string& path);
    std::vector<Color> im_colors;
};