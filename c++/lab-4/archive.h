#pragma once

#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

struct Archive {
    std::vector<std::string> filenames;
    std::vector<int> bits;
    uint64_t count_control_bit;
    std::string path;
    std::string archive_file;
    std::string name;

    Archive(std::vector<std::string> vector, std::string n, std::string p) {
        if (!vector.empty()) {
            filenames.assign(vector.begin(), vector.end());
        }
        path = std::move(p);
        name = std::move(n);
        archive_file = path + name + ".haf";
        count_control_bit = 0;
    }

    void GetFileInfo();

    void Compression();

    static std::string GetFilename(const std::string& fn);
};

void Decompression(const std::string& archive, const std::string& control_bits, const std::string& path,
                   std::vector<std::string> filenames);

void GetFiles(const std::string& archive, std::vector<std::string>& filenames);