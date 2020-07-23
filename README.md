# CPP20-Cross-Platform-Template
A template for a cross-platform C++20 project including CMake, unit-testing with Catch and cross-platform Travis-CI

## What's included
- CMake C++20 project skeleton, with strict warning flags enabled when using GCC or Clang.
- Unit testing using [Catch2](https://github.com/catchorg/Catch2), with automatic test discovery integration with CTest.
- Travis-CI config file supporting building and running tests on Linux, macOS and Windows using the following compilers:
    - Linux: GCC-10, Clang-10
    - macOS: Clang-10
    - Windows: MSVC 2017
    - 1 Additional build on Linux to check Doxygen documentation is well-formed
- Doxygen config file with tweaks from the default config settings to provide a few more graphs (usage, caller/callee relationships) than are enabled by default.

## Usage
1. Click the <kbd>Use this template</kbd> button at the top of this page to create your own new copy of this template
2. Fill in the project details on the next page as you desire
3. Once you've got your new project produced from this template, make changes in the following files:
    - `CMakeLists.txt`:
        - Replace all instances of `PROJ` or `proj` with your project's name, capitalised or uncapitalised as appropriate
    - `Doxyfile`:
        - Change the `PROJECT_NAME` and `INPUT` settings to your project's name.
    - `LICENSE`:
        - Do with this what you will. You probably want to at a bare minimum change the statement that would otherwise assert my copyright on _your_ work, you may wish to (and it might even be advisable) to leave a statement acknowledging this template, but it's nought but a project template ultimately, also I'm not in a position to give legal advice. Note that the BSD 3-clause licence was chosen as that's the licence attached to some of the CMake files in `cmake/Modules`, which I did not produce.
    - `proj`:
        - Rename this directory to the name of your project.
4. Enjoy!

> The above instructions are the bare minimum required to get your own project based on this template off of the ground. You'll almost certainly want to change more things in `Doxyfile` and definitely `README.md`, but that should be well within the capabilities of a developer and also beyond the scope of this guide.
