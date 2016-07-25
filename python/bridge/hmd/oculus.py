"""
Oculus
======

Oculus (oculus.com) head mounted display for OSX and Linux
It uses a python wrapper to connect with the SDK

It supports the Oculus SDK 1.5
"""

from .backend import HMD as baseHMD
from .backend import Backend


class HMD(baseHMD):
    _backend = Backend.OCULUS

