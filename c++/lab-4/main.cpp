#include "archive.h"

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if ((std::string) argv[i] == "-c" || (std::string) argv[i] == "--create") {
            std::string archname;
            int file_index;
            if ((std::string) argv[i + 1] == "-f") {
                archname = (std::string) argv[i + 2];
                file_index = i + 3;
            } else {
                archname = (std::string) argv[i + 1];
                archname = archname.substr(7, archname.length() - 7);
                file_index = i + 2;
            }
            std::vector<std::string> filenames;
            for (int j = file_index; j < argc; j++) {
                std::string filename = argv[j];
                filenames.push_back(filename);
            }
            std::string name = archname.substr(archname.find_last_of('\\') + 1, archname.size());
            std::string path = archname.substr(0, archname.length() - name.length());
            Archive archive(filenames, name, path);
            archive.Compression();
        } else if ((std::string) argv[i] == "-l" || (std::string) argv[i] == "--list") {
            std::string archname;
            if ((std::string) argv[i + 1] == "-f") {
                archname = (std::string) argv[i + 2];
            } else {
                archname = (std::string) argv[i + 1];
                archname = archname.substr(7, archname.length() - 7);
            }
            std::vector<std::string> filenames;
            std::string name = archname.substr(archname.find_last_of('\\') + 1, archname.size());
            std::string path = archname.substr(0, archname.length() - name.length());
            GetFiles(path + name + ".haf", filenames);
            for (int j = 0; j < filenames.size(); j++) {
                std::cout << filenames[j] << std::endl;
            }
        } else if ((std::string) argv[i] == "-a" || (std::string) argv[i] == "--append") {
            std::vector<std::string> filenames;
            std::vector<std::string> filenames_to_delete;
            std::string archname;
            int file_index;
            if ((std::string) argv[i + 1] == "-f") {
                archname = (std::string) argv[i + 2];
                file_index = i + 3;
            } else {
                archname = (std::string) argv[i + 1];
                archname = archname.substr(7, archname.length() - 7);
                file_index = i + 2;
            }
            std::string name = archname.substr(archname.find_last_of('\\') + 1, archname.size());
            std::string path = archname.substr(0, archname.length() - name.length());
            GetFiles(path + name + ".haf", filenames);
            std::ifstream in(path + name + "control_bit.txt");
            std::string control_bits;
            getline(in, control_bits);
            Decompression(path + name + ".haf", control_bits, path, filenames);
            for (int i = 0; i < filenames.size(); i++) {
                filenames[i].insert(0, path);
                filenames_to_delete.push_back(filenames[i]);
            }
            for (int j = file_index; j < argc; j++) {
                std::string filename = argv[j];
                filenames.push_back(filename);
            }
            Archive archive(filenames, name, path);
            archive.Compression();
            for (int i = 0; i < filenames_to_delete.size(); i++) {
                remove((filenames_to_delete[i]).c_str());
            }
        } else if ((std::string) argv[i] == "-d" || (std::string) argv[i] == "--delete") {
            std::vector<std::string> filenames;
            std::vector<std::string> filenames_to_delete;
            std::string archname;
            int file_index;
            if ((std::string) argv[i + 1] == "-f") {
                archname = (std::string) argv[i + 2];
                file_index = i + 3;
            } else {
                archname = (std::string) argv[i + 1];
                archname = archname.substr(7, archname.length() - 7);
                file_index = i + 2;
            }
            std::string name = archname.substr(archname.find_last_of('\\') + 1, archname.size());
            std::string path = archname.substr(0, archname.length() - name.length());
            GetFiles(path + name + ".haf", filenames);
            GetFiles(path + name + ".haf", filenames_to_delete);
            std::ifstream in(path + name + "control_bit.txt");
            std::string control_bits;
            getline(in, control_bits);
            Decompression(path + name + ".haf", control_bits, path, filenames);
            for (int j = file_index; j < argc; j++) {
                std::string filename = argv[j];
                for (int k = 0; k < filenames.size(); k++) {
                    if (filenames[k] == filename) {
                        filenames.erase(filenames.begin() + k);
                    }
                }
            }
            for (int i = 0; i < filenames.size(); i++) {
                filenames[i].insert(0, path);
            }
            for (int i = 0; i < filenames_to_delete.size(); i++) {
                filenames_to_delete[i].insert(0, path);
            }
            Archive archive(filenames, name, path);
            archive.Compression();
            for (int i = 0; i < filenames_to_delete.size(); i++) {
                remove(filenames_to_delete[i].c_str());
            }
        } else if ((std::string) argv[i] == "-x" || (std::string) argv[i] == "--extract") {
            std::vector<std::string> filenames;
            std::string archname;
            int file_index;
            if ((std::string) argv[i + 1] == "-f") {
                archname = (std::string) argv[i + 2];
                file_index = i + 3;
            } else {
                archname = (std::string) argv[i + 1];
                archname = archname.substr(7, archname.length() - 7);
                file_index = i + 2;
            }
            for (int j = file_index; j < argc; j++) {
                std::string filename = argv[j];
                filenames.push_back(filename);
            }
            std::string name = archname.substr(archname.find_last_of('\\') + 1, archname.size());
            std::string path = archname.substr(0, archname.length() - name.length());
            std::ifstream in(path + name + "control_bit.txt");
            std::string control_bits;
            getline(in, control_bits);
            if (filenames.empty()) {
                GetFiles(path + name + ".haf", filenames);
                Decompression(path + name + ".haf", control_bits, path, filenames);
            } else {
                Decompression(path + name + ".haf", control_bits, path, filenames);
            }
        } else if ((std::string) argv[i] == "-A" || (std::string) argv[i] == "--concatenate") {
            std::string archname;
            std::vector<std::string> archives;
            std::vector<std::string> filenames_all;
            int j = i + 1;
            while (argv[j][0] != '-') {
                archives.push_back(argv[j]);
                j++;
            }
            if ((std::string) argv[j] == "-f") {
                archname = (std::string) argv[j + 1];
            } else {
                archname = (std::string) argv[i + 2];
                archname = archname.substr(7, archname.length() - 7);
            }
            std::string name = archname.substr(archname.find_last_of('\\') + 1, archname.size());
            std::string path = archname.substr(0, archname.length() - name.length());
            for (int i = 0; i < archives.size(); i++) {
                std::vector<std::string> filenames;
                GetFiles(archives[i] + ".haf", filenames);
                GetFiles(archives[i] + ".haf", filenames_all);
                std::ifstream in(archives[i] + "control_bit.txt");
                std::string control_bits;
                getline(in, control_bits);
                Decompression(archives[i] + ".haf", control_bits, path, filenames);
            }
            for (int i = 0; i < filenames_all.size(); i++) {
                filenames_all[i].insert(0, path);
            }
            Archive archive(filenames_all, name, path);
            archive.Compression();
            for (int i = 0; i < filenames_all.size(); i++) {
                remove((filenames_all[i]).c_str());
            }
        }
    }
}