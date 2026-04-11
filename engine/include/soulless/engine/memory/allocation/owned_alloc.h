#pragma once

#include <soulless/engine/memory/allocation/allocator.h>

namespace SoullessEngine::memory::allocation
{
    template <typename T>
    struct AllocatorDeleter
    {
        Allocator* OwnerAllocator = nullptr;

        void operator()(T* ptr) const
        {
            if (!ptr || !OwnerAllocator)
                return;

            ptr->~T();
            OwnerAllocator->Deallocate(ptr);
        }
    };
    
    template <typename T>
    using AllocScope = std::unique_ptr<T, AllocatorDeleter<T>>;

    template <typename T, typename... Args>
    AllocScope<T> CreateAllocScope(Allocator& allocator, Args&&... args)
    {
        void* memory = allocator.Allocate(sizeof(T), alignof(T));
        T* object = new (memory) T(std::forward<Args>(args)...);

        return AllocScope<T>(object, AllocatorDeleter<T>{ &allocator });
    }
}
