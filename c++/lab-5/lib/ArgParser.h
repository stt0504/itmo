#pragma once

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

namespace ArgumentParser {

    class ArgParser {
    public:
        std::string name_;

        ArgParser(const std::string& name);

        class StringArgument {
        public:
            std::string full_arg_name_;
            std::string arg_description_;
            char short_arg_name_ = '\0';
            std::string value_;
            int count_ = 0;
            bool is_multi_value_ = false;
            std::string* store_ = nullptr;

            void Default(const std::string& default_value);

            void StoreValue(std::string& value);

            void MultiValue(int count);
        };

        std::vector<StringArgument> args_string;

        StringArgument& AddStringArgument(const std::string& arg1);

        StringArgument& AddStringArgument(char arg1, const std::string& arg2);

        StringArgument& AddStringArgument(char arg1, const std::string& arg2, const std::string& arg3);

        std::string GetStringValue(const std::string& arg) const;

        class IntArgument {
        public:
            std::string full_arg_name_;
            std::string arg_description_;
            char short_arg_name_ = '\0';
            int value_ = 0;
            std::vector<int> values_;
            std::vector<int>* store_ = nullptr;
            size_t min_args_count_ = 0;
            bool is_multi_value_ = false;
            bool is_positional_ = false;

            IntArgument& MultiValue();

            IntArgument& MultiValue(size_t count);

            IntArgument& Positional();

            IntArgument& StoreValues(std::vector<int>& values);

            void StoreValue(std::vector<int>& values);
        };

        std::vector<IntArgument> args_int;

        IntArgument& AddIntArgument(const std::string& arg1);

        IntArgument& AddIntArgument(const std::string& arg1, const std::string& arg2);

        IntArgument& AddIntArgument(char arg1, const std::string& arg2);

        int GetIntValue(const std::string& arg) const;

        int GetIntValue(const std::string& arg, int pos) const;

        bool GetFlag(const std::string& FlagArgument) const;

        class FlagArgument {
        public:
            std::string full_arg_name_;
            std::string arg_description_;
            char short_arg_name_ = '\0';
            bool value_ = false;
            bool* store_ = nullptr;
            bool value_is_default_ = false;

            void Default(bool value);

            void StoreValue(bool& value);
        };

        std::vector<FlagArgument> args_flag;

        FlagArgument& AddFlag(char arg1, const std::string& arg2);

        FlagArgument& AddFlag(char arg1, const std::string& arg2, const std::string& arg3);

        FlagArgument& AddFlag(const std::string& arg1, const std::string& arg2);

        class Help {
        public:
            std::string full_arg_name_;
            std::string arg_description_;
            char short_arg_name_ = '\0';
            bool exists_ = false;
        };

        Help help_;

        void AddHelp(char arg1, const std::string& arg2, const std::string& arg3);

        bool Help();

        bool ParseStrings(const std::vector<std::string>& args_input);

        bool ParseInts(const std::vector<std::string>& args_input);

        bool ParseFlags(const std::vector<std::string>& args_input);

        bool ParseHelp(const std::vector<std::string>& args_input);

        bool Parse(const std::vector<std::string>& args_input);

        bool Parse(int argc, char** argv);

        std::string HelpDescription();
    };

} // namespace ArgumentParser