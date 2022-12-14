cmake_minimum_required(VERSION 3.9)

project(Vector_ASC
    VERSION 1.1.3
    DESCRIPTION "Vector ASCII Log File support library")

# build types: None, Debug, Release, RelWithDebInfo, MinSizeRel
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector-all")

# source code documentation
option(OPTION_RUN_DOXYGEN "Run Doxygen" OFF)

# static code analysis
option(OPTION_RUN_CCCC "Run CCCC" OFF)
option(OPTION_RUN_CPPCHECK "Run Cppcheck" OFF)

# dynamic tests
option(OPTION_BUILD_EXAMPLES "Run examples" OFF)
option(OPTION_BUILD_TESTS "Run tests" OFF)
option(OPTION_USE_GCOV "Build with gcov to generate coverage data on execution" OFF)
option(OPTION_USE_GPROF "Build with gprof" OFF)
option(OPTION_ADD_LCOV "Add lcov targets to generate HTML coverage report" OFF)

# directories
include(GNUInstallDirs)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# dependencies
# find_package(FLEX REQUIRED)
# if(OPTION_RUN_DOXYGEN)
#     find_package(Doxygen REQUIRED)
#     find_package(Graphviz)
#     if(WIN32)
#         find_package(HTMLHelp REQUIRED)
#     endif()
# endif()

if(OPTION_RUN_CCCC)
    find_package(CCCC REQUIRED)
endif()
if(OPTION_RUN_CPPCHECK)
    find_package(Cppcheck REQUIRED)
endif()
if(OPTION_BUILD_TESTS)
    enable_testing()
    find_package(Boost 1.55 COMPONENTS system filesystem unit_test_framework REQUIRED)
endif()
if(OPTION_ADD_LCOV)
    find_package(LCOV REQUIRED)
endif()

# package
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT "Tobias Lorenz <tobias.lorenz@gmx.net>")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.GPL-3.0)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
include(CPack)

# install
install(
    FILES
        CHANGELOG.md
        README.md
        LICENSE.GPL-3.0
    DESTINATION ${CMAKE_INSTALL_DOCDIR})

# sub directories
add_subdirectory(src)
