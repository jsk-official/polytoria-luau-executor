# Polytoria Luau Executor

Supports Polytoria v2.0.1 as of 5/11/2026.

It WILL have a stroke and die if you play a game on Polytoria that does not use any client scripts, as Luau.VM.dll are only loaded as needed (and hence will never be loaded if there is no need for them)
It seems like Luau.Compiler.Dll is now never actually loaded regardless? Very peculiar, I just load it anyway with LoadLibrary if it is not already loaded but Luau.VM.Dll is loaded.

Uses GetProcAddress. Polytoria developers can break this simply by statically linking Luau.VM.dll and Luau.Compiler.dll.

The only actual relevant file is Dll2/polytoria_executor.cpp. Everything else is just [MinHook](https://github.com/tsudakageyu/minhook) source files copied into there. (💀)

(yea it's half pasted btw)
