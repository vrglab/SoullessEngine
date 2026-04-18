#include <soulless/engine/pch.hpp>

#include <soulless/engine/rendering/renderer.h>

int SoullessEngine::rendering::Renderer::InitRenderer(const AllocScope<windowing::Window>& window)
{
    PlatformData data = _extractPlatformData(window);
    return initBgfx(data, window);
}

PlatformData SoullessEngine::rendering::Renderer::_extractPlatformData(const AllocScope<windowing::Window>& window)
{
    m_CurrentWindowInfo = window->GetActiveInfo();
    PlatformData pd;
    SDL_PropertiesID props = SDL_GetWindowProperties(window->GetSDlWindowPtr());

#ifdef SDL_PLATFORM_WIN32
    pd.nwh = (HWND) SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL );
    pd.ndt = NULL;
#elif defined(SDL_PLATFORM_MACOS)
    pd.nwh = (__bridge NSWindow *) SDL_GetPointerProperty( props, SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, NULL );
    pd.ndt = NULL;
#elif defined(SDL_PLATFORM_LINUX)
    if( SDL_strcmp( SDL_GetCurrentVideoDriver(), "x11" ) == 0 ) 
    {
        pd.ndt = (Display *) SDL_GetPointerProperty( props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, NULL );
        pd.nwh = (Window) SDL_GetNumberProperty( props, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0 );
    } 
    else if( SDL_strcmp( SDL_GetCurrentVideoDriver(), "wayland" ) == 0 ) 
    {
        /*struct wl_display *display*/ pd.ndt = (struct wl_display *) SDL_GetPointerProperty( props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, NULL );
        /*struct wl_surface *surface*/ pd.nwh = (struct wl_surface *) SDL_GetPointerProperty( props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, NULL );
    }
#endif

    pd.context = NULL;
    pd.backBuffer = NULL;
    pd.backBufferDS = NULL;
    setPlatformData(pd);
    return pd;
}

int SoullessEngine::rendering::Renderer::initBgfx(PlatformData platformData, const AllocScope<windowing::Window>& window)
{
    Init init;
    init.type = RendererType::Count;
    init.vendorId = BGFX_PCI_ID_NONE;
    init.platformData.nwh = platformData.nwh;
    init.platformData.ndt = platformData.ndt;
    init.resolution.width = m_CurrentWindowInfo->width;
    init.resolution.height = m_CurrentWindowInfo->height;
    //init.resolution.reset = BGFX_RESET_VSYNC;
    if( !bgfx::init( init ) )
        return Fail;

    //bgfx::reset( 1280, 720, BGFX_RESET_VSYNC );
    setDebug(BGFX_DEBUG_TEXT);
    setViewClear( 0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030FF, 1.0f, 0 );
    
    RendererType::Enum type = getRendererType();
    const char* rendererName = getRendererName(type);
    
    SOULLESS_INFO(rendererName)
    
    return Success;
}

void SoullessEngine::rendering::Renderer::RenderHead()
{
    setViewRect( 0, 0, 0, uint16_t(m_CurrentWindowInfo->width), uint16_t(m_CurrentWindowInfo->height) );
    touch(0);
    dbgTextClear();
    frame();
}

void SoullessEngine::rendering::Renderer::Cleanup()
{
    bgfx::shutdown();
}
