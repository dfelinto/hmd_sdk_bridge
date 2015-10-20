"""
Oculus
======

Oculus (oculus.com) head mounted display for OSX and Linux
It uses a python wrapper to connect with the SDK

It supports the Oculus SDK 0.7
"""

from . import HMD as baseHMD

import bridge_wrapper as bridge

from ctypes import (
        c_float,
        )

class HMD(baseHMD):
    def __init__(self):
        super(HMD, self).__init__()
        self._device = bridge.Oculus_new()

    def __del__(self):
        bridge.Oculus_del(self._device)

    @property
    def width_left(self):
        return bridge.Oculus_widthLeft(self._device)

    @property
    def width_right(self):
        return bridge.Oculus_widthRight(self._device)

    @property
    def height_left(self):
        return bridge.Oculus_heightLeft(self._device)

    @property
    def height_right(self):
        return bridge.Oculus_heightRight(self._device)

    def _getProjectionMatrix(self, near, far, bridge_func):
        arr = (c_float * 16)(*range(16))
        bridge_func(self._device, c_float(near), c_float(far), arr)
        return [i for i in arr]

    def _updateProjectionMatrix(self, near, far):
        self.projection_matrix_left = self._getProjectionMatrix(
                near, far, bridge.Oculus_projectionMatrixLeft)

        self.projection_matrix_right = self._getProjectionMatrix(
                near, far, bridge.Oculus_projectionMatrixRight)

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
        return bridge.Oculus_setup(self._device, color_texture_left, color_texture_right)

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

        if bridge.Oculus_update(self._device, orientation_ptr[0], position_ptr[0], orientation_ptr[1], position_ptr[1]):
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
        return bridge.Oculus_frameReady(self._device)

    def reCenter(self):
        """
        Re-center the HMD device

        :return: return True if success
        :rtype: bool
        """
        return bridge.Oculus_reCenter(self._device)
