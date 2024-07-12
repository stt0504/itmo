#include "number.h"

uint32_t CountNum(uint32_t num) {
    if (num == 0) {
        return 1;
    }
    uint32_t tmp = num;
    uint32_t count = 0;
    while (tmp > 0) {
        count++;
        tmp /= 10;
    }

    return count;
}

uint2022_t from_uint(uint32_t i) {
    uint2022_t result;
    result.digits[kSize - 1] = i % (kMaxNumber + 1);
    result.digits[kSize - 2] = i / (kMaxNumber + 1);

    return result;
}

uint2022_t from_string(const char* buff) {
    uint2022_t result;
    uint32_t counter; // отсчитывает по 9 цифр с конца строки
    uint32_t index_digits = kSize - 1;
    char tmp[kCountDigits];
    char* res = tmp;
    int index_buff = strlen(buff) - 1;
    while (index_buff >= 0) {
        counter = 0;
        memset(res, '0', kCountDigits);
        while (index_buff >= 0 && counter < kCountDigits) {
            res[kCountDigits - counter - 1] = buff[index_buff];
            counter++;
            index_buff--;
        }
        result.digits[index_digits] = std::atoi(res);
        index_digits--;
    }

    return result;
}


uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint32_t tmp = 0;
    for (int i = kSize - 1; i >= 0; i--) {
        result.digits[i] = (lhs.digits[i] + rhs.digits[i] + tmp) % (kMaxNumber + 1);
        tmp = (lhs.digits[i] + rhs.digits[i] + tmp) / (kMaxNumber + 1);
    }

    return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint32_t tmp = 0;
    for (int i = kSize - 1; i >= 0; i--) {
        if (lhs.digits[i] >= rhs.digits[i] + tmp) {
            result.digits[i] = lhs.digits[i] - rhs.digits[i] - tmp;
            tmp = 0;
        } else {
            result.digits[i] = kMaxNumber + 1 + lhs.digits[i] - rhs.digits[i] - tmp;
            tmp = 1;
        }
    }

    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint32_t a[kSize]; // массив в котором хранится произведение lhs на один разряд rhs
    uint32_t tmp2 = 0; // переход разряда для result (когда прибавляем a)
    uint32_t tmp; // переход разряда для a
    uint32_t x;
    int index; // позиция с которой записываем а
    for (int i = kSize - 1; i >= 0; i--) {
        tmp = 0;
        memset(a, 0, sizeof(a));
        index = i;
        for (int j = kSize - 1; j >= 0; j--) {
            if (index >= 0) {
                a[index] = (uint64_t(lhs.digits[j]) * uint64_t(rhs.digits[i]) + tmp) % (kMaxNumber + 1);
                index--;
                tmp = (uint64_t(lhs.digits[j]) * uint64_t(rhs.digits[i]) + tmp) / (kMaxNumber + 1);
            }
        }
        for (int j = kSize - 1; j >= 0; j--) {
            x = result.digits[j] + a[j] + tmp2;
            result.digits[j] = x % (kMaxNumber + 1);
            tmp2 = x / (kMaxNumber + 1);
        }
    }

    return result;
}

uint2022_t operator/(const uint2022_t& lhs, const uint32_t& rhs) {
    uint2022_t result;
    uint64_t ost = 0;
    for (int i = 0; i <= kSize - 1; i++) {
        result.digits[i] = (uint64_t(lhs.digits[i]) + ost) / rhs;
        ost = (uint64_t(lhs.digits[i]) + ost) % rhs * (kMaxNumber + 1);
    }

    return result;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t l = from_uint(0);
    uint2022_t r = lhs;
    uint2022_t mid = (l + r) / 2;
    while (!((lhs >= rhs * mid) && (lhs <= rhs * mid + rhs - from_uint(1)))) {
        if (lhs < rhs * mid) {
            r = mid - from_uint(1);
        } else {
            l = mid + from_uint(1);
        }
        mid = (l + r) / 2;
    }

    return mid;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i < kSize; i++) {
        if (lhs.digits[i] != rhs.digits[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

bool operator>(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i <= kSize - 1; i++) {
        if (lhs.digits[i] > rhs.digits[i]) {
            return true;
        } else if (lhs.digits[i] < rhs.digits[i]) {
            return false;
        }
    }

    return false;
}

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs > rhs || lhs == rhs);
}

bool operator<=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    int i = 0;
    while (i <= kSize - 1 && value.digits[i] == 0) {
        i++;
    }
    if (i == kSize) {
        stream << 0;
        return stream;
    }
    stream << value.digits[i];
    uint32_t count_numbers;
    for (int j = i + 1; j <= kSize - 1; j++) {
        count_numbers = CountNum(value.digits[j]);
        for (int k = 0; k < kCountDigits - count_numbers; k++) {
            stream << 0;
        }
        stream << value.digits[j];
    }

    return stream;
}