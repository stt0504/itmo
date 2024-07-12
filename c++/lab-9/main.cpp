#include <chrono>
#include "allocator.h"
#include <list>
#include <map>

int main() {
    std::cout << "Allocator type (1 - MemoryPoolAllocator, 2 - std::allocator): " << std::endl;
    std::string alloc_type;
    std::cin >> alloc_type;
    std::size_t n;
    std::cout << "Number of objects: " << std::endl;
    std::cin >> n;
    if (alloc_type == "2") {
        std::vector<int> a;
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < n; ++i) {
            a.push_back(i);
        }
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << "Program time: " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
        a.clear();
    } else {
        std::size_t count;
        std::cout << "Number of pools: " << std::endl;
        std::cin >> count;
        std::vector<MemoryPool> pools;
        pools.reserve(count);
        for (std::size_t i = 0; i < count; ++i) {
            std::size_t block_number;
            std::size_t block_size;
            std::cout << "Number of blocks and size (through a space): " << std::endl;
            std::cin >> block_number >> block_size;
            pools.emplace_back(block_number, block_size);
        }
        MemoryPoolAllocator<int> alloc(&pools);
        MemoryPoolAllocator<std::pair<const int,int>> m_all(&pools);
        //std::list<int, MemoryPoolAllocator<int>> a(alloc);
        std::map<int,int,MemoryPoolAllocator<std::pair<const int,int>>> m;

        std::vector<int, MemoryPoolAllocator<int>> v(alloc);
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < n; ++i) {
            v.push_back(i);
        }
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << "Program time: " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    }
}