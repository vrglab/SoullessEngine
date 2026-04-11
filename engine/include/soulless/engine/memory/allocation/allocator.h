#pragma once

#include <cstddef>
#include <soulless/engine/commons/macros.h>

namespace SoullessEngine::memory::allocation
{
    class SOULLESS_API Allocator
    {
    public:
        virtual ~Allocator() = default;
        
        virtual void* Allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) = 0;
        virtual void Deallocate(void* ptr) = 0;

        virtual const char* GetName() const = 0;
    };
}
