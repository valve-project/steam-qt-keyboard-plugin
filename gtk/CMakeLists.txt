
add_library(im-steam MODULE)

target_sources(im-steam PRIVATE
    steam-imcontext-gtk.c
    steam-imcontext-gtk.h
    steam-imcontext-plugin.c
)

set_target_properties(im-steam PROPERTIES C_VISIBILITY_PRESET default)

target_link_libraries(im-steam PRIVATE PkgConfig::GTK3)

install(TARGETS im-steam DESTINATION ${KDE_INSTALL_LIBDIR}/gtk-3.0/3.0.0/immodules)
