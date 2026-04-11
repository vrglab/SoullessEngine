#pragma once


#include <soulless/engine/memory/allocation/linear_allocator.h>
#include <soulless/engine/memory/allocation/heap_allocator.h>
#include <soulless/engine/memory/allocation/pool_allocator.h>
#include <soulless/engine/memory/allocation/allocation_utils.h>
#include <soulless/engine/memory/allocation/owned_alloc.h>

#include <soulless/engine/memory/memory_tracker.h>

namespace SoullessEngine::memory
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using WeakRef = std::weak_ptr<T>;
}
