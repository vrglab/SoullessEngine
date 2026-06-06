#pragma once

#include <soulless/engine/commons/commons.h>
#include <SDL3/SDL.h>

using SoullessEngine::events::Event;

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
        
        SOULLESS_EVENT(m_OnResize, int, int)
        SOULLESS_EVENT(m_OnFrameBufferResized, int, int)
        SOULLESS_EVENT(m_OnFocusLost)
        SOULLESS_EVENT(m_OnFocusGained)
        SOULLESS_EVENT(m_OnMinimize)
        SOULLESS_EVENT(m_OnRestored)
        
    private:
        int _openAndStartWindow();
        
    private:
        SDL_Window* m_WindowRef;
        Ref<WindowInfo> m_Info;
        Allocator& m_Allocator;
        bool m_ShouldClose = false;
    };
}
