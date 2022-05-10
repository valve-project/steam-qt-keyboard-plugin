
kcoreaddons_add_plugin(steamkeyboard SOURCES
    keyboardmodule.cpp
    keyboardmodule.h
    INSTALL_NAMESPACE "kf5/kded"
)

target_link_libraries(steamkeyboard
    KF5::CoreAddons
    KF5::DBusAddons
    KF5::ConfigCore
    KF5::I18n
    Qt5::Widgets
)
