#include <soulless/engine/pch.hpp>

#include <soulless/engine/windowing/window.h>

SoullessEngine::windowing::Window::Window(Allocator& allocator)
    : m_Allocator(allocator), m_WindowRef(nullptr)
{
}

int SoullessEngine::windowing::Window::Init(Ref<WindowInfo> info)
{
    SOULLESS_INFO("Windowing init called")
    m_Info = info;
    return _openAndStartWindow();
}

int SoullessEngine::windowing::Window::_openAndStartWindow()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SOULLESS_ERROR("SDL Failed to initialize")
        return Fail;
    }
    
    m_WindowRef = SDL_CreateWindow(m_Info->title, m_Info->width, m_Info->height, m_Info->flags);
    
    if (m_WindowRef == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        
        SOULLESS_ERROR("SDL Failed create window")
        return Fail;
    }
    
    return Success;
}

void SoullessEngine::windowing::Window::ProcessEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            m_ShouldClose = true;
            break;
            
        default:
            break;
        }
    }
}

void SoullessEngine::windowing::Window::Cleanup()
{
    SDL_DestroyWindow(m_WindowRef);
    SDL_Quit();
}

bool SoullessEngine::windowing::Window::ShouldClose()
{
    return m_ShouldClose;
}

SDL_Window* SoullessEngine::windowing::Window::GetSDlWindowPtr()
{
    return m_WindowRef;
}

Ref<SoullessEngine::windowing::Window::WindowInfo> SoullessEngine::windowing::Window::GetActiveInfo()
{
    return m_Info;
}
