include(GNUInstallDirs)

add_library(myhovercraftisfullofeels STATIC)
# ALIAS target to export a namespaced target even when building in-tree
add_library(MyHovercraftIsFullOfEels::myhovercraftisfullofeels ALIAS myhovercraftisfullofeels)
# add source files
add_subdirectory(src)
# library public header files location
target_include_directories(
    myhovercraftisfullofeels PUBLIC
    # different include directory path depending on if using the local or installed version of library
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
# pass in version of project as preprocessor definitions
target_compile_definitions(
    myhovercraftisfullofeels PRIVATE
    -DMYHOVERCRAFTISFULLOFEELS_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DMYHOVERCRAFTISFULLOFEELS_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DMYHOVERCRAFTISFULLOFEELS_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    -DMYHOVERCRAFTISFULLOFEELS_VERSION_STRING=${MYHOVERCRAFTISFULLOFEELS_ESCAPED_VERSION_STRING}
)
# set up version and soversion for the main library object
set_target_properties(
    myhovercraftisfullofeels PROPERTIES
    VERSION ${MYHOVERCRAFTISFULLOFEELS_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_MyHovercraftIsFullOfEels_MAJOR_VERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_MyHovercraftIsFullOfEels_MINOR_VERSION ${PROJECT_VERSION_MINOR}
)
set_property(
    TARGET myhovercraftisfullofeels
    APPEND PROPERTY COMPATIBLE_INTERFACE_STRING "${MyHovercraftIsFullOfEels_MAJOR_VERSION}.${MyHovercraftIsFullOfEels_MINOR_VERSION}"
)
# inherit common project compiler options
target_link_libraries(
    myhovercraftisfullofeels
        PRIVATE
            $<BUILD_INTERFACE:myhovercraftisfullofeels-compiler-options>
)

# install if we're not being built as a sub-project
if (NOT MYHOVERCRAFTISFULLOFEELS_SUBMYHOVERCRAFTISFULLOFEELS)
    # library
    install(
        TARGETS myhovercraftisfullofeels
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
