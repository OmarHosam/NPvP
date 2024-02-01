#include <Windows.h>
#include <consoleapi.h>
#include <libloaderapi.h>
#include <thread>
#include <winuser.h>

#include "Java.h"
#include "cheat/Cheat.h"

void initialize(HMODULE module)
{  
    jsize count;

    if (JNI_GetCreatedJavaVMs(&ct.vm, 1, &count) != JNI_OK || count == 0)
        return;

    jint rest = ct.vm->GetEnv((void**)&ct.env, JNI_VERSION_1_6);

    if (rest == JNI_EDETACHED)
        rest = ct.vm->AttachCurrentThread((void**)&ct.env, nullptr);

    if (ct.env != nullptr)
        while (!GetAsyncKeyState(VK_END))
            runModules();
    
    ct.vm->DetachCurrentThread();
    FreeLibrary(module);
}

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    static std::thread main_thread;
    static FILE* p_file;

    switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        AllocConsole();
        freopen_s(&p_file, "CONOUT$", "w", stdout);
        
        printf("[-] NPvP injected.");
        
        main_thread = std::thread([hInstance] { initialize(hInstance); });
	    if (main_thread.joinable())
            main_thread.detach();
    case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
        fclose(p_file);
        FreeConsole();
		break;
	}
	return TRUE;
}
