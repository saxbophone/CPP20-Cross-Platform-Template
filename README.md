# CPP20-Cross-Platform-Template
A template for a cross-platform C++20 project including CMake, unit-testing with Catch, cross-platform CI with Travis-CI/Github Actions and cross-platform release builds using Github Actions.

## What's included
- CMake C++20 project skeleton, with strict warning flags enabled when using GCC or Clang.
- Unit testing using [Catch2](https://github.com/catchorg/Catch2), with automatic test discovery integration with CTest.
- Travis-CI config file supporting building and running tests on Linux, macOS and Windows using the following compilers:
    - Linux: GCC-10, Clang-10
    - macOS: Clang-10
    - Windows: MSVC 2019
    - 1 Additional build on Linux to check Doxygen documentation is well-formed
- Github Action config file supporting:
    - Building and running tests on the same Operating Systems and Compilers as Travis-CI (additionally, GCC-10 on macOS)
    - Building Releases on each platform when a Github Release is published, uploading these as build Artifacts.
- Doxygen config file with tweaks from the default config settings to provide a few more graphs (usage, caller/callee relationships) than are enabled by default.

## Usage
1. Click the <kbd>Use this template</kbd> button at the top of this page to create your own new copy of this template
2. Fill in the project details on the next page as you desire
3. Once you've got your new project produced from this template, make changes in the following files:
    - `CMakeLists.txt`:
        - Replace all instances of `PROJ` or `proj` with your project's name, capitalised or uncapitalised as appropriate
    - `Doxyfile`:
        - Change the `PROJECT_NAME` and `INPUT` settings to your project's name.
    - `proj`:
        - Rename this directory to the name of your project.
4. Enjoy!

> The above instructions are the bare minimum required to get your own project based on this template off of the ground. You'll almost certainly want to change more things in `Doxyfile` and definitely `README.md`, but that should be well within the capabilities of a developer and also beyond the scope of this guide.
