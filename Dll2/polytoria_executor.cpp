#include <cstdio>
#include <iostream>

#include "MinHook.h"

// tf is this mess jesus
LPVOID old_lua_resume;

HMODULE luaVMDLL = GetModuleHandle(L"Luau.VM.dll");
HMODULE luaCompilerDLL = GetModuleHandle(L"Luau.Compiler.dll");

FARPROC luau_resume_addr = GetProcAddress(luaVMDLL, "lua_resume");
FARPROC luau_load_addr = GetProcAddress(luaVMDLL, "luau_load");
FARPROC luau_pcall_addr = GetProcAddress(luaVMDLL, "lua_pcall");

FARPROC luau_compile_addr = GetProcAddress(luaCompilerDLL, "luau_compile");

typedef int(__cdecl* luau_load_type)(LPVOID lua_State, const char* chunkname, const char* data, size_t size, int env);
luau_load_type luau_load = (luau_load_type)luau_load_addr;

typedef char*(__cdecl* luau_compile_type)(const char* source, size_t size, LPVOID options, size_t* outsize);
luau_compile_type luau_compile = (luau_compile_type)luau_compile_addr;

typedef int(__cdecl* luau_pcall_type)(LPVOID lua_State, int nargs, int nresults, int errfunc);
luau_pcall_type lua_pcall = (luau_pcall_type)luau_pcall_addr;

typedef int(__cdecl* luau_resume_type)(LPVOID lua_State, LPVOID from, int nargs);
luau_resume_type lua_resume = (luau_resume_type)luau_resume_addr;

int execute(LPVOID lua_State, const char* source) {
    size_t bytecode_size = 0;
    char* bytecode = luau_compile(source, strlen(source), NULL, &bytecode_size);

    int load_result = luau_load(lua_State, "Chunk", bytecode, bytecode_size, 0);

    std::cout << "luau_load result: " << load_result << std::endl;

    int pcall_result = lua_pcall(lua_State, 0, 0, 0);

    std::cout << "lua_pcall result: " << pcall_result << std::endl;

    return pcall_result;
}

int hooked_lua_resume(LPVOID lua_State, LPVOID lua_state_from, int nargs) {
    std::cout << "Hook Hit" << std::endl;
    std::cout << "Lua state address: " << lua_State << std::endl;
    
    MH_DisableHook(NULL); // disables all hooks, but whatever

    execute(lua_State, "game.Players.LocalPlayer.SprintSpeed = 200"); // did not implement anything for receiving code from the user

    return lua_resume(lua_State, lua_state_from, nargs);

    // also, i'm pretty sure this lua_State becomes invalidated/unused at some point, trying to use it later (like 1 second later) often causes a crash
    // just re-enable the hook and grab another lua_State address then use that when executing again later, lua_resume seems to be called like all the time
}

int main() {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);

    std::cout << "lua_resume address: " << luau_resume_addr << std::endl;

    MH_STATUS status = MH_CreateHook((LPVOID)luau_resume_addr, hooked_lua_resume, &old_lua_resume);
    if (status == MH_OK) {
        std::cout << "Hook success" << std::endl;

        MH_EnableHook((LPVOID)luau_resume_addr);
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, // handle to DLL module
    const DWORD fdwReason, // reason for calling function
    const LPVOID lpvReserved) // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        MH_Initialize();
        DisableThreadLibraryCalls(hinstDLL);

        CreateThread(nullptr, 0x1000, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), 0, 0, nullptr);
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:

        if (lpvReserved != nullptr) {
            break; // do not do cleanup if process termination scenario
        }

        // Perform any necessary cleanup.
        break;
    }
    return TRUE; // Successful DLL_PROCESS_ATTACH.
}