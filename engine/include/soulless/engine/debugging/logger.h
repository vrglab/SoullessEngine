#pragma once

#include <soulless/engine/memory/memory.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <iostream>

using namespace SoullessEngine::memory;
using namespace SoullessEngine::memory::allocation;

namespace SoullessEngine::debugging
{
     class SOULLESS_API Logger
    {
    public:
        static int Init();
        static int Flush();
         static int Cleanup();
        static Ref<spdlog::logger>& CoreLogger();
        
    private:
        static inline Ref<spdlog::logger> m_CoreLogger = nullptr;
        
    };
}

#define SOULLESS_TRACE(...)  Logger::CoreLogger()->trace(__VA_ARGS__);
#define SOULLESS_INFO(...)   Logger::CoreLogger()->info(__VA_ARGS__);
#define SOULLESS_WARN(...)   Logger::CoreLogger()->warn(__VA_ARGS__);
#define SOULLESS_ERROR(...)  Logger::CoreLogger()->error(__VA_ARGS__);