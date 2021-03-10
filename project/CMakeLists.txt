include(GNUInstallDirs)

add_library(project STATIC)
# ALIAS target to export a namespaced target even when building in-tree
add_library(Project::project ALIAS project)
# add source files
add_subdirectory(src)
# library public header files location
target_include_directories(
    project PUBLIC
    # different include directory path depending on if using the local or installed version of library
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
# pass in version of project as preprocessor definitions
target_compile_definitions(
    project PRIVATE
    -DPROJECT_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DPROJECT_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DPROJECT_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    -DPROJECT_VERSION_STRING=${PROJECT_ESCAPED_VERSION_STRING}
)
# set up version and soversion for the main library object
set_target_properties(
    project PROPERTIES
    VERSION ${PROJECT_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_Project_MAJOR_VERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_Project_MINOR_VERSION ${PROJECT_VERSION_MINOR}
)
set_property(
    TARGET project
    APPEND PROPERTY COMPATIBLE_INTERFACE_STRING "${Project_MAJOR_VERSION}.${Project_MINOR_VERSION}"
)
# inherit common project compiler options
target_link_libraries(
    project
        PRIVATE
            $<BUILD_INTERFACE:project-compiler-options>
)

# install if we're not being built as a sub-project
if (NOT PROJECT_SUBPROJECT)
    # library
    install(
        TARGETS project
        EXPORT ProjectTargets
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
        EXPORT ProjectTargets
        FILE ProjectTargets.cmake
        NAMESPACE Project::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Project"
    )
    # CMake package
    include(CMakePackageConfigHelpers)
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/ProjectConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Project"
    )
    # generate the version file for the config file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/ProjectConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY SameMinorVersion
    )
    install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/ProjectConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/ProjectConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Project"
    )
endif()
