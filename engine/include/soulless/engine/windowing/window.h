#pragma once

#include <soulless/engine/commons/commons.h>
#include <SDL3/SDL.h>

namespace SoullessEngine::windowing
{
    class SOULLESS_API Window
    {
    public:
        struct WindowInfo
        {
            const char *title;
            int width;
            int height;
            SDL_WindowFlags flags;
        };
        
    public:
        explicit Window(Allocator& allocator);
        int Init(Ref<WindowInfo> info);
        void ProcessEvents();
        void Cleanup();
        bool ShouldClose();
        SDL_Window* GetSDlWindowPtr();
        Ref<WindowInfo> GetActiveInfo();
        
        
    private:
        int _openAndStartWindow();
        
    private:
        SDL_Window* m_WindowRef;
        Ref<WindowInfo> m_Info;
        Allocator& m_Allocator;
        bool m_ShouldClose = false;
    };
}
