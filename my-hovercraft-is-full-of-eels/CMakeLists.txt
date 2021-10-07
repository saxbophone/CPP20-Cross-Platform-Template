include(GNUInstallDirs)

add_library(my-hovercraft-is-full-of-eels STATIC)
# ALIAS target to export a namespaced target even when building in-tree
add_library(MyHovercraftIsFullOfEels::my-hovercraft-is-full-of-eels ALIAS my-hovercraft-is-full-of-eels)
# add source files
add_subdirectory(src)
# library public header files location
target_include_directories(
    my-hovercraft-is-full-of-eels PUBLIC
    # different include directory path depending on if using the local or installed version of library
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
# pass in version of project as preprocessor definitions
target_compile_definitions(
    my-hovercraft-is-full-of-eels PRIVATE
    -DMY_HOVERCRAFT_IS_FULL_OF_EELS_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DMY_HOVERCRAFT_IS_FULL_OF_EELS_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DMY_HOVERCRAFT_IS_FULL_OF_EELS_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    -DMY_HOVERCRAFT_IS_FULL_OF_EELS_VERSION_STRING=${MY_HOVERCRAFT_IS_FULL_OF_EELS_ESCAPED_VERSION_STRING}
)
# set up version and soversion for the main library object
set_target_properties(
    my-hovercraft-is-full-of-eels PROPERTIES
    VERSION ${MY_HOVERCRAFT_IS_FULL_OF_EELS_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_MyHovercraftIsFullOfEels_MAJOR_VERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_MyHovercraftIsFullOfEels_MINOR_VERSION ${PROJECT_VERSION_MINOR}
)
set_property(
    TARGET my-hovercraft-is-full-of-eels
    APPEND PROPERTY COMPATIBLE_INTERFACE_STRING "${MyHovercraftIsFullOfEels_MAJOR_VERSION}.${MyHovercraftIsFullOfEels_MINOR_VERSION}"
)
# inherit common project compiler options
target_link_libraries(
    my-hovercraft-is-full-of-eels
        PRIVATE
            $<BUILD_INTERFACE:my-hovercraft-is-full-of-eels-compiler-options>
)

# install if we're not being built as a sub-project
if (NOT MY_HOVERCRAFT_IS_FULL_OF_EELS_SUBPROJECT)
    # library
    install(
        TARGETS my-hovercraft-is-full-of-eels
        EXPORT MyHovercraftIsFullOfEelsTargets
        # when a static library
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        # when a shared library on UNIX
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        # when a DLL on Windows
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    # public headers
    install(
        DIRECTORY "include/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    # CMake export
    install(
        EXPORT MyHovercraftIsFullOfEelsTargets
        FILE MyHovercraftIsFullOfEelsTargets.cmake
        NAMESPACE MyHovercraftIsFullOfEels::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MyHovercraftIsFullOfEels"
    )
    # CMake package
    include(CMakePackageConfigHelpers)
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/MyHovercraftIsFullOfEelsConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MyHovercraftIsFullOfEels"
    )
    # generate the version file for the config file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/MyHovercraftIsFullOfEelsConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY SameMinorVersion
    )
    install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/MyHovercraftIsFullOfEelsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/MyHovercraftIsFullOfEelsConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MyHovercraftIsFullOfEels"
    )
endif()
