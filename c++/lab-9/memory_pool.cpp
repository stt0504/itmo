#include "memory_pool.h"

MemoryPool::MemoryPool(std::size_t num_blocks, std::size_t block_size)
    : num_blocks_(num_blocks), block_size_(block_size) {
    memory_ = std::malloc(block_size_ * num_blocks_);
    reserved_ = new bool[num_blocks_];
    std::memset(reserved_, false, num_blocks_);
}

MemoryPool::~MemoryPool() {
    std::free(memory_);
    delete[] reserved_;
}

bool MemoryPool::operator<(const MemoryPool& other) const {
    return block_size() < other.block_size();
}

std::size_t MemoryPool::block_size() const {
    return block_size_;
}

std::size_t MemoryPool::num_blocks() const {
    return num_blocks_;
}

void* MemoryPool::memory_begin() const {
    return memory_;
}

bool MemoryPool::owns(void* ptr) const {
    return ptr >= memory_begin()
        && ptr < static_cast<void*>(static_cast<char*>(memory_begin()) + num_blocks() * block_size());
}

void* MemoryPool::allocate(std::size_t size) {
    std::size_t num_blocks_alloc =
        (size + block_size() - 1) / block_size();
    void* first = nullptr;
    std::size_t num_first;
    std::size_t count_free = 0;
    for (std::size_t i = 0; i < num_blocks(); i++) {
        if (!reserved_[i]) {
            if (!first) {
                first = static_cast<void*>(static_cast<char*>(memory_begin()) + i * block_size());
                num_first = i;
            }
            count_free++;
        } else {
            first = nullptr;
            count_free = 0;
        }
        if (count_free == num_blocks_alloc) {
            std::memset(reserved_ + num_first, true, num_blocks_alloc);
            return first;
        }
    }
    return nullptr;
}

void MemoryPool::deallocate(void* ptr, std::size_t size) {
    std::size_t num_blocks_to_free =
        (size + block_size() - 1) / block_size();
    for (std::size_t i = 0; i < num_blocks(); i++) {
        if (static_cast<void*>(static_cast<char*>(memory_begin()) + i * block_size()) == ptr) {
            std::memset(reserved_ + i, false, num_blocks_to_free);
            break;
        }
    }
}

MemoryPool::MemoryPool(const MemoryPool& other)
    : num_blocks_(other.num_blocks_), block_size_(other.block_size_) {
    memory_ = std::malloc(block_size_ * num_blocks_);
    std::memcpy(memory_, other.memory_, block_size_ * num_blocks_);
    reserved_ = new bool[num_blocks_];
    std::memcpy(reserved_, other.reserved_, num_blocks_);
}

MemoryPool& MemoryPool::operator=(const MemoryPool& other) {
    if (this == &other) {
        return *this;
    }
    std::size_t new_num_blocks = other.num_blocks();
    std::size_t new_block_size = other.block_size();
    void* new_memory = std::malloc(new_block_size * new_num_blocks);
    bool* new_reserved = new bool[new_num_blocks];
    std::memcpy(new_memory, other.memory_begin(), new_block_size * new_num_blocks);
    std::memcpy(new_reserved, other.reserved_, new_num_blocks);
    std::free(memory_);
    delete[] reserved_;
    num_blocks_ = new_num_blocks;
    block_size_ = new_block_size;
    memory_ = new_memory;
    reserved_ = new_reserved;
    return *this;
}
