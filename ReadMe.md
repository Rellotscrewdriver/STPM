# Simple Terminal Password Manager

STPM is a password manager that manages and generates your password 

# usage
just type `./stpm` within the build folder to run

`add` to add a site

`change` to change a site

`remove` to remove a site

`list` prints everything

# Screenshots
People usually like to see how it looks before downloading the product.
<img src="">

# Contributions

##  Guide

We explicitly welcome outside contributors.
you can read our <a href="https://github.com/Rellotscrewdriver/my-project-template/blob/master/CODE_OF_CONDUCT.md">CODE_OF_CONDUCT</a> for rules</br>
and <a href="https://github.com/Rellotscrewdriver/my-project-template/blob/master/CONTRIBUTING.md">CONTRIBUTING</a> for contribution guidelines and coding style

## Setting up the project

### External Dependencies(if you're new to C++)
- CMake
- GNU make or Ninja
- GCC or Clang or MSVC(windows only)
- AStyle(optional)
- Doxide and mkdocs + mkdocs-material(optional)

### Setup
clone the repo with submodules
```
git clone --recurse-submodules https://github.com/Rellotscrewdriver/STPM.git STPM
```

goto the cloned repo and configure the project
```
cd STPM
cmake -S . -B build
```

build the project
```
cmake --build build
```
then run the program

### Generating the documentation

you need to have Doxide and Mkdocs + Mkdocs material installed

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
**NOTE:** the linker name will be different for each library you trying to add so make sure to read their documentation on how to link their libraries through CMake or just see the `project(name)` in their CMakeLists.txt and put the `name` in the linker


# COPYRIGHT

this project is free to use and distribute as long as you don't claim that you wrote the original software.
crediting of this project is required when it is modified and/or distributed. goto <a href="https://github.com/Rellotscrewdriver/my-project-template/blob/master/LICENSE">LICENSE</a> for more details 
