#pragma once
#include <cinttypes>
#include <cstring>
#include <iostream>

const int kSize = 68;
const int kMaxNumber = 999999999;
const int kCountDigits = 9;

struct uint2022_t {
    uint32_t digits[kSize];
    uint2022_t () {
        memset(digits, 0, sizeof(digits));
    }
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint32_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator>(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator<=(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator>=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);