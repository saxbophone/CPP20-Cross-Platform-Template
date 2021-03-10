# CPP20-Cross-Platform-Template
A template for a cross-platform C++20 project including modern CMake, unit-testing with Catch, cross-platform CI and release builds using using Github Actions.

## What's included
- CMake C++20 project skeleton, with strict warning flags enabled when using GCC or Clang.
- Usage of modern CMake practices for setting project-wide compiler options, etc. in a target-focused way.
- Properly exported CMake project that can be used by other CMake projects with minimal effort (no hand-written `FindMyProject.cmake` files)
- Unit testing using [Catch2](https://github.com/catchorg/Catch2), with automatic test discovery integration with CTest.
- Github Actions config files supporting building and running tests on Linux, macOS and Windows using the following compilers:
    - Linux: GCC-10, Clang-10
    - macOS: GCC-10, Clang-12
    - Windows: MSVC 2019
- Building Releases on each platform when a Github Release is published, uploading these as build Artifacts.
- Doxygen config file with tweaks from the default config settings to provide a few more graphs (usage, caller/callee relationships) than are enabled by default.

> **Note** There's also a Travis-CI build config for a cross-platform build of similar structure to the Github Actions builds, however this is no longer maintained as Travis-CI has been found to not support more recent versions of CMake on all platforms.

## Usage
1. Click the <kbd>Use this template</kbd> button at the top of this page to create your own new copy of this template
2. Fill in the project details on the next page as you desire
3. Once you've got your new project produced from this template, make changes in the following files:
    - `CMakeLists.txt`, `project/CMakeLists.txt`, `project/src/CMakeLists.txt`, `tests/CMakeLists.txt`:
        - Replace all instances of `PROJECT`, `project` and `Project` with your project's name, capitalised or uncapitalised as appropriate
    - `Doxyfile`:
        - Change the `PROJECT_NAME` and `INPUT` settings to your project's name.
    - `project`:
        - Rename this directory to the name of your project.
    - **Choose a Software License for your code** if it is open-source and you want other people to be able to use it with ease!

      This _project template_ is placed into the public domain, but you may want to use a different license for your own projects that you create from this template. Here is the public domain dedication text for this project:

      ```
      This is free and unencumbered software released into the public domain.

      Anyone is free to copy, modify, publish, use, compile, sell, or
      distribute this software, either in source code form or as a compiled
      binary, for any purpose, commercial or non-commercial, and by any
      means.

      In jurisdictions that recognize copyright laws, the author or authors
      of this software dedicate any and all copyright interest in the
      software to the public domain. We make this dedication for the benefit
      of the public at large and to the detriment of our heirs and
      successors. We intend this dedication to be an overt act of
      relinquishment in perpetuity of all present and future rights to this
      software under copyright law.

      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
      EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
      MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
      IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
      OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
      ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
      OTHER DEALINGS IN THE SOFTWARE.

      For more information, please refer to <http://unlicense.org/>
      ```
4. Enjoy!

> The above instructions are the bare minimum required to get your own project based on this template off of the ground. You'll almost certainly want to change more things in `Doxyfile` and definitely `README.md`, but that should be well within the capabilities of a developer and also beyond the scope of this guide.
