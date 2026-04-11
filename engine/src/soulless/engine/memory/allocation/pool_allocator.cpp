#include <soulless/engine/pch.hpp>
#include <soulless/engine/memory/allocation/pool_allocator.h>

void* SoullessEngine::memory::allocation::PoolAllocator::Allocate(std::size_t size, std::size_t alignment)
{
    (void)alignment;

    if (size > m_BlockSize || !m_FreeList)
        return nullptr;

    FreeNode* node = m_FreeList;
    m_FreeList = node->Next;
    return node;
}

void SoullessEngine::memory::allocation::PoolAllocator::Deallocate(void* ptr)
{
    if (!ptr)
        return;

    auto* node = static_cast<FreeNode*>(ptr);
    node->Next = m_FreeList;
    m_FreeList = node;
}

const char* SoullessEngine::memory::allocation::PoolAllocator::GetName() const
{
    return m_Name;
}

void SoullessEngine::memory::allocation::PoolAllocator::InitializeFreeList()
{
    const std::size_t blockCount = m_TotalSize / m_BlockSize;
    m_FreeList = nullptr;

    for (std::size_t i = 0; i < blockCount; ++i)
    {
        auto* block = reinterpret_cast<FreeNode*>(m_Start + i * m_BlockSize);
        block->Next = m_FreeList;
        m_FreeList = block;
    }
}
