#pragma once

#include <soulless/engine/commons/commons.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_properties.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>


#if defined(SDL_PLATFORM_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined(SDL_PLATFORM_MACOS)
#import <Cocoa/Cocoa.h>
#elif defined(SDL_PLATFORM_LINUX)
#include <X11/Xlib.h>
#include <wayland-client.h>
#endif

#include "soulless/engine/windowing/window.h"

using namespace bgfx;


namespace SoullessEngine::rendering
{
    class SOULLESS_API Renderer
    {
    public:
        int InitRenderer(windowing::Window window);
        void RenderHead();
        void Cleanup();
    private:
        PlatformData _extractPlatformData(windowing::Window window);
        int initBgfx(PlatformData platformData, windowing::Window window);
        
    private:
        Ref<windowing::Window::WindowInfo> m_CurrentWindowInfo;
    };
}
