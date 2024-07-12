#include <lib/number.h>
#include <iostream>

int main() {
    uint2022_t x = from_string("123456765434567865432345678765432456787654323456787654324567876543456789");
    uint2022_t y = from_string("1");
    std::cout << x/y << std::endl;
    return 0;
}
