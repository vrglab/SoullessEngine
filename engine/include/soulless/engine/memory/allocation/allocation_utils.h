#pragma once

#include <soulless/engine/memory/allocation/allocator.h>
#include <utility>
#include <new>

namespace SoullessEngine::memory::allocation
{
    template <typename T, typename... Args>
    T* New(Allocator& allocator, Args&&... args)
    {
        void* memory = allocator.Allocate(sizeof(T), alignof(T));
        return new (memory) T(std::forward<Args>(args)...);
    }

    template <typename T>
    void Delete(Allocator& allocator, T* ptr)
    {
        if (!ptr)
            return;

        ptr->~T();
        allocator.Deallocate(ptr);
    }
}