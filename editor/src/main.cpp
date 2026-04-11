#include <soulless/editor/pch.hpp>
#include "soulless/engine/commons/macros.h"
#include "soulless/engine/debugging/logger.h"

using namespace SoullessEngine::debugging;

int main() {
    Logger::Init();
    SOULLESS_INFO("HAHHA")
    return 0;
}