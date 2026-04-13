#include <soulless/editor/pch.hpp>

#include <soulless/editor/editor_app.h>

int main() {
    SoullessEditor::EditorApp::Init();
    int result = SoullessEditor::EditorApp::Start();
    SoullessEditor::EditorApp::Cleanup();
    return result;
}