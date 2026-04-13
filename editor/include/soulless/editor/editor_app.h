#pragma once

#include <soulless/engine/commons/commons.h>
#include <soulless/engine/windowing/window.h>
#include <soulless/engine/memory/allocation/heap_allocator.h>

using namespace SoullessEngine::windowing;

namespace SoullessEditor
{
    class EditorApp
    {
    public:
        static void Init();
        static int Start();
        static void Cleanup();
        
    private:
        static HeapAllocator m_CoreAllocator;
        static AllocScope<Window> m_ActiveWindow;
        static int m_InitResultCode;
    };
}
