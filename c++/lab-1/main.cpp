#include <iostream>
#include <fstream>

int Lines(const std::string& file) {
    char symbol;
    int result = 0;
    std::ifstream in(file);
    if (in.is_open()) {
        in.get(symbol);
        if (in.eof()) {
            return 0;
        } else {
            do {
                if (symbol == '\n') {
                    result++;
                }
            }
            while (in.get(symbol));
            if (symbol == '\n') {
                return result;
            } else {
                return result + 1;
            }
        }
    }
    in.close();
}

int Words(const std::string& file) {
    char symbol;
    int result = 0;
    bool next_word;
    std::ifstream in(file);
    if (in.is_open()) {
        while (in.get(symbol)) {
            next_word = false;
            while (isprint(symbol) && !isblank(symbol) && !in.eof()) {
                next_word = true;
                in.get(symbol);
            }
            if (next_word) {
                result++;
            }
        }
    }
    in.close();
    return result;
}

int Bytes(const std::string& file) {
    std::ifstream in(file, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

int Chars(const std::string& file) {
    char symbol;
    int result = 0;
    std::ifstream in(file);
    if (in.is_open()) {
        while (in.get(symbol)) {
            if (isprint(symbol) && !isblank(symbol)) {
                result++;
            }
        }
    }
    in.close();
    return result;
}

int main(int argc, char* argv[]) {
    bool is_option = false;
    std::string filename;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            is_option = true;
        }
    }
    if (!is_option) {
        for (int i = 1; i < argc; i++) {
            filename = argv[i];
            std::ifstream file(filename);
            if (file.is_open()) {
                std::cout << Lines(filename)
                          << ' ' << Words(filename)
                          << ' ' << Bytes(filename)
                          << ' ' << Chars(filename)
                          << ' ' << filename << std::endl;
            } else {
                std::cout << "File not found" << std::endl;
            }
            file.close();
        }
    } else {
        int file_index_1 = 0, file_index_2 = 0, option_index_1, option_index_2;
        bool option_is_valid;
        std::string option;
        for (int i = 1; i < argc; i++)
            if (argv[i][0] != '-') {
                if (file_index_1 == 0) {
                    file_index_1 = i;
                } else {
                    file_index_2 = i;
                }
            }
        if (file_index_2 == 0) {
            file_index_2 = file_index_1;
        }
        if (file_index_1 == 0) {
            std::cout << "No filename";
        }
        for (int i = file_index_1; i <= file_index_2; i++) {
            filename = argv[i];
            std::ifstream file(filename);
            if (file.is_open()) {
                if (file_index_1 == 1) {
                    option_index_1 = file_index_2 + 1;
                    option_index_2 = argc - 1;
                } else {
                    option_index_1 = 1;
                    option_index_2 = file_index_1 - 1;
                }
                for (int j = option_index_1; j <= option_index_2; j++) {
                    option = argv[j];
                    if (option == "--lines" | option == "-l") {
                        std::cout << Lines(filename) << ' ';
                    } else if (option == "--words" | option == "-w") {
                        std::cout << Words(filename) << ' ';
                    } else if (option == "--bytes" | option == "-c") {
                        std::cout << Bytes(filename) << ' ';
                    } else if (option == "--chars" | option == "-m") {
                        std::cout << Chars(filename) << ' ';
                    } else {
                        option_is_valid = true;
                        for (int k = 1; k < option.length(); k++) {
                            if (option[k] != 'l' && option[k] != 'w' && option[k] != 'c' && option[k] != 'm') {
                                option_is_valid = false;
                            }
                        }
                        if (option_is_valid) {
                            for (int k = 1; k < option.length(); k++) {
                                if (option[k] == 'l') {
                                    std::cout << Lines(filename) << ' ';
                                } else if (option[k] == 'w') {
                                    std::cout << Words(filename) << ' ';
                                } else if (option[k] == 'c') {
                                    std::cout << Bytes(filename) << ' ';
                                } else if (option[k] == 'm') {
                                    std::cout << Chars(filename) << ' ';
                                }
                            }
                        } else {
                            std::cout << "Invalid option" << ' ';
                        }
                    }
                }
                if (file_index_1 != 0) {
                    std::cout << filename << std::endl;
                }
            } else {
                std::cout << "File not found";
            }
            file.close();
        }
    }
    return 0;
}