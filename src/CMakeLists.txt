
set(keyboard_plugin_SRCS main.cpp steaminputcontext.cpp)

add_library(steam-qt-keyboard-plugin MODULE ${keyboard_plugin_SRCS})

target_link_libraries(steam-qt-keyboard-plugin
    Qt5::GuiPrivate # for qpa
    Qt5::DBus
)

install(TARGETS steam-qt-keyboard-plugin LIBRARY DESTINATION ${KDE_INSTALL_QTPLUGINDIR}/platforminputcontexts)
