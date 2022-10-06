import os

from setuptools import setup

setup(name="steamdeckkeyboardlauncher",
      version="0.0.1",
      author="David Edmundson",
      author_email="david@davidedmundson.org",
      description="Launch steam keyboard on demand based on hints from the accessibility bus",
      licensen="GPLv3",
      packages=["steamdeckkeyboardlauncher"],
      entry_points={"console_scripts": ["steamdeckkeyboardlauncher = steamdeckkeyboardlauncher:main"]},
)
