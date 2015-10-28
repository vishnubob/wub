#!/usr/bin/env python

import re
import subprocess
from setuptools import setup, Extension
from distutils.spawn import find_executable
from distutils.version import LooseVersion
import setuptools.command.install
import setuptools.command.build_ext


# this kludge ensures we run the build_ext first before anything else
# otherwise, we will be missing generated files during the copy
class Install_Command_build_ext_first(setuptools.command.install.install):
    def run(self):
        self.run_command("build_ext")
        return setuptools.command.install.install.run(self)

class Build_Ext_find_swig3(setuptools.command.build_ext.build_ext):
    def find_swig(self):
        return get_swig_executable()

def get_swig_executable():
    # stolen from https://github.com/FEniCS/ffc/blob/master/setup.py
    "Get SWIG executable"

    # Find SWIG executable
    swig_executable = None
    swig_minimum_version = "3.0.2"
    for executable in ["swig", "swig3.0"]:
        swig_executable = find_executable(executable)
        if swig_executable is not None:
            # Check that SWIG version is ok
            output = subprocess.check_output([swig_executable, "-version"]).decode('utf-8')
            swig_version = re.findall(r"SWIG Version ([0-9.]+)", output)[0]
            if LooseVersion(swig_version) >= LooseVersion(swig_minimum_version):
                break
            swig_executable = None
    if swig_executable is None:
        raise OSError("Unable to find SWIG version %s or higher." % swig_minimum_version)
    print("Found SWIG: %s (version %s)" % (swig_executable, swig_version))
    return swig_executable

wub_ext = Extension("_wub",
    sources = [
        "src/audio_source.cpp",
        "src/aubio_module.cpp",
        "src/alsa_audio_source.cpp",
        "src/tempo.cpp",
        "src/fft.cpp",
        "src/onset.cpp",
        "src/pitch.cpp",
        "src/wub.i",
    ],
    language = "c++",
    swig_opts=["-threads", "-c++", "-Wall"],
    libraries = ["asound", "aubio"],
    extra_compile_args=['-std=c++11'],
    # XXX: ugh
    #extra_link_args=["-zmuldefs"],
)

setup_config = {
    "name":"wub", 
    "version":"0.1",
    "description":"Python audio analysis toolkit",
    "author":"Giles Hall",
    "author_email":"giles@polymerase.org",
    "ext_modules":[wub_ext],
    "py_modules": ["wub"],
    "package_dir": {"": "src"},
    "cmdclass": {
        "install": Install_Command_build_ext_first,
        "build_ext": Build_Ext_find_swig3,
    },
}

if __name__ == "__main__":
    setup(**setup_config)
