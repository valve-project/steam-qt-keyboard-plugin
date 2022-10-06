# -*- coding: utf-8 -*-

# Copyright © 2012-2015 marmuta <marmvta@gmail.com>
# Copyright 2022 David Edmundson <daviddmundson@kde.org>

# This file is mostly copied from Onboard.
#
# Onboard is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# Onboard is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.


from __future__ import division, print_function, unicode_literals

from steamdeckkeyboardlauncher.AtspiStateTracker import AtspiStateTracker
from steamdeckkeyboardlauncher.Timer import TimerOnce
from steamdeckkeyboardlauncher.Config import Config

### Logging ###
import logging

import os
import subprocess
###############

class AutoShow(object):
    """
    Auto-show and hide Onboard.
    """

    # Delay from the last focus event until the keyboard is shown/hidden.
    # Raise it to reduce unnecessary transitions (flickering).
    # Lower it for more immediate reactions.
    SHOW_REACTION_TIME = 0.0
    HIDE_REACTION_TIME = 0.3

    _lock_visible = False
    _frozen = False
    _paused = False
    _state_tracker = AtspiStateTracker()
    _autoshow_enabled = True
    _config = Config()
    _steampath = "/home/deck/.local/share/Steam/ubuntu12_32/steam"

    def __init__(self):
        self._auto_show_timer = TimerOnce()
        self._pause_timer = TimerOnce()
        self._thaw_timer = TimerOnce()
        self._active_accessible = None
        self.enable(self._config.autoshow_enabled())
        self._config.connect("config-changed",
                             self._on_config_changed)

        # add a safe fallback
        if not os.path.isfile(self._steampath):
            self._steampath = "steam"

    def reset(self):
        self._auto_show_timer.stop()
        self._pause_timer.stop()
        self._thaw_timer.stop()
        self._frozen = False
        self._paused = False

    def cleanup(self):
        self.reset()
        self.enable(False)  # disconnect atspi events

    def enable(self, enable):
        print("Enabling:", enable)
        if enable:
            self._state_tracker.connect("text-entry-activated",
                                        self._on_text_entry_activated)
            self._state_tracker.connect("text-caret-moved",
                                        self._on_text_caret_moved)
        else:
            self._state_tracker.disconnect("text-entry-activated",
                                        self._on_text_entry_activated)
            self._state_tracker.disconnect("text-caret-moved",
                                        self._on_text_caret_moved)

        if enable:
            self._lock_visible = False
            self._frozen = False

    def is_paused(self):
        return self._paused

    def pause(self, duration = None):
        """
        Stop showing and hiding the keyboard window for longer time periods,
        e.g. after pressing a key on a physical keyboard.

        duration in seconds, None to pause forever.
        """
        self._paused = True
        self._pause_timer.stop()
        if not duration is None:
            self._pause_timer.start(duration, self.resume)

        # Discard pending hide/show actions.
        self._auto_show_timer.stop()

    def resume(self):
        """
        Allow hiding and showing the keyboard window again.
        """
        self._pause_timer.stop()
        self._paused = False

    def is_frozen(self):
        return self._frozen

    def freeze(self, thaw_time = None):
        """
        Disable showing and hiding the keyboard window for short periods,
        e.g. to skip unexpected focus events.
        thaw_time in seconds, None to freeze forever.
        """
        self._frozen = True
        self._thaw_timer.stop()
        if not thaw_time is None:
            self._thaw_timer.start(thaw_time, self._on_thaw)

        # Discard pending hide/show actions.
        self._auto_show_timer.stop()

    def thaw(self, thaw_time = None):
        """
        Allow hiding and showing the keyboard window again.
        thaw_time in seconds, None to thaw immediately.
        """
        self._thaw_timer.stop()
        if thaw_time is None:
            self._on_thaw()
        else:
            self._thaw_timer.start(thaw_time, self._on_thaw)

    def _on_thaw(self):
        self._thaw_timer.stop()
        self._frozen = False
        return False

    def lock_visible(self, lock, thaw_time = 1.0):
        """
        Lock window permanetly visible in response to the user showing it.
        Optionally freeze hiding/showing for a limited time.
        """
        # Permanently lock visible.
        self._lock_visible = lock

        # Temporarily stop showing/hiding.
        if thaw_time:
            self.freeze(thaw_time)

        # Leave the window in its current state,
        # discard pending hide/show actions.
        self._auto_show_timer.stop()

    def _on_text_caret_moved(self, event):
        """
        Show the keyboard on click of an already focused text entry
        (LP: 1078602). Do this only for single line text entries to
        still allow clicking longer documents without having onboard show up.
        """
        if self._autoshow_enabled:
           # and not self._keyboard.is_visible():

            accessible = self._active_accessible
            if accessible:
                if self._state_tracker.is_single_line():
                    self._on_text_entry_activated(accessible)

    def _on_text_entry_activated(self, accessible):
        self._active_accessible = accessible
        active = bool(accessible)

        # show/hide the keyboard window
        if not active is None:
            # Always allow to show the window even when locked.
            # Mitigates right click on unity-2d launcher hiding
            # onboard before _lock_visible is set (Precise).
            if self._lock_visible:
                active = True

            if not self.is_paused() and \
               not self.is_frozen():
                self.show_keyboard(active)

    def _on_config_changed(self):
        self.enable(self._config.autoshow_enabled())

    def show_keyboard(self, show):
        """ Begin AUTO_SHOW or AUTO_HIDE transition """
        # Don't act on each and every focus message. Delay the start
        # of the transition slightly so that only the last of a bunch of
        # focus messages is acted on.
        delay = self.SHOW_REACTION_TIME if show else \
                self.HIDE_REACTION_TIME
        self._auto_show_timer.start(delay, self._begin_transition, show)

    def _begin_transition(self, show):
        print("Show", show)
        final_url = ""
        if (show):
            final_url = "steam://open/keyboard"
        else :
            final_url = "steam://close/keyboard"
        subprocess.run([self._steampath, "-ifrunning", final_url])


