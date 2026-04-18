#include <soulless/editor/pch.hpp>

#include <soulless/editor/editor_app.h>


HeapAllocator SoullessEditor::EditorApp::m_CoreAllocator("CoreAllocator");
AllocScope<Window> SoullessEditor::EditorApp::m_ActiveWindow = nullptr;
AllocScope<Renderer> SoullessEditor::EditorApp::m_Renderer = nullptr;
int SoullessEditor::EditorApp::m_InitResultCode = 0;


void SoullessEditor::EditorApp::Init()
{
    SoullessEngine::debugging::Logger::Init();
    
    SOULLESS_INFO("Allocating space for Editor Windowing")
    m_ActiveWindow = CreateAllocScope<Window>(m_CoreAllocator, m_CoreAllocator);
    m_Renderer = CreateAllocScope<Renderer>(m_CoreAllocator);
    
    Ref<Window::WindowInfo> windowInfo = CreateRef<Window::WindowInfo>();
    windowInfo->title = "Test";
    windowInfo->width = 600;
    windowInfo->height = 600;
    windowInfo->flags = SDL_WINDOW_RESIZABLE;
    
    m_InitResultCode = m_ActiveWindow->Init(windowInfo);
    m_InitResultCode = m_Renderer->InitRenderer(m_ActiveWindow);
}

int SoullessEditor::EditorApp::Start()
{
    if (m_InitResultCode != SoullessEngine::Success)
    {
        return m_InitResultCode;
    }
    
    while (!m_ActiveWindow->ShouldClose())
    {
        m_Renderer->RenderHead();
        m_ActiveWindow->ProcessEvents();
    }
    return SoullessEngine::Success;
}

void SoullessEditor::EditorApp::Cleanup()
{
    SOULLESS_INFO("Clean up called")
    m_ActiveWindow->Cleanup();
    m_ActiveWindow.reset();
    
    m_Renderer->Cleanup();
    m_Renderer.reset();
}
