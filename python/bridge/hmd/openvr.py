"""
Vive
======

HTC Vive (vive.com) head mounted display for Windows
"""

from .backend import HMD as baseHMD
from .backend import Backend


class HMD(baseHMD):
    _backend = Backend.OPENVR

