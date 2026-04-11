#include <soulless/engine/pch.hpp>
#include <soulless/engine/memory/memory_tracker.h>

SoullessEngine::memory::MemoryTracker& SoullessEngine::memory::MemoryTracker::Get()
{
    static MemoryTracker instance;
    return instance;
}

void SoullessEngine::memory::MemoryTracker::OnAllocate(const std::string& tag, std::size_t size)
{
    std::scoped_lock lock(m_Mutex);
    auto& stat = m_Stats[tag];
    ++stat.AllocationCount;
    stat.TotalBytes += size;
}

void SoullessEngine::memory::MemoryTracker::OnDeallocate(const std::string& tag, std::size_t size)
{
    std::scoped_lock lock(m_Mutex);
    auto& stat = m_Stats[tag];
    --stat.AllocationCount;
    stat.TotalBytes -= size;
}

const std::unordered_map<std::string, SoullessEngine::memory::MemoryTracker::Stats>& SoullessEngine::memory::
MemoryTracker::GetStats() const
{
    return m_Stats;
}
