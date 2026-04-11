#include <soulless/engine/pch.hpp>
#include <soulless/engine/memory/allocation/linear_allocator.h>

void* SoullessEngine::memory::allocation::LinearAllocator::Allocate(std::size_t size, std::size_t alignment)
{
    std::uintptr_t current = m_Start + m_Offset;
    std::uintptr_t aligned = AlignForward(current, alignment);
    std::size_t adjustment = static_cast<std::size_t>(aligned - current);

    if (m_Offset + adjustment + size > m_Size)
        return nullptr;

    m_Offset += adjustment;
    void* result = reinterpret_cast<void*>(m_Start + m_Offset);
    m_Offset += size;

    return result;
}

void SoullessEngine::memory::allocation::LinearAllocator::Deallocate(void* ptr)
{
    // no-op for linear allocator
    (void)ptr;
}

void SoullessEngine::memory::allocation::LinearAllocator::Reset()
{
    m_Offset = 0;
}

const char* SoullessEngine::memory::allocation::LinearAllocator::GetName() const
{
    return m_Name;
}

std::size_t SoullessEngine::memory::allocation::LinearAllocator::GetUsed() const
{
    return m_Offset;
}

std::size_t SoullessEngine::memory::allocation::LinearAllocator::GetCapacity() const
{
    return m_Size;
}

/* PRIVATE STATICS*/

std::uintptr_t SoullessEngine::memory::allocation::LinearAllocator::AlignForward(std::uintptr_t ptr,
    std::size_t alignment)
{
    const std::uintptr_t p = ptr;
    const std::uintptr_t a = static_cast<std::uintptr_t>(alignment);
    const std::uintptr_t modulo = p % a;

    if (modulo == 0)
        return p;

    return p + (a - modulo);
}
