#include "AutoSprint.h"
#include <Windows.h>

#include "../../net/minecraft/entity/Entity.h"

void AutoSprint::runModule()
{
    // checking if player is already sprinting (probably the worst approach possible).
    if (!GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState(VK_LCONTROL)) return;

    C_Entity::setSprinting(true); 
}
