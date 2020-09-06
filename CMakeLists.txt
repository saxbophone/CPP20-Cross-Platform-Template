# begin basic metadata
# minimum CMake version required for C++20 support, among other things
cmake_minimum_required(VERSION 3.12)

project(proj VERSION 0.0.0 LANGUAGES CXX)

# set the C++ standard to use to C++20 always
set(PROJ_CXX_STANDARD "20")
message(STATUS "[proj] C++ Standard set to C++${PROJ_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD ${PROJ_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    PROJ_VERSION_STRING
    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
)
set(PROJ_ESCAPED_VERSION_STRING "\"${PROJ_VERSION_STRING}\"")
# end basic metadata

# pass in version of project as preprocessor definitions
add_definitions(-DPROJ_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DPROJ_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DPROJ_VERSION_PATCH=${PROJECT_VERSION_PATCH})
add_definitions(-DPROJ_VERSION_STRING=${PROJ_ESCAPED_VERSION_STRING})

# used for enabling additional compiler options if supported
include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    message(STATUS "[proj] Checking if compiler supports warning flag '${flag}'")
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            message(STATUS "[proj] Enabling warning flag '${flag}'")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
    unset(flag_already_set CACHE)
    unset(flag_supported CACHE)
endfunction()

# enable extra flags (warnings) if we're not in release mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "[proj] Warnings Enabled")
    if (MSVC) # MSVC supports different warning options to GCC/Clang
        add_compile_options(/WX /W3) # treat all warnings as errors, set warning level 3
    else() # GCC/Clang warning option
        # NOTE: GCC and Clang support most of the same options, but neither supports all
        # of the others'. By only enabling them if supported, we get graceful failure
        # when trying to enable unsupported flags
        # e.g. at the time of writing, GCC does not support -Wdocumentation
        #
        # enable all warnings about 'questionable constructs'
        enable_cxx_compiler_flag_if_supported("-Wall")
        # issue 'pedantic' warnings for strict ISO compliance
        enable_cxx_compiler_flag_if_supported("-pedantic")
        # enable 'extra' strict warnings
        enable_cxx_compiler_flag_if_supported("-Wextra")
        # enable sign conversion warnings
        enable_cxx_compiler_flag_if_supported("-Wsign-conversion")
        # enable warnings about mistakes in Doxygen documentation
        enable_cxx_compiler_flag_if_supported("-Wdocumentation")
        # convert all warnings into errors
        enable_cxx_compiler_flag_if_supported("-Werror")
        # exclude the following kinds of warnings from being converted into errors
        # unknown-pragma is useful to have as a warning but not as an error, if you have
        # pragmas which are for the consumption of one compiler only
        enable_cxx_compiler_flag_if_supported("-Wno-error=unknown-pragmas")
        # unused variable and function warnings are helpful but we don't need them as errors
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-function")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-variable")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-parameter")
    endif()
endif()


# add custom dependencies directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# begin dependencies

# ...Add additional dependencies here...

# end dependencies

# C++ library source files
file(GLOB PROJ_SOURCES "proj/*.cpp")
# C++ program source file
set(PROJ_CLI_SOURCE "main.cpp")
# C++ source files for unit tests
file(GLOB TEST_SOURCES "tests/*.cpp")
# Header files
set(PROJ_HEADERS "proj/*.hpp")

# if project is a library
add_library(proj ${PROJ_SOURCES})
# set up version for library objects
set_target_properties(
    proj PROPERTIES VERSION ${PROJ_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
# link proj with C math library if we're on Linux
if (UNIX AND NOT APPLE)
    target_link_libraries(proj m)
endif()

# the proj executable --this is the command-line program
add_executable(proj-cli ${PROJ_CLI_SOURCE})
# link the program with the library
target_link_libraries(proj-cli proj)
# set output name property so it will be called proj despite target name being different
set_target_properties(proj-cli PROPERTIES OUTPUT_NAME proj)

# build unit tests
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests proj)
enable_testing()

# auto-discover and add Catch2 tests from unit tests program
include(CTest)
include(Catch)

catch_discover_tests(unit_tests)

install(
    TARGETS proj
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(
    TARGETS proj-cli
    RUNTIME DESTINATION bin
)

# Generate rough (nearest major) version-dependent header installation folder
set(
    PROJ_ROUGH_HEADER_DESTINATION
    "proj-${PROJECT_VERSION_MAJOR}"
)
# Generate precise (major and minor) version-dependent header installation folder
set(
    PROJ_PRECISE_HEADER_DESTINATION
    "proj-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)

# Install main library header files, both to rough and precise install locations
install(
    FILES ${PROJ_HEADERS}
    DESTINATION "include/${PROJ_ROUGH_HEADER_DESTINATION}"
)

install(
    FILES ${PROJ_HEADERS}
    DESTINATION "include/${PROJ_PRECISE_HEADER_DESTINATION}"
)
