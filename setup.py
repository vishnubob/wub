#!/usr/bin/env python

from setuptools import setup, Extension
import setuptools.command.install

wub_ext = Extension("_wub",
    sources = [
        "src/wub.i",
        "src/tempo.cpp",
        "src/audio_source.cpp",
        "src/alsa_audio_source.cpp",
        "src/wub.cpp",
    ],
    swig_opts=["-threads", "-c++", "-Wall"],
    libraries = ["asound", "aubio"],
)

setup_config = {
    "name":"wub", 
    "version":"0.1",
    "description":"Python audio analysis toolkit",
    "author":"Giles Hall",
    "author_email":"giles@polymerase.org",
    "package_dir":{"wub": "src"},
    "py_modules":["wub"],
    "ext_modules":[wub_ext],
}

# this kludge ensures we run the build_ext first before anything else
# otherwise, we will be missing generated files during the copy
"""
class Install_Command_build_ext_first(setuptools.command.install.install):
    def run(self):
        self.run_command("build_ext")
        return setuptools.command.install.install.run(self)
"""

if __name__ == "__main__":
    setup(**setup_config)
