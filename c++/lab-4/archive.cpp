#include "archive.h"

bool Is2Degree(int i) {
    double int_part;
    if (modf(log2(i), &int_part) == 0) {
        return true;
    }
    return false;
}

int CountDigits(int x) {
    if (x == 0) {
        return 1;
    } else {
        int res = 0;
        while (x > 0) {
            res++;
            x = x / 10;
        }
        return res;
    }
}

void Archive::GetFileInfo() {
    std::string s_info;
    remove((path + "info.txt").c_str());
    FILE* info = fopen((path + "info.txt").c_str(), "a+");
    int bytes_size = 0;
    for (auto& filename: filenames) {
        FILE* f = fopen(filename.c_str(), "rb");
        if (!f) break;
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        std::string f_name = Archive::GetFilename(filename);
        char* m_size = new char[CountDigits(size) + 1];
        itoa(size, m_size, 10);
        fclose(f);
        bytes_size += CountDigits(size);
        bytes_size += strlen(f_name.c_str());
        s_info.append(m_size);
        s_info.append("||");
        s_info.append(f_name);
        s_info.append("||");
        delete[] m_size;
    }
    bytes_size = s_info.size() + 2;
    char* b_buff = new char[CountDigits(bytes_size)];
    itoa(bytes_size, b_buff, 10);
    if (CountDigits(bytes_size) < 5) {
        fputs(std::string(5 - CountDigits(bytes_size), '0').c_str(), info);
    }
    fputs(b_buff, info);
    fputs("||", info);
    fputs(s_info.c_str(), info);
    fclose(info);
}

void Archive::Compression() {
    bits.clear();
    bits.push_back(0);
    GetFileInfo();
    FILE* archive = fopen((archive_file).c_str(), "wb");
    FILE* archive_info = fopen((path + "info.txt").c_str(),
                               "rb");
    while (!feof(archive_info)) {
        char byte[1];
        if (fread(byte, 1, 1, archive_info) == 1) {
            //std::cout << byte[0] << std::endl;
            fwrite(byte, 1, 1, archive);
            for (int i = 15; i >= 0; i--) {
                bits.push_back((byte[0] >> i) & 1u);
            }
        }
    }
    fclose(archive_info);
    remove((path + "info.txt").c_str());

    for (auto& filename: filenames) {
        FILE* f = fopen(filename.c_str(), "rb");
        while (!feof(f)) {
            char byte[1];
            if (fread(byte, 1, 1, f) == 1) {
                //std::cout << byte[0] << std::endl;
                fwrite(byte, 1, 1, archive);
                for (int i = 15; i >= 0; i--) {
                    bits.push_back((byte[0] >> i) & 1u);
                }
            }
        }
        fclose(f);
    }
    fclose(archive);

    /*std::cout << "bits:  " << bits.size() << std::endl;

    int j  = 1;
    while (j < bits.size()) {
        for (int k = 0; k < 16; k++) {
            std::cout << bits[j];
            j++;
        }
        std::cout << std::endl;
    }
    std::cout << "bits end  " << std::endl;*/

    double int_part;
    if (modf(log2(bits.size() + 1), &int_part) == 0) {
        count_control_bit = (int) int_part;
    } else {
        count_control_bit = (int) (int_part + 1);
    }

    for (int i = 0; i < count_control_bit; i++) {
        int number_bit = (int) (pow(2, i));
        bits.insert(bits.begin() + number_bit, 0);
    }

    FILE* control_bits = fopen((path + name + "control_bit.txt").c_str(),
                               "wb");
    for (int i = 0; i < count_control_bit; i++) {
        int number_bit = (int) (pow(2, i));
        int j = number_bit;
        while (j < bits.size()) {
            for (int k = 0; k < number_bit; k++) {
                if (j < bits.size()) {
                    bits[number_bit] ^= bits[j];
                    j++;
                }
            }
            j += number_bit;
        }
        std::string control_bit;
        control_bit = std::to_string(bits[number_bit]);
        fwrite(control_bit.c_str(), 1, control_bit.size(), control_bits);
    }
    fclose(control_bits);
}

std::string Archive::GetFilename(const std::string& fn) {
    return fn.substr(fn.find_last_of('\\') + 1, fn.size());
}

void Decompression(const std::string& archive, const std::string& control_bits, const std::string& path,
                   std::vector<std::string> filenames) {
    FILE* arch_file = fopen(archive.c_str(), "rb");
    std::vector<int> new_bits;
    new_bits.clear();
    new_bits.push_back(0);
    while (!feof(arch_file)) {
        char byte[1];
        if (fread(byte, 1, 1, arch_file) == 1) {
            for (int i = 15; i >= 0; i--) {
                new_bits.push_back((byte[0] >> i) & 1u);
            }
        }
    }
    fclose(arch_file);
    // std::cout << "new bits:  " << new_bits.size() << std::endl;
    //std::cout << new_bits[16] << std::endl;
    /*int j  = 1;
    while (j < new_bits.size()) {
        for (int k = 0; k < 16; k++) {
            std::cout << new_bits[j];
            j++;
        }
        std::cout << std::endl;
    }
    std::cout << "new bits end  " << std::endl;*/

    int count_control_bit;
    double int_part;
    if (modf(log2(new_bits.size() + 1), &int_part) == 0) {
        count_control_bit = (int32_t) int_part;
    } else {
        count_control_bit = (int32_t) (int_part + 1);
    }

    for (int i = 0; i < count_control_bit; i++) {
        int number_bit = (int) (pow(2, i));
        new_bits.insert(new_bits.begin() + number_bit, 0);
    }

    std::string new_control_bits;
    for (int i = 0; i < count_control_bit; i++) {
        int number_bit = (int) (pow(2, i));
        int j = number_bit;
        while (j < new_bits.size()) {
            for (int k = 0; k < number_bit; k++) {
                if (j < new_bits.size()) {
                    new_bits[number_bit] ^= new_bits[j];
                    j++;
                }
            }
            j += number_bit;
        }
        new_control_bits += std::to_string(new_bits[number_bit]);
    }

    int index_error = 0;
    for (int i = 0; i < count_control_bit; i++) {
        if (control_bits[i] != new_control_bits[i]) {
            //std::cout << i << std::endl;
            index_error += (int) pow(2, i);
        }
    }
    //std::cout << "error: " << index_error << std::endl;
    if (index_error > 0 && index_error < new_bits.size()) {
        new_bits[index_error] ^= 1;
    }

    for (int i = 1; i < new_bits.size(); i++) {
        if (Is2Degree(i)) {
            new_bits[i] = -1;
        }
    }

    int i = 1;
    int size = new_bits.size();
    while (i < size) {
        if (new_bits[i] == -1) {
            for (int j = i; j < size - 1; j++) {
                new_bits[j] = new_bits[j + 1];
            }
            size--;
        } else {
            i++;
        }
    }

    int bit_index = 1;
    FILE* new_archive = fopen(archive.c_str(), "wb");
    while (bit_index < size) {
        char byte[1] = {'0'};
        std::string byte_str;
        for (int i = 0; i < 16; i++) {
            byte_str += std::to_string(new_bits[bit_index]);
            bit_index++;
        }
        byte[0] = strtol(byte_str.c_str(), nullptr, 2);
        //std::cout << byte[0] << std::endl;
        fwrite(byte, 1, 1, new_archive);
    }
    fclose(new_archive);

    FILE* new_archive_read = fopen(archive.c_str(), "rb");
    char info_block_size[5];
    fread(info_block_size, 1, 5, new_archive);
    int block_size = 0;
    int d = 1;
    for (int i = 4; i >= 0; i--) {
        block_size += (info_block_size[i] - 48) * d;
        d *= 10;
    }
    char* info_block = new char[block_size];
    fread(info_block, 1, block_size, new_archive);
    /*for (int i = 0; i < block_size; i++) {
        std::cout << info_block[i];
    }*/
    std::vector<std::string> tokens;
    char* tok = strtok(info_block, "||");
    int token_count = 0;
    while (tok != nullptr) {
        if (strlen(tok) == 0) {
            break;
        }
        tokens.emplace_back(tok);
        tok = strtok(nullptr, "||");
        token_count++;
    }
    int files = token_count / 2;
    int k = 0;
    for (int i = 0; i < files; i++) {
        const char* size_file = tokens[i * 2].c_str();
        const char* name = tokens[i * 2 + 1].c_str();
        char byte[1];
        if (k < filenames.size() && filenames[k] == name) {
            char full_path[255];
            strcpy(full_path, path.c_str());
            strcat(full_path, name);
            int sz = atoi(size_file);
            //std::cout << "sizefile: " << sz << std::endl;
            FILE* curr = fopen(full_path, "wb");
            for (int j = 1; j <= sz; j++) {
                int x = fread(byte, 1, 1, new_archive_read);
                //std::cout << x << std::endl;
                if (x == 1) {
                    //std::cout << byte[0] << std::endl;
                    fwrite(byte, 1, 1, curr);
                }
            }
            fclose(curr);
            k++;
        } else {
            fread(byte, 1, 1, new_archive_read);
        }
    }
    fclose(new_archive_read);
}

void GetFiles(const std::string& archive, std::vector<std::string>& filenames) {
    FILE* arch_file = fopen(archive.c_str(), "rb");
    char info_block_size[5];
    fread(info_block_size, 1, 5, arch_file);
    int sz = atoi(info_block_size);
    char* info_block = new char[sz];
    fread(info_block, 1, sz, arch_file);
    std::vector<std::string> tokens;
    char* tok = strtok(info_block, "||");
    int token_count = 0;
    while (tok != nullptr) {
        if (strlen(tok) == 0) break;
        tokens.emplace_back(tok);
        tok = strtok(nullptr, "||");
        token_count++;
    }
    int files = token_count / 2;
    for (int i = 0; i < files; i++) {
        const char* name = tokens[i * 2 + 1].c_str();
        filenames.emplace_back(name);
    }
    fclose(arch_file);
}