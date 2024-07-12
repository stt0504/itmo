#include <id3v2parser.h>

int main(int argc, char** argv) {
    std::vector<ID3v2Frame*> frames;
    std::ofstream out;
    bool out_was_entered = false;
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--file") {
            if (i + 1 >= argc) {
                std::cout << "Enter a filename" << std::endl;
            } else {
                frames = ParseMP3File(argv[i + 1]);
            }
        } else if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--output") {
            if (i + 1 >= argc) {
                std::cout << "Enter an output file" << std::endl;
            } else {
                out.open(argv[i + 1]);
                out_was_entered = true;
            }
        }
    }
    if (out_was_entered) {
        if (out.is_open()) {
            for (auto& frame : frames) {
                out << *frame;
            }
        } else {
            std::cerr << "Error opening file" << std::endl;
        }
    } else {
        for (auto& frame : frames) {
            std::cout << *frame;
        }
    }
    for (auto& frame : frames) {
        delete frame;
    }

    return 0;
}
