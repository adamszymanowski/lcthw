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

**Usage examples** (inside `msvc` folder)
- build `build ex10.c`
- run `builds\ex10.exe`
- debug `devenv builds\ex10.exe`, then I drag-and-drop source code file into Visual Studio.

### Linux
Using gcc.

I'm using `make` right now (just as book intended), but I will probalby experiment with something else.

**Usage examples** (inside `gcc` folder)
- build `make ex01`
- run `./builds/ex01`


# Additional References
- [GitHub with SSH](https://docs.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh)
- [Push to GitHub using SSH Key](https://stackoverflow.com/questions/14762034/push-to-github-without-a-password-using-ssh-key)
  * `git remote set-url origin git@github.com:<Username>/<Project>.git`
- [Show remote URL](https://intellipaat.com/community/3102/git-show-remote-url-how-can-i-determine-the-url-that-a-local-git-repository-was-originally-cloned-from)
  * `git config --get remote.origin.url`