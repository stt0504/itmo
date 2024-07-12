#pragma once
#include "memory_pool.h"
#include <stdexcept>
#include <vector>

template<typename T>
class MemoryPoolAllocator {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using pointer = T*;

        MemoryPoolAllocator() {
            m_pools = nullptr;
        };

        explicit MemoryPoolAllocator(std::vector<MemoryPool>* pools) {
            m_pools = pools;
            std::sort(pools->begin(), pools->end());
        }

        MemoryPoolAllocator(const MemoryPoolAllocator& other) {
            m_pools = other.m_pools;
        }

        template<typename U>
        explicit MemoryPoolAllocator(MemoryPoolAllocator<U>& other) {
            m_pools = other.GetPools();
        }

        MemoryPoolAllocator& operator=(const MemoryPoolAllocator& other) {
            if (this == &other) {
                return *this;
            }
            m_pools = other.m_pools;
            return *this;
        }

        pointer allocate(size_type count_objects) {
            size_type size = count_objects * sizeof(value_type);
            for (auto& pool : *m_pools) {
                auto ptr = static_cast<pointer>(pool.allocate(size));
                if (ptr) {
                    return ptr;
                }
            }
            throw std::bad_alloc();
        }

        void deallocate(pointer ptr, size_type size) {
            for (auto& pool : *m_pools) {
                if (pool.owns(static_cast<void*>(ptr))) {
                    pool.deallocate(static_cast<void*>(ptr), size * sizeof(value_type));
                    return;
                }
            }
        }

        bool operator==(const MemoryPoolAllocator& other) const {
            return m_pools == other.m_pools;
        }

        bool operator!=(const MemoryPoolAllocator& other) const {
            return !(*this == other);
        }

        std::vector<MemoryPool>* GetPools() {
            return m_pools;
        }
        ~MemoryPoolAllocator() = default;

    private:
        std::vector<MemoryPool>* m_pools;
};