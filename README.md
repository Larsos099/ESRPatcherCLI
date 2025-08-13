# ESRPatcherCLI



ESRPatcherCLI is a **cross-platform command-line interface (CLI) application** written in **C++23**, serving as a modern rewrite of the original Windows-only ESR Patchers

## Features

- Fully rewritten in **C++23** with modern C++ practices
- **Cross-platform**: Runs on Windows, Linux, and macOS (unlike the original Windows-only version)
- Lightweight and terminal-friendly **CLI interface**
- Supports all core ESR patching functionality

## Why ESRPatcherCLI?

The original ESR Patchers were tightly coupled to Windows and WinAPI, limiting portability and modern C++ development practices. ESRPatcherCLI modernizes the codebase, making it:

- Platform-independent   
- Future-proof with modern C++23 features  

## Requirements

- **C++23 compiler** (tested with GCC 15 & Clang 17)
- **CMake ≥ 4**
- Standard C++ libraries only; no Windows Forms or WinAPI dependencies

## Building

```bash
git clone https://github.com/Larsos099/ESRPatcherCLI.git
cd ESRPatcherCLI
mkdir build && cd build
cmake ..
cmake --build .
```
## Usage
Just type in ./ESRPatcherCLI and you'll get a shell that looks like this:
```bash
esr> # Now you can type in stuff, for example: help
esr> help
ESRPatcherCLI
Available Commands: 
help
unpatch
patch
quit
exit
esr>
```
