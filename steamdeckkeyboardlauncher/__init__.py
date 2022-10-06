#!/bin/env python3

from gi.repository import GLib

import logging
from steamdeckkeyboardlauncher import AutoShow
from steamdeckkeyboardlauncher import Config

def main():
    logging.basicConfig(level=logging.DEBUG)
    autoshow = AutoShow.AutoShow()

    loop = GLib.MainLoop()
    loop.run()

if __name__ == "__main__":
    main()
