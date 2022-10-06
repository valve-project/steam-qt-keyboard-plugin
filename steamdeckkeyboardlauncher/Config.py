import configparser
import dbus
from gi.repository import GLib
from dbus.mainloop.glib import DBusGMainLoop

from steamdeckkeyboardlauncher.utils import XDGDirs, EventSource

class Config(EventSource):
    config = configparser.ConfigParser()
    DBusGMainLoop(set_as_default=True)
    bus = dbus.SessionBus()

    _event_names = ["config-changed"]

    def __init__(self):
        EventSource.__init__(self, self._event_names)
        self.bus.add_signal_receiver(self._handle_settings_changed, "ConfigChanged", "org.kde.kconfig.notify", None, "/kdesteam")

    def autoshow_enabled(self):
        try:
            config_location = XDGDirs.find_config_file("kdesteam")
            config = configparser.ConfigParser()
            config.read(config_location)
            return config["Keyboard"].getboolean("showAutomatically", False)
        except:
            return False

    def _handle_settings_changed(self, args):
        read_settings()
        self.emit("config-changed")
