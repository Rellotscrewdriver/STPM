# Simple TUI Password Manager

STPM is a secure, lightweight terminal-based password manager built in Modern C++. It provides a full-featured TUI mode to easily store and manage credentials locally across multiple platforms.
Users also got the option to directly manage credentials through commandline arguements.

- **Terminal-Based UI:** Interactive terminal interface bulit using FTXUI.
- **Local Data Encryption:** Uses `libsodium` to safely encrypt and persist user credentials locally. your data is never shared or stored online. everything is local.
- **Cross-Platform:** Supports Windows, Mac(untested) and various distros of linux(tested on arch).
- **Clipboard Integration:** Easily copy credentials directly from TUI using `libclip`.
- **Password Generation & Validation:** Includes regex validation and secure password generation utilities.

## why another password manager?

this app is mainly for my personal use, and posting this here if others find it useful.
I like making my own tools for my own use.

# usage
simply type `stpm` to launch the TUI session
type `stpm -h` to see help on commandline arguement, I hope they're easy to read.

# Screenshots

People usually like to see how it looks or feels like before downloading the product :)

## Linux

TUI

![App Screenshot](assets/lins1.png)
![App Screenshot](assets/lins2.png)
![App Screenshot](assets/lins3.png)
![App Screenshot](assets/lins4.png)

---

Commandline

![App Screenshot](assets/lins5.png)
![App Screenshot](assets/lins6.png)

## Windows

TUI

![App Screenshot](assets/wins1.png)
![App Screenshot](assets/wins2.png)
![App Screenshot](assets/wins3.png)

---

Commandline

![App Screenshot](assets/wins4.png)
![App Screenshot](assets/wins5.png)

# Contributions

##  Guide

I explicitly welcome outside contributors that are serious about developing my app further and further to perfection.
you can read my <a href="https://github.com/Rellotscrewdriver/my-project-template/blob/master/CODE_OF_CONDUCT.md">CODE_OF_CONDUCT</a> for rules</br>
and <a href="https://github.com/Rellotscrewdriver/my-project-template/blob/master/CONTRIBUTING.md">CONTRIBUTING</a> for contribution guidelines and coding style

## Setting up the project

### External Dependencies(if you're new to C++)
- CMake (3.16+)
- GNU make or Ninja
- GCC or Clang or MSVC(windows only)
- AStyle(optional)
- Doxide and mkdocs + mkdocs-material(optional)
- `libpng-dev`, `libxcb1-dev`, `libxcb-render0-dev`, `libxcb-shape0-dev`, `libxcb-xfixes0-dev` (linux only, required for clipboard functionality)
- `wl-copy`, `wl-paste` (if you're using wayland)

### Bundled Libraries
- libsodium: Cryptographic operations
- re2 & abseil-cpp: regex matching
- clip: cross-platform clipboard handling [dacap/clip](https://github.com/dacap/clip)
- FTXUI: TUI mode

### Setup
clone the repo with submodules
```
git clone --recurse-submodules https://github.com/Rellotscrewdriver/STPM.git STPM
```

goto the cloned repo and configure the project
```
cd STPM && cmake -S . -B build
```

build the project
```
cmake --build build
```

your build is ready in the `build` directory! if there's issues, create one in issues tab!

### Generating the documentation

you must have Doxide and Mkdocs + Mkdocs material(if doxide decides to switch to zensical, [see here](https://github.com/lawmurray/doxide/issues/86)) installed

run the `gendocs.sh` script to avoid typing commands manually everytime
after running go to your browser and type `localhost:8000` to see the generated documentation.

if you're using windows you can rename the `gendocs.sh` file to `gendocs.bat`. Ditto `fmtallfiles.sh`

## Adding Internal Libraries

This project template currently uses git submodules to manage internal libraries in the `libs` folder.
to add the library into this project(not in this template)
```
git submodule add <github_link> libs/<library>
```

add the cloned directory to CMakeLists.txt
```
add_subdirectory(libs/<library>)
```
link the library to the main project 
```
target_link_libraries(${PROJECT_NAME} PRIVATE <library_linkers>)
```

# COPYRIGHT

this project is free to use and distribute as long as you don't claim that you wrote the original software.
crediting of this project is required when it is modified and/or distributed. goto [LICENSE](https://github.com/Rellotscrewdriver/my-project-template/blob/master/LICENSE) for more details 
