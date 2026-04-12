#include <soulless/engine/pch.hpp>
#include <soulless/engine/debugging/logger.h>

int SoullessEngine::debugging::Logger::Init()
{
    m_CoreLogger = spdlog::stdout_color_mt("SOULLESS_ENGINE");
    MemoryTracker::Get().OnAllocate("Logger", sizeof(m_CoreLogger));
    
    m_CoreLogger->set_level(spdlog::level::trace);
    m_CoreLogger->set_pattern("%^[%T] %n: %v%$");
    return 0;
}

int SoullessEngine::debugging::Logger::Flush()
{
    spdlog::flush_on(spdlog::level::trace);
    return 0;
}

int SoullessEngine::debugging::Logger::Cleanup()
{
    m_CoreLogger.reset();
    MemoryTracker::Get().OnDeallocate("Logger", sizeof(m_CoreLogger));
    return 0;
}

Ref<spdlog::logger>& SoullessEngine::debugging::Logger::CoreLogger()
{
    if (m_CoreLogger == nullptr)
    {
        std::cout << "Logger is nullptr, Must call Logger::Init() before logging anything" << "\n";
    }
    
    return m_CoreLogger;
}
