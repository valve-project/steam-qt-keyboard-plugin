cmake_minimum_required(VERSION 3.16)

project(steam-qt-keyboard-plugin)

set(QT_MIN_VERSION "5.15.0")
set(KF5_MIN_VERSION "5.88.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Qt Creator 4.1 extra qml import paths")

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Gui
    DBus
    Widgets
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons DBusAddons Config I18n)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 gtk+-3.0 IMPORTED_TARGET)

add_subdirectory(src)
add_subdirectory(kded)

if (TARGET PkgConfig::GTK3)
    add_subdirectory(gtk)
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
