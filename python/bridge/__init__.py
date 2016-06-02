"""
Bridge
======
"""
import struct
import os
import sys

from .dylibs import load_library

def load(name, win_lib=None, linux_lib=None, osx_lib=None):

    if 64 == 8 * struct.calcsize("P"):
        path = "x64"
    else:
        path = "x86"

    if "linux" in sys.platform:
        if not linux_lib:
            return
        _file = linux_lib

    elif "darwin" in sys.platform:
        if not osx_lib:
            return
        _file = osx_lib

    else:
        if not win_lib:
            return
        _file = win_lib

    libfile = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "lib", path, _file)
    print("Using Library: {0}".format(libfile))

    if os.path.isfile(libfile):
        lib = load_library(libfile)

        # make it accessible for this package files
        sys.modules[name] = lib
    else:
        print("lib \"{0}\" not found".format(libfile))


load('bridge_wrapper', win_lib='BridgeLib.dll')
load('oculus_legacy_base', win_lib='OculusVR.dll', linux_lib='libOculusVR.so', osx_lib='libOculusVR.dylib')
