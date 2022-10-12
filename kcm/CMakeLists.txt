add_definitions(-DTRANSLATION_DOMAIN=\"kcmkdesteam\")

set(kcm_kdesteamsettings_PART_SRCS kcmkdesteamsettings.cpp kcmkdesteamsettings.h)
kconfig_add_kcfg_files(kcm_kdesteamsettings_PART_SRCS kdesteamsettings.kcfgc)

ki18n_wrap_ui(kcm_kdesteamsettings_PART_SRCS kcmkdesteamsettingswidget.ui)

add_library(kcm_kdesteamsettings MODULE ${kcm_kdesteamsettings_PART_SRCS})
kcmutils_generate_desktop_file(kcm_kdesteamsettings)

target_link_libraries(kcm_kdesteamsettings
    Qt::Widgets
    KF5::WidgetsAddons
    KF5::KCMUtils
    KF5::I18n
)

########### install files ###############

install(TARGETS kcm_kdesteamsettings  DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/kcms/systemsettings_qwidgets)
