cmake_minimum_required(VERSION 3.5)

project(toasc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        utype.h
        umessage.h
        converter.cpp
        mainwindow.ui
)

find_package(Vector_ASC)

add_executable(toasc
    ${PROJECT_SOURCES}
)

include_directories(Vector_ASC/src)
include_directories(${CMAKE_BINARY_DIR}/Vector_ASC/src)
target_link_libraries(toasc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Vector_ASC)

set_target_properties(toasc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER www.ulantec.cn
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

add_subdirectory(Vector_ASC)
