#pragma once

#include <algorithm>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace omfl {
    class Data {
    public:
        bool valid_ = true;

        class Key {
        public:
            std::string name_;
            std::string value_;
            std::vector<Key> keys_;

            Key operator[](size_t n);

            bool IsInt() const;

            int AsInt() const;

            int AsIntOrDefault(int default_value) const;

            bool IsFloat() const;

            float AsFloat() const;

            float AsFloatOrDefault(float default_value) const;

            bool IsString() const;

            std::string AsString() const;

            std::string AsStringOrDefault(const std::string& default_value) const;

            bool IsBool() const;

            bool AsBool() const;

            bool IsArray() const;

            Key Get(const std::string& name);
        };

        inline static std::vector<Key> keys;

        Key Get(const std::string& name) const;

        bool valid() const;
    };

    Data parse(const std::filesystem::path& path);

    Data parse(const std::string& str);

    bool ValueIsCorrect(const std::string& value);

    void RemoveBlanks(std::string& str);

    std::string RemovedQuotes(const std::string& str);

    bool IsCorrectChar(char ch);

    bool NameIsCorrect(const std::string& name);

    bool SectionNameIsValid(const std::string& name);

    bool IsInt(const std::string& value);

    bool IsFloat(const std::string& value);

    bool IsString(const std::string& value);

    bool IsBool(const std::string& value);

    bool IsArray(const std::string& value);

    std::vector<Data::Key> ParseArray(const Data::Key& key);

}// namespace