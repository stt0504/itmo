#include "image.h"
#include <fstream>

Color::Color()
        :r(0), g(0), b(0)
{}

Color::Color(int r, int g, int b)
        :r(r), g(g), b(b)
{}

Image::Image(uint16_t height, uint16_t width)
        :im_height(height), im_width(width), im_colors(std::vector<Color>(width * height))
{}

Color Image::GetColor(int x, int y) {
    return im_colors[x + y * im_width];
}

void Image::SetColor(const Color& color, int x, int y) {
    im_colors[x + y * im_width].r = color.r;
    im_colors[x + y * im_width].g = color.g;
    im_colors[x + y * im_width].b = color.b;
}

void Image::Export(const std::string& path) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    unsigned char Pad[3] = {0, 0, 0};
    const int paddingAmount = ((4 - (im_width * 3) % 4) % 4);
    const int kHeaderSize = 14;
    const int kInformHeaderSize = 40;
    const int kFileSize = kHeaderSize + kInformHeaderSize + im_width * im_height * 3 + paddingAmount * im_width;
    unsigned char Header[kHeaderSize];
    Header[0] = 'B';
    Header[1] = 'M';
    Header[2] = kFileSize;
    Header[3] = kFileSize >> 8;
    Header[4] = kFileSize >> 16;
    Header[5] = kFileSize >> 24;
    Header[6] = 0;
    Header[7] = 0;
    Header[8] = 0;
    Header[9] = 0;
    Header[10] = kHeaderSize + kInformHeaderSize;
    Header[11] = 0;
    Header[12] = 0;
    Header[13] = 0;
    unsigned char InformationHeader[kInformHeaderSize];
    for (int i = 1; i < kInformHeaderSize - 1; i++) {
        InformationHeader[i] = 0;
    }
    InformationHeader[0] = kInformHeaderSize;
    InformationHeader[4] = im_width;
    InformationHeader[5] = im_width >> 8;
    InformationHeader[6] = im_width >> 16;
    InformationHeader[7] = im_width >> 24;
    InformationHeader[8] = im_height;
    InformationHeader[9] = im_height >> 8;
    InformationHeader[10] = im_height >> 16;
    InformationHeader[11] = im_height >> 24;
    InformationHeader[12] = 1;
    InformationHeader[14] = 24;
    file.write(reinterpret_cast<char*>(Header), kHeaderSize);
    file.write(reinterpret_cast<char*>(InformationHeader), kInformHeaderSize);
    for (int y = 0; y < im_height; y++) {
        for (int x = 0; x < im_width; x++) {
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r);
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g);
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b);
            unsigned char color[] = {b, g, r};
            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char*>(Pad), paddingAmount);
    }
    file.close();
}