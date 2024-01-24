
add_library(libim-steam MODULE)

target_sources(libim-steam PRIVATE
    steam-imcontext-gtk.c
    steam-imcontext-gtk.h
)

set_target_properties(libim-steam PROPERTIES C_VISIBILITY_PRESET default)

target_link_libraries(libim-steam PRIVATE PkgConfig::GTK4)

install(TARGETS libim-steam DESTINATION ${KDE_INSTALL_LIBDIR}/gtk-4.0/4.0.0/immodules)
