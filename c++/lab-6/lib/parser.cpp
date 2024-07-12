#include "parser.h"

using namespace omfl;

void omfl::RemoveBlanks(std::string& str) {
    while (isblank(str[0])) {
        str.erase(0, 1);
    }
    while (isblank(str[str.size() - 1])) {
        str.erase(str.size() - 1, 1);
    }
}

std::string omfl::RemovedQuotes(const std::string& str) {
    return str.substr(1, str.size() - 2);
}

bool omfl::IsInt(const std::string& value) {
    if (value.empty()) {
        return false;
    }
    if ((value[0] == '+' || value[0] == '-') && value.size() == 1) {
        return false;
    }
    for (int i = 0; i < value.size(); i++) {
        if (!((i == 0 && (value[i] == '+' || value[i] == '-')) || isdigit(value[i]))) {
            return false;
        }
    }
    return true;
}

bool omfl::IsFloat(const std::string& value) {
    if (value.size() < 3 || std::count(value.begin(), value.end(), '.') != 1) {
        return false;
    }
    if (!isdigit(value[0]) && (value[0] != '+') && (value[0] != '-')) {
        return false;
    }
    if (value[0] == '+' || value[0] == '-') {
        if (!isdigit(value[1])) {
            return false;
        }
    }
    if (!isdigit(value[value.size() - 1])) {
        return false;
    }
    for (int i = 1; i < value.size(); i++) {
        if (!(isdigit(value[i]) || value[i] == '.')) {
            return false;
        }
    }
    return true;
}

bool omfl::IsString(const std::string& value) {
    if (value.size() < 2 || value[0] != '"' || value[value.size() - 1] != '"') {
        return false;
    }
    for (int i = 1; i < value.size() - 1; i++) {
        if (value[i] == '"') {
            return false;
        }
    }
    return true;
}

bool omfl::IsBool(const std::string& value) {
    return (value == "true" || value == "false");
}

bool omfl::IsArray(const std::string& value) {
    if (value.size() < 2 || value[0] != '[' || value[value.size() - 1] != ']') {
        return false;
    }
    std::string str = value.substr(1, value.size() - 2);
    std::vector<std::string> array_elements;
    int i = 0;
    RemoveBlanks(str);
    std::string elem;
    while (i < str.size()) {
        while (i < str.size() && str[i] != ',') {
            elem += str[i];
            if (str[i] == '[') {
                int count_brackets = 1;
                i++;
                while (i < str.size() && count_brackets != 0) {
                    if (str[i] == '[') {
                        count_brackets++;
                    } else if (str[i] == ']') {
                        count_brackets--;
                    }
                    elem += str[i];
                    i++;
                }
            } else {
                i++;
            }
        }
        RemoveBlanks(elem);
        array_elements.push_back(elem);
        elem = "";
        i++;
    }
    return std::all_of(array_elements.begin(), array_elements.end(), ValueIsCorrect);
}

bool omfl::ValueIsCorrect(const std::string& value) {
    return IsInt(value) || IsFloat(value) || IsString(value) || IsBool(value) || IsArray(value);
}

bool Data::Key::IsInt() const {
    return ::IsInt(value_);
}

int Data::Key::AsInt() const {
    return stoi(value_);
}

int Data::Key::AsIntOrDefault(int default_value) const {
    return IsInt() ? stoi(value_) : default_value;
}

bool Data::Key::IsFloat() const {
    return ::IsFloat(value_);
}

float Data::Key::AsFloat() const {
    return stof(value_);
}

float Data::Key::AsFloatOrDefault(float default_value) const {
    return IsFloat() ? stof(value_) : default_value;
}

bool Data::Key::IsString() const {
    return ::IsString(value_);
}

std::string Data::Key::AsString() const {
    return RemovedQuotes(value_);
}

std::string Data::Key::AsStringOrDefault(const std::string& default_value) const {
    return IsString() ? RemovedQuotes(value_) : default_value;
}

bool Data::Key::IsBool() const {
    return ::IsBool(value_);
}

bool Data::Key::AsBool() const {
    return value_ == "true";
}

bool Data::Key::IsArray() const {
    return ::IsArray(value_);
}

Data::Key Data::Key::operator[](size_t n) {
    if (n >= keys_.size()) {
        Key key;
        return key;
    }
    return keys_[n];
}

Data::Key Data::Get(const std::string& name) const {
    for (const auto& key: keys) {
        if (key.name_ == name) {
            return key;
        }
    }
    Key key;
    key.name_ = name + '.';
    return key;
}

Data::Key Data::Key::Get(const std::string& name) {
    name_ += name;
    for (auto& key: keys) {
        if (name_ == key.name_) {
            return key;
        }
    }
    name_ += '.';
    return *this;
}

bool omfl::IsCorrectChar(char ch) {
    return isdigit(ch) || isalpha(ch) || ch == '-' || ch == '_';
}

bool omfl::NameIsCorrect(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    return std::all_of(name.begin(), name.end(), IsCorrectChar);
}

bool Data::valid() const {
    return valid_;
}

std::vector<Data::Key> omfl::ParseArray(const Data::Key& key) {
    std::string str = RemovedQuotes(key.value_);
    std::vector<Data::Key> elements;
    int i = 0;
    RemoveBlanks(str);
    std::string elem;
    while (i < str.size()) {
        while (i < str.size() && str[i] != ',') {
            elem += str[i];
            if (str[i] == '[') {
                int count_brackets = 1;
                i++;
                while (i < str.size() && count_brackets != 0) {
                    if (str[i] == '[') {
                        count_brackets++;
                    } else if (str[i] == ']') {
                        count_brackets--;
                    }
                    elem += str[i];
                    i++;
                }
            } else {
                i++;
            }
        }
        RemoveBlanks(elem);
        Data::Key element;
        element.value_ = elem;
        if (element.IsArray()) {
            element.keys_ = ParseArray(element);
        }
        elements.push_back(element);
        elem = "";
        i++;
    }
    return elements;
}

bool omfl::SectionNameIsValid(const std::string& name) {
    if (name.empty() || name[0] == '.' || name[name.size() - 1] == '.') {
        return false;
    }
    std::vector<std::string> sections;
    std::string tmp = name;
    const char* delim = ".";
    char* section = strtok(const_cast<char*>(tmp.c_str()), delim);
    while (section != nullptr) {
        sections.emplace_back(section);
        section = strtok(nullptr, delim);
    }
    return std::all_of(sections.begin(), sections.end(), NameIsCorrect);
}

Data omfl::parse(const std::string& str) {
    Data data;
    std::vector<std::string> lines;
    const char* delim = "\n";
    char* tok = strtok(const_cast<char*>(str.c_str()), delim);
    while (tok != nullptr) {
        lines.emplace_back(tok);
        tok = strtok(nullptr, delim);
    }
    for (auto& line: lines) {
        RemoveBlanks(line);
    }
    std::string section_name;
    for (auto& i: lines) {
        std::string line = i;
        if (line[0] == '[' && line[line.size() - 1] == ']') {
            section_name = line.substr(1, line.size() - 2);
            if (!SectionNameIsValid(section_name)) {
                data.valid_ = false;
            }
            section_name += '.';
        } else if (std::count(line.begin(), line.end(), '=') == 1) {
            std::string key_name;
            std::string value;
            int ind = 0;
            while (ind < line.size() && line[ind] != ' ' && line[ind] != '=') {
                key_name += line[ind];
                ind++;
            }
            while (ind < line.size() && (line[ind] == ' ' || line[ind] == '=')) {
                ind++;
            }
            while (ind < line.size() && (line[ind] != '#')) {
                value += line[ind];
                ind++;
            }
            RemoveBlanks(value);
            RemoveBlanks(key_name);
            RemoveBlanks(section_name);
            if (!NameIsCorrect(key_name)) {
                data.valid_ = false;
            }
            if (!ValueIsCorrect(value)) {
                data.valid_ = false;
            }
            Data::Key key;
            key.value_ = value;
            key.name_ = section_name + key_name;
            for (int j = 0; j < data.keys.size(); j++) {
                if (data.keys[j].name_ == key.name_) {
                    data.valid_ = false;
                }
            }
            if (key.IsArray()) {
                key.keys_ = ParseArray(key);
            }
            data.keys.push_back(key);
        } else {
            int ind = 0;
            while (ind < line.size() && line[ind] != '#') {
                ind++;
            }
            if (ind == line.size()) {
                data.valid_ = false;
            }
        }
    }
    return data;

}

Data omfl::parse(const std::filesystem::path& path) {
    std::ifstream in(path);
    char c;
    std::string file;
    while (in.get(c)) {
        file += c;
    }
    return parse(file);
}
