"""
OpenVR
======

OpenVR Compatible head mounted display
It uses a python wrapper to connect with the SDK

"""

from . import HMD as baseHMD

import glew32 as glew
import openvr_api as openvr
import bridge_wrapper as bridge

import ctypes

from ctypes import (
        c_float,
        )

class HMD(baseHMD):

    def init_ctypes(self):
        """  I spent a day getting access violations.. I don't know how dalai's just seems to work but this one doesn't work without explicity setting the return types... baffled.
        """
        bridge.HMD_new.restype = ctypes.POINTER(ctypes.c_long)
        bridge.HMD_getStatus.restype = ctypes.c_char_p
        bridge.HMD_getStateBool.restype = ctypes.c_bool

    def __init__(self):
        super(HMD, self).__init__()
        self.init_ctypes()
        self._device = bridge.HMD_new(4)

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

    @property
    def height_right(self):
        return bridge.HMD_heightRight(self._device)

    def get_status(self):
        ret = bridge.HMD_getStatus(self._device)
        return str(ret, 'utf8')

    def get_state_bool(self):
        return bridge.HMD_getStateBool(self._device)




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
