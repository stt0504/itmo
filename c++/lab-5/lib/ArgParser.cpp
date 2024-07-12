#include "ArgParser.h"

using namespace ArgumentParser;

ArgParser::ArgParser(const std::string& name) {
    name_ = name;
}

ArgParser::StringArgument& ArgParser::AddStringArgument(const std::string& arg) {
    StringArgument new_string_argument;
    new_string_argument.full_arg_name_ = arg;
    args_string.push_back(new_string_argument);
    return args_string.back();
}

ArgParser::StringArgument& ArgParser::AddStringArgument(char arg1, const std::string& arg2) {
    StringArgument new_string_argument;
    new_string_argument.short_arg_name_ = arg1;
    new_string_argument.full_arg_name_ = arg2;
    args_string.push_back(new_string_argument);
    return args_string.back();
}

ArgParser::StringArgument& ArgParser::AddStringArgument(char arg1, const std::string& arg2, const std::string& arg3) {
    StringArgument new_string_argument;
    new_string_argument.short_arg_name_ = arg1;
    new_string_argument.full_arg_name_ = arg2;
    new_string_argument.arg_description_ = arg3;
    args_string.push_back(new_string_argument);
    return args_string.back();
}

std::string ArgParser::GetStringValue(const std::string& arg) const {
    for (int i = 0; i < args_string.size(); i++) {
        if (args_string[i].full_arg_name_ == arg || args_string[i].arg_description_ == arg) {
            return args_string[i].value_;
        }
    }
}

ArgParser::IntArgument& ArgParser::AddIntArgument(const std::string& arg1) {
    IntArgument new_int_argument;
    new_int_argument.full_arg_name_ = arg1;
    args_int.push_back(new_int_argument);
    return args_int.back();
}

ArgParser::IntArgument& ArgParser::AddIntArgument(char arg1, const std::string& arg2) {
    IntArgument new_int_argument;
    new_int_argument.short_arg_name_ = arg1;
    new_int_argument.full_arg_name_ = arg2;
    args_int.push_back(new_int_argument);
    return args_int.back();
}

ArgParser::IntArgument& ArgParser::AddIntArgument(const std::string& arg1, const std::string& arg2) {
    IntArgument new_int_argument;
    new_int_argument.full_arg_name_ = arg1;
    new_int_argument.arg_description_ = arg2;
    args_int.push_back(new_int_argument);
    return args_int.back();
}

bool ArgParser::ParseStrings(const std::vector<std::string>& args_input) {
    bool result = true;
    for (int i = 0; i < args_string.size(); i++) {
        bool has_arg = false;
        std::string arg1 = args_string[i].full_arg_name_;
        std::string arg2 = args_string[i].arg_description_;
        char arg3 = args_string[i].short_arg_name_;
        for (int j = 0; j < args_input.size(); j++) {
            if ((args_input[j].size() >= 2) && args_input[j][1] == '-') {
                int count = 0;
                while (count + 2 < args_input[j].size() && args_input[j][count + 2] != '=') {
                    count++;
                }
                std::string arg = args_input[j].substr(2, count);
                std::string value;
                if (count + 3 < args_input[j].size()) {
                    value = args_input[j].substr(count + 3, args_input[j].size());
                }
                if (arg == arg1 || arg == arg2) {
                    args_string[i].value_ = value;
                    if (args_string[i].store_ != nullptr) {
                        *args_string[i].store_ = value;
                    }
                    has_arg = true;
                }
            } else if (!args_input[j].empty() && args_input[j][0] == '-') {
                char arg = args_input[j][1];
                std::string value = args_input[j].substr(3, args_input[j].size());
                if (arg == arg3) {
                    args_string[i].value_ = value;
                    if (args_string[i].store_ != nullptr) {
                        *args_string[i].store_ = value;
                    }
                    has_arg = true;
                }
            } else {
                if (!args_string[i].value_.empty()) {
                    has_arg = true;
                }
            }
        }
        if (!has_arg) {
            result = has_arg;
        }
    }
    return result;
}

bool ArgParser::ParseInts(const std::vector<std::string>& args_input) {
    bool result = true;
    for (int i = 0; i < args_int.size(); i++) {
        bool has_arg = false;
        std::string arg1 = args_int[i].full_arg_name_;
        std::string arg2 = args_int[i].arg_description_;
        char arg3 = args_int[i].short_arg_name_;
        for (int j = 0; j < args_input.size(); j++) {
            if ((args_input[j].size() >= 2) && args_input[j][1] == '-') {
                int count = 0;
                while (count + 2 < args_input[j].size() && args_input[j][count + 2] != '=') {
                    count++;
                }
                std::string arg = args_input[j].substr(2, count);
                int value;
                if (count + 3 < args_input[j].size()) {
                    value = stoi(args_input[j].substr(count + 3, args_input[j].size()));
                }
                if (arg == arg1 || arg == arg2) {
                    if (!args_int[i].is_multi_value_) {
                        args_int[i].value_ = value;
                        has_arg = true;
                    } else {
                        args_int[i].values_.push_back(value);
                        (*args_int[i].store_).push_back(value);
                        if ((*args_int[i].store_).size() < args_int[i].min_args_count_) {
                            has_arg = false;
                        } else {
                            has_arg = true;
                        }
                    }
                }
            } else if (args_int[i].is_positional_) {
                if (j != 0) {
                    args_int[i].values_.push_back(stoi(args_input[j]));
                    (*args_int[i].store_).push_back(stoi(args_input[j]));
                    if ((*args_int[i].store_).size() < args_int[i].min_args_count_) {
                        has_arg = false;
                    } else {
                        has_arg = true;
                    }
                }
            }
        }
        if (!has_arg) {
            result = has_arg;
        }
    }
    return result;
}

bool ArgParser::ParseFlags(const std::vector<std::string>& args_input) {
    bool result = true;
    for (int i = 0; i < args_flag.size(); i++) {
        bool has_arg = false;
        std::string arg1 = args_flag[i].full_arg_name_;
        std::string arg2 = args_flag[i].arg_description_;
        char arg3 = args_flag[i].short_arg_name_;
        for (int j = 0; j < args_input.size(); j++) {
            if ((args_input[j].size() >= 2) && args_input[j][1] == '-') {
                std::string arg = args_input[j].substr(2, args_input[j].size());
                if (arg == arg1 || arg == arg2) {
                    has_arg = true;
                    if (args_flag[i].store_ != nullptr) {
                        *args_flag[i].store_ = args_flag[i].value_;
                    }
                }
            } else if (!args_input[j].empty() && args_input[j][0] == '-') {
                for (int k = 1; k < args_input[j].size(); k++) {
                    char arg = args_input[j][k];
                    if (arg == arg3 || args_flag[i].value_is_default_) {
                        has_arg = true;
                        if (args_flag[i].store_ != nullptr) {
                            *args_flag[i].store_ = args_flag[i].value_;
                        }
                    }
                }
            }
        }
        if (!has_arg) {
            result = has_arg;
        }
    }
    return result;
}

bool ArgParser::ParseHelp(const std::vector<std::string>& args_input) {
    bool result = true;
    if (Help()) {
        bool has_arg = false;
        std::string arg1 = help_.full_arg_name_;
        std::string arg2 = help_.arg_description_;
        char arg3 = help_.short_arg_name_;
        for (int j = 0; j < args_input.size(); j++) {
            if ((args_input[j].size() >= 2) && args_input[j][1] == '-') {
                std::string arg = args_input[j].substr(2, args_input[j].size());
                if (arg == arg1 || arg == arg2) {
                    has_arg = true;
                }
            }
        }
        if (!has_arg) {
            result = has_arg;
        } else {
            return has_arg;
        }
    }
    return result;
}

bool ArgParser::Parse(const std::vector<std::string>& args_input) {
    ParseHelp(args_input);
    bool parse_str = ParseStrings(args_input);
    bool parse_int = ParseInts(args_input);
    bool parse_flag = ParseFlags(args_input);
    if (Help()) {
        return true;
    }
    return (parse_str && parse_int && parse_flag);
}

int ArgParser::GetIntValue(const std::string& arg) const {
    for (int i = 0; i < args_int.size(); i++) {
        if (args_int[i].full_arg_name_ == arg || args_int[i].arg_description_ == arg) {
            return args_int[i].value_;
        }
    }
}

int ArgParser::GetIntValue(const std::string& arg, int pos) const {
    for (int i = 0; i < args_int.size(); i++) {
        if (args_int[i].full_arg_name_ == arg || args_int[i].arg_description_ == arg) {
            return args_int[i].values_[pos];
        }
    }
}

ArgParser::FlagArgument& ArgParser::AddFlag(char arg1, const std::string& arg2) {
    FlagArgument new_flag;
    new_flag.short_arg_name_ = arg1;
    new_flag.full_arg_name_ = arg2;
    new_flag.value_ = true;
    args_flag.push_back(new_flag);
    return args_flag.back();
}


bool ArgParser::GetFlag(const std::string& FlagArgument) const {
    for (int i = 0; i < args_flag.size(); i++) {
        if (args_flag[i].full_arg_name_ == FlagArgument || args_flag[i].arg_description_ == FlagArgument) {
            return true;
        }
    }
    return false;
}

void ArgParser::AddHelp(char arg1, const std::string& arg2, const std::string& arg3) {
    class Help new_help;
    new_help.full_arg_name_ = arg2;
    new_help.arg_description_ = arg3;
    new_help.short_arg_name_ = arg1;
    new_help.exists_ = true;
    help_ = new_help;
}

bool ArgParser::Help() {
    return help_.exists_;
}

ArgParser::FlagArgument& ArgParser::AddFlag(char arg1, const std::string& arg2, const std::string& arg3) {
    FlagArgument new_flag;
    new_flag.short_arg_name_ = arg1;
    new_flag.full_arg_name_ = arg2;
    new_flag.arg_description_ = arg3;
    new_flag.value_ = true;
    args_flag.push_back(new_flag);
    return args_flag.back();
}

ArgParser::FlagArgument& ArgParser::AddFlag(const std::string& arg1, const std::string& arg2) {
    FlagArgument new_flag;
    new_flag.full_arg_name_ = arg1;
    new_flag.arg_description_ = arg2;
    new_flag.value_ = true;
    args_flag.push_back(new_flag);
    return args_flag.back();
}

std::string ArgParser::HelpDescription() {
    std::string description;
    description += name_ += '\n';
    description += help_.arg_description_ + '\n' + '\n';
    for (int i = 0; i < args_string.size(); i++) {
        if (args_string[i].short_arg_name_ == '\0') {
            description += "     ";
        } else {
            description += '-' + std::string(1, args_string[i].short_arg_name_) + ",  ";
        }
        description += "--" + args_string[i].full_arg_name_ + "=<string>,  ";
        description += args_string[i].arg_description_;
        if (args_string[i].is_multi_value_) {
            description += " [repeated, min args = " + std::to_string(args_string[i].count_) + "]\n";
        }
    }
    for (int i = 0; i < args_flag.size(); i++) {
        if (args_flag[i].short_arg_name_ == '\0') {
            description += "     ";
        } else {
            description += '-' + std::string(1, args_flag[i].short_arg_name_) + ",  ";
        }
        description += "--" + args_flag[i].full_arg_name_ + ",  ";
        description += args_flag[i].arg_description_;
        if (args_flag[i].value_is_default_) {
            description += " [default = " + (std::string) (args_flag[i].value_ ? "true" : "false") + "]\n";
        } else {
            description += '\n';
        }
    }
    for (int i = 0; i < args_int.size(); i++) {
        if (args_int[i].short_arg_name_ == '\0') {
            description += "     ";
        } else {
            description += '-' + std::string(1, args_int[i].short_arg_name_) + ",  ";
        }
        description += "--" + args_int[i].full_arg_name_ + "=<int>,  ";
        description += args_int[i].arg_description_;
        if (args_int[i].is_multi_value_) {
            description += " [repeated, min args = " + std::to_string(args_int[i].min_args_count_) + "]\n";
        } else {
            description += '\n';
        }
    }
    description += '\n';
    description += '-' + std::string(1, help_.short_arg_name_) + ",  ";
    description += "--" + help_.full_arg_name_ + " " + "Display this help and exit\n";
    return description;
}

bool ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> args_input;
    for (int i = 0; i < argc; i++) {
        args_input.push_back(argv[i]);
    }
    return Parse(args_input);
}

void ArgParser::StringArgument::Default(const std::string& default_value) {
    value_ = default_value;
}

void ArgParser::StringArgument::StoreValue(std::string& value) {
    store_ = &value;
}

void ArgParser::StringArgument::MultiValue(int count) {
    is_multi_value_ = true;
    count_ = count;
}

ArgParser::IntArgument& ArgParser::IntArgument::MultiValue() {
    is_multi_value_ = true;
    return *this;
}

ArgParser::IntArgument& ArgParser::IntArgument::StoreValues(std::vector<int>& values) {
    store_ = &values;
}

ArgParser::IntArgument& ArgParser::IntArgument::MultiValue(size_t count) {
    is_multi_value_ = true;
    min_args_count_ = count;
    return *this;
}

ArgParser::IntArgument& ArgParser::IntArgument::Positional() {
    is_positional_ = true;
    return *this;
}

void ArgParser::IntArgument::StoreValue(std::vector<int>& values) {
    store_ = &values;
}

void ArgParser::FlagArgument::Default(bool value) {
    value_ = value;
    value_is_default_ = true;
}

void ArgParser::FlagArgument::StoreValue(bool& value) {
    store_ = &value;
}