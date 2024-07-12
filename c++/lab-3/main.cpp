#include "image.cpp"
#include <filesystem>
#include <iostream>

int main(int argc, char *argv[]) {
    int height;
    int width;
    std::string input;
    std::string output;
    int freq = 0;
    int max_iter = -1;
    for (int i = 1; i < argc; i++) {
        std::string s = argv[i];
        if (s == "-l" || s == "--length") {
            height = std::stoi(argv[i + 1]);
        } else if (s == "-w" || s == "--width") {
            width = std::stoi(argv[i + 1]);
        } else if (s == "-i" || s == "--input") {
            input = argv[i + 1];
        } else if (s == "-m" || s == "--max-iter") {
            max_iter = std::stoi(argv[i + 1]);
        } else if (s == "-o" || s == "--output") {
            output = argv[i + 1];
        } else if (s == "-f" || s == "--freq") {
            freq = std::stoi(argv[i + 1]);
        }
    }
    std::filesystem::remove_all(output);
    std::filesystem::create_directory(output);
    Image image(height, width);
    std::ifstream file(input);
    std::string line;
    std::vector<std::vector<int>> sand;
    std::vector<int> row;
    row.assign(image.im_width, 0);
    sand.assign(image.im_height, row);
    while (getline(file, line)) {
        int tab1 = 0;
        int tab2 = 0;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '\t' && tab1 == 0) {
                tab1 = i;
            } else if (line[i] == '\t') {
                tab2 = i;
            }
        }
        int x = stoi(line.substr(0, tab1));
        int y = stoi(line.substr(tab1 + 1, tab2 - tab1 - 1));
        int count_sand = stoi(line.substr(tab2 + 1, line.length() - tab2 - 1));
       sand[x][y] = count_sand;
    }
    bool is_stable = false;
    int count_iter = 0;
    std::vector<std::vector<int>> new_sand;
    new_sand.assign(image.im_height, row);
    int image_num = 0;
    while ((max_iter == -1 || count_iter < max_iter) && !is_stable) {
        is_stable = true;
        new_sand.assign(sand.begin(), sand.end());
        for (int i = 0; i < image.im_height; i++) {
            for (int j = 0; j < image.im_width; j++) {
                if (sand[i][j] > 3) {
                    new_sand[i][j] -= 4;
                    if (i >= 1) {
                        new_sand[i - 1][j]++;
                    } else {
                        row.assign(image.im_width, 0);
                        new_sand.insert(new_sand.begin(), row);
                        sand.insert(sand.begin(), row);
                        image.im_height++;
                        Color color(1, 1, 1);
                        image.im_colors.insert(image.im_colors.begin(), image.im_width, color);
                        new_sand[i][j]++;
                        i++;
                    }
                    if (i + 1 < image.im_height) {
                        new_sand[i + 1][j]++;
                    } else {
                        row.assign(image.im_width, 0);
                        new_sand.insert(new_sand.end(), row);
                        sand.insert(sand.end(), row);
                        image.im_height++;
                        Color color(1, 1, 1);
                        image.im_colors.insert(image.im_colors.end(), image.im_width, color);
                        new_sand[i + 1][j]++;
                    }
                    if (j >= 1) {
                        new_sand[i][j - 1]++;
                    } else {
                        for (int k = 0; k < image.im_height; k++) {
                            new_sand[k].insert(new_sand[k].begin(), 0);
                            sand[k].insert(sand[k].begin(), 0);
                        }
                        int position = 0;
                        for (int k = 0; k < image.im_height; k++) {
                            Color color(1, 1, 1);
                            image.im_colors.insert(image.im_colors.begin() + position, color);
                            position += image.im_width + 1;
                        }
                        image.im_width++;
                        new_sand[i][j]++;
                        j++;
                    }
                    if (j + 1 < image.im_width) {
                        new_sand[i][j + 1]++;
                    } else {
                        for (int k = 0; k < image.im_height; k++) {
                            new_sand[k].insert(new_sand[k].end(), 0);
                            sand[k].insert(sand[k].end(), 0);
                        }
                        int position = 0;
                        for (int k = 0; k < image.im_height; k++) {
                            Color color(1, 1, 1);
                            position += image.im_width;
                            image.im_colors.insert(image.im_colors.begin() + position, color);
                            position++;
                        }
                        image.im_width++;
                        new_sand[i][j + 1]++;
                    }
                }
            }
        }
        sand = new_sand;
        for (int i = 0; i < image.im_height; i++) {
            for (int j = 0; j < image.im_width; j++) {
                if (sand[i][j] > 3) {
                    is_stable = false;
                }
            }
        }
        for (int y = 0; y < image.im_height; y++) {
            for (int x = 0; x < image.im_width; x++) {
                if (sand[y][x] == 0) {
                    image.SetColor(Color(255, 255, 255), x, y);
                } else if (sand[y][x] == 1) {
                    image.SetColor(Color(50, 205, 50), x, y);
                } else if (sand[y][x] == 2) {
                    image.SetColor(Color(148, 0, 211), x, y);
                } else if (sand[y][x] == 3) {
                    image.SetColor(Color(255, 255, 102), x, y);
                } else {
                    image.SetColor(Color(0, 0, 0), x, y);
                }
            }
        }
        count_iter++;
        if (freq != 0 && count_iter % freq == 0) {
            image_num++;
            image.Export(output + std::to_string(image_num) + ".bmp");
        }
    }
    if (freq == 0) {
        image_num++;
        image.Export(output + std::to_string(image_num) + ".bmp");
    }
}