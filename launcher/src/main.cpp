#include <soulless/launcher/pch.hpp>
#include "soulless/engine/commons/commons.h"

using namespace SoullessEngine::debugging;

int main() {
    Logger::Init();
    SOULLESS_INFO("Funny")
    Logger::Cleanup();
    return SoullessEngine::Success;
}