#pragma once

#ifdef _WIN32
    #ifdef SOULLESS_ENGINE_EXPORTS
        #define SOULLESS_API __declspec(dllexport)
    #else
        #define SOULLESS_API __declspec(dllimport)
    #endif
#else
#define SOULLESS_API
#endif

#define SOULLESS_EXTERN extern "C" SOULLESS_API