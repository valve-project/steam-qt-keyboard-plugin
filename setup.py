import os

from setuptools import setup

setup(name="steamdeckkeyboardlauncher",
      version="0.0.1",
      author="David Edmundson",
      author_email="david@davidedmundson.org",
      description="some stuff",
      licensen="GPLv3",
      packages=["steamdeckkeyboardlauncher"],
      entry_points={"console_scripts": ["steamdeckkeyboardlauncher = steamdeckkeyboardlauncher:main"]},
)
