# Learn C The Hard Way
Me doing code from [the book](https://learncodethehardway.org/c/). 

I will do it two times (repetition legitimizes) on two different platforms.
1. Windows - using MSVC copiler (actually `cl` tool).
2. Linux - using gcc complier , probably.

## How to build, run and debug
### Windows
Using msvc.

Visual Studio 2019 Community.

It has convinient `x64 Native Tools Command Prompt for VS 2019`, that runs `%comspec% /k "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"`, so that necessary tools `cl` and `devenv` are available on the command line.

`build.bat` handles the build process.

**Usage examples**
- build `build ex10.c`
- run `builds\ex10.exe`
- debug `devenv builds\ex10.exe`, then I drag-and-drop source code file into Visual Studio.

### Linux
Using gcc.

I'm using `make` right now (just as book intended), but I will probalby experiment with something else.

**Usage examples**
- build `make ex01`
- run `./builds/ex01`