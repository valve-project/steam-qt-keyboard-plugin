
#pragma once

#include <memory>
#include <QSystemTrayIcon>
#include <KDEDModule>
#include <KSharedConfig>

class KeyboardModule : public KDEDModule
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.valvesoftware.keyboard")

public:
    explicit KeyboardModule(QObject *parent, const QVariantList &);

    Q_SCRIPTABLE bool isEnabled() const;
    Q_SCRIPTABLE void setEnabled(bool enabled);
    Q_SCRIPTABLE Q_SIGNAL void enabledChanged(bool enabled);

private:
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

    bool m_enabled = true;
    KSharedConfig::Ptr m_config;
    std::unique_ptr<QSystemTrayIcon> m_trayIcon;
};
