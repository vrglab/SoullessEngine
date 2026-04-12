#include <soulless/editor/pch.hpp>

#include <soulless/editor/windowing/window.h>

SoullessEditor::windowing::Window::Window(Allocator& allocator)
    : m_Allocator(allocator), m_WindowRef(nullptr)
{
}

int SoullessEditor::windowing::Window::Init(Ref<WindowInfo> info)
{
    SOULLESS_INFO("Windowing init called")
    m_Info = info;
    return _openAndStartWindow();
}

int SoullessEditor::windowing::Window::_openAndStartWindow()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SOULLESS_ERROR("SDL Failed to initialize")
        return SoullessEngine::Fail;
    }
    
    m_WindowRef = SDL_CreateWindow(m_Info->title, m_Info->width, m_Info->height, m_Info->flags);
    
    if (m_WindowRef == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        
        SOULLESS_ERROR("SDL Failed create window")
        return SoullessEngine::Fail;
    }
    
    return SoullessEngine::Success;
}

void SoullessEditor::windowing::Window::ProcessEvents()
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

void SoullessEditor::windowing::Window::Cleanup()
{
    SDL_DestroyWindow(m_WindowRef);
    SDL_Quit();
}

bool SoullessEditor::windowing::Window::ShouldClose()
{
    return m_ShouldClose;
}
