# Polytoria Luau Executor

Supports the 2.0 beta as of 4/20/2026. (beta 85)

It WILL have a stroke and die if you play a game on Polytoria that does not use any client scripts, as Luau.VM.dll and Luau.Compiler.dll are only loaded as needed (and hence will never be loaded if there is no need for them)

Uses GetProcAddress. Polytoria developers can break this simply by statically linking Luau.VM.dll and Luau.Compiler.dll.

The only actual relevant file is Dll2/polytoria_executor.cpp. Everything else is just [MinHook](https://github.com/tsudakageyu/minhook) source files copied into there. (💀)

(yea it's half pasted btw)

Does not have any way of accepting input from users, and is unfinished, but it can execute code at least. (You must change the source string passed to the execute function)
