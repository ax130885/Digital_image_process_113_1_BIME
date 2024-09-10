cmake_minimum_required(VERSION 3.16)

project(code VERSION 0.1 LANGUAGES CXX)

# Enable automatic handling of Qt's MOC, UIC, and RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Add source files
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ImageProcessor.cpp
    ImageProcessor.h
    secondwindow.cpp
    secondwindow.h
    secondprocess.cpp
    secondprocess.h
)

# Configure the Qt executable target
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(code
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        mainwindow.h mainwindow.cpp
        ImageProcessor.h ImageProcessor.cpp
        secondwindow.h secondwindow.cpp
        secondprocess.h secondprocess.cpp


    )
else()
    if(ANDROID)
        add_library(code SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(code
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link Qt libraries
target_link_libraries(code PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Set properties for bundle identifiers, macOS, and Windows specifics
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.code)
endif()
set_target_properties(code PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installation rules
include(GNUInstallDirs)
install(TARGETS code
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the Qt executable if using Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(code)
endif()