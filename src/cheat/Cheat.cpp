#include "Cheat.h"
#include "../Java.h"

#include <thread>
#include <chrono>

jclass getMinecraftClass()
{
    // mappings stuff
    return ct.env->FindClass("ave");
}

jobject getMinecraft()
{
    jmethodID getMinecraftMethod = ct.env->GetStaticMethodID(getMinecraftClass(), "A", "()Lave;");
    return ct.env->CallStaticObjectMethod(getMinecraftClass(), getMinecraftMethod);
}

jobject getWorld()
{
    jfieldID getWorldField = ct.env->GetFieldID(getMinecraftClass(), "f", "Lbdb;");
    return ct.env->GetObjectField(getMinecraft(), getWorldField);
}

jobject getPlayer()
{
    jfieldID getPlayerField = ct.env->GetFieldID(getMinecraftClass(), "h", "Lbew;");
    return ct.env->GetObjectField(getMinecraft(), getPlayerField);
}

void sprintToggle()
{
    jmethodID setSprintingMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "d", "(Z)V");

    ct.env->CallBooleanMethod(getPlayer(), setSprintingMethod, true);
}

void runModules()
{
    while (true)
    {
        if (!getMinecraft()) continue;
        if (!getWorld()) continue;
        if (!getPlayer()) continue;

        sprintToggle();

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
