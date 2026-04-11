#pragma once

#include <soulless/engine/commons/macros.h>

namespace SoullessEngine::memory
{
    class SOULLESS_API MemoryTracker
    {
    public:
        struct Stats
        {
            std::size_t AllocationCount = 0;
            std::size_t TotalBytes = 0;
        };

        static MemoryTracker& Get();

        void OnAllocate(const std::string& tag, std::size_t size);

        void OnDeallocate(const std::string& tag, std::size_t size);

        const std::unordered_map<std::string, Stats>& GetStats() const;

    private:
        std::unordered_map<std::string, Stats> m_Stats;
        std::mutex m_Mutex;
    
    };
}
