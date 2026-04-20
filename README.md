# Polytoria Luau Executor

Supports the 2.0 beta as of 4/20/2026.
It WILL have a stroke and die if you play a game on Polytoria that does not use any client scripts, as Luau.VM.dll and Luau.Compiler.dll are only loaded as needed (and hence will never be loaded if there is no need for them)

Does not have any way of accepting input from users, and is unfinished, but it can execute code at least. (You must change the source string passed to the execute function)
