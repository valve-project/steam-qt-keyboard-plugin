cmake_minimum_required(VERSION 3.0)

project(steam-qt-keyboard-plugin)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

option(ENABLE_QT "Build the Qt input module" ON)
option(ENABLE_GTK "Build the GTK input module" ON)
option(FLATPAK_BULD "Build for Flatpak" OFF)

include(GNUInstallDirs)
include(FeatureSummary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if (ENABLE_QT)
    find_package(Qt5 5.15 CONFIG REQUIRED COMPONENTS Core Gui DBus)
    add_subdirectory(qt)
endif()

if (ENABLE_GTK)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 gtk+-3.0 REQUIRED IMPORTED_TARGET)
    add_subdirectory(gtk)
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
