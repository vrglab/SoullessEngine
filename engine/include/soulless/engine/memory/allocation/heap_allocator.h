#pragma once

#include "allocator.h"
#include <new>
#include <soulless/engine/commons/macros.h>

namespace SoullessEngine::memory::allocation
{
    class SOULLESS_API HeapAllocator final : public Allocator
    {
    private:
        struct AllocationHeader
        {
            std::size_t Size;
            std::size_t Alignment;
        };
        
    public:
        explicit HeapAllocator(const char* name = "HeapAllocator")
            : m_Name(name), m_AllocationCount(0), m_BytesAllocated(0)
        {
        }

        void* Allocate(std::size_t size, std::size_t alignment) override;

        void Deallocate(void* ptr) override;

        const char* GetName() const override;
        std::size_t GetAllocationCount() const;
        std::size_t GetBytesAllocated() const;

    private:
        const char* m_Name;
        std::size_t m_AllocationCount;
        std::size_t m_BytesAllocated;
    };
}