#pragma once

#include <soulless/engine/memory/allocation/allocator.h>
#include <soulless/engine/commons/macros.h>
#include <cassert>

namespace SoullessEngine::memory::allocation
{
    class SOULLESS_API LinearAllocator final : public Allocator
    {
    public:
        LinearAllocator(void* memory, std::size_t size, const char* name = "LinearAllocator")
            : m_Start(reinterpret_cast<std::uintptr_t>(memory)),
              m_Size(size),
              m_Offset(0),
              m_Name(name)
        {
        }

        void* Allocate(std::size_t size, std::size_t alignment) override;

        void Deallocate(void* ptr) override;

        void Reset();

        const char* GetName() const override;
        std::size_t GetUsed() const;
        std::size_t GetCapacity() const;


    private:
        static std::uintptr_t AlignForward(std::uintptr_t ptr, std::size_t alignment);

    private:
        std::uintptr_t m_Start;
        std::size_t m_Size;
        std::size_t m_Offset;
        const char* m_Name;
    };
}