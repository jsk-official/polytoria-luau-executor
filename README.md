# Polytoria Luau Executor

Supports Polytoria v2.0.1 as of 5/11/2026.

![Demo](https://raw.githubusercontent.com/jsk-official/polytoria-luau-executor/refs/heads/master/media/2026-05-1122-20-46-ezgif.com-video-to-gif-converter.gif)

It WILL have a stroke and die if you play a game on Polytoria that does not use any client scripts, as Luau.VM.dll is only loaded as needed (and hence will never be loaded if there is no need for it)

It seems like Luau.Compiler.dll is now never actually loaded regardless? Very peculiar, I just load it anyway with LoadLibrary if it is not already loaded but Luau.VM.dll is loaded.

Uses GetProcAddress. Polytoria developers can break this simply by statically linking Luau.VM.dll and Luau.Compiler.dll.

The only actual relevant file is Dll2/polytoria_executor.cpp. Everything else is just [MinHook](https://github.com/tsudakageyu/minhook) source files copied into there. (💀)

(yea it's half pasted btw)
