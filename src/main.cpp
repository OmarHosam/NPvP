#include <Windows.h>
#include <consoleapi.h>
#include <libloaderapi.h>
#include <minwinbase.h>
#include <processthreadsapi.h>
#include <winuser.h>

#include "Java.h"
#include "cheat/Cheat.h"

void initialize(void* instance)
{  
    jsize count;

    if (JNI_GetCreatedJavaVMs(&ct.vm, 1, &count) != JNI_OK || count == 0)
        return;

    jint rest = ct.vm->GetEnv((void**)&ct.env, JNI_VERSION_1_6);

    if (rest == JNI_EDETACHED)
        rest = ct.vm->AttachCurrentThread((void**)&ct.env, nullptr);

    AllocConsole();

    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    
    printf("[-] NPvP injected.\n");

    if (ct.env != nullptr)
        runModules();
    
    fclose(f);
    FreeConsole();

    ct.vm->DetachCurrentThread();

    FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    DisableThreadLibraryCalls(module);
    switch (ul_reason_for_call)
	{
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)initialize, module, 0, nullptr);
	case DLL_THREAD_DETACH:  
        //FreeLibrary(module);
        break;
	}
	return TRUE;
}
