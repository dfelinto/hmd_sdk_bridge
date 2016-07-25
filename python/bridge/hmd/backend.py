"""
Backend
=======

Generic backend for HMD
It uses a python wrapper to connect with the SDK
"""

from . import HMD as baseHMD

import bridge_wrapper as bridge

from ctypes import (
        c_float,
        c_long,
        POINTER,
        )


class Backend:
    OCULUS = 0
    OCULUS_LEGACY = 1
    VIVE = 2
    OSVR = 3
    OPENVR = 4
    OPENHMD = 5


class HMD(baseHMD):
    _backend = None

    def __init__(self):
        super(HMD, self).__init__()
        self.init_ctypes()

        if self._backend is None:
            assert False, "Backend not fully implemented"

        self._device = bridge.HMD_new(self._backend)

    def __del__(self):
        bridge.HMD_del(self._device)

    @property
    def width_left(self):
        return bridge.HMD_widthLeft(self._device)

    @property
    def width_right(self):
        return bridge.HMD_widthRight(self._device)

    @property
    def height_left(self):
        return bridge.HMD_heightLeft(self._device)

    @property
    def height_right(self):
        return bridge.HMD_heightRight(self._device)

    def _getProjectionMatrix(self, near, far, bridge_func):
        arr = (c_float * 16)(*range(16))
        bridge_func(self._device, c_float(near), c_float(far), arr)
        return [i for i in arr]

    def _updateProjectionMatrix(self, near, far):
        self.projection_matrix_left = self._getProjectionMatrix(
                near, far, bridge.HMD_projectionMatrixLeft)

        self.projection_matrix_right = self._getProjectionMatrix(
                near, far, bridge.HMD_projectionMatrixRight)

    def setup(self, color_texture_left, color_texture_right):
        """
        Initialize device

        :param color_texture_left: color texture created externally with the framebuffer object data
        :type color_texture_left: GLuint
        :param color_texture_right: color texture created externally with the framebuffer object data
        :type color_texture_right: GLuint
        :return: return True if the device was properly initialized
        :rtype: bool
        """
        return bridge.HMD_setup(self._device, color_texture_left, color_texture_right)

    def update(self):
        """
        Get fresh tracking data

        :return: return left orientation, left_position, right_orientation, right_position
        :rtype: tuple(list(4), list(3), list(4), list(3))
        """

        orientation_ptr = [None, None]
        position_ptr = [None, None]

        orientation_ptr[0] = (c_float * 4)(*range(4))
        orientation_ptr[1] = (c_float * 4)(*range(4))

        position_ptr[0] = (c_float * 3)(*range(3))
        position_ptr[1] = (c_float * 3)(*range(3))

        if bridge.HMD_update(self._device, orientation_ptr[0], position_ptr[0], orientation_ptr[1], position_ptr[1]):
            self._orientation[0] = list(orientation_ptr[0])
            self._orientation[1] = list(orientation_ptr[1])
            self._position[0] = list(position_ptr[0])
            self._position[1] = list(position_ptr[1])

        return super(HMD, self).update()

    def frameReady(self):
        """
        The frame is ready to be send to the device

        :return: return True if success
        :rtype: bool
        """
        return bridge.HMD_frameReady(self._device)

    def reCenter(self):
        """
        Re-center the HMD device

        :return: return True if success
        :rtype: bool
        """
        return bridge.HMD_reCenter(self._device)

    @staticmethod
    def init_ctypes():
        """
        for the 64 bit platform the return types need to be
        explicitly defines
        """
        bridge.HMD_new.restype = POINTER(c_long)
