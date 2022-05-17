cmake_minimum_required(VERSION 3.5)

project(Chess_GUI LANGUAGES CXX)

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
        mainwindow.ui
        ChessBoard.cpp
        ChessBoard.h
        imageResource.qrc
        Engine.h
        Engine.cpp
        GameInstance.h
        GameInstance.cpp
        utils.h
        utils.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Chess_GUI
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Chess_GUI SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Chess_GUI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Chess_GUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET Chess_GUI PROPERTY WIN32_EXECUTABLE true)
endif()
