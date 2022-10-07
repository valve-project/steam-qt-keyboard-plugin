import configparser
import dbus
from gi.repository import GLib
from dbus.mainloop.glib import DBusGMainLoop
import logging
_logger = logging.getLogger(__name__)

from steamdeckkeyboardlauncher.utils import XDGDirs, EventSource

class Config(EventSource):
    config = configparser.ConfigParser()
    DBusGMainLoop(set_as_default=True)
    bus = dbus.SessionBus()

    _event_names = ["config-changed"]

    def __init__(self):
        EventSource.__init__(self, self._event_names)
        self.bus.add_signal_receiver(self._handle_settings_changed, "ConfigChanged", "org.kde.kconfig.notify", None, "/kdesteam")

        # enable the a11y bus
        self.bus.call_async("org.a11y.Bus", "/org/a11y/bus", "org.freedesktop.DBus.Properties", "Set", "ssv",
                          ["org.a11y.Status", "IsEnabled", True], None, self._on_enable_a11y_error)

    def autoshow_enabled(self):
        try:
            config_location = XDGDirs.find_config_file("kdesteam")
            config = configparser.ConfigParser()
            config.read(config_location)
            return config["Keyboard"].getboolean("showAutomatically", True)
        except:
            return True

    def _on_enable_a11y_error(self):
        _logger.warning("Failed to enable the accessibility bus")

    def _handle_settings_changed(self, args):
        read_settings()
        self.emit("config-changed")
