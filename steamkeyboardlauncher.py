#!/bin/env python3

import gi
from gi.repository import GLib

import logging
import AutoShow

def main():
    logging.basicConfig(level=logging.DEBUG)
    autoshow = AutoShow.AutoShow()
    autoshow.enable(True)
    loop = GLib.MainLoop()
    loop.run()

if __name__ == "__main__":
    main()
