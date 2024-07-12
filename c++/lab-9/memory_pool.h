#pragma once
#include <cstring>
#include <iostream>

class MemoryPool {
    public:
        MemoryPool(std::size_t num_blocks, std::size_t block_size);

        ~MemoryPool();

        MemoryPool(const MemoryPool& other);

        MemoryPool& operator=(const MemoryPool& other);

        bool operator<(const MemoryPool& other) const;

        [[nodiscard]] std::size_t block_size() const;

        [[nodiscard]] std::size_t num_blocks() const;

        [[nodiscard]] void* memory_begin() const;

        bool owns(void* ptr) const;

        void* allocate(std::size_t size);

        void deallocate(void* ptr, std::size_t size);

    private:
        std::size_t block_size_;
        std::size_t num_blocks_;
        void* memory_;
        bool* reserved_;
};