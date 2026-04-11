#include <soulless/engine/pch.hpp>
#include <soulless/engine/memory/allocation/heap_allocator.h>

void* SoullessEngine::memory::allocation::HeapAllocator::Allocate(std::size_t size, std::size_t alignment)
{
    const std::size_t totalSize = sizeof(AllocationHeader) + size;

    void* raw = ::operator new(totalSize, std::align_val_t(alignment));

    auto* header = static_cast<AllocationHeader*>(raw);
    header->Size = size;
    header->Alignment = alignment;

    ++m_AllocationCount;
    m_BytesAllocated += size;

    return static_cast<void*>(header + 1);
}

void SoullessEngine::memory::allocation::HeapAllocator::Deallocate(void* ptr)
{
    if (!ptr)
        return;

    auto* header = static_cast<AllocationHeader*>(ptr) - 1;

    assert(m_AllocationCount > 0);
    --m_AllocationCount;
    m_BytesAllocated -= header->Size;

    ::operator delete(
        static_cast<void*>(header),
        std::align_val_t(header->Alignment)
    );
}


const char* SoullessEngine::memory::allocation::HeapAllocator::GetName() const
{
    return m_Name;
}

std::size_t SoullessEngine::memory::allocation::HeapAllocator::GetAllocationCount() const
{
    return m_AllocationCount;
}

std::size_t SoullessEngine::memory::allocation::HeapAllocator::GetBytesAllocated() const
{
    return m_BytesAllocated;
}
