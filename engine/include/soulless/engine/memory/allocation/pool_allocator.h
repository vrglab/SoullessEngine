#pragma once

#include <soulless/engine/memory/allocation/allocator.h>
#include <soulless/engine/commons/macros.h>
#include <cstddef>
#include <cstdint>

namespace SoullessEngine::memory::allocation {
    
    class SOULLESS_API PoolAllocator final : public Allocator
    {
    private:
        struct FreeNode
        {
            FreeNode* Next;
        };

    public:
        PoolAllocator(void* memory, std::size_t totalSize, std::size_t blockSize, const char* name = "PoolAllocator")
            : m_Start(static_cast<std::byte*>(memory)),
              m_TotalSize(totalSize),
              m_BlockSize(blockSize < sizeof(FreeNode*) ? sizeof(FreeNode*) : blockSize),
              m_Name(name),
              m_FreeList(nullptr)
        {
            InitializeFreeList();
        }

        void* Allocate(std::size_t size, std::size_t alignment) override;


        void Deallocate(void* ptr) override;


        const char* GetName() const override;


    private:
        void InitializeFreeList();

    private:
        std::byte* m_Start;
        std::size_t m_TotalSize;
        std::size_t m_BlockSize;
        const char* m_Name;
        FreeNode* m_FreeList;
    };
}