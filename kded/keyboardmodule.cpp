#include "keyboardmodule.h"

#include <KConfigGroup>
#include <KPluginFactory>
#include <KLocalizedString>

K_PLUGIN_CLASS_WITH_JSON(KeyboardModule, "keyboardmodule.json")

static const QString KeyboardEnabledIcon = QStringLiteral("input-keyboard-virtual-on");
static const QString KeyboardDisabledIcon = QStringLiteral("input-keyboard-virtual-off");

KeyboardModule::KeyboardModule(QObject *parent, const QVariantList &)
    : KDEDModule(parent)
{
    m_config = KSharedConfig::openConfig();
    m_enabled = m_config->group(QStringLiteral("SteamKeyboard")).readEntry<bool>("enabled", true);
    m_trayIcon = std::make_unique<QSystemTrayIcon>();
    m_trayIcon->setIcon(QIcon::fromTheme(m_enabled ? KeyboardEnabledIcon : KeyboardDisabledIcon));
    m_trayIcon->setToolTip(i18n("Toggle Steam Virtual Keyboard"));
    connect(m_trayIcon.get(), &QSystemTrayIcon::activated, this, &KeyboardModule::onTrayIconActivated);
    m_trayIcon->show();
}

bool KeyboardModule::isEnabled() const
{
    return m_enabled;
}

void KeyboardModule::setEnabled(bool enabled)
{
    if (enabled == m_enabled) {
        return;
    }

    m_enabled = enabled;
    m_config->group(QStringLiteral("SteamKeyboard")).writeEntry("enabled", m_enabled);
    Q_EMIT enabledChanged(m_enabled);
}

void KeyboardModule::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason != QSystemTrayIcon::Trigger) {
        return;
    }

    setEnabled(!m_enabled);
    m_trayIcon->setIcon(QIcon::fromTheme(m_enabled ? KeyboardEnabledIcon : KeyboardDisabledIcon));
}

#include "keyboardmodule.moc"

