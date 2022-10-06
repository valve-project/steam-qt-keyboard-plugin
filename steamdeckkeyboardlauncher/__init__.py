#!/bin/env python3

from gi.repository import GLib
import signal
import logging

from steamdeckkeyboardlauncher import AutoShow
from steamdeckkeyboardlauncher import Config

loop = GLib.MainLoop()

def sigint_handler(sig, frame):
    if sig == signal.SIGINT:
        loop.quit()

def main():
    logging.basicConfig(level=logging.DEBUG)
    autoshow = AutoShow.AutoShow()
    signal.signal(signal.SIGINT, sigint_handler)
    loop.run()

if __name__ == "__main__":
    main()
