#include "Cheat.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/entity/Entity.h"
#include "net/minecraft/world/World.h"

#include <thread>
#include <chrono>
#include <Windows.h>
#include <winuser.h>

void runModules()
{   
    while (!GetAsyncKeyState(VK_END))
    {
        if (!C_Minecraft::getInstance()) continue;
        if (!C_World::getInstance()) continue;
        if (!C_Entity::getInstance()) continue;

        AutoSprint::runModule();
        Velocity::runModule();

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
