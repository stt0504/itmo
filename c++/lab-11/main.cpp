#include "algorithm.h"
#include "xrange.h"
#include "zip.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <list>




int main() {
    std::list<int> list = {};
    std::vector<int> vector = {1, 2};
    std::vector<std::pair<int, int>> expected = {};
   // auto result = zip(list, vector);
    for(auto value : zip(list, vector)) {
        std::cout << value.first << " " << value.second << std::endl;
    }

    return 0;
}